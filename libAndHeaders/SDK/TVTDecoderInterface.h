/*********************************************************************
* 版权所有 (C)2017, 深圳市同为视频技术有限公司。
* 
* 文件名称： // TVTDecoderInterface.h
* 内容摘要： // Defines the exported functions for the DLL application.
* 当前版本： // 1.0.0.1
* 完成日期： // 2017年6月13日
* 与对应lib使用
**********************************************************************/
#ifndef _TVTDECODER_INTERFACE_H_
#define _TVTDECODER_INTERFACE_H_

//#ifdef __cplusplus
//extern "C" {
//#endif  // __cplusplus


typedef int				tint32; /////32 bit  signed



#ifdef TVTDECODER_EXPORTS
#define TVTDECODERAPI _declspec(dllexport)
#else
#define TVTDECODERAPI _declspec(dllimport)
#endif // TVT_Dec_EXPORTS
#define CALLMETHOD __stdcall

#define TVTDEC_RET_SUCCEED              (0)
#define TVTDEC_RET_FAIL                 (-1)
#define TVTDEC_RET_INVALID_PARAM        (-101)
#define TVTDEC_RET_SYS_ERROR            (-102)
#define TVTDEC_RET_CODEC_NOT_SUPPORT    (-103)

#define TVTDEC_HANDLE_MIN               (10000)

#define TVTDEC_VCODEC_H264              (1000)     // H264
#define TVTDEC_VCODEC_HEVC              (1001)     // H265
#define TVTDEC_VCODEC_MJPEG             (1002)     // MJPEG
#define TVTDEC_VCODEC_MPEG4             (1003)     // MJPEG
#define TVTDEC_VCODEC_H264_QSV          (2000)     // H264 INTEL 硬解
#define TVTDEC_VCODEC_HEVC_QSV          (2001)     // H265 INTEL 硬解
//#define TVTDEC_VCODEC_MPEG2_QSV       (2002)     // MPEG2 INTEL 硬解
//#define TVTDEC_VCODEC_VC1_QSV         (2003)     // VC1 INTEL 硬解
//#define TVTDEC_VCODEC_VP8_QSV         (2004)     // VP8 INTEL 硬解
#define TVTDEC_VCODEC_H264_CUDA         (2100)     // H264 NVIDIA 硬解
#define TVTDEC_VCODEC_HEVC_CUDA         (2101)     // H265 NVIDIA 硬解
//#define TVTDEC_VCODEC_MPEG2_CUDA      (2102)     // MPEG2 NVIDIA 硬解
//#define TVTDEC_VCODEC_VC1_CUDA        (2103)     // VC1 NVIDIA 硬解
//#define TVTDEC_VCODEC_VP8_CUDA        (2104)     // VP8 NVIDIA 硬解
#define TVTDEC_VCODEC_H264_AUTO         (2200)     // H264 自动
#define TVTDEC_VCODEC_HEVC_AUTO         (2201)     // H265 自动

// 解码后的视频数据格式
#define TVTDEC_PIXFMT_YUV420            0   // 默认

#define FOURCC_H264	    mmioFOURCC('H','2','6','4')
#define FOURCC_H265     mmioFOURCC('H','E','V','C')
#define FOURCC_MJPEG    mmioFOURCC('M','J','P','G')

/* yuyu		4:2:2 16bit, y-u-y-v, packed*/
#define FOURCC_YUYV	mmioFOURCC('Y','U','Y','V')
#define FOURCC_YUY2	mmioFOURCC('Y','U','Y','2')
/* yvyu		4:2:2 16bit, y-v-y-u, packed*/
#define FOURCC_YVYU	mmioFOURCC('Y','V','Y','U')
/* uyvy		4:2:2 16bit, u-y-v-y, packed */
#define FOURCC_UYVY	mmioFOURCC('U','Y','V','Y')
/* i420		y-u-v, planar */
#define FOURCC_I420	mmioFOURCC('I','4','2','0')
#define FOURCC_IYUV	mmioFOURCC('I','Y','U','V')
/* yv12		y-v-u, planar */
#define FOURCC_YV12	mmioFOURCC('Y','V','1','2')

// 结构体定义，1字节对齐
#pragma pack(push,1)
typedef struct tagVIDEOFORMAT
{
    tint32 iWidth;
    tint32 iHeight;
    tint32 iPixFmt;
} VIDEOFORMAT, *PVIDEOFORMAT;
#pragma pack(pop)

typedef enum tagHARDWARE_ACCEL_ENUM
{
    ENUM_HARDWARE_ACCEL_AUTO = 1,    //自动
    ENUM_HARDWARE_ACCEL_NVIDIA,      //英伟达
    ENUM_HARDWARE_ACCEL_INTEL,       //英特尔
    ENUM_HARDWARE_ACCEL_SOFTWARE     //软解
}HARDWARE_ACCEL_ENUM;

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Init();
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Cleanup();

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_CreateDecoder(tint32 &iHandle, tint32 iCodec);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_DestroyDecoder(tint32 iHandle);

// TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetHWMode(HARDWARE_ACCEL_ENUM enumHWAccel);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_DecodeVideo(tint32 iHandle, BYTE *pInData, tint32 iInLen, BYTE *pOutData, tint32 &iOutLen);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_GetVideoFormat(tint32 iHandle, VIDEOFORMAT &stSrcVFmt, VIDEOFORMAT &stDstVFmt);
TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_SetVideoFormat(tint32 iHandle, VIDEOFORMAT &stSrcVFmt, VIDEOFORMAT &stDstVFmt);

TVTDECODERAPI tint32 CALLMETHOD TVT_Dec_Capture(tint32 iHandle, const char *sFileName);

//#ifdef __cplusplus
//}
//#endif  // __cplusplus

#endif  // _TVTDECODER_INTERFACE_H_
