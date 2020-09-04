/*
 * SOSPLAY - A simple HMI MIDI player for DOS
 *
 * Copyright © 2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <conio.h>

#include "sos.h"
#include "sosm.h"

const char VERSION[] = "1.00";

static PSTR dumpFile(const char *szName, int extraSize)
{
    PSTR  pData;
    int  wSize;
    int  hFile;

    if((hFile = open(szName, O_RDONLY | O_BINARY)) == -1)
        return(_NULL);

    wSize =  lseek(hFile, 0, SEEK_END);
    lseek(hFile, 0, SEEK_SET);

    if((pData = (PSTR)malloc(wSize + extraSize)) == _NULL)
    {
        close(hFile);
        return(_NULL);
    }

    if(read(hFile, pData + extraSize, wSize) != wSize)
    {
        close(hFile);
        free(pData);
        return(_NULL);
    }

    close(hFile);
    return(pData);
}

static int endsWith(const char *str, const char *suffix)
{
    size_t lenstr;
    size_t lensuffix;

    if(!str || !suffix)
        return 0;

    lenstr = strlen(str);
    lensuffix = strlen(suffix);

    if(lensuffix >  lenstr)
        return 0;

    return stricmp(str + lenstr - lensuffix, suffix) == 0;
}

static W32 hmiBranchCallback( HANDLE hSong, BYTE bTrack, BYTE bID )
{
    // hSong	song handle
    // bTrack	track branch occured on
    // bID		ID value of branch
    (void)hSong;

    printf("Loop callback: Track %d, Branch %d\n", bTrack, bID);

    // return _TRUE to branch and _FALSE to continue
    // without branching.
    return TRUE;
}


int main(int argc, char **argv)
{
    char key;
    int keepWork = 1;

    _SOS_MIDI_DRIVER        sMIDIDriver;               // midi driver structure

    W32      err;

    _SOS_MIDI_SONG *sSong;
    W32      wMIDIDeviceID = _MIDI_OPL3;                            // midi device ID
    HANDLE   hMIDIDriver;                              // handle to MIDI driver
    HANDLE   hMIDISong;                                // handle to MIDI song
    PSTR     pSong;                                    // pointer to MIDI song
    PSTR     pMelodicPatch;                            // melodic FM instruments
    PSTR     pDrumPatch;                               // drum FM instruments

    const char *bankMelodic = "rickmelo.bnk";
    const char *bankDrum = "rickdrum.bnk";
    const char *songPath = "maz.hmi";

    printf("\nSOSPLAY version %s  Copyright (C) 2020 Vitaly Novichkov \"Wohlstand\"\n", VERSION);
    printf("-------------------------------------------------------------------------------\n\n");

    if(argc < 2)
    {
        printf("This program plays a HMI MIDI sequence through a \n");
        printf("Sound Operating System V4.0 sound driver.\n\n");
        printf("Usage: SOSPLAY HMI_filename [melodic.bnk] [drums.bnk]\n");
        exit(1);
    }


    songPath = argv[1];

    if(argc >= 3)
        bankMelodic = argv[2];

    if(argc >= 4)
        bankDrum = argv[3];

    if((err = sosTIMERInitSystem(_TIMER_DOS_RATE, _SOS_DEBUG_NORMAL)))
        if(err != _ERR_INITIALIZED)
            return 1;

    sosMIDIInitSystem(_NULL, _SOS_DEBUG_NORMAL);

    memset(&sMIDIDriver, 0, sizeof(_SOS_MIDI_DRIVER));

    sMIDIDriver.wID = wMIDIDeviceID;
    sMIDIDriver.sHardware.wPort = 0x388;

    if((err = sosMIDIInitDriver(&sMIDIDriver, &hMIDIDriver)) != _ERR_NO_ERROR)
    {
        // uninitialize system
        printf("Fail to initialize MIDI!!!!\n");

        switch(err)
        {
        case _ERR_NO_HANDLES:
            printf("No more driver handles were free\n");
            break;
        case _ERR_DRIVER_LOADED:
            printf("The driver was previously loaded\n");
            break;
        case _ERR_INVALID_DRIVER_ID:
            printf("An invalid driver ID was passed\n");
            break;
        case _ERR_MEMORY_FAIL:
            printf("The system was unable to allocate memory for the driver\n");
            break;
        case _ERR_FAIL_ON_FILE_OPEN:
            printf("The .DRV or .386 files were not located (1)\n");
            break;
        case _ERR_DRV_FILE_FAIL:
            printf("The .DRV or .386 files were not located (2)\n");
        default:
            printf("Another error: %d\n", err);
            break;
        }

        sosMIDIUnInitSystem();
        return 1;
    }

    // attempt to load melodic patch
    if((pMelodicPatch = dumpFile(bankMelodic, 0)) == _NULL)
    {
        printf("Failed to load melodic bank\n");
        sosMIDIUnInitSystem();
        return 1;
    }

    // attempt to load drum patch
    if((pDrumPatch = dumpFile(bankDrum, 0)) == _NULL)
    {
        printf("Failed to load drum bank\n");
        sosMIDIUnInitSystem();
        return 1;
    }

    // set instrument data
    if((sosMIDISetInsData(hMIDIDriver, (LPSTR)pMelodicPatch, 0)))
    {
        printf("Failed to set melodic bank %s\n", pMelodicPatch);
        sosMIDIUnInitSystem();
        return 1;
    }

    // set instrument data
    if((sosMIDISetInsData(hMIDIDriver, (LPSTR)pDrumPatch, 1)))
    {
        printf("Failed to set drum bank %s\n", pDrumPatch);
        sosMIDIUnInitSystem();
        return 1;
    }

    // attempt to load song file
    if((pSong = dumpFile(songPath, sizeof(_SOS_MIDI_SONG))) == _NULL)
    {
        printf("Failed to load song %s\n", songPath);
        sosMIDIUnInitSystem();
        return 1;
    }

    sSong  =  ( _SOS_MIDI_SONG * )pSong;

    memset(sSong, 0, sizeof(_SOS_MIDI_SONG));

    sSong->pSong =  (PSTR)( pSong + sizeof(_SOS_MIDI_SONG));

    // initialize song
    if(sosMIDIInitSong(sSong, &hMIDISong))
    {
        printf("Failed to init song\n");
        sosMIDIUnInitSystem();
        return 1;
    }

    sosMIDIRegisterBranchFunction(hMIDISong, hmiBranchCallback);

    sosMIDIStartSong(hMIDISong);

    printf("----------------------\n");
    printf("Song: %s\n", songPath);
    printf("Melodic bank: %s\n", bankMelodic);
    printf("Drum bank: %s\n", bankDrum);
    printf("----------------------\n");
    printf("Press ESC to stop the song.\n");
    printf("----------------------\n");
    printf("S - Pause song\n");
    printf("R - Resume paused song\n");
    printf("P - Play song at start\n");
    printf("----------------------\n");

    keepWork = 1;
    while(keepWork)
    {
        key = getch();
        switch(key)
        {
        case 'r':
        case 'R':
            sosMIDIResumeSong(hMIDISong);
            break;
        case 's':
        case 'S':
            sosMIDIPauseSong(hMIDISong, FALSE);
            break;
        case 'p':
        case 'P':
            sosMIDIStopSong(hMIDISong);
            sosMIDIStartSong(hMIDISong);
            break;
        case 27:
            keepWork = 0;
            break;
        }
    }

    sosMIDIStopSong(hMIDISong);

    free(pSong);
    free(pMelodicPatch);
    free(pDrumPatch);
    sosMIDIUnInitSystem();

    sosTIMERUnInitSystem(0);

    printf("Bye!\n");

    return 0;
}
