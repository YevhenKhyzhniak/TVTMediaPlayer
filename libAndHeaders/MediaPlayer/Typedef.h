//∂®“Â ˝æ›¿‡–Õ£¨Œ™øÁ∆ΩÃ®ø™∑¢∑˛ŒÒ∑˛ŒÒ
#ifndef _DVRTYPEDEFINE_
#define _DVRTYPEDEFINE_

#ifdef WIN32 ////////////////////»Áπ˚ «Windows∆ΩÃ®
#include "stdafx.h"

//∂®“ÂPACKED ÷˜“™”√”⁄Ω‚æˆ‘⁄WindowsΩ‚æˆ∂‘∆Ê“ª∞„ π”√#pragma pack(n)∂¯Linuxœ¬“ª∞„ π”√__attribute__((packed))
//‘⁄¥ÀΩ·ππÃÂ“™–¥»ÎŒƒº˛ªÚ’ﬂ‘⁄øÁ∆ΩÃ®÷Æº‰∑√Œ  ±≤≈–Ë“™“‘œ¬∂®“Â£¨◊¢“‚__attribute__((packed))÷ª”√”⁄µ•◊÷Ω⁄∂‘∆Î
#define PACKED
//#define PACK(n)    #pragma pack(n)
//#define PACKEND    #pragma pack()

#else ////////////////////linux∆ΩÃ®

#define PACKED __attribute__((packed))
//#define PACK(n)
//#define PACKEND

typedef unsigned int       DWORD;
typedef unsigned int       ULONG;

//typedef int                LONG;
typedef unsigned long long  ULONGLONG;
//typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef int                 INT;
typedef unsigned int        UINT;
typedef long long           LONGLONG;

//“‘œ¬ «Œ™¡À«˝∂Øø‚µƒ∂®“Â π”√∑Ω±„
typedef    signed char            SBYTE;

#include <sys/time.h>
typedef struct timeval             DVRDATETIME;  //zld 2016/6/7

enum
{
    VIDEO_COMPRESS_FORMAT_H264=0,
    VIDEO_COMPRESS_FORMAT_XVID,
    VIDEO_COMPRESS_FORMAT_H265,
    VIDEO_COMPRESS_FORMAT_OTHER,
    VIDEO_COMPRESS_FORMAT_H264_EX, //zld2016/3/23 其实就是VIDEO_COMPRESS_FORMAT_H264只是保存录像时做个特殊处理
    VIDEO_COMPRESS_FORMAT_NONE = 0xFFFF
};


typedef enum view_mode
{
    VIEW_MODE_NONE,
    VIEW_MODE_LIVE,
    VIEW_MODE_IMAGE,
    VIEW_MODE_PLAYBACK,
    VIEW_MODE_CONFIGURE,
    VIEW_MODE_INFORMATION,
    VIEW_MODE_SERVERLIST,
    VIEW_MODE_LOGIN,//未用到
    VIEW_MODE_HELP,
    VIEW_MODE_BAR_CODE,//未用到
    VIEW_MODE_PUSH_LOGIN,//未用到
    VIEW_MODE_PUSH_JUMP,//未用到
    VIEW_MODE_PUSH_SERVERLIST,//未用到
    VIEW_MODE_LOCAL_CONFIG,
    VIEW_MODE_GESTURE_PSW,
    VIEW_MODE_ABOUTUI,
    VIEW_MODE_PUSH_CONFIGURE,
    VIEW_MODE_PUSH_MESSAGE,
    VIEW_MODE_ADD_FACE,
    VIEW_MODE_FACE_SEARCH,
    VIEW_MODE_USER_INFO,
    VIEW_MODE_ACOUNT_LOGIN,
    VIEW_MODE_ACOUNT_DEVICEMANAGER,
    VIEW_MODE_VAS_VIEW,
    VIEW_MODE_CLOUD_STORAGE_PLAY,
    VIEW_MODE_VIDEO_PASSWORD_INFO,
    VIEW_MODE_UNKNOWN
}VIEW_MODE;

enum
{
    PLAYBACK_STATUS_PLAY,
    PLAYBACK_STATUS_PAUSE,
    PLAYBACK_STATUS_STOP,
    PLAYBACK_STATUS_FF,
    PLAYBACK_STATUS_REW,
    PLAYBACK_STATUS_STEP_FRAME,  //单帧播放
    PLAYBACK_STATUS_END,    //播放结束
    PLAYBACK_STATUS_NO_DATA,    //没有数据
};

#endif ////////#ifdef WIN32 //»Áπ˚ «Windows∆ΩÃ®

#endif ////////#ifndef _DVRTYPEDEFINE_





