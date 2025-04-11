
#ifndef __BASE_TYPE_DEFINE_
#define __BASE_TYPE_DEFINE_

//#include <ASSERT.h>
#include <string.h>
#include <stdio.h>
#include <typeinfo>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <algorithm>
// inet_ntoa 需要
#include <arpa/inet.h>

/************************************************************************/
/* 基本类型, 不能修改                                                                     */
/************************************************************************/
typedef signed char  tchar, tint8;/////8bit signed
typedef unsigned char  tbyte, tuchar, tuint8; ///////8bit unsigned
typedef short          tint16; ////16bit  signed
typedef unsigned short  tuint16; ////16bit  unsigned
typedef int     tint32; /////32 bit  signed
typedef unsigned int  tuint32; /////32 bit unsigned
typedef long long    tint64; //////64bit  signed
typedef unsigned long long   tuint64; ////64bit  unsigned


#if defined(OS_IS_64BIT)
    typedef tuint64     tuint_ptr;
    typedef tint64      tint_ptr;
    
    #define WINAPI
#else
    typedef tuint32     tuint_ptr;
    typedef tint32      tint_ptr;
    
    #define WINAPI      __attribute__((stdcall))
#endif /////


/************************************************************************************
 *扩展类型,  不能随便添加
************************************************************************************/
typedef tuint_ptr            HANDLE;
typedef void *               HWND;
typedef void               * LPVOID, *HDC, VOID;
typedef tuint64              ULONGLONG;
typedef tint64               LONGLONG;
typedef tuint32              COLORREF;
typedef tuint8               BYTE;


/************************************************************************/
/*                                                                      */
/************************************************************************/
#define DEBUG_NEW  new

#ifndef ERROR_SUCCESS
#define ERROR_SUCCESS 0L
#endif

#define         FALSE          0
#define         TRUE           1

#define         IN
#define         OUT


#define        MAXWORD      0xffff
#define        WM_USER      0x2000

#define        INVALID_HANDLE_VALUE   -1
#define        INVALID_SOCKET   (tint32)(~0)

#define   stricmp   strcasecmp
#define		_atoi64		atoll
#define _strtoui64 strtoull

/* _countof helper */
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
template <typename _CountofType, size_t _SizeOfArray>
char (*__countof_helper(_CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) sizeof(*__countof_helper(_Array))
}
#endif
#endif


#define INFINITE 0xFFFFFFFF
	//Signaled
#define WAIT_OBJECT_0	0x00000000L
#define WAIT_ABANDONED	0x00000080L
#define WAIT_TIMEOUT	0x00000102L
#define WAIT_FAILED ((tuint32)0xFFFFFFFF)

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((tuint16)((BYTE)(g))<<8))|(((tuint32)(BYTE)(b))<<16)))
#define MAKELONG(a, b)      ((tint32)(((tuint16)(((tuint32)(a)) & 0xffff)) | ((tuint32)((tuint16)(((tuint32)(b)) & 0xffff))) << 16))
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
	((tuint32)(tuint8)(ch0) | ((tuint32)(tuint8)(ch1) << 8) |   \
	((tuint32)(tuint8)(ch2) << 16) | ((tuint32)(tuint8)(ch3) << 24 ))


#define        UNREFERENCED_PARAMETER(P)     \
	{ \
	(P) = (P);\
	}\

//#include <ASSERT.h>
//#define ASSERT(X)      ASSERT(X)


typedef struct tagRECT
{
	tint32    left;
	tint32    top;
	tint32    right;
	tint32    bottom;
} RECT, *PRECT,  *LPRECT;


/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef void* TRHEAD_RETVALUE;

typedef TRHEAD_RETVALUE (*PTHREAD_START_ROUTINE)(
	LPVOID lpThreadParameter
	);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;


/************************************************************************/ 
/*                                                                      */
/************************************************************************/
typedef struct _GUID {
	unsigned int  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[ 8 ];
} GUID;
const GUID GUID_NULL={0,0,0,{0,0,0,0,0,0,0,0}};
typedef const GUID &     REFGUID;
__inline bool operator < (const GUID& guidOne, const GUID& guidOther)
{
	return (memcmp(&guidOne, &guidOther, sizeof(GUID)) < 0);
}

__inline bool operator > (const GUID& guidOne, const GUID& guidOther)
{
	return (memcmp(&guidOne, &guidOther, sizeof(GUID)) > 0);
}

__inline bool operator == (const GUID& guidOne, const GUID& guidOther)
{
	return (memcmp(&guidOne, &guidOther, sizeof(GUID)) == 0);
}

__inline bool operator != (const GUID& guidOne, const GUID& guidOther)
{
	return (memcmp(&guidOne, &guidOther, sizeof(GUID)) != 0);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct _FILETIME {
	tuint32 dwLowDateTime;
	tuint32 dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
const FILETIME ZERO_FILE_TIME={0,0};
__inline bool operator < (FILETIME leftTime, FILETIME rightTime)
{
	ULONGLONG *pLeftTime=(ULONGLONG*)&leftTime;
	ULONGLONG *pRightTime=(ULONGLONG*)&rightTime;
	return ((*pLeftTime) < (*pRightTime));
}

__inline bool operator > (FILETIME leftTime, FILETIME rightTime)
{
	ULONGLONG *pLeftTime=(ULONGLONG*)&leftTime;
	ULONGLONG *pRightTime=(ULONGLONG*)&rightTime;
	return ((*pLeftTime) > (*pRightTime));
}

__inline bool operator == (FILETIME leftTime, FILETIME rightTime)
{
	return ((leftTime.dwHighDateTime== rightTime.dwHighDateTime) && 
		(leftTime.dwLowDateTime==rightTime.dwLowDateTime));
}

__inline bool operator != (FILETIME leftTime, FILETIME rightTime)
{
	return !(leftTime == rightTime);
}

__inline FILETIME & operator += (FILETIME &ftTime, const ULONGLONG &ullTime)
{
    ULONGLONG *pftTime = (ULONGLONG *)(&ftTime);
    *pftTime += ullTime;
    return ftTime;
}

__inline FILETIME & operator -= (FILETIME &ftTime, const ULONGLONG &ullTime)
{
	ULONGLONG *pftTime = (ULONGLONG *)(&ftTime);
	*pftTime -= ullTime;
	return ftTime;
}

__inline LONGLONG operator - (const FILETIME &ftTime1, const FILETIME &ftTime2)
{
    const LONGLONG *pllTime1 = (const LONGLONG *)(&ftTime1);
    const LONGLONG *pllTime2 = (const LONGLONG *)(&ftTime2);

    return *pllTime1 - *pllTime2;
}

////////////////////////////////////////////音视频媒体相关的定义

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

// typedef struct tagBITMAPINFOHEADER{
//     tuint32   biSize;
//     tint32    biWidth;
//     tint32    biHeight;
//     tuint16    biPlanes;
//     tuint16    biBitCount;
//     tuint32   biCompression;
//     tuint32   biSizeImage;
//     tint32    biXPelsPerMeter;
//     tint32    biYPelsPerMeter;
//     tuint32   biClrUsed;
//     tuint32   biClrImportant;
// }BITMAPINFOHEADER,  *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

#pragma pack(push,2)
// typedef struct tagBITMAPFILEHEADER{
//     tuint16 bfType;
//     tuint32 bfSize;
//     tuint16 bfReserved1;
//     tuint16 bfReserved2;
//     tuint32 bfOffBits;
// }BITMAPFILEHEADER, *LPBITMAPFIlEHEADER, *PBITMAPFIlEHEADER;
#pragma pack()


/**************************************************************************
 *
 *
 *                Waveform audio support
 *
 *
**************************************************************************/
#define DECLARE_HANDLE(name) \
    struct name##__ { tint32 unused; }; \
    typedef struct name##__ *name; \


DECLARE_HANDLE(HWAVE);
DECLARE_HANDLE(HWAVEIN);
DECLARE_HANDLE(HWAVEOUT);


/* wave data block header */
typedef struct wavehdr_tag {
    tint8   * lpData;                 /* pointer to locked data buffer */
    tuint32       dwBufferLength;         /* length of data buffer */
    tuint32       dwBytesRecorded;        /* used for input only */
    tuint32   dwUser;                 /* for client's use */
    tuint32       dwFlags;                /* assorted flags (see defines) */
    tuint32       dwLoops;                /* loop control counter */
    struct wavehdr_tag  *lpNext;     /* reserved for driver */
    tuint32   reserved;               /* reserved for driver */
} WAVEHDR, *PWAVEHDR,  *LPWAVEHDR;


#ifndef WAVE_FORMAT_PCM

/* OLD general waveform format structure (information common to all formats) */
typedef struct waveformat_tag {
    tuint16    wFormatTag;        /* format type */
    tuint16    nChannels;         /* number of channels (i.e. mono, stereo, etc.) */
    tuint32   nSamplesPerSec;    /* sample rate */
    tuint32   nAvgBytesPerSec;   /* for buffer estimation */
    tuint16    nBlockAlign;       /* block size of data */
} WAVEFORMAT, *PWAVEFORMAT;

/* flags for wFormatTag field of WAVEFORMAT */
#define WAVE_FORMAT_PCM     1


/* specific waveform format structure for PCM data */
typedef struct pcmwaveformat_tag {
    WAVEFORMAT  wf;
    tuint16        wBitsPerSample;
} PCMWAVEFORMAT, *PPCMWAVEFORMAT;
#endif /* WAVE_FORMAT_PCM */

#define WAVE_FORMAT_DVI_ADPCM 0x0011
#define WAVE_FORMAT_ALAW 0x0006

//extended waveform format structure used for all non-PCM formats. this structure is common to all non-PCM formats.
// typedef struct tWAVEFORMATEX
// {
//     tuint16        wFormatTag;         //format type
//     tuint16        nChannels;          //number of channels (i.e. mono, stereo...)
//     tuint32       nSamplesPerSec;     //sample rate
//     tuint32       nAvgBytesPerSec;    //for buffer estimation
//     tuint16        nBlockAlign;        //block size of data
//     tuint16        wBitsPerSample;     //number of bits per sample of mono data
//     tuint16        cbSize;             //the count in bytes of the size of
//     //extra information (after cbSize)
// } WAVEFORMATEX, *PWAVEFORMATEX;


















#endif   //////////#ifndef __BASE_TYPE_DEFINE_



