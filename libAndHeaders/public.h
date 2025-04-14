//
//  public.h
//  DVR_NET_SDK_ios
//
//  Created by 123 on 16/12/7.
//  Copyright © 2016年 wei.wang. All rights reserved.
//

#ifndef public_h
#define public_h

#define AUDIO_FORMAT_G711   6
#define AUDIO_FORMAT_ADPCM	17

enum enPlat_CodecType{
    CODEC_VIDEO_H264=1,    //标准H264
    CODEC_VIDEO_H265,      //标准H265
    CODEC_VIDEO_MJPEG,     //标准MJPEG
    CODEC_VIDEO_HIK,       //HIK流
    
    CODEC_AUDIO_PCM = 100, //标准PCM
    CODEC_AUDIO_G711a,  //标准G711 A
    CODEC_AUDIO_G711u,  //标准G711 U
    CODEC_AUDIO_G722,   //标准G722
    CODEC_AUDIO_G729,   //标准G729
    CODEC_AUDIO_MP3,    //mp3
    CODEC_AUDIO_AAC,    //aac
    CODEC_AUDIO_HI_ADPCM, //海思Adpcm
    CODEC_AUDIO_HI_G711a, //海思G711a
    CODEC_AUDIO_HI_G711u, //海思G711U
};

typedef struct _video_frame_header_info
{
    int width;
    int height;
    int videoEncodeType;
}FRAME_HEADER_INFO;

enum StreamType
{
    STREAMTYPE_LIVE = 0x01,
    STREAMTYPE_PLAYBACK = 0x02
};

enum Resolution_StreamType
{
    MAIN_STREAM = 0,
    SUB_STREAM,
    THIRD_STREAM,
};

#endif /* public_h */
