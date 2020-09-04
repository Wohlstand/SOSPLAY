/*
 * MID2CMF v1.1a - convert a type-0 MIDI file into a CMF file
 *
 * Copyright (C) 2010 Adam Nielsen <malvineous@shikadi.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Bugs/limitations in this version:
 *
 *  - Percussion is not converted.  This can be worked around by placing
 *    each percussion instrument on its own channel before conversion.
 *
 *  - GM patches don't seem to sound right, more testing required, but
 *    most people probably won't keep the default patches anyway.
 *
 *  - Rhythm mode is unused so polyphony is limited to nine notes (on
 *    OPL2 at least) rather than 11.
 *
 * To compile:
 *
 *  g++ -o mid2cmf mid2cmf.cpp
 *
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdint.h>

// Default GM assignments (taken from Creative's PLAY.EXE/CTMIDI.DRV)
static char gmInst[128][11];
static char gmNoteOffsets[128];

const  char *gmInstDefault[] = {
	"\x00\x00\x4F\x00\xF1\xD2\x51\x43\x00\x00\x06",
	"\x02\x12\x4F\x00\xF1\xD2\x51\x43\x00\x00\x02",
	"\x00\x11\x4A\x00\xF1\xD2\x53\x74\x00\x00\x06",
	"\x03\x11\x4F\x00\xF1\xD2\x53\x74\x01\x01\x06",
	"\x01\x11\x66\x00\xF1\xD2\x51\xC3\x00\x00\x06",
	"\xC0\xD2\x52\x00\xF1\xD2\x53\x94\x00\x00\x06",
	"\x12\x18\x86\x00\xF3\xFC\x00\x33\x00\x00\x08",
	"\xD0\x12\x4E\x00\xA8\x92\x32\xA7\x03\x02\x00",
	"\xC8\xD1\x4F\x00\xF2\xF3\x64\x77\x00\x00\x08",
	"\x33\x34\x0E\x00\x01\x7D\x11\x34\x00\x00\x08",
	"\x17\x16\x50\x00\xD1\xD3\x52\x92\x00\x01\x04",
	"\xE7\xE1\x21\x00\xF5\xF6\x77\x14\x00\x00\x08",
	"\x95\x81\x4E\x00\xDA\xF9\x25\x15\x00\x00\x0A",
	"\x27\x21\x1F\x00\xF5\xF5\x96\x57\x00\x00\x08",
	"\x87\xF1\x4E\x80\xB1\xE6\x33\x42\x00\x00\x00",
	"\x31\x11\x87\x80\xA1\x7D\x11\x43\x00\x00\x08",
	"\x32\xB1\x8C\x00\x91\xA1\x07\x19\x02\x00\x05",
	"\x31\xB4\x54\x80\xF1\xF5\x07\x19\x00\x00\x07",
	"\x24\x21\x40\x49\xFF\xFF\x0F\x0F\x00\x00\x01",
	"\xD2\xF1\x44\x80\x91\xA1\x57\x09\x01\x01\x03",
	"\x01\x02\x52\x80\xF0\xF0\x1F\x1F\x01\x00\x0A",
	"\x21\x32\x4F\x01\xF2\x52\x0B\x0B\x00\x01\x0A",
	"\xF0\xF2\x93\x00\xD8\xB3\x0B\x0B\x02\x01\x0A",
	"\x20\x31\x5D\x00\xF2\x52\x0B\x0B\x03\x02\x00",
	"\x01\x01\x1B\x00\xF4\xF3\x25\x46\x02\x00\x00",
	"\x11\x01\x0F\x00\xF4\xF3\x25\x46\x01\x00\x00",
	"\x01\x01\x27\x00\xF1\xF4\x1F\x88\x02\x00\x0A",
	"\x12\x13\x44\x00\xEA\xD2\x32\xE7\x01\x01\x00",
	"\x30\x31\x45\x00\xA4\xF5\x32\xE7\x03\x00\x00",
	"\x21\x21\x0F\x00\xF5\xF1\x17\x78\x02\x01\x04",
	"\x01\x20\x41\x00\xD1\xC1\x34\xA5\x03\x03\x04",
	"\x10\x12\x43\x00\xA7\xE3\x97\xE7\x03\x02\x00",
	"\x20\x21\x28\x00\xC5\xD2\x15\xA4\x00\x00\x0C",
	"\x30\x21\x16\x00\xF2\xF3\x9F\x78\x00\x00\x0C",
	"\x30\x21\x11\x00\x82\xF3\x9F\x78\x00\x00\x0A",
	"\x21\x21\x23\x00\x73\x93\x1A\x87\x00\x00\x0C",
	"\x30\x21\x0E\x00\x62\xF3\x55\x68\x02\x00\x0A",
	"\x30\x22\x0C\x00\x62\xD5\xB5\x98\x01\x00\x08",
	"\x70\x72\x93\x40\x64\xA1\x43\x43\x00\x00\x0A",
	"\x30\x32\x8D\x80\x44\x92\x43\x43\x02\x00\x0A",
	"\xE1\xE2\x4E\x00\x65\x61\x43\x44\x02\x02\x00",
	"\xA1\xA2\x8E\x00\x65\x63\x43\x45\x02\x02\x00",
	"\xB0\x61\x87\x40\xD1\x62\x11\x15\x02\x01\x06",
	"\xF0\x20\x8A\x80\xB1\xA0\x11\x15\x02\x01\x06",
	"\xF1\xE2\x89\x40\x73\x43\x01\x05\x02\x00\x06",
	"\x31\x21\x57\x80\xF8\xF7\xF9\xE6\x03\x02\x0E",
	"\x32\x01\x24\x80\xF1\xF5\x35\x35\x00\x00\x00",
	"\x00\x00\x04\x00\xAA\xD2\xC8\xB3\x00\x00\x0A",
	"\xE0\xF1\x4F\x00\xD4\x55\x0B\x0B\x02\x02\x0A",
	"\xE0\xF0\x52\x00\x96\x35\x05\x01\x02\x02\x0A",
	"\xE1\xF1\x4F\x00\x36\x45\x05\x02\x02\x02\x0A",
	"\xE2\xE1\x48\x80\x21\x41\x43\x45\x02\x01\x00",
	"\xE0\xF1\x16\x00\x41\x20\x52\x72\x02\x02\x00",
	"\xE0\xF1\x11\x00\x01\xD0\x52\x72\x02\x02\x00",
	"\xE0\xF1\x1A\x00\x61\x30\x52\x73\x00\x02\x00",
	"\x50\x50\x0B\x00\x84\xA4\x4B\x99\x00\x00\x0A",
	"\x31\x61\x1C\x80\x41\x92\x0B\x3B\x00\x00\x0E",
	"\xB1\x61\x1C\x00\x41\x92\x1F\x3B\x00\x00\x0E",
	"\x20\x21\x18\x00\x52\xA2\x15\x24\x00\x00\x0C",
	"\xC1\xC1\x94\x80\x74\xA3\xEA\xF5\x02\x01\x0E",
	"\x21\x21\x28\x00\x41\x81\xB4\x98\x00\x00\x0E",
	"\x21\x21\x1D\x00\x51\xE1\xAE\x3E\x02\x01\x0E",
	"\xE0\xE0\x93\x80\x51\x81\xA6\x97\x02\x01\x0E",
	"\xE0\xE1\x93\x80\x51\xE1\xA6\x97\x02\x01\x0E",
	"\xE0\xF2\x4B\x01\xD8\xB3\x0B\x0B\x02\x01\x08",
	"\xE0\xF1\x49\x01\xB8\xB3\x0B\x0B\x02\x01\x08",
	"\xE0\xF0\x4E\x01\x98\xC3\x0B\x0B\x01\x02\x08",
	"\xE0\xF1\x4C\x01\x88\xD3\x0B\x0B\x01\x01\x08",
	"\xF1\xE4\xC5\x00\x7E\x8C\x17\x0E\x00\x00\x08",
	"\x60\x72\x4F\x00\xD8\xB3\x0B\x0B\x00\x01\x0A",
	"\x31\x72\xD1\x80\xD5\x91\x19\x1B\x00\x00\x0C",
	"\x32\x71\xC8\x80\xD5\x73\x19\x1B\x00\x00\x0C",
	"\xE2\x62\x6A\x00\x9E\x55\x8F\x2A\x00\x00\x0E",
	"\xE0\x61\xEC\x00\x7E\x65\x8F\x2A\x00\x00\x0E",
	"\x62\xA2\x88\x83\x84\x75\x27\x17\x00\x00\x09",
	"\x62\xA2\x84\x83\x84\x75\x27\x17\x00\x00\x09",
	"\xE3\x62\x6D\x00\x57\x57\x04\x77\x00\x00\x0E",
	"\xF1\xE1\x28\x00\x57\x67\x34\x5D\x03\x00\x0E",
	"\xD1\x72\xC7\x00\x31\x42\x0F\x09\x00\x00\x0B",
	"\xF2\x72\xC7\x00\x51\x42\x05\x69\x00\x00\x0B",
	"\x23\x31\x4F\x00\x51\x60\x5B\x25\x01\x01\x00",
	"\x22\x31\x48\x00\x31\xC0\x9B\x65\x02\x01\x00",
	"\xF1\xE1\x28\x00\x57\x67\x34\x0D\x03\x00\x0E",
	"\xE1\xE1\x23\x00\x57\x67\x04\x4D\x03\x00\x0E",
	"\xE2\x31\x42\x08\x78\xF3\x0B\x0B\x01\x01\x08",
	"\xE2\xE2\x21\x00\x11\x40\x52\x73\x01\x01\x08",
	"\x23\xA4\xC0\x00\x51\x35\x07\x79\x01\x02\x0D",
	"\x24\xA0\xC0\x00\x51\x75\x07\x09\x01\x02\x09",
	"\xE0\xF0\x16\x00\xB1\xE0\x51\x75\x02\x02\x00",
	"\x03\xA4\xC0\x00\x52\xF4\x03\x55\x00\x00\x09",
	"\xE1\xE1\x93\x80\x31\xA1\xA6\x97\x01\x01\x0A",
	"\xF0\x71\xC4\x80\x10\x11\x01\xC1\x02\x02\x01",
	"\xC1\xE0\x4F\x00\xB1\x12\x53\x74\x02\x02\x06",
	"\xC0\x41\x6D\x00\xF9\xF2\x21\xB3\x01\x00\x0E",
	"\xE3\xE2\x4C\x00\x21\xA1\x43\x45\x01\x01\x00",
	"\xE3\xE2\x0C\x00\x11\x80\x52\x73\x01\x01\x08",
	"\x26\x88\xC0\x00\x55\xF8\x47\x19\x00\x00\x0B",
	"\x23\xE4\xD4\x00\xE5\x35\x03\x65\x00\x00\x07",
	"\x27\x32\xC0\x00\x32\xA4\x62\x33\x00\x00\x00",
	"\xD0\x31\x4E\x00\x98\xA2\x32\x47\x01\x02\x00",
	"\xF0\x71\xC0\x00\x93\x43\x03\x02\x01\x00\x0F",
	"\xE0\xF1\x1A\x80\x13\x33\x52\x13\x01\x02\x00",
	"\xE0\xF1\x1A\x00\x45\x32\xBA\x91\x00\x02\x00",
	"\x11\x15\x18\x03\x58\xA2\x02\x72\x01\x00\x0A",
	"\x10\x18\x80\x40\xF1\xF1\x53\x53\x00\x00\x00",
	"\x31\x17\x86\x80\xA1\x7D\x11\x23\x00\x00\x08",
	"\x10\x18\x80\x40\xF1\xF6\x53\x54\x00\x00\x00",
	"\x31\x34\x21\x00\xF5\x93\x56\xE8\x01\x00\x08",
	"\x03\x15\x4F\x00\xF1\xD6\x39\x74\x03\x00\x06",
	"\x31\x22\x43\x00\x6E\x8B\x17\x0C\x01\x02\x02",
	"\x31\x22\x1C\x80\x61\x52\x03\x67\x00\x00\x0E",
	"\x60\xF0\x0C\x80\x81\x61\x03\x0C\x00\x01\x08",
	"\x27\x05\x55\x00\x31\xA7\x62\x75\x00\x00\x00",
	"\x95\x16\x81\x00\xE7\x96\x01\x67\x00\x00\x04",
	"\x0C\x01\x87\x80\xF0\xF2\x05\x05\x01\x01\x04",
	"\x35\x11\x44\x00\xF8\xF5\xFF\x75\x00\x00\x0E",
	"\x10\x10\x0B\x00\xA7\xD5\xEC\xF5\x00\x00\x00",
	"\x20\x01\x0B\x00\xA8\xD6\xC8\xB7\x00\x00\x00",
	"\x00\x01\x0B\x00\x88\xD5\xC4\xB7\x00\x00\x00",
	"\x0C\x10\x8F\x80\x41\x33\x31\x2B\x00\x03\x08",
	"\x17\xF7\x00\x00\x3B\xEA\xDF\x97\x03\x00\x0B",
	"\x12\x18\x06\x00\x73\x3C\x02\x74\x00\x00\x0E",
	"\x02\x08\x00\x00\x3E\x14\x01\xF3\x02\x02\x0E",
	"\xF5\xF6\xD4\x00\xEB\x45\x03\x68\x00\x00\x07",
	"\xF0\xCA\x00\xC0\xDA\xB0\x71\x17\x01\x01\x08",
	"\xF0\xE2\x00\xC0\x1E\x11\x11\x11\x01\x01\x08",
	"\xE7\xE8\x00\x04\x34\x10\x00\xB2\x02\x02\x0E",
	"\x0C\x04\x00\x00\xF0\xF6\xF0\xE6\x02\x00\x0E"
};

int dumpIbk(const char* ibkPath)
{
    std::vector<unsigned char> data;
    FILE *f = fopen(ibkPath, "rb");
    if(!f)
    {
        std::cout << "ERROR: Can't open IBK file" << std::endl;
        return -1;
    }
    fseek(f, 0, SEEK_END);
    data.resize(size_t(ftell(f)));
    rewind(f);

    if(fread(&data[0], 1, data.size(), f) != data.size())
    {
        std::cout << "ERROR: bad IBK file" << std::endl;
        fclose(f);
        return -1;
    }
    fclose(f);
    unsigned offs1_base = 0x804, offs1_len = 9;
    unsigned offs2_base = 0x004, offs2_len = 16;

    for(unsigned a = 0; a < 128; ++a)
    {
        unsigned offset1 = offs1_base + a * offs1_len;
        unsigned offset2 = offs2_base + a * offs2_len;
        if(data.size() <= offset2 + 0)
        {
            std::cout << "ERROR: bad IBK file: unexpected ending!" << std::endl;
            return -1;
        }
        memcpy(gmInst[a], &data[offset2 + 0], 11);
        gmNoteOffsets[a] = static_cast<char>(data[offset2 + 12]);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    const char *musIn = NULL;
    const char *musOut = NULL;
    const char *musIbk = NULL;
	std::cout << "MID2CMF v1.1a - a quick and dirty MIDI to CMF converter\n"
		         "Copyright 2010 Adam Nielsen <malvineous@shikadi.net>\n"
		      << std::endl;

	if (argc < 3) {
		std::cout << "Usage: mid2cmf in.mid out.cmf" << std::endl
		          << "       mid2cmf bank.ibk in.mid out.cmf" << std::endl;
		return 1;
	}

	musIn = argv[1];
	musOut = argv[2];

	if (argc == 4) {
	    musIbk = argv[1];
		musIn = argv[2];
    	musOut = argv[3];
	}

	std::ifstream in(musIn, std::ios::binary);
	std::ofstream out(musOut, std::ios::trunc | std::ios::binary);
    memset(gmNoteOffsets, 0, sizeof(gmNoteOffsets));
	if (musIbk) {
	    if(dumpIbk(musIbk) < 0)
    	    return 1;
    } else for(unsigned a = 0; a < 128; ++a) {
        memcpy(gmInst[a], gmInstDefault[a], 11);
    }


	// Make sure we've been given a MIDI file as input.  We should be
	// reading the length field to do it properly, but as all MIDI files
	// have the same value we'll just assume it's a normal file.
	uint8_t header[14];
	if (
		// Make sure we read in all the 14 byte header
		(in.rdbuf()->sgetn((char *)header, 14) != 14) ||
		// And if we did, that it starts with "MThd"
		(strncmp((char *)header, "MThd", 4) != 0)
	) {
		std::cerr << "ERROR: " << musIn << " is not a MIDI file!"
			<< std::endl;
		return 2;
	}

	// Make sure it's only got one track
	int type = (header[8] << 8) | header[9];
	if (type != 0) {
		std::cerr << "ERROR: This is a format-" << type
			<< " MIDI file, only format-0 is accepted."
			<< std::endl;
		return 2;
	}

	// Need this for the tempo calculations later
	int ticksPerQuarterNote = (header[12] << 8) | header[13];
	std::cout << "Song has " << ticksPerQuarterNote
		<< " ticks per quarter note." << std::endl;
	// Default tempo (can be overridden later)
	int ticksPerSecond = ticksPerQuarterNote * (1000000 / 500000);
	std::cout << "  @ default 500ms/quarter note => " << ticksPerSecond
		<< " ticks per second." << std::endl;

	bool ticksPerSecond_changed = false;

	// Read in the track header
	if (
		// Four bytes for signature and four for length
		(in.rdbuf()->sgetn((char *)header, 8) != 8) ||
		// Verify signature like before
		(strncmp((char *)header, "MTrk", 4) != 0)
	) {
		std::cerr << "ERROR: " << argv[1] << " did not have its "
			"track at the expected location!" << std::endl;
		return 2;
	}
	int trackLength =
		((uint8_t)header[4] << 24) |
		((uint8_t)header[5] << 16) |
		((uint8_t)header[6] << 8) |
		(uint8_t)header[7];

	// At this point we're sitting at the start of the MIDI track data,
	// and there are trackLength bytes of it.
	std::cout << "Track length is " << trackLength << " bytes." << std::endl;
	uint8_t *midi = new uint8_t[trackLength];
	if (in.rdbuf()->sgetn((char *)midi, trackLength) != trackLength) {
		std::cerr << "ERROR: Track data was cut off!" << std::endl;
		delete[] midi;
		return 2;
	}

	// Scan through the MIDI data and figure out which channels are being
	// used, how many instruments there are and renumber the instruments
	// starting at zero so that only patches for the instruments being
	// used need to be included in the CMF.
	int pos = 0;
	uint8_t patchesUsed[128]; // patchesUsed[GM patch num] = CMF inst num
	memset(patchesUsed, 255, sizeof(patchesUsed));
	uint8_t numInstruments = 0;
	uint8_t prevEvent = 0x80; // 0x80 should never be used, but just in case
	uint8_t channelInUse[16];
	uint8_t currentPatch[16];
	memset(channelInUse, 0, sizeof(channelInUse));
	memset(currentPatch, 0, sizeof(channelInUse));
	while (pos < trackLength) {
		// Skip over the delay byte
		while (midi[pos] & 0x80) pos++;
		pos++; // skip final delay byte

		// Process the next event
		uint8_t event = midi[pos];
		if (event & 0x80) {  // normal event
			pos++;
			// Remember the event for continuation, except if it's
			// a sysex, which can't be continued like this.
			if ((event & 0xF0) != 0xF0) {
				prevEvent = event;
				// Also note the channel is being used
				channelInUse[event & 0x0F] = 1;
			}
		} else { // continuation from last event
			event = prevEvent;
		}
		switch (event & 0xF0) {
			case 0x80: // note off
			case 0x90: // note on
			case 0xA0: // key pressure
			{
			    char noteOffset = gmNoteOffsets[currentPatch[event & 0x0F]];
			    midi[pos] += noteOffset;
                pos += 2;
    			break;
			}
			case 0xB0: pos += 2; break; // controller
			case 0xC0: { // instrument change
				int midiPatch = midi[pos];
			    currentPatch[event & 0x0F] = (uint8_t)midiPatch;
				if (patchesUsed[midiPatch] == 255) {
					// Grab another mapping
					std::cout << "Mapping GM patch " << midiPatch
						<< " (channel " << (midi[pos] & 0x0F) + 1
						<< ") to CMF instrument #" << (int)numInstruments
						<< std::endl;
					patchesUsed[midiPatch] = numInstruments++;
				}
				// Change the instrument to the CMF number
				midi[pos] = patchesUsed[midiPatch];
				pos++;
				break;
			}
			case 0xD0: pos += 1; break; // channel pressure
			case 0xE0: pos += 2; break; // pitch bend
			case 0xF0: { // sysex
				if (event == 0xFF) { // meta event
					if (midi[pos] == 0x51) { // set tempo
					    if(!ticksPerSecond_changed) {
						    long usPerQuarterNote = (midi[pos+1] << 16) | (midi[pos+2] << 8) | midi[pos+3];
						    double quarterNotesPerSecond = 1000000.0 / usPerQuarterNote;
						    ticksPerSecond = (double)ticksPerQuarterNote * quarterNotesPerSecond;
						    std::cout << "Tempo set to " << usPerQuarterNote
							    << "us/quarter-note => " << ticksPerSecond
							    << " ticks per second." << std::endl;
						    ticksPerSecond_changed = true;
						}
					}
					pos++; // skip 'type'
				}
				int len = 0;
				for (int i = 0; i < 4; i++) {
					len |= midi[pos] & 0x7F;
					if (midi[pos++] & 0x80) len <<= 7;
					else break;
				}
				if(event == 0xF0 || event == 0xF9) { // sysex
				std::cout << "Skipped sysex block of " << len
					<< " bytes" << std::endl;
				}
				pos += len;
				break;
			}
		}
		//pos++;
	}

	// Now we generate the CMF header, before writing out the MIDI data.
	int musicOffset = 40 + (numInstruments * 16);
	uint8_t cmfHeader[20] = {
		'C','T','M','F', // Signature
		1, 1,            // Version
		40, 0,           // Offset of instrument data
		musicOffset         & 0xFF, (musicOffset         >> 8) & 0xFF,
		ticksPerQuarterNote & 0xFF, (ticksPerQuarterNote >> 8) & 0xFF,
		ticksPerQuarterNote & 0xFF, (ticksPerQuarterNote >> 8) & 0xFF,//ticksPerSecond      & 0xFF, (ticksPerSecond      >> 8) & 0xFF,
		0, 0,            // Offset of song title string
		0, 0,            // Offset of composer string
		0, 0,            // Offset of remarks string
	};
	out.write((char *)cmfHeader, 20);

	// Then the channel in use table
	out.write((char *)channelInUse, 16);

	// Followed by the rest of the header
	uint8_t cmfHeader1v1[4] = {
		numInstruments & 0xFF, (numInstruments >> 8) & 0xFF,
		0, 1, // basic tempo (?)
	};
	out.write((char *)cmfHeader1v1, 4);

	// Write out the instrument patches
	for (int c = 0; c < numInstruments; c++) {
		for (int i = 0; i < 128; i++) {
			if (patchesUsed[i] == c) {
				out.write(gmInst[i], 11);
				out.write("\x00\x00\x00\x00\x00", 5); // padding
				break;
			}
		}
	}

	// And lastly the actual MIDI data
	out.write((char *)midi, trackLength);
	delete[] midi;

	// Print summary
	std::cout << "Wrote " << musOut << " successfully."
		<< std::endl;
	return 0;
}
