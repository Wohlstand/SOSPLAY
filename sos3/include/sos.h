/****************************************************************************

   File              : sos.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/

#ifndef  _SOS_DEFINED   
#define  _SOS_DEFINED   

//
// #include "sosdefs.h"
//
/****************************************************************************

   File              : sosdefs.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/


#ifndef  _SOSDEFS_DEFINED
#define  _SOSDEFS_DEFINED

#undef   _TRUE
#undef   _FALSE
#undef   _NULL
enum  
	  { 
		 _FALSE, 
		 _TRUE 
	  };

#define  _NULL  0

#ifndef  VOID
#define  VOID           void
#endif
typedef  int            BOOL;
typedef  unsigned int   UINT;
typedef  unsigned char  BYTE;
typedef  unsigned       WORD;
#ifndef  LONG
typedef  signed long    LONG;
#endif
typedef  unsigned long  DWORD;

typedef  BYTE  *        PBYTE;
typedef  char near *    PSTR;
typedef  WORD  *        PWORD;
typedef  LONG  *        PLONG;
typedef  VOID  *        PVOID;

typedef  BYTE  far   *  LPBYTE;
typedef  BYTE  far   *  LPSTR;
typedef  WORD  far   *  LPWORD;
typedef  LONG  far   *  LPLONG;
typedef  VOID  far   *  LPVOID;

typedef  BYTE  huge  *  HPBYTE;
typedef  BYTE  huge  *  HPSTR;
typedef  WORD  huge  *  HPWORD;
typedef  LONG  huge  *  HPLONG;
typedef  VOID  huge  *  HPVOID;

typedef  unsigned       HANDLE;

#endif



#pragma pack(4)
 
// error definition for sound operating system  
#define  _SOS_ERR          -1

// number of drivers allowed to be open at one time
#define  _SOS_MAX_DRIVERS  5

// structure definition for the capabilities
typedef struct _tagCAPABILITIES
{
   BYTE  szDeviceName[ 32 ];  // device name
   WORD  wDeviceVersion;      // device version
   WORD  wBitsPerSample;      // bits per sound sample
   WORD  wChannels;           // stereo/mono sound card
   WORD  wMinRate;            // minimum rate
   WORD  wMaxRate;            // maximum rate
   WORD  wMixerOnBoard;       // board contains mixer
   WORD  wMixerFlags;         // mixer capabilities
   WORD  wFlags;              // miscellaneous flags   
   short far * lpPortList;         // list of usable ports
   short far * lpDMAList;          // list of usable dma channels
   short far * lpIRQList;          // list of usable irq channels
   short far * lpRateList;         // list of usable rates, -1 if any in min to max
   WORD  fBackground;         // foreground or background driver
   WORD  wDeviceID;           // ID for the device
   WORD  wTimerID;            // ID for the timer
   
} _SOS_CAPABILITIES; 

// far pointer to the device capabilities structure
typedef _SOS_CAPABILITIES far *  LPSOSDEVICECAPS;

// flag types for driver
#define  _FLAGS_SIGNED              0x8000
  
// devices that can be loaded
#define  _SOUND_BLASTER_8_MONO      0xe000
#define  _SOUND_BLASTER_8_ST        0xe001
#define  _SBPRO_8_ST                _SOUND_BLASTER_8_ST
#define  _SBPRO_8_MONO              0xe00f
#define  _SOUND_MASTER_II_8_MONO    0xe002
#define  _MV_PAS_8_MONO             0xe003
#define  _MV_PAS_16_MONO            0xe004
#define  _MV_PAS_8_ST               0xe005
#define  _MV_PAS_16_ST              0xe006
#define  _ADLIB_GOLD_8_ST           0xe007
#define  _ADLIB_GOLD_16_ST          0xe008
#define  _ADLIB_GOLD_8_MONO         0xe009
#define  _ADLIB_GOLD_16_MONO        0xe00a
#define  _MICROSOFT_8_MONO          0xe00b
#define  _MICROSOFT_8_ST            0xe00c
#define  _MICROSOFT_16_MONO         0xe00d
#define  _MICROSOFT_16_ST           0xe00e
#define  _SOUND_SOURCE_8_MONO_PC    0xe010
#define  _SOUND_SOURCE_8_MONO_TANDY 0xe011
#define  _GENERAL_PORT_8_MONO       0xe012
#define  _GENERAL_PORT_8_MONO_R     0xe013
#define  _SIERRA_8_MONO             0xe014
#define  _SB16_8_MONO               0xe015
#define  _SB16_8_ST                 0xe016
#define  _SB16_16_MONO              0xe017
#define  _SB16_16_ST                0xe018
#define  _ESS_AUDIODRIVE_8_MONO     0xe019
#define  _ESS_AUDIODRIVE_8_ST       0xe01a
#define  _ESS_AUDIODRIVE_16_MONO    0xe01b
#define  _ESS_AUDIODRIVE_16_ST      0xe01c
#define  _SOUNDSCAPE_8_MONO         0xe01d
#define  _SOUNDSCAPE_8_ST           0xe01e
#define  _SOUNDSCAPE_16_MONO        0xe01f
#define  _SOUNDSCAPE_16_ST          0xe020
#define  _RAP10_8_MONO              0xe021
#define  _RAP10_16_MONO             0xe022
#define  _GUS_8_MONO                0xe023
#define  _GUS_8_ST                  0xe024
#define  _GUS_16_MONO               0xe025
#define  _GUS_16_ST                 0xe026
#define  _GUS_MAX_8_MONO            0xe027
#define  _GUS_MAX_8_ST              0xe028
#define  _GUS_MAX_16_MONO           0xe029
#define  _GUS_MAX_16_ST             0xe02a
#define  _WAVEJAMMER_8_MONO         0xe02b
#define  _WAVEJAMMER_8_ST           0xe02c
#define  _WAVEJAMMER_16_MONO        0xe02d
#define  _WAVEJAMMER_16_ST          0xe02e
#define  _TEMPOCS_8_MONO            0xe02f
#define  _TEMPOCS_8_ST              0xe030
#define  _TEMPOCS_16_MONO           0xe031
#define  _TEMPOCS_16_ST             0xe032
#define  _WAVEJAMMERCD_8_MONO       0xe033
#define  _WAVEJAMMERCD_8_ST         0xe034
#define  _WAVEJAMMERCD_16_MONO      0xe035
#define  _WAVEJAMMERCD_16_ST        0xe036
#define  _SOUND_BLASTER_8_MONO_R    0xe050
#define  _MICROSOFT_8_MONO_R        0xe051
#define  _SOUND_MASTER_II_8_MONO_R  0xe052
#define  _ADLIB_GOLD_8_MONO_R       0xe053
#define  _MV_PAS_8_MONO_R           0xe054
#define  _RAP10_8_MONO_R            0xe058
#define  _RAP10_16_MONO_R           0xe059
#define  _SB16_8_MONO_R             0xe05a
#define  _SB16_8_ST_R               0xe05b
#define  _SB16_16_MONO_R            0xe05c
#define  _SB16_16_ST_R              0xe05d
#define  _MV_PAS_16_MONO_R          0xe060
#define  _SOUNDSCAPE_8_MONO_R       0xe061
#define  _SOUNDSCAPE_8_ST_R         0xe062
#define  _SOUNDSCAPE_16_MONO_R      0xe063
#define  _SOUNDSCAPE_16_ST_R        0xe064
#define  _ESS_AUDIODRIVE_8_MONO_R   0xe065
#define  _ESS_AUDIODRIVE_8_ST_R     0xe066
#define  _ESS_AUDIODRIVE_16_MONO_R  0xe067
#define  _ESS_AUDIODRIVE_16_ST_R    0xe068
#define  _SPEECH_THING_8_MONO       0xe090
#define  _YAMAHA_8_MONO             0xe106
#define  _INT_SPEAKER_8_MONO        0xe107

// call indexes for the loadable drivers
enum
{ 
   _DRV_INIT,
   _DRV_UNINIT,
   _DRV_SETRATE,
   _DRV_SETACTION,
   _DRV_START,
   _DRV_STOP,
   _DRV_PAUSE,
   _DRV_RESUME,
   _DRV_CAPABILITIES,
   _DRV_PLAY_FOREGROUND,
   _DRV_GET_FILL_INFO, 
   _DRV_GET_CALL_FUNCTIONS,
   _DRV_SET_CALL_FUNCTIONS
};

// fill info
typedef  struct   _tagFillInfo
		 {

			LPSTR lpFillHandler;                   // pointer to fill handler
			LPWORD lpDMAFillCount;                 // pointer to dma count
			LPSTR lpSampleList;                    // pointer to sample list
			LPWORD lpDMAMasterVolume;              // pointer to dma count

		 } _SOS_FILL_INFO;

// caps info structure
typedef  struct   _tagCapsInfo
		 {

			LPSTR    lpPortList;                   // pointer to port list
			LPSTR    lpDMAList;                    // pointer to DMA list
			LPSTR    lpIRQList;                    // pointer to IRQ list
			LPSTR    lpRateList;                   // pointer to rate list

		 } _SOS_CAPS_INFO;

// maximum number of available voice
#define  _MAX_VOICES    32

// structure definition
typedef  struct   _tagSAMPLE
{
   LPSTR    samplePtr;                 // pointer to data buffer
   LPSTR    sampleData;                // pointer to active data
   LPSTR    sampleLoopPtr;             // pointer for loop back

   WORD     sampleLength;              // length of sample
   WORD     sampleIndex;               // index into sample
   WORD     sampleLoopLength;          // length of loop
   
   WORD     sampleBytesLeft;           // bytes left to play in sample

   WORD     sampleLoopPoint;           // byte count for loop point
   WORD     sampleLoopEndLength;       // length of remaining chunk

   short    sampleFlags;               // control sample
   short    sampleVolume;              // volume control
   short    sampleID;                  // sample ID

   short    sampleChannel;             // channel to play sample on
   short    sampleLoopCount;           // loop count
   short    sampleLastFill;            // last fill position
   VOID ( far cdecl * sampleCallback )( WORD, WORD, WORD ); // callback function for sample

   WORD     samplePitchAdd;
   short    samplePitchFraction;

   short    samplePort;                // port to use for non-dma digitized

   WORD     sampleTotalBytes;
   WORD     sampleByteLength;

   short    samplePanLocation;
   short    samplePanSpeed;
   short    samplePanDirection;
   short    samplePanStart;
   short    samplePanEnd;
   
   short    sampleDelayBytes;
   short    sampleDelayRepeat;
   
   WORD     sampleADPCMPredicted;
   short    sampleADPCMIndex;

   short    sampleRootNoteMIDI;   

   WORD  sampleTemp1;   
   
} _SOS_SAMPLE;

// enumeration for left or right channel
enum
{
   _LEFT_CHANNEL,
   _RIGHT_CHANNEL,
   _CENTER_CHANNEL,
   _INTERLEAVED
};

// enumeration for foreground and background
enum
{ 
   _FOREGROUND,
   _BACKGROUND 
};

// defines for the sample flags
#define  _ACTIVE           0x8000
#define  _LOOPING          0x4000
#define  _FIRST_TIME       0x2000
#define  _PENDING_RELEASE  0x1000
#define  _CONTINUE_BLOCK   0x0800
#define  _PITCH_SHIFT      0x0400
#define  _PANNING          0x0200
#define  _VOLUME           0x0100
#define  _TRANSLATE16TO8   0x0080
#define  _STAGE_LOOP       0x0040
#define  _TRANSLATE8TO16   0x0020
#define  _STEREOTOMONO     0x0010

// defines for the wParam flags 
#define  _SINGLE_SAMPLE 0x01

#define  _SOS_DCAPS_AUTO_REINIT     0x01
#define  _SOS_DCAPS_MPU_401         0x02
#define  _SOS_DCAPS_OPL2            0x04
#define  _SOS_DCAPS_OPL3            0x08
#define  _SOS_DCAPS_OPL4            0x10
#define  _SOS_DCAPS_WAVETABLE       0x20
#define  _SOS_DCAPS_DL_SAMPLES      0x40
#define  _SOS_DCAPS_FIFO_DEVICE     0x80
#define  _SOS_DCAPS_ENV_NEEDED      0x100
#define  _SOS_DCAPS_PSEUDO_DMA1     0x200
#define  _SOS_DCAPS_SIGNED_DATA     0x8000

// file header structure
typedef struct
{
   // name ID
   BYTE  szName[ 32 ];

   // number of drivers in the file
   WORD  wDrivers;

   // offset of first driver
   WORD  lOffset;

   // size of the file
   WORD  lFileSize;

} _FILEHEADER;

// driver header structure
typedef struct
{
   // name ID
   BYTE  szName[ 32 ];

   // offset of next driver
   WORD  lNextDriver;

   // size of current driver
   WORD  wSize;

   // id for the current device
   WORD  wDeviceID;

   // id for the type of DOS extender
   WORD  wExtenderType;

} _DRIVERHEADER;

// device hardware information
typedef struct
{
   // port to be used
   WORD  wPort;

   // irq to use
   WORD  wIRQ;

   // dma channel to se
   WORD  wDMA; 
  
   // extra parameter
   WORD  wParam;

} _SOS_HARDWARE;

// structure definition for start sample
typedef struct
{
   // pointer to sample
   LPSTR lpSamplePtr;

   // size of the sample
   WORD  dwSampleSize;

   // number of times to loop the sample -1 is infinite
   WORD  wLoopCount;

   // channel to play sample on
   WORD  wChannel;

   // volume to play sample at
   WORD wVolume;

   // id for the sample
   WORD  wSampleID;

   // far pointer to the callback function
   VOID ( far cdecl *lpCallback )( WORD, WORD, WORD );

   // port to use if driver is a non-dma background driver
   WORD  wSamplePort; 

   // flags field
   WORD  wSampleFlags;

   // total length of sample including loops, etc..
   WORD     dwSampleByteLength;

   // loop point for the sample
   WORD  dwSampleLoopPoint;
   WORD  dwSampleLoopLength;

   // pitch shifting components 
   WORD     dwSamplePitchAdd;
   WORD    wSamplePitchFraction;

   // pan components
   WORD    wSamplePanLocation;
   WORD    wSamplePanSpeed;
   WORD    wSamplePanDirection;
   WORD    wSamplePanStart;
   WORD    wSamplePanEnd;
   
   // delay parts
   WORD    wSampleDelayBytes;
   WORD    wSampleDelayRepeat;

   // compression components   
   WORD     dwSampleADPCMPredicted;
   WORD    wSampleADPCMIndex;

   // root note for pitch shifting 
   WORD    wSampleRootNoteMIDI;   

   // filler for future upgrades
   WORD  dwSampleTemp1;   
   WORD  dwSampleTemp2;   
   WORD  dwSampleTemp3;   

} _SOS_START_SAMPLE;

// structure for initializing a driver
typedef struct
{  
   WORD  wBufferSize;
   LPSTR lpBuffer;
   BOOL  wAllocateBuffer;
   WORD  wSampleRate;
   WORD  wParam;
   LONG  dwParam;
   VOID ( far *lpFillHandler )( VOID );
   LPSTR lpDriverMemory;
   LPSTR lpDriverMemoryCS;
   LPSTR lpTimerMemory;
   LPSTR lpTimerMemoryCS;
   WORD  wTimerID;
   WORD  wPhysical;

} _SOS_INIT_DRIVER;

// define for the timer types to use
#define  _SOS_NORMAL_TIMER          0x00

// enumeration for the timer types
enum
{
   _TIMER_8_MONO   =     0x1000,
   _TIMER_8_ST,          
   _TIMER_16_MONO,       
   _TIMER_16_ST,         
   _TIMER_8_MONO_ULAW,  
   _TIMER_8_ST_ULAW,    
   _TIMER_16_MONO_ULAW, 
   _TIMER_16_ST_ULAW,   
   _TIMER_8_MONO_REC,   
   _TIMER_8_MONO_ULAW_REC,
   _TIMER_UNDEFINED_1,      
   _TIMER_UNDEFINED_2,
   _TIMER_UNDEFINED_3,
   _TIMER_UNDEFINED_4,
   _TIMER_UNDEFINED_5,
   _TIMER_UNDEFINED_6,
   _TIMER_UNDEFINED_7,
   _TIMER_UNDEFINED_8,
   _TIMER_UNDEFINED_9,
   _TIMER_UNDEFINED_A,
   _TIMER_UNDEFINED_B,
   _TIMER_UNDEFINED_C,
   _TIMER_UNDEFINED_D,
   _TIMER_UNDEFINED_E,
   _TIMER_UNDEFINED_F,
   _TIMER_UNDEFINED_10,
   _TIMER_UNDEFINED_11,
   _TIMER_UNDEFINED_12,
   _TIMER_UNDEFINED_13,
   _TIMER_UNDEFINED_14,
   _TIMER_UNDEFINED_15,
   _TIMER_UNDEFINED_16,
   _TIMER_8_SOUND_SOURCE,
   _TIMER_8_SOUND_SOURCE_TANDY,
   _TIMER_8_GENERAL_PORT,
   _TIMER_8_GENERAL_PORT_REC   
};

// define for no slots available
#define  _ERR_NO_SLOTS ( WORD )-1

// error codes for the system
enum
{
   _ERR_NO_ERROR,
   _ERR_DRIVER_NOT_LOADED,
   _ERR_INVALID_POINTER,
   _ERR_DETECT_INITIALIZED,
   _ERR_FAIL_ON_FILE_OPEN,
   _ERR_MEMORY_FAIL,
   _ERR_INVALID_DRIVER_ID,
   _ERR_NO_DRIVER_FOUND,
   _ERR_DETECTION_FAILURE,
   _ERR_DRIVER_LOADED,
   _ERR_INVALID_HANDLE,
   _ERR_NO_HANDLES,
   _ERR_PAUSED,   
   _ERR_NOT_PAUSED,
   _ERR_INVALID_DATA,
   _ERR_DRV_FILE_FAIL,
   _ERR_INVALID_PORT,
   _ERR_INVALID_IRQ,
   _ERR_INVALID_DMA,
   _ERR_INVALID_DMA_IRQ
};   

// maximum number of timer events that can be registered 
#define  _TIMER_MAX_EVENTS    0x10  

// flags for the debugging system
#define  _SOS_DEBUG_NORMAL       0x0000
#define  _SOS_DEBUG_NO_TIMER     0x0001
#define  _SOS_TIMER_DPMI         0x0002

// define for types of DOS extenders
#define  _SOS_RATIONAL           0x8000
#define  _SOS_FLASHTECK          0x4000

// defines for the types of timers for different
// dos extenders
#define  _SOS_TIMER_NEAR         0x8000
#define  _SOS_TIMER_FAR          0x4000
 
// values for callback information
enum
{
   _SAMPLE_PROCESSED,
   _SAMPLE_LOOPING,
   _SAMPLE_DONE
};

// define for special 18.2 callback rate to dos
#define  _TIMER_DOS_RATE   0xff00

#pragma pack()

#pragma aux int_3 = "int 3"
 
#pragma pack( 1 ) 
typedef struct
{
	unsigned       region_size;
	unsigned       offset;
	unsigned       segment;
	unsigned short  number_available;
	unsigned short number_used;
	unsigned       page0;

} EVDS_STRUCT;

typedef struct 
{
	unsigned       region_size;
	unsigned       offset;
	unsigned short segment;
	unsigned short  ID;
	unsigned       physical;

} VDS_STRUCT;

#pragma pack() 

//
// #include "sosdata.h"
//
/****************************************************************************

   File              : sosdata.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/

#ifndef  _SOS_DATA
#define  _SOS_DATA

#include <stddef.h>

#pragma pack(4) 
extern   WORD     _sosDIGIData_Start;
extern   WORD     _sosDIGIData_End;
extern   WORD     _wSOSDriverLinear[];
extern   WORD     _wSOSTimerLinear[];
extern   LPSTR    _lpSOSDriver[];
extern   LPSTR    _lpSOSTimer[];
extern   LPSTR    _lpSOSDriverCS[];
extern   LPSTR    _lpSOSTimerCS[];
extern   BOOL     _wSOSDriverLoaded[];
extern   BOOL     _wSOSTimerLoaded[];
extern   BOOL     _wSOSDriverInitialized[];
extern   WORD     _wSOSOutputRate[];
extern   WORD     _wSOSDMABuffersize[];
extern   LONG     _dwSOSDMABufferPhysical[];
extern   LPSTR    _lpSOSDMABuffer[];
extern   BOOL     _wTimerUsed;
extern   VOID ( far *_lpSOSFillHandler[] )( VOID );
extern   WORD     _wSOSTimerType[];
extern   WORD     _wSOSDriverType[];
extern   _SOS_SAMPLE far * _lpSOSSampleList[][ _MAX_VOICES ];
extern   LPWORD      _lpSOSDMAIrqCount[];
extern   LPWORD      _lpSOSDMAFillCount[];
extern   WORD        _wSOSTmrNextCount;
extern   VOID ( interrupt far *_lpSOSOldTimer )( VOID );
extern   WORD     _wSOSDriverID[];
extern   _SOS_CAPABILITIES _sSOSDriverCaps[];
extern   WORD        _wSOSDMAPortList[];
extern   BYTE        _bSOSDMAChannel[];
extern   _SOS_INIT_DRIVER     _sSOSDIGIInitDriver[];
extern   BYTE  _pSOSDriverPath[];
extern   BYTE  _pSOSTempDriverPath[];
extern   BOOL  _wTIMERUsed;
extern   WORD  _wTIMERValue;
extern   VOID ( far * _lpTIMEREvents[] )( VOID );
extern   WORD _wTIMEREventRate[];
extern   WORD _dwTIMEREventFraction[];
extern   WORD _dwTIMEREventFractionCurrent[];
extern   BYTE  _bSOSMIDITimerSongHandler[];
extern   BYTE  _bSOSMIDISongHandle;
extern   WORD  _wSOSTimerMemHandle[];
extern   WORD  _wSOSDriverMemHandle[];
extern   WORD  _wSOSRealSeg[];

extern   _FILEHEADER    _sDETFileHeader;
extern   _DRIVERHEADER  _sDETDriverHeader;
extern   _FILEHEADER    sLOADFileHeader;
extern   _DRIVERHEADER  sLOADDriverHeader;
extern   BOOL           _wDETInitialized;
extern   WORD           _wDETLinear;
extern   LPSTR          _lpDETDriverBuffer;    
extern   LPSTR          _lpDETDriverBufferCS;
extern   WORD           _hDETFile;
extern   DWORD          _dwDETDriverIndex;
extern   WORD           _wDETDriverIndexCur;
extern   WORD           _wDETMemHandle;
extern   LPSOSDEVICECAPS _lpDETDeviceCaps;
extern   _SOS_CAPABILITIES _sDETCaps;  
extern   PSTR _pSOSErrorStrings[];
extern   BOOL _wSOSBufferAllocated[];
extern   BOOL _wSOSSystemInitialized;
extern   VDS_STRUCT _sSOSVDSInfo;
extern   _SOS_FILL_INFO _sSOSFillInfo;
extern   WORD    _wSOSTimerEventIndex;
extern   WORD  _wSOSTimerEntered;
extern   WORD  _wSOSDriverSize[];
extern   WORD  _wSOSTimerSize[];

#ifdef __cplusplus
extern "C" {
#endif
extern   WORD  _sosDIGIData1_Start;
extern   WORD  _sosDIGIData1_End;
extern   WORD  _sosDIGIData2_Start;
extern   WORD  _sosDIGIData2_End;
extern   BYTE  _bTIMERInstalled;
extern   BYTE  _bTIMERDPMI;
extern   WORD  wDetectPort;
extern   WORD  wDetectIRQ;
extern   WORD  wDetectDMA;
extern   WORD  wDetectParam;
#ifdef __cplusplus
}
#endif 

#pragma pack()

#endif


//
// #include "sosfnct.h"
//
/****************************************************************************

   File              : sosfnct.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/

#ifndef  _SOS_FUNCTIONS
#define  _SOS_FUNCTIONS

#pragma pack(4)

WORD sosDIGILockMemory          (  VOID  );
WORD sosDIGIUnLockMemory        (  VOID  );
WORD sosDIGIInitSystem           (  LPSTR, WORD  );
WORD sosDIGIUnInitSystem         (  VOID  );
WORD sosDIGIInitDriver           (  WORD, _SOS_HARDWARE far *,
									_SOS_INIT_DRIVER far *, WORD far *   );
WORD sosDIGIUnInitDriver         (  WORD, BOOL, BOOL  );
WORD sosDIGILoadDriver          (  WORD, WORD, LPSTR far *, LPSTR far *, PSTR, PSTR, WORD * );
WORD sosDIGIUnLoadDriver         (  WORD  );
WORD sosDIGIGetDeviceCaps        (  WORD, LPSOSDEVICECAPS  );

#ifdef PHARLAP
LPSTR sosDIGIAllocateBuffer      (  WORD , WORD *, WORD * );
#else
LPSTR sosDIGIAllocateBuffer      (  WORD , WORD *, WORD * );
#endif

WORD sosDIGIStopSample           (  WORD, WORD  );
WORD sosDIGISamplesPlaying       (  WORD  );
BOOL sosDIGISampleDone           (  WORD, WORD  );
BOOL sosDIGISampleFilling        (  WORD, WORD  );
WORD sosDIGIStartSample          (  WORD, _SOS_START_SAMPLE far *  );
WORD sosDIGIContinueSample       (  WORD, WORD, _SOS_START_SAMPLE far * );


WORD  sosDIGIDetectInit          (  LPSTR  );
WORD  sosDIGIDetectUnInit        (  VOID  );
WORD  sosDIGIDetectFindHardware  (  WORD, _SOS_CAPABILITIES far *, WORD far * );
WORD  sosDIGIDetectFindFirst     (  _SOS_CAPABILITIES far *, WORD far *  );
WORD  sosDIGIDetectFindNext      (  _SOS_CAPABILITIES far *, WORD far *  );
WORD  sosDIGIDetectGetSettings   (  _SOS_HARDWARE far *  );
WORD  sosDIGIDetectGetCaps       (  WORD, _SOS_CAPABILITIES far *  );
WORD  sosDIGIDetectVerifySettings(  _SOS_HARDWARE far *  );
PSTR  sosGetErrorString          (  WORD  );

WORD  sosDIGILoadTimer           (  WORD , LPSTR far *, LPSTR far *, PSTR, PSTR, WORD * );
WORD  sosDIGIUnLoadTimer         (  WORD  );

WORD  sosTIMERRegisterEvent      ( WORD wCallRate, VOID ( far * lpTimerEvent )( VOID ), WORD far *lpTimerHandle );
WORD  sosTIMERInitSystem               (  WORD, WORD  );
WORD  sosTIMERUnInitSystem             (  WORD  );
WORD  sosTIMERSetRate                  (  WORD  );  
WORD  sosTIMERRemoveEvent              (  WORD );
WORD  sosTIMERAlterEventRate           (  WORD, WORD  );
WORD  sosTIMERGetEventRate             (  WORD  );
VOID far sosTIMEROldHandler            (  VOID  );
VOID far sosTIMERHandler               (  VOID  );

// functions in soscntl.c
WORD  sosDIGISetSampleVolume     ( WORD, WORD, WORD );
WORD  sosDIGIGetSampleVolume     ( WORD, WORD );
WORD  sosDIGISetChannel          ( WORD, WORD, WORD );
WORD  sosDIGIGetChannel          ( WORD, WORD );
WORD  sosDIGIGetBytesProcessed   ( WORD, WORD );
WORD  sosDIGIGetLoopCount        ( WORD, WORD );
WORD  sosDIGISetPanLocation      ( WORD, WORD, WORD );
WORD  sosDIGIGetPanLocation      ( WORD, WORD );
DWORD sosDIGISetPitch            ( WORD, WORD, DWORD );
DWORD sosDIGIGetPitch            ( WORD, WORD );
WORD  sosDIGIGetDMAPosition      ( WORD );
WORD  sosDIGISetPanSpeed         ( WORD, WORD, WORD );
WORD  sosDIGIGetPanSpeed         ( WORD, WORD );
WORD  sosDIGIGetSampleID         ( WORD, WORD );
WORD  sosDIGIGetSampleHandle     ( WORD, WORD );
WORD  sosDIGISetMasterVolume     ( WORD, WORD );
#ifdef PHARLAP
VOID  sosFreeVDSPage          ( unsigned short, unsigned short, DWORD );
WORD  sosAllocVDSPage         ( unsigned short *, unsigned short *, DWORD * );
#else
WORD  sosAllocVDSPage            ( LPSTR *, WORD *, WORD * );
VOID  sosFreeVDSPage             ( WORD, WORD, LONG );
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PHARLAP
extern   int   cdecl sosRealFree          ( int );
extern   BOOL  cdecl  _sos_read( WORD, LPSTR, WORD, WORD * );
extern   int   cdecl sosRealAlloc( int, int *, int * );
extern   void  cdecl sosDRVFarMemCopy( LPSTR, LPSTR, WORD );
extern   int   cdecl sosGetCS( VOID );
extern   int   cdecl sosGetES( VOID );
#else
extern   int   cdecl sosRealAlloc         ( int, int *, int * );
extern   int   cdecl sosRealFree          ( int );
#endif

// sos driver functions
extern   WORD  cdecl sosDRVLockMemory     ( DWORD, DWORD );
extern   WORD  cdecl sosDRVUnLockMemory   ( DWORD, DWORD );
extern   void  cdecl sosDRVGetCapsInfo    ( LPSTR, LPSTR, _SOS_CAPABILITIES far * );
extern   void  cdecl sosDetDRVGetCapsInfo ( LPSTR, LPSTR, _SOS_CAPABILITIES far * );
extern   void  cdecl sosDRVGetCapsPtr     ( LPSTR, LPSTR, _SOS_CAPABILITIES far * );
extern   void  cdecl sosDRVInit           ( LPSTR, LPSTR, int, int, int, int, int, int );  
extern   void  cdecl sosDRVStart          ( LPSTR, LPSTR, int, int );
extern   void  cdecl sosDRVSetRate        ( LPSTR, LPSTR, int );
extern   void  cdecl sosDRVSetAction      ( LPSTR, LPSTR );
extern   void  cdecl sosDRVStop           ( LPSTR, LPSTR );
extern   void  cdecl sosDRVUnInit         ( LPSTR, LPSTR );
extern   void  cdecl sosDRVGetFillInfo    ( LPSTR, LPSTR, LPSTR, int, int, int, _SOS_FILL_INFO * );
extern   void  cdecl sosFillSampleStructs ( PSTR, LPSTR );
extern   WORD  cdecl sosDetDRVExist       ( LPSTR, LPSTR );
extern   WORD  cdecl sosDetDRVGetSettings ( LPSTR, LPSTR );
extern   WORD  cdecl sosDetDRVVerifySettings( LPSTR, WORD, WORD, WORD, LPSTR );
extern   WORD  cdecl sosDIGIInitForWindows( WORD );
extern   WORD  cdecl sosDIGIUnInitForWindows( WORD );
extern   LPSTR cdecl sosAllocateFarMem      ( WORD, PSTR, WORD * );
extern   LPSTR cdecl sosCreateAliasCS       ( LPSTR );
extern   VOID  cdecl sosFreeSelector        ( LPSTR, DWORD );
extern   LPSTR cdecl sosMAKEDOSPtr          ( PSTR );
extern   VOID  cdecl sosDetDRVSetEnvString  ( DWORD, PSTR );
extern   PSTR  cdecl sosDetDRVGetEnvString  ( DWORD );
extern   VOID  cdecl sosDetDRVEnvStringInit ( LPSTR, LPSTR );
extern   VOID  cdecl sosDRVSetupCallFunctions( LPSTR, LPSTR, LPSTR, LPSTR );
extern   WORD  cdecl sosDRVGetFreeMemory     ( VOID );
extern   WORD  cdecl sosDRVAllocVDSStruct    ( WORD, WORD *, WORD * );
extern   WORD  cdecl sosDRVFreeVDSStruct     ( WORD, WORD );
extern   WORD  cdecl sosDRVIsWindowsActive   ( VOID );
extern   WORD  cdecl sosDRVVDSGetBuffer    ( WORD );
extern   WORD  cdecl sosDRVVDSFreeBuffer   ( WORD );
extern   WORD  cdecl getDS( VOID );
extern   WORD  cdecl sosDRVMakeDMASelector   ( WORD );  
extern   WORD  cdecl sosDRVFreeDMASelector   ( WORD );  


extern   void  cdecl sosTIMERDRVInit( int wRate, void ( far * )( void ) );
extern   void  cdecl sosTIMERDRVUnInit( void );
extern   void  cdecl sosTIMERDRVHandler( void );
extern   void  cdecl sosTIMERDRVFHandler( void );
extern   void  cdecl sosTIMERDRVEnable( void );
extern   void  cdecl sosTIMERDRVDisable( void );
extern   void  cdecl sosTIMERDRVCallOld( void );
extern   void  cdecl sosTIMERDRVSetRate( WORD );    
extern   void  cdecl sosDIGITimer_Start( void );
extern   void  cdecl sosDIGITimer_End( void );
extern   void  cdecl sosDIGIDrv_Start( void );
extern   void  cdecl sosDIGIDrv_End( void );
#ifdef __cplusplus
}
#endif 

// external functions for handling system initialization and 
// uninitialization
WORD  sosEXDIGInitDriver               (  WORD, WORD, WORD, LPSTR,
										  _SOS_HARDWARE far *, WORD *  );
WORD  sosEXDIGIUnInitDriver            (  VOID  );

WORD  sosEXDETFindDriver               (  WORD, LPSTR, _SOS_HARDWARE far *,
										  _SOS_CAPABILITIES far *  );

// memory locking prototypes
VOID  sosDIGICaps_Start( VOID );
VOID  sosDIGICaps_End( VOID );
VOID  sosDIGIErr_Start( VOID );
VOID  sosDIGIErr_End( VOID );
VOID  sosDIGITmr_Start( VOID );
VOID  sosDIGITmr_End( VOID );
VOID  sosDIGIStart_Start( VOID );
VOID  sosDIGIStart_End( VOID );
VOID  sosDIGIPlyng_Start( VOID );
VOID  sosDIGIPlyng_End( VOID );
VOID  sosDIGIRate_Start( VOID );
VOID  sosDIGIRate_End( VOID );
VOID  sosDIGIDone_Start( VOID );
VOID  sosDIGIDone_End( VOID );
VOID  sosDIGIDetec_Start( VOID );
VOID  sosDIGIDetec_End( VOID );
VOID  sosDIGIInit_Start( VOID );
VOID  sosDIGIInit_End( VOID );
VOID  sosDIGILoad_Start( VOID );
VOID  sosDIGILoad_End( VOID );
VOID  sosDIGICntl_Start( VOID );
VOID  sosDIGICntl_End( VOID );

#pragma pack()

#endif


#endif



//
// include sosm.h and its includes so just call
// sos.h from teksnd.c
//
/****************************************************************************

   File              : sosm.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/

#ifndef  _SOS_MIDI_DEFINED   
#define  _SOS_MIDI_DEFINED   

//
//#include "sosdefs.h"
//#include "sos.h"
//

#pragma pack(4)

#define  _SOS_MIDI_ERR          -1

// number of drivers allowed to be open at one time
#define  _SOS_MIDI_MAX_DRIVERS  5

// maximum number of allowed channels
#define  _SOS_MIDI_MAX_CHANNELS    0x10

// structure definition for the capabilities
typedef struct
{
   BYTE     szDeviceName[ 32 ];  // device name
   WORD     wDeviceVersion;      // device version
   WORD     wFlags;              // miscellaneous flags   
   WORD     wProcessData;        // process data before sending to driver
   short far *   lpPortList;          // list of usable ports
   short far *   lpIRQList;           // list of usable irq channels
   WORD     wDeviceID;           // ID for the device
   
} _SOS_MIDI_CAPABILITIES; 

#define  LPSOSMIDIDEVICECAPS  _SOS_MIDI_CAPABILITIES far *

// call indexes for the loadable drivers
enum
{ 
   _DRV_MIDI_GET_CAPS,
   _DRV_MIDI_GET_CALL_TABLE,
   _DRV_MIDI_SPECIAL1
};

// file header for the driver
typedef struct
{
   // name ID
   BYTE  szName[ 32 ];

   // number of drivers in the file
   WORD  wDrivers;

   // offset of first driver
   WORD  lOffset;

   // size of the file
   WORD  lFileSize;

} _MIDIFILEHEADER;

// driver header structure
typedef struct
{
   // name ID
   BYTE  szName[ 32 ];

   // offset of next driver
   WORD  lNextDriver;

   // size of current driver
   WORD  wSize;

   // id for the current device
   WORD  wDeviceID;

   // id for the extender type
   WORD  wExtenderType;

} _MIDIDRIVERHEADER;

// device hardware information
typedef struct
{
   // port to be used
   WORD  wPort;

   // IRQ for the board
   WORD  wIRQ;

   // extra parameter
   WORD  wParam;

} _SOS_MIDI_HARDWARE;

// structure for initializing a digital driver 
typedef struct
{
   // ID for the digital driver
   WORD  wDriverID;

   // timer rate to use
   WORD  wTimerRate;

   // timer callback rate to use
   WORD  wTimerCallbackRate;

   // max voices for the driver to use
   WORD  wMaxVoices;

   // velocity sensing flag
   WORD  wVelocitySensing;

   // init driver info
   _SOS_INIT_DRIVER far * sDIGIDriverInfo;

   // hardware information
   _SOS_HARDWARE far *  sDIGIHardwareInfo;    

} _SOS_MIDI_DIGI_INIT_DRIVER;

// structure for initializing a driver
typedef struct
{  
   // type of driver to use if using a digital driver
   WORD        wDIGIDriverID;

   // pointer to driver memory
   VOID far * lpDriverMemory;
   VOID far * lpDriverMemoryCS;

   // pointer to digital driver initialization information
   _SOS_MIDI_DIGI_INIT_DRIVER far * sDIGIInitInfo;

   // miscellaneous WORD parameter for driver
   WORD  wParam;

   // miscellaneous DWORD parameter for driver
   DWORD dwParam;

} _SOS_MIDI_INIT_DRIVER;

// structure for starting a song
typedef struct
{  
   // pointer to song memory 
   BYTE _huge * lpSongData;

   // pointer to callback function for pertinent song information
   VOID ( far * lpSongCallback )( WORD );

} _SOS_MIDI_INIT_SONG;

// define to indicate that track mapping can be used
// from the midi file for the song
#define  _MIDI_MAP_TRACK   0xff
  
// MIDI channel to device mapping structure
typedef struct
{
   // track to device mapping information
   WORD wTrackDevice[ 32 ];
	 
} _SOS_MIDI_TRACK_DEVICE;

// MIDI channel to device mapping structure
typedef struct
{
   // track to device mapping information
   WORD wTrackDevice[ 32 ][ 5 ];
	 
} _SOS_MIDI_TRACK_DEVICE1;

// NEW
// header for the NDMF format MIDI file 
typedef struct
{
   // ID for the file
   BYTE  szFileID[ 32 ];

   WORD dwBranchOffset;
   WORD temp1;
   WORD temp2;
   WORD temp3;

//   // name of the instrument file to use with the song   
//   BYTE  szInstrumentFile[ 16 ];

   // number of tracks in the song
   WORD  wNDMFTracks;

   // ticks/quarter note song is used at
   WORD  wTicksQuarterNote;

   // tempo
   WORD  wTempo;

   // time for song to play at current tempo
   WORD  wTimeToPlay;

   // channel mapping priority information
   WORD  wChannelPriority[ _SOS_MIDI_MAX_CHANNELS ];

   // channel mapping information
   _SOS_MIDI_TRACK_DEVICE1 sTrackMap;

   // array of flags for which controllers to restore on a loop/branch
   BYTE  bCtrlRestore[ 128 ];

   // pointer to callback function for song to call with 
   // pertinent information
   VOID ( far * lpSongCallback )( WORD ); 

} _NDMF_FILE_HEADER;
// END

// header for the tracks in the NDMF format MIDI file
typedef struct
{
   // track number
   WORD  wTrackNumber;

   // length of the track
   WORD  wTrackLength;

   // channel used on the track
   WORD  wChannel;

} _NDMF_TRACK_HEADER;

// MIDI event structure
typedef struct
{
   // dummy name to access midi data from
   BYTE  bMidiData[ 256 ];

} _NDMF_MIDI_EVENT;

// maximum number of songs that can be played at any time
#define  _SOS_MIDI_MAX_SONGS     8

// maximum number of tracks that can be used
#define  _SOS_MIDI_MAX_TRACKS    32

// number of driver functions
#define  _SOS_MIDI_DRV_FUNCTIONS 12

// enumeration for all of the drv functions
enum
{
   _MIDI_DRV_SEND_DATA,
   _MIDI_DRV_INIT,
   _MIDI_DRV_UNINIT,
   _MIDI_DRV_RESET,
   _MIDI_DRV_SET_INST_DATA
};

// defines for the loadable driver ids
#define  _MIDI_SOUND_MASTER_II      0xa000
#define  _MIDI_MPU_401              0xa001
#define  _MIDI_FM                   0xa002
#define  _MIDI_OPL2                 0xa002
#define  _MIDI_CALLBACK             0xa003
#define  _MIDI_MT_32                0xa004
#define  _MIDI_DIGI                 0xa005  
#define  _MIDI_INTERNAL_SPEAKER     0xa006
#define  _MIDI_WAVE_TABLE_SYNTH     0xa007  
#define  _MIDI_AWE32                0xa008  
#define  _MIDI_OPL3                 0xa009  
#define  _MIDI_GUS                  0xa00a  

// structure for the hmi instrument file header
typedef struct
{
   // file id type
   BYTE  szFileID[ 32 ];

   // file version
   WORD  wFileVersion;

   // size of the file
   WORD dwFileSize;

} _HMI_INS_FILE_HEADER;


// define for identifying a drum instrument  
#define  _SOS_MIDI_DRUM_INS   ( short )0x8000

// maximum number of timer events that can be registered 
#define  _TIMER_MAX_EVENTS    0x10  

// structure for digital driver queue element
typedef struct _tagQueueElement
{
   // handle for the sample
   WORD  wSampleHandle;

   // id for the sample
   WORD  wSampleID;

   // velocity for the sample
   WORD  wVelocity;

   // channel for the sample
   WORD  wChannel;

} _DIGI_QUEUE_ELEMENT;

// maximum number of instruments that can be set in the 
// digital driver
#define  _MAX_INS    128

// define for the maximum number of times a channel can be stolen
#define  _SOS_MIDI_MAX_LEVELS    0x04

// structure for MIDI information to be stored on the local stack
// when a channel is stolen
typedef struct
{
   // used element
   BYTE  bUsed;

   // last pitch bend information sent
   BYTE  bPitchBend;

   // channel volume
   BYTE  bChannelVolume;

   // instrument information
   BYTE  bInstrument;

   // sustain pedal
   BYTE  bSustain;

} _SOS_MIDI_CHANNEL_DATA;
 
// flags for the debugging system
#define  _SOS_DEBUG_NORMAL       0x0000
#define  _SOS_DEBUG_NO_TIMER     0x0001

// ID for 32 bit MIDI file
#define  _SOS_MIDI_FILE_ID       "HMIMIDIP"  

// structure for branch location controller
typedef struct
{
   // offset from start of track data
   WORD     dwOffset;

   // branch ID number
   BYTE     bBranchID;

   // current instrument
   BYTE     bInstrument;

   // current loop count for temporary storage
   // so that a track can be looped without 
   // needing any data from the program
   BYTE     bLoopCount;

   // number of controller messages stored
   BYTE     bCtrlChangeCount;

   // offset of control change information from start of file
   WORD     lpCtrlChangeData;   
   WORD     lpCtrlChangeDataTemp;
   
   // reserved fields
   WORD     wReserved1;
   WORD     wReserved2;

} _SOS_BRANCH_POINT;

#define  _SOS_MIDI_FADE_IN          0x01  
#define  _SOS_MIDI_FADE_OUT         0x02  
#define  _SOS_MIDI_FADE_OUT_STOP    0x04  

// structure for digital drums to use to store midi information
typedef struct
{
   // current volume
   WORD  wVolume;

   // current pan position
   WORD  wPanPosition;

   // reserved
   DWORD dwReserved;
   
} _SOS_MIDI_DIGI_CHANNEL;

// instrument file header structure
typedef struct
{
   // file ID
   BYTE  szID[ 32 ];

   // file version
   WORD  wVersion;

   // instruments in file
   WORD  wInstruments;

   // list of pointers to start sample structures
   _SOS_START_SAMPLE far * lpStartSample[ _MAX_INS ];

   DWORD temp1;
   DWORD temp2;

} _WAVE_FILE_HEADER;

#pragma pack()

// define for the busy error returned from send data
#define  _ERR_DRIVER_BUSY  0xf000

// NEW
// defines for the looping branch controllers
#define  _SOS_SET_FLAG   103
#define  _SOS_RESET_FLAG 104
#define  _SOS_BRANCH1   108
#define  _SOS_BRANCH2   109
#define  _SOS_BRANCH3   110
#define  _SOS_BRANCH4   111
#define  _SOS_BRANCH5   112
#define  _SOS_BRANCH6   113
#define  _SOS_BRANCH7   114
#define  _SOS_BRANCH8   115
#define  _SOS_BRANCH9   116
#define  _SOS_BRANCH10  117
#define  _SOS_BRANCH11  118
#define  _SOS_BRANCH12  119
#define  _SOS_BRANCH13  120
#define  _SOS_BRANCH14  121

// define for the program change controller flag
#define  _SOS_PROGRAM_CHANGE_FLAG   108

// END


// 
// #include "sosmdata.h"
//
/****************************************************************************

   File              : sosmdata.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/


#ifndef  _SOS_MIDI_DATA
#define  _SOS_MIDI_DATA

// #include "sos.h"

#pragma pack(4)

extern   WORD     _wSOSMIDIDriverLinear[];
extern   LPSTR    _lpSOSMIDIDriver[];
extern   LPSTR    _lpSOSMIDIDriverCS[];
extern   WORD     _wSOSMIDIMemHandle[];
extern   BOOL     _wSOSMIDIDriverLoaded[];
extern   WORD     _wSOSMIDIDriverType[];
extern   WORD     _wSOSMIDIDriverID[];
extern   DWORD    _dwSOSMIDITrackDeltaCurrent[][_SOS_MIDI_MAX_TRACKS];
extern   WORD     _wSOSMIDIActiveTracks[];
extern   WORD     _wSOSMIDITotalTracks[];
extern   DWORD    _dwSOSMIDITrackDeltaTime[][_SOS_MIDI_MAX_TRACKS];
extern   WORD     _wSOSMIDISongPaused[];
extern   WORD     _wSOSMIDISongMuted[];
extern   BOOL     _wSOSMIDISongActive[];
extern   BYTE     _bSOSMIDIEventSize[];
extern   BYTE     _bSOSMIDIEventSizeControl[];
extern   _SOS_MIDI_CAPABILITIES far * _lpSOSMIDIDriverCaps[];
extern   _SOS_MIDI_TRACK_DEVICE far * _sSOSMIDITrackMap[];   
extern   _NDMF_MIDI_EVENT _huge *  _lpSOSMIDITrack[][_SOS_MIDI_MAX_TRACKS];
extern   WORD  ( cdecl far *_lpSOSMIDIDrvFunction[ _SOS_MIDI_MAX_DRIVERS ][ _SOS_MIDI_DRV_FUNCTIONS ] )( LPSTR, WORD, WORD );   
extern   _NDMF_FILE_HEADER far * _sSOSMIDISongHeader[];
extern   _SOS_INIT_DRIVER        _sSOSDIGIInitDriver[];
extern   WORD _wSOSMIDIEventHandle[];
extern   BYTE  _szSOSMIDIDrvFile[];
extern   _MIDIFILEHEADER    _sSOSMIDIDRVFileHeader;
extern   _MIDIDRIVERHEADER  _sSOSMIDIDRVDriverHeader;
extern   BOOL  _wSOSMIDISysInititalized;
extern   WORD ( cdecl far *_lpSOSMIDICBCKDrvFunctions[] )( LPSTR, WORD, WORD );
extern   VOID ( cdecl far *_lpSOSMIDICBCKFunctions )( LPSTR, WORD, WORD );
extern   WORD _wMIDIDIGISampleQueueHead[];
extern   WORD _wMIDIDIGISampleQueueTail[];
extern   WORD _wMIDIDIGIMaxSamples[];
extern   WORD _wMIDIDIGIUsedSamples[];
extern   _DIGI_QUEUE_ELEMENT _sMIDIDIGIQueue[][ _MAX_VOICES ];


extern   WORD ( cdecl far *_lpMIDIDIGIDrvFunctions[] )( LPSTR, WORD, WORD );
extern   _SOS_START_SAMPLE far * _sMIDIDIGIStartSample[][ _MAX_INS ];
extern   _HMI_INS_FILE_HEADER far * _sMIDIDIGIInsFileHeader[];
extern   WORD _wMIDIDIGIDriverHandle[];
extern   WORD _wMIDIDIGIDriverInitialized[];
extern   WORD _wMIDIDIGITimerEventHandle[];
extern   WORD _wMIDIDIGIDriverInitMIDI[];
extern   WORD _wMIDIDIGIVelocitySensing[];
extern   BYTE _szMIDIDIGIInsFileID[];

extern   BYTE  _bSOSMIDIMasterVolume;
extern   BYTE  _bSOSMIDIDeviceChannelVolume[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIMT32SendData;

extern   LPSTR lpFake;
extern   WORD  wFake;

extern   _NDMF_TRACK_HEADER _huge *_lpSOSMIDITrackHeaders[][ _SOS_MIDI_MAX_TRACKS ];
extern   BYTE  _bSOSMIDIChannelRemap[][ _SOS_MIDI_MAX_SONGS ][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIChannelPriority[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIOwnerChannel[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIOwnerSong[][ _SOS_MIDI_MAX_CHANNELS ];
extern   _SOS_MIDI_CHANNEL_DATA _sSOSMIDIChannelData[][ _SOS_MIDI_MAX_CHANNELS ][ _SOS_MIDI_MAX_LEVELS ];
extern   BYTE  _bSOSMIDIChannelDataIndex[][ _SOS_MIDI_MAX_SONGS ][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIData[];
extern   BYTE  _bSOSMIDIData1[];
extern   BYTE  _bSOSMIDIDeviceLowPriority[];
extern   WORD  _wSOSMIDIChannelStealing;
extern   BYTE  _bSOSMIDIDeviceChannelActive[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIDeviceChannelAvailable[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDISongHandle;
extern   BYTE  _szMIDIMIDIFileID[];
extern   BYTE  _pSOSMIDIDriverPath[];
extern   BYTE  _pSOSMIDITempDriverPath[];
extern   WORD  sosMIDIData_Start;
extern   WORD  sosMIDIData_End;
extern   WORD  ( cdecl far *_lpSOSMIDIAWEDrvFunctions[5] )( LPSTR, WORD, WORD );
extern   WORD  _wSOSGravisTimerHandle;
extern   WORD  _wSOSMIDISongVolume[];

extern   _SOS_BRANCH_POINT far * _lpMIDIBranchData[][ _SOS_MIDI_MAX_TRACKS ];
extern   WORD ( far *_lpSOSMIDIBranchCallback[] )( WORD, BYTE, BYTE );
extern   WORD ( far *_lpSOSMIDILoopCallback[] )( WORD, BYTE, BYTE, BYTE );
extern   WORD ( far *_lpSOSMIDITriggerCallback[][ 127 ] )( WORD, BYTE, BYTE );
extern   BYTE _bSOSMIDIBranchOccurred;

extern   WORD  _wSOSMIDIVolumeFadeDirection[];
extern   DWORD _dwSOSMIDIVolumeFadeFraction[];
extern   DWORD _dwSOSMIDIVolumeFadeVolume[];
extern   WORD  _wSOSMIDIVolumeFadeTicks[];
extern   BYTE  _bSOSMIDIHandleVolumeFade[];
extern   WORD  _wSOSDIGIMIDIHandle[];

extern   _SOS_MIDI_DIGI_CHANNEL _sMIDIDIGIChannel[];

extern   WORD ( cdecl far *_lpMIDIWAVEDrvFunctions[] )( LPSTR, WORD, WORD );
extern   WORD  _wSOSMIDIChannelMuted[][ _SOS_MIDI_MAX_CHANNELS ];

extern   BYTE  _szPLYMIDIBuffer[];
extern   WORD  _wPLYMIDIBufferIndex;
extern   WORD  _wSOSMIDIDriverSize[];

#pragma pack()

#endif


//
// #include "sosmfnct.h"
//
/****************************************************************************

   File              : sosmfnct.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
			   Copyright(c) 1993,1994 Human Machine Interfaces 
							All Rights Reserved
****************************************************************************/

#ifndef  _SOS_MIDI_FUNCTIONS
#define  _SOS_MIDI_FUNCTIONS

#pragma pack(4)

VOID interrupt far sosMIDITimerHandler (  VOID  );
WORD  sosMIDILockMemory                (  VOID  );
WORD  sosMIDIUnLockMemory              (  VOID  );
WORD  sosMIDIGetDeviceCaps             (  WORD, LPSOSMIDIDEVICECAPS  );
WORD  sosMIDIInitSystem                (  LPSTR, WORD  );
WORD  sosMIDIUnInitSystem              (  VOID  );
WORD  sosMIDIInitDriver                (  WORD, _SOS_MIDI_HARDWARE far *,
										 _SOS_MIDI_INIT_DRIVER far *, WORD far *  );
WORD  sosMIDIUnInitDriver              (  WORD, BOOL  );
WORD  sosMIDILoadDriver                (  WORD, WORD, LPSTR far *, LPSTR far *, PSTR, PSTR, WORD * );
WORD  sosMIDIUnLoadDriver              (  WORD  );
WORD  sosMIDIInitSong                  (  _SOS_MIDI_INIT_SONG far *,
										  _SOS_MIDI_TRACK_DEVICE far *,
										  WORD far * );
WORD  sosMIDIUnInitSong                (  WORD  );
WORD  sosMIDIResetSong                 (  WORD, _SOS_MIDI_INIT_SONG far *  );
WORD  sosMIDIStartSong                 (  WORD  );  
WORD  sosMIDIStopSong                  (  WORD  );  
WORD  sosMIDIPauseSong                 (  WORD, WORD  );
WORD  sosMIDIMuteSong                  (  WORD  );
WORD  sosMIDIUnMuteSong                (  WORD  );
WORD  sosMIDIResumeSong                (  WORD  );
BOOL  sosMIDISongDone                  (  WORD  );  
WORD  sosMIDISongAlterTempo            (  WORD, WORD  );  
WORD  sosMIDIGetDeltaTime              (  LPSTR, DWORD far *  );
WORD  sosMIDISongGetTimeToPlay         (  WORD  );  
BYTE _huge * sosMIDINormalizePtr       (  BYTE _huge *  );
WORD  sosMIDISetInsData                (  WORD, LPSTR, WORD  );
WORD  sosMIDIResetDriver               (  WORD  );
BOOL  sosMIDIHandleMIDIData            (  WORD, LPSTR, WORD, WORD  );
WORD  sosMIDISendMIDIData              (  WORD, LPSTR, WORD  );
// NEW
VOID  sosMIDISetTrackState             (  WORD, WORD, WORD  );
// END

// compiled in drivers function interface
LPSTR digiGetCallTable                 (  VOID  );
LPSTR callbackGetCallTable             (  VOID  );
LPSTR aweGetCallTable                  (  VOID  );

WORD cdecl far callbackSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far callbackInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far callbackUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far callbackReset                (  LPSTR, WORD, WORD  );
WORD cdecl far callbackSetInstrumentData    (  LPSTR, WORD, WORD  );

WORD cdecl far aweSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far aweInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far aweUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far aweReset                (  LPSTR, WORD, WORD  );
WORD cdecl far aweSetInstrumentData    (  LPSTR, WORD, WORD  );

// function prototypes
WORD cdecl far digiSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far digiInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far digiUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far digiReset                (  LPSTR, WORD, WORD  );
WORD cdecl far digiSetInstrumentData    (  LPSTR, WORD, WORD  );

LPSTR waveGetCallTable                 (  VOID  );
WORD cdecl far waveSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far waveInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far waveUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far waveReset                (  LPSTR, WORD, WORD  );
WORD cdecl far waveSetInstrumentData    (  LPSTR, WORD, WORD  );
VOID cdecl far waveSampleCallback(  WORD, WORD, WORD  );

VOID        digiQueueInit           (  WORD, WORD  );
VOID        digiQueueUnInit         (  WORD  );
WORD        digiQueueAddItem        (  WORD, WORD, WORD, WORD, WORD );
WORD        digiQueueGetItem        (  WORD, WORD  );
WORD        digiQueueGetItemWAVE    (  WORD  );
WORD        digiQueueDeleteItem     (  WORD, WORD  );
WORD        digiQueueDeleteItemWAVE (  WORD, WORD  );
WORD        digiQueueDeleteItemMIDI (  WORD, WORD, WORD  );
WORD        digiQueueFindItemMIDI   (  WORD, WORD, WORD  );

// function prototypes
VOID cdecl far digiSampleCallback(  WORD, WORD, WORD  );

WORD        sosMIDIRegisterBranchFunction (  WORD, WORD ( far * )( WORD, BYTE, BYTE )  );
WORD        sosMIDIRegisterLoopFunction   (  WORD, WORD ( far * )( WORD, BYTE, BYTE, BYTE )  );
WORD        sosMIDIRegisterTriggerFunction(  WORD, BYTE, WORD ( far * )( WORD, BYTE, BYTE ) );
WORD        sosMIDIBranchToTrackLocation  (  WORD, BYTE, BYTE  );
WORD        sosMIDIBranchToSongLocation   (  WORD, BYTE  );

#ifdef __cplusplus
extern "C" {
#endif

extern   void  cdecl sosMIDIDRVGetCapsInfo( LPSTR, LPSTR, _SOS_MIDI_CAPABILITIES far * );
extern   void  cdecl sosMIDIDRVGetCapsPtr ( LPSTR, LPSTR, _SOS_MIDI_CAPABILITIES far * );
extern   void  cdecl sosMIDIDRVGetFuncsPtr( LPSTR, LPSTR, LPSTR );
extern   LPSTR cdecl sosMIDIDRVSpecialFunction( LPSTR, LPSTR, WORD );
extern   WORD cdecl xgetES( void );

#ifdef __cplusplus
}
#endif 

BOOL sosMIDIResetChannelStealing (  WORD  );
WORD sosMIDIEnableChannelStealing(  WORD  );
VOID far sosMIDISongHandler( VOID );

WORD sosMIDISetMT32InsData       (  WORD, LPSTR, WORD  );
WORD sosMIDISetMasterVolume      (  BYTE  );
VOID far sosMIDIMT32Timer        (  VOID  );

WORD sosMIDISetSongVolume        (  WORD, BYTE  );
WORD        sosMIDIFadeSong            (  WORD, WORD, WORD, BYTE, BYTE, WORD  );       

// functions for memory locking
VOID  sosMIDICaps_Start( VOID );
VOID  sosMIDICaps_End( VOID );
VOID  sosMIDICbck_Start( VOID );
VOID  sosMIDICbck_End( VOID );
VOID  sosMIDIDigi_Start( VOID );
VOID  sosMIDIDigi_End( VOID );
VOID  sosMIDIDone_Start( VOID );
VOID  sosMIDIDone_End( VOID );
VOID  sosMIDIDq_Start( VOID );
VOID  sosMIDIDq_End( VOID );
VOID  sosMIDIInit_Start( VOID );
VOID  sosMIDIInit_End( VOID );
VOID  sosMIDIIns_Start( VOID );
VOID  sosMIDIIns_End( VOID );
VOID  sosMIDILoad_Start( VOID );
VOID  sosMIDILoad_End( VOID );
VOID  sosMIDIPause_Start( VOID );
VOID  sosMIDIPause_End( VOID );
VOID  sosMIDIPtr_Start( VOID );
VOID  sosMIDIPtr_End( VOID );
VOID  sosMIDISong_Start( VOID );
VOID  sosMIDISong_End( VOID );
VOID  sosMIDISt_Start( VOID );
VOID  sosMIDISt_End( VOID );
VOID  sosMIDITmpo_Start( VOID );
VOID  sosMIDITmpo_End( VOID );
VOID  sosMIDITmr_Start( VOID );
VOID  sosMIDITmr_End( VOID );

void    StringOut( BYTE X, BYTE Y, BYTE * String, BYTE Color );

#pragma pack()

#endif


#endif


