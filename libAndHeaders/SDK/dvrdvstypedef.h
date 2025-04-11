/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       : YSW
** Date         : 2010-11-19
** Name         : dvrdvstypedef.h
** Version      : 1.0
** Description  :	描述DVR/DVS相关的一些基本特性
** Modify Record:
1:创建
***********************************************************************/
#ifndef __DVR_DVS_TYPEDEF_H__
#define __DVR_DVS_TYPEDEF_H__

#ifdef WIN32 ////////////////////如果是Windows平台
#include "stdafx.h"
typedef DWORD				THREAD_ID;
typedef long                POINTERHANDLE;

//定义PACKED 主要用于解决在Windows解决对奇一般使用#pragma pack(n)而Linux下一般使用__attribute__((packed))
//在此结构体要写入文件或者在跨平台之间访问时才需要以下定义，注意__attribute__((packed))只用于单字节对齐
#define PACKED
#else ////////////////////linux平台
#include <sys/types.h>
#include <stddef.h>

#define PACKED __attribute__((packed))

typedef pid_t				THREAD_ID;
typedef unsigned int       DWORD, *LPDWORD;
typedef unsigned int       ULONG;
//大概检查了内部LONG的使用，发现很多地方将指针直接转给LONG,且某些地方LONG值可能为负值，最稳妥的定义成long long
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef int                LONG;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               LONG;
    #else
        typedef long                LONG;
    #endif
#endif

//手机端handle用的long long，win，linux端用的LONG。现为了统一一套代码且不影响客户，定义POINTERHANDLE来兼容
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef long long                POINTERHANDLE;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               POINTERHANDLE;
    #else
        typedef long                POINTERHANDLE;
    #endif
#endif


typedef unsigned long long  ULONGLONG;


//zld 2016/10/22
#ifdef __ENVIRONMENT_IOS__

#if (TARGET_OS_IPHONE && __LP64__)  ||  TARGET_OS_WATCH
#define OBJC_BOOL_IS_BOOL 1
typedef bool BOOL;
#else
#define OBJC_BOOL_IS_CHAR 1
typedef signed char BOOL;  //wyf
//typedef bool BOOL;
#endif

#else
typedef bool                BOOL;
#endif

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef int                 INT;
typedef unsigned int        UINT;
typedef long long           LONGLONG; 
typedef void				*HWND, *HDC, *LPVOID;

#define CALLBACK
#define FALSE				false
#define TRUE				true
//#define NULL				0
#endif //WIN32

typedef enum _dd_system_status_
{
	DD_SYSTEM_RUNING,		//运行中
	DD_SYSTEM_REBOOT,		//系统重启
	DD_SYSTEM_REDRAW,		//重新初始化界面
	DD_SYSTEM_LOGOUT,		//需要退出到登录界面
	DD_SYSTEM_EXIT			//退出系统
}DD_SYSTEM_STATUS;

//视频制式定义
typedef enum _dd_video_format_
{
	DD_VIDEO_FORMAT_NTSC	= 0x01,
	DD_VIDEO_FORMAT_PAL		= 0x02
}DD_VIDEO_FORMAT;

typedef enum _dd_frame_type_
{
	DD_FRAME_TYPE_NONE				= 0x00,//空类型数据帧
	DD_FRAME_TYPE_VIDEO				= 0x01,//视频数据帧
	DD_FRAME_TYPE_AUDIO				= 0x02,//音频数据帧
	DD_FRAME_TYPE_TALK_AUDIO		= 0x03,//对讲音频数据帧
	DD_FRAME_TYPE_JPEG				= 0x04,//JPEG图片流数据帧

	DD_FRAME_TYPE_VIDEO_FORMAT		= 0x05,//视频格式帧
	DD_FRAME_TYPE_AUDIO_FORMAT		= 0x06,//音频格式帧
	DD_FRAME_TYPE_TALK_AUDIO_FORMAT	= 0x07,//对讲音频格式帧

	DD_FRAME_TYPE_RESV1				= 0x08,
	DD_FRAME_TYPE_RESV2				= 0x09,

	DD_FRAME_TYPE_END				= 0x0a,
}DD_FRAME_TYPE;

typedef enum _dd_frame_attrib_
{
	DD_PLAY_FRAME_NO_SHOW			= 0x01,		//此帧不显示
	DD_PLAY_FRAME_SHOW				= 0x02,		//此帧可显示
	DD_PLAY_FRAME_ALL_END			= 0x04,		//数据读取结束了，后面再没有数据
	DD_PLAY_FRAME_SEC_END			= 0x08,		//此事件段结束了
	DD_PLAY_FRAME_NO_TIME_STAMP		= 0x10,		//此帧数据有时间戳，抓图的时候注意要屏蔽打时间的功能
	DD_PLAY_FRAME_FF				= 0x20,		//当前帧用于快进

	DD_LIVE_FRAME_FIRST_STREAM		= 0x40,		//此帧为现场主码流
	DD_LIVE_FRAME_SECOND_STREAM		= 0x80,		//此帧为现场子码流
	DD_LIVE_FRAME_JPEG				= 0x100,	//此帧为JPEG图片
	DD_LIVE_FRAME_TALK				= 0x200,		//此帧为对讲语音数据
    DD_LIVE_FRAME_THIRD_STREAM		= 0x400,		//此帧为现场第三码流
    DD_LIVE_FRAME_FOURTH_STREAM		= 0x800,		//此帧为现场第四码流
}DD_FRAME_ATTRIB;

//按位保存。最多不能超过32个
typedef enum _dd_video_size_
{
	DD_VIDEO_SIZE_QCIF	= 0x0001,	//QCIF
	DD_VIDEO_SIZE_CIF	= 0x0002,	//CIF
	DD_VIDEO_SIZE_HD1	= 0x0004,	//HD1
	DD_VIDEO_SIZE_D1	= 0x0008,	//D1

	DD_VIDEO_SIZE_QVGA	= 0x0010,	//QVGA
	DD_VIDEO_SIZE_VGA	= 0x0020,	//VGA
	DD_VIDEO_SIZE_XVGA	= 0x0040,	//XVGA
	DD_VIDEO_SIZE_QQVGA	= 0x0080,	//QQVGA

	DD_VIDEO_SIZE_480P	= 0x0100,	//480P
	DD_VIDEO_SIZE_720P	= 0x0200,	//720P
	DD_VIDEO_SIZE_1080P	= 0x0400,	//1080P
	DD_VIDEO_SIZE_960H  = 0x0800,   //960H

	DD_VIDEO_SIZE_960P   = 0x01000,	//(1280 X 960)
	DD_VIDEO_SIZE_SXGA   = 0x02000,	//(1280 X 1024)
	DD_VIDEO_SIZE_3M     = 0x04000,	//(2048 X 1536)

	DD_VIDEO_SIZE_16_9_3M     = 0x10000,	//(2304 X 1296)
	DD_VIDEO_SIZE_2K          = 0x20000,	//(2560 X 1440)
	DD_VIDEO_SIZE_HDLITE      = 0x40000,	//(960 X 1080)
}DD_VIDEO_SIZE;

//按位保存，最多只能为32个。
typedef enum _dd_video_encode_mode_
{
	DD_VIDEO_ENCODE_MODE_VBR	=	0x01,	//变码流
	DD_VIDEO_ENCODE_MODE_CBR	=	0x02	//固定码流
}DD_VIDEO_ENCODE_MODE;

typedef enum _dd_video_encode_format_
{
    DD_VIDEO_ENCODE_FORMAT_H264	=	0x0,
    DD_VIDEO_ENCODE_FORMAT_H265	=	0x01,
    DD_VIDEO_ENCODE_FORMAT_MJPEG=	0x02,
    DD_VIDEO_ENCODE_FORMAT_H264PLUS=	0x03,
    DD_VIDEO_ENCODE_FORMAT_H265PLUS=	0x04,
}DD_VIDEO_ENCODE_FORMAT;

typedef enum _dd_image_quality_
{
	DD_IMAGE_QUALITY_LOWEST		= 0x01,
	DD_IMAGE_QUALITY_LOWER		= 0x02,
	DD_IMAGE_QUALITY_LOW		= 0x03,
	DD_IMAGE_QUALITY_MEDIUM		= 0x04,
	DD_IMAGE_QUALITY_HEIGHTER	= 0x05,
	DD_IMAGE_QUALITY_HEIGHTEST	= 0x06
}DD_IMAGE_QUALITY;

//VGA分辨率，既可以用于保存也可以用于支持功能参数,'
//注意：要按位表示
typedef enum _dd_vga_resolution_
{
	DD_VGA_640X480		= 0x0001,
	DD_VGA_720X480		= 0x0002,
	DD_VGA_720X576		= 0x0004,
	DD_VGA_800X600		= 0x0008,
	DD_VGA_1024X768		= 0x0010,
	DD_VGA_1280X960		= 0x0020,
	DD_VGA_1280X1024	= 0x0040,
	DD_VGA_1920X1080	= 0x0080,
	DD_VGA_320X240		= 0x0100,
	DD_VGA_352X240		= 0x0200,
	DD_VGA_480X240		= 0x0400,
	DD_VGA_704X480		= 0x0800,
	DD_VGA_704X576		= 0x1000,
	DD_VGA_960X480		= 0x2000,
	DD_VGA_960X576		= 0x4000,
	DD_VGA_960X1080		= 0x8000,
	DD_VGA_1280X720		= 0x00010000,
	DD_VGA_1600X1200	= 0x00020000,
	DD_VGA_1920X1536	= 0x00040000,
	DD_VGA_2048X1536	= 0x00080000,
	DD_VGA_2304X1296	= 0x00100000,
	DD_VGA_2560X1440	= 0x00200000,
	DD_VGA_2592X1520	= 0x00400000,
	DD_VGA_2592X1944	= 0x00800000,
	DD_VGA_3840X2160	= 0x01000000,
}DD_VGA_RESOLUTION;

//显示年月日的模式
typedef enum _dd_date_mode_
{
	DD_DATE_MODE_YMD	= 0x01,		//年月日模式
	DD_DATE_MODE_MDY	= 0x02,		//月日年模式
	DD_DATE_MODE_DMY	= 0x03		//日月年模式
}DD_DATE_MODE;

typedef enum _dd_time_zone_name_
{
	DD_TIME_ZONE_GMT_D12	= 0,
	DD_TIME_ZONE_GMT_D11,
	DD_TIME_ZONE_GMT_D10,
	DD_TIME_ZONE_GMT_D9,
	DD_TIME_ZONE_GMT_D8,
	DD_TIME_ZONE_GMT_D7,
	DD_TIME_ZONE_GMT_D6,
	DD_TIME_ZONE_GMT_D5,
	DD_TIME_ZONE_GMT_D4_30,
	DD_TIME_ZONE_GMT_D4,
	DD_TIME_ZONE_GMT_D3_30,
	DD_TIME_ZONE_GMT_D3,
	DD_TIME_ZONE_GMT_D2,
	DD_TIME_ZONE_GMT_D1,
	DD_TIME_ZONE_GMT,
	DD_TIME_ZONE_GMT_A1,
	DD_TIME_ZONE_GMT_A2,
	DD_TIME_ZONE_GMT_A3,
	DD_TIME_ZONE_GMT_A3_30,
	DD_TIME_ZONE_GMT_A4,
	DD_TIME_ZONE_GMT_A4_30,
	DD_TIME_ZONE_GMT_A5,
	DD_TIME_ZONE_GMT_A5_30,
	DD_TIME_ZONE_GMT_A5_45,
	DD_TIME_ZONE_GMT_A6,
	DD_TIME_ZONE_GMT_A6_30,
	DD_TIME_ZONE_GMT_A7,
	DD_TIME_ZONE_GMT_A8,
	DD_TIME_ZONE_GMT_A9,	
	DD_TIME_ZONE_GMT_A9_30,
	DD_TIME_ZONE_GMT_A10,
	DD_TIME_ZONE_GMT_A11,
	DD_TIME_ZONE_GMT_A12,
	DD_TIME_ZONE_GMT_A13,
	DD_TIME_ZONE_NUM,
}DD_TIME_ZOME_NAME;

//三级用户权限，每级用户具有默认权限，但是可以向下调节具体权限（不能向上调节）。
typedef enum _dd_user_group_
{
	DD_USER_GROUP_NONE		= 0x00,	//
	DD_USER_GROUP_ADMIN		= 0x01,	//管理员，拥有所有的权限
	DD_USER_GROUP_ADVANCE	= 0x02,	//高级用户，默认具有：基本、录像、配置、回放、备份、数据管理、磁盘管理，云台控制，远程登录，及全通道权限
	DD_USER_GROUP_NORMAL	= 0x04	//一般用户，默认具有：基本、录像、回放、备份、云台控制、远程登录，及全通道权限
}DD_USER_GROUP;
typedef enum _dd_operate_type_
{
	DD_OPERATE_ADD = 0x01,
	DD_OPERATE_EDIT = 0x02,
	DD_OPERATE_DELETE = 0x03,
}DD_OPERATE_TYPE;

typedef enum _dd_record_type_
{
	DD_RECORD_TYPE_NONE		= 0x0000,			//无录像类型

	DD_RECORD_TYPE_MANUAL	= 0x0001,			//手动录像
	DD_RECORD_TYPE_SCHEDULE	= 0x0002,			//定时录像
	DD_RECORD_TYPE_MOTION	= 0x0004,			//移动侦测录像
	DD_RECORD_TYPE_SENSOR	= 0x0008,			//传感器报警录像

	DD_RECORD_TYPE_BEHAVIOR = 0x0010,			//行为分析报警录像
    DD_RECORD_TYPE_SHELTER     = 0x20,		//遮挡报警
    DD_RECORD_TYPE_OVERSPEED   = 0x40,		//超速
    DD_RECORD_TYPE_OVERBOUND   = 0x80,		//越界
    DD_RECORD_TYPE_OSC         = 0x0100,     //物品看护侦测录像
    DD_RECORD_TYPE_AVD         = 0x0200,     //异常侦测
    DD_RECORD_TYPE_TRIPWIRE    = 0x0400,     //越界侦测
    DD_RECORD_TYPE_PERIMETER   = 0x0800,     //区域入侵侦测
    DD_RECORD_TYPE_VFD         = 0x1000,     //人脸识别
    DD_RECORD_TYPE_POS         = 0x2000,     //POS
	DD_RECORD_TYPE_PIR         = 0x4000,	 //C12 IPC的pir报警录像
    DD_RECORD_TYPE_INTELLIGENT = DD_RECORD_TYPE_OSC | DD_RECORD_TYPE_AVD | DD_RECORD_TYPE_TRIPWIRE | DD_RECORD_TYPE_PERIMETER | DD_RECORD_TYPE_VFD,
    DD_RECORD_TYPE_ALL         = 0xFFFFFFFF, //所有的录像类型
}DD_RECORD_TYPE;
typedef enum _dd_record_status_
{
	DD_RECORD_STATUS_OFF = 0,     //停止录像
	DD_RECORD_STATUS_ON,		  //录像中				
	DD_RECORD_STATUS_ABNORMAL 	  //录像异常
}DD_RECORD_STATUS;

typedef enum _dd_behavior_type_
{
	DD_BEHAVIOR_TRAVERSE_PLANE = 0,
	DD_BEHAVIOR_ENTER_AREA,				//进入
	DD_BEHAVIOR_EXIT_AREA,				//
	DD_BEHAVIOR_INTRUSION,
	DD_BEHAVIOR_LOITER,
	DD_BEHAVIOR_LEFT_TAKE,
	DD_BEHAVIOR_PARKING,
	DD_BEHAVIOR_RUN,
	DD_BEHAVIOR_HIGH_DENSITY
}DD_BEHAVIOR_TYPE;

typedef enum _dd_log_content_
{
	DD_LOG_CONTENT_SYSTEM_CTRL		= 0x00000001,
	DD_LOG_CONTENT_CONFIG			= 0x00000002,
	DD_LOG_CONTENT_PLAYBACK			= 0x00000004,
	DD_LOG_CONTENT_BACKUP			= 0x00000008,
	DD_LOG_CONTENT_SEARCH			= 0x00000010,
	DD_LOG_CONTENT_VIEW_INFO		= 0x00000020,
	DD_LOG_CONTENT_EVENT_INFO		= 0x00000040,
	DD_LOG_CONTENT_ERROR_INFO		= 0x00000080
}DD_LOG_CONTENT;

typedef enum _dd_event_type_
{
	DD_EVENT_TYPE_MOTION    = 0x00000001,		//移动侦测
	DD_EVENT_TYPE_SENSOR    = 0x00000002,		//传感器报警
	DD_EVENT_TYPE_V_LOSS    = 0x00000004,		//视频丢失
	DD_EVENT_TYPE_V_COVER   = 0x00000008,		//视频遮挡
}DD_EVENT_TYPE;

typedef enum _dd_log_type_
{
	//系统控制(Control)
	DD_LOG_TYPE_SYSTEM_CTRL		= 0x01000000,
	DD_LOG_TYPE_BOOT,							//系统开机
	DD_LOG_TYPE_SHUTDOWN,						//系统关机
	DD_LOG_TYPE_REBOOT,							//系统重启
	DD_LOG_TYPE_FORMAT_SUCC,					//格式化磁盘成功
	DD_LOG_TYPE_FORMAT_FAIL,					//格式化磁盘失败
	DD_LOG_TYPE_UPGRADE_SUCC,					//升级成功
	DD_LOG_TYPE_UPGRADE_FAIL,					//升级失败
	DD_LOG_TYPE_CLEAR_ALARM,					//清除报警
	DD_LOG_TYPE_OPEN_ALARM,						//开启报警
	DD_LOG_TYPE_MANUAL_START,					//开启手动录像
	DD_LOG_TYPE_MANUAL_STOP,					//停止手动录像
	DD_LOG_TYPE_PTZ_ENTER,						//开始云台控制
	DD_LOG_TYPE_PTZ_CTRL,						//云台操作
	DD_LOG_TYPE_PTZ_EXIT,						//结束云台控制
	DD_LOG_TYPE_AUDIO_CH_CHANGE,				//改变现场音频通道
	DD_LOG_TYPE_VOLUME_ADJUST,					//调节音量
	DD_LOG_TYPE_MUTE_ENABLE,					//开启静音
	DD_LOG_TYPE_MUTE_DISENABLE,					//关闭静音
	DD_LOG_TYPE_DWELL_ENABLE,					//开启轮循
	DD_LOG_TYPE_DWELL_DISENABLE,				//关闭轮循
	DD_LOG_TYPE_LOG_IN,							//登录
	DD_LOG_TYPE_LOG_OFF,						//登出
	DD_LOG_TYPE_CHANGE_TIME,					//修改系统时间
	DD_LOG_TYPE_MANUAL_SNAP_SUCC,				//手动抓图成功
	DD_LOG_TYPE_MANUAL_SNAP_FAIL,				//手动抓图失败

	//系统配置(Setup)
	DD_LOG_TYPE_CONFIG			= 0x02000000,
	DD_LOG_TYPE_CHGE_VIDEO_FORMAT,				//改变视频制式
	DD_LOG_TYPE_CHGE_VGA_RESOLUTION,			//改变显示器分辨率
	DD_LOG_TYPE_CHGE_LANGUAGE,					//调整语言
	DD_LOG_TYPE_CHGE_NET_USER_NUM,				//调整网络用户数目
	DD_LOG_TYPE_CHGE_TIME_ZONE,					//调整时区
	DD_LOG_TYPE_NTP_MANUAL,						//手动网络校时
	DD_LOG_TYPE_NTP_ON,							//开启自动网络校时
	DD_LOG_TYPE_NTP_OFF,						//关闭自动网络校时
	DD_LOG_TYPE_CHGE_NTP_SERVER,				//修改网络时间服务器地址
	DD_LOG_TYPE_CHGE_DST,						//调整夏令时设置
	DD_LOG_TYPE_PASSWD_ON,						//开启操作密码
	DD_LOG_TYPE_PASSWD_OFF,						//关闭操作密码

	DD_LOG_TYPE_CHGE_CAM_NAME,					//调整通道名称
	DD_LOG_TYPE_MODIFY_COLOR,					//调整图像色彩
	DD_LOG_TYPE_CHGE_HOST_MONITOR,				//调整主监视器画面设置
	DD_LOG_TYPE_CHGE_SPOT,						//调整辅助输出画面设置
	DD_LOG_TYPE_CHGE_OSD,						//调整字符叠加设置

	DD_LOG_TYPE_CHGE_LOCAL_ENCODE,				//调整录像流编码参数
	DD_LOG_TYPE_CHGE_REC_VIDEO_SWITCH,			//调整录像开关设置
	DD_LOG_TYPE_CHGE_REC_AUDIO_SWITCH,			//调整录制音频开关设置
	DD_LOG_TYPE_CHGE_REC_REDU_SWITCH,			//调整冗余录像开关设置
	DD_LOG_TYPE_CHGE_REC_PRE_TIME,				//调整景前录像时间
	DD_LOG_TYPE_CHGE_REC_POST_TIME,				//调整景后录像时间
	DD_LOG_TYPE_CHGE_REC_HOLD_TIME,				//调整录像数据过期时间

	DD_LOG_TYPE_CHGE_SCH_SCHEDULE,				//调整定时录像计划
	DD_LOG_TYPE_CHGE_SCH_MOTION,				//调整移动侦测录像计划
	DD_LOG_TYPE_CHGE_SCH_ALARM,					//调整报警录像计划

	DD_LOG_TYPE_CHGE_SENSOR_SWITCH,				//调整报警输入开关设置
	DD_LOG_TYPE_CHGE_SENSOR_TYPE,				//调整报警输入设备类型
	DD_LOG_TYPE_CHGE_SENSOR_TRIGGER,			//调整报警输入处理方式设置
	DD_LOG_TYPE_CHGE_SENSOR_SCH,				//调整报警输入侦测计划

	DD_LOG_TYPE_CHGE_MOTION_SWITCH,				//调整移动侦测开关设置
	DD_LOG_TYPE_CHGE_MOTION_SENS,				//调整移动侦测灵敏度
	DD_LOG_TYPE_CHGE_MOTION_AREA,				//调整移动侦测区域设置
	DD_LOG_TYPE_CHGE_MOTION_TRIGGER,			//调整移动侦测处理方式
	DD_LOG_TYPE_CHGE_MOTION_SCH,				//调整移动侦测计划

	DD_LOG_TYPE_CHGE_VL_TRIGGER,				//调整视频丢失处理方式设置

	DD_LOG_TYPE_CHGE_RELAY_SWITCH,				//调整报警输出开关设置
	DD_LOG_TYPE_CHGE_RELAY_SCH,					//调整报警输出计划

	DD_LOG_TYPE_BUZZER_ON,						//开启声音报警设备
	DD_LOG_TYPE_BUZZER_OFF,						//关闭声音报警设备
	DD_LOG_TYPE_CHGE_BUZZER_SCH,				//调整声音报警计划

	DD_LOG_TYPE_CHGE_HTTP_PORT,					//修改HTTP服务器端口
	DD_LOG_TYPE_CHGE_SER_PORT,					//修改网络服务器端口
	DD_LOG_TYPE_CHGE_IP,						//设置网络地址
	DD_LOG_TYPE_DHCP_SUCC,						//自动获取网络地址成功
	DD_LOG_TYPE_DHCP_FAIL,						//自动获取网络地址失败
	DD_LOG_TYPE_CHGE_PPPOE,						//设置PPPoE
	DD_LOG_TYPE_CHGE_DDNS,						//设置DDNS
	DD_LOG_TYPE_NET_STREAM_CFG,					//调整网络流编码设置

	DD_LOG_TYPE_CHGE_SERIAL,					//调整云台串口设置
	DD_LOG_TYPE_PRESET_MODIFY,					//调整预置点
	DD_LOG_TYPE_CRUISE_MODIFY,					//调整巡航线
	DD_LOG_TYPE_TRACK_MODIFY,					//调整轨迹

	DD_LOG_TYPE_USER_ADD,						//增加用户
	DD_LOG_TYPE_USER_MODIFY,					//调整用户权限
	DD_LOG_TYPE_USER_DELETE,					//删除用户
	DD_LOG_TYPE_CHANGE_PASSWD,					//修改用户密码

	DD_LOG_TYPE_LOAD_DEFAULT,					//恢复默认配置
	DD_LOG_TYPE_IMPORT_CONFIG,					//导入配置
	DD_LOG_TYPE_EXPORT_CONFIG,					//导出配置

	DD_LOG_TYPE_CHGE_IMAGE_MASK,				//图像遮挡
	DD_LOG_TYPE_RECYCLE_REC_ON,					//开启循环录像
	DD_LOG_TYPE_RECYCLE_REC_OFF,				//关闭循环录像
	DD_LOG_TYPE_CHGE_DISK_ALARM,				//调整磁盘报警空间

	DD_LOG_TYPE_CHGE_SEND_EMAIL,				//设置Email 发送人信息
	DD_LOG_TYPE_CHGE_RECV_EMAIL,				//设置Email 接收人信息
	DD_LOG_TYPE_CHGE_SNAP_SETTING,				//调整抓图配置

	//录像回放(Playback)
	DD_LOG_TYPE_PLAYBACK		= 0x03000000,
	DD_LOG_TYPE_PLAYBACK_PLAY,					//播放
	DD_LOG_TYPE_PLAYBACK_PAUSE,					//暂停
	DD_LOG_TYPE_PLAYBACK_RESUME,				//恢复播放
	DD_LOG_TYPE_PLAYBACK_FF,					//快进
	DD_LOG_TYPE_PLAYBACK_REW,					//快退
	DD_LOG_TYPE_PLAYBACK_STOP,					//停止
	DD_LOG_TYPE_PLAYBACK_NEXT_SECTION,			//下一段
	DD_LOG_TYPE_PLAYBACK_PREV_SECTION,			//上一段

	//数据备份(Backup)
	DD_LOG_TYPE_BACKUP			= 0x04000000,
	DD_LOG_TYPE_BACKUP_START,					//开始备份
	DD_LOG_TYPE_BACKUP_COMPLETE,				//备份完成
	DD_LOG_TYPE_BACKUP_CANCEL,					//放弃备份
	DD_LOG_TYPE_BACKUP_FAIL,					//备份失败

	//录像检索(Search)
	DD_LOG_TYPE_SEARCH			= 0x05000000,
	DD_LOG_TYPE_SEARCH_TIME,					//按时间检索
	DD_LOG_TYPE_SEARCH_EVENT,					//按事件检索
	DD_LOG_TYPE_SEARCH_FILE_MAN,				//文件管理
	DD_LOG_TYPE_SEARCH_PICTURE,					//搜索图片
	DD_LOG_TYPE_DELETE_FILE,					//删除文件
	DD_LOG_TYPE_LOCK_FILE,						//锁定文件
	DD_LOG_TYPE_UNLOCK_FILE,					//解锁文件
	DD_LOG_TYPE_DELETE_PICTURE,					//删除图片
	DD_LOG_TYPE_LOCK_PICTURE,					//锁定图片
	DD_LOG_TYPE_UNLOCK_PICTURE,					//解锁图片


	//查看信息(View information)
	DD_LOG_TYPE_VIEW_INFO		= 0x06000000,
	DD_LOG_TYPE_VIEW_SYSTEM,					//查看系统信息
	DD_LOG_TYPE_VIEW_EVENT,						//查看事件
	DD_LOG_TYPE_VIEW_LOG,						//查看日志
	DD_LOG_TYPE_VIEW_NETWORK,					//查看网络状态
	DD_LOG_TYPE_VIEW_ONLINE_USER,				//查看在线用户
	DD_LOG_TYPE_VIEW_EXPORT_LOG,				//导出日志
	DD_LOG_TYPE_VIEW_EXPORT_EVENT,				//导出事件

	//事件信息(Event information)
	DD_LOG_TYPE_EVENT_INFO		= 0x07000000,
	DD_LOG_TYPE_SENSOR_START,					//传感器报警开始
	DD_LOG_TYPE_SENSOR_END,						//传感器报警结束
	DD_LOG_TYPE_MOTION_START,					//移动侦测开始
	DD_LOG_TYPE_MOTION_END,						//移动侦测结束
	DD_LOG_TYPE_VLOSS_START,					//视频丢失开始
	DD_LOG_TYPE_VLOSS_END,						//视频丢失结束
	DD_LOG_TYPE_SHELTER_START,					//视频遮挡开始
	DD_LOG_TYPE_SHELTER_END,					//视频遮挡结束

	//行为分析(Behavior)
	DD_LOG_TYPE_BEHAVIOR_INFO	= 0x08000000,
	DD_LOG_TYPE_TRAVERSE_PLANE,			//
	DD_LOG_TYPE_ENTER_AREA,				//进入
	DD_LOG_TYPE_EXIT_AREA,				//
	DD_LOG_TYPE_INTRUSION,
	DD_LOG_TYPE_LOITER,
	DD_LOG_TYPE_LEFT_TAKE,
	DD_LOG_TYPE_PARKING,
	DD_LOG_TYPE_RUN,
	DD_LOG_TYPE_HIGH_DENSITY,

	//异常信息(Error)
	DD_LOG_TYPE_ERROR_INFO		= 0x09000000,
	DD_LOG_TYPE_IP_CONFLICT,					//网络地址冲突
	DD_LOG_TYPE_NETWORK_ERR,					//网络异常
	DD_LOG_TYPE_DDNS_ERR,						//DDNS错误
	DD_LOG_TYPE_DISK_IO_ERR,					//磁盘读写错误
	DD_LOG_TYPE_UNKNOWN_OFF,					//异常断电
	DD_LOG_TYPE_UNKNOWN_ERR,					//未知错误	
}DD_LOG_TYPE;

typedef enum _dd_view_split_mode_
{
	DD_VIEW_SPLIT_1X1	= 0x00010000,	//1X1

	DD_VIEW_SPLIT_2X2	= 0x00020000,	//2X2

	DD_VIEW_SPLIT_1A2	= 0x00040000,	//2X3
	DD_VIEW_SPLIT_2X3,

	DD_VIEW_SPLIT_1A5	= 0x00080000,	//3X3
	DD_VIEW_SPLIT_3X3,

	DD_VIEW_SPLIT_1A7	= 0x00100000,	//4X4
	DD_VIEW_SPLIT_1A12,
	DD_VIEW_SPLIT_4X4,

	DD_VIEW_SPLIT_2A6	= 0x00200000,	//4X6
	DD_VIEW_SPLIT_4X6,

	DD_VIEW_SPLIT_1A9	= 0x00400000,	//5X5
	DD_VIEW_SPLIT_4A9,
	DD_VIEW_SPLIT_1A16,
	DD_VIEW_SPLIT_4A16,
	DD_VIEW_SPLIT_5X5,

	DD_VIEW_SPLIT_1A11	= 0x00800000,	//6X6
	DD_VIEW_SPLIT_1A20,
	DD_VIEW_SPLIT_4A20,
	DD_VIEW_SPLIT_6X6,
}DD_VIEW_SPLIT_MODE;

inline unsigned char DDSplitModeToNum(DD_VIEW_SPLIT_MODE mode)
{
	unsigned char num = 1;
	switch(mode)
	{
	case DD_VIEW_SPLIT_2X2:
		num = 4;
		break;
	case DD_VIEW_SPLIT_2X3:
		num = 6;
		break;
	case DD_VIEW_SPLIT_3X3:
		num = 9;
		break;
	case DD_VIEW_SPLIT_4X4:
		num = 16;
		break;
	case DD_VIEW_SPLIT_5X5:
		num = 25;
		break;
	case DD_VIEW_SPLIT_6X6:
		num = 36;
		break;
	default:
		num = 1;
		break;
	}

	return num;
}

typedef enum
{
	DD_PTZ_TYPE_PRESET	= 1,
	DD_PTZ_TYPE_CRUISE	= 2,
	DD_PTZ_TYPE_TRACE	= 3,
}DD_PTZ_TYPE;

//////////////////////////////////////////////////////////////////////////
//以下为N9000相关类型
typedef enum _n9000_log_type
{
	LOG_ALARM_MOTION = 0x100,		   // 移动侦测报警。
	LOG_ALARM_SENSOR,				   // 传感器报警。
	LOG_ALARM_ALARMOUTPUT,			   // 报警输出。
	LOG_ALARM_OCCLUSION,			   // 遮蔽报警。
	LOG_ALARM_VLOSS,				   // 视频丢失报警。
	LOG_ALARM_VEHICLE_PLATE_MATCH,	   // 车牌识别报警。
	LOG_ALARM_INTELLIGENT,			   // 智能侦测报警。
	LOG_ALARM_FACE_MATCH,			   // 人脸对比报警。
	LOG_ALARM_COMBINED,				   // 组合报警。
	LOG_OPERATE_RECORD_SPB,			   // 录像检索/回放/备份。
	LOG_OPERATE_MANUAL_RECORD,		   // 手动录像。
	LOG_OPERATE_MANUAL_ALARM,		   // 手动报警。
	LOG_OPERATE_SYSTEM_MAINTENANCE,	   // 系统维护。
	LOG_OPERATE_PTZ_CONTROL,		   // 云台控制。
	LOG_OPERATE_AUDIO_TALK,			   // 语音对讲。
	LOG_OPERATE_SYSTEM_SCR,			   // 开关机。
	LOG_OPERATE_LOGIN_LOGOUT,		   // 登录/登出。
	LOG_OPERATE_SNAPSHOT_MSPB,		   // 图片。
	LOG_OPERATE_FORMAT_HD,			   // 格式化磁盘。
	LOG_OPERATE_HDD_INSERT,			   // 硬盘插入。
	LOG_OPERATE_FEATURELIBRARY,		   // 特征库增加。
	LOG_CONFIG_CHANNEL,				   // 通道参数。
	LOG_CONFIG_RECORD,				   // 录像参数。
	LOG_CONFIG_ALARM,				   // 报警参数。
	LOG_CONFIG_DISK,				   // 磁盘参数。
	LOG_CONFIG_NETWORK,				   // 网络参数。
	LOG_CONFIG_SCHEDULE,			   // 排程参数。
	LOG_CONFIG_USER,				   // 用户参数。
	LOG_CONFIG_BASIC,				   // 基本配置。
	LOG_EXCEPTION_UNLAWFUL_ACCESS,	   // 非法访问。
	LOG_EXCEPTION_DISK_FULL,		   // 磁盘满。
	LOG_EXCEPTION_DISK_IO_ERROR,	   // 磁盘读写出错。
	LOG_EXCEPTION_IP_COLLISION,		   // IP地址冲突。
	LOG_EXCEPTION_INTERNET_DISCONNECT, // 网络断开。
	LOG_EXCEPTION_IPC_DISCONNECT,	   // 前端掉线。
	LOG_EXCEPTION_ABNORMAL_SHUTDOWN,   // 系统异常关机。
	LOG_EXCEPTION_NO_DISK,			   // 无磁盘。
	LOG_EXCEPTION_VIDEO_LOSS,		   // 视频丢失。
}N9000_LOG_TYPE;

typedef enum _n9000_log_major_type
{
	LOG_ALL		= 0x01,//全部类型
	LOG_ALARM_ALL,		//报警日志
	LOG_OPERATE_ALL,	//操作日志
	LOG_CONFIG_ALL,		//设置日志
	LOG_EXCEPTION_ALL,	//异常日志
	LOG_INFOR_ALL,		//其它日志
	LOG_MAJOR_TYPE_END,
}N9000_LOG_MAJOR_TYPE;

//按位保存。最多不能超过32个
typedef enum _dd_video_size_n9000_
{
	DD_VIDEO_SIZE_640X480		= 0x0001,
	DD_VIDEO_SIZE_720X480		= 0x0002,
	DD_VIDEO_SIZE_720X576		= 0x0004,
	DD_VIDEO_SIZE_800X600		= 0x0008,
	DD_VIDEO_SIZE_1024X768		= 0x0010,
	DD_VIDEO_SIZE_1280X960		= 0x0020,
	DD_VIDEO_SIZE_1280X1024		= 0x0040,
	DD_VIDEO_SIZE_1920X1080		= 0x0080,
	DD_VIDEO_SIZE_320X240		= 0x0100,
	DD_VIDEO_SIZE_352X240		= 0x0200,
	DD_VIDEO_SIZE_480X240		= 0x0400,
	DD_VIDEO_SIZE_704X480		= 0x0800,
	DD_VIDEO_SIZE_704X576		= 0x1000,
	DD_VIDEO_SIZE_960X480		= 0x2000,
	DD_VIDEO_SIZE_960X576		= 0x4000,
	DD_VIDEO_SIZE_960X1080		= 0x8000,
	DD_VIDEO_SIZE_1280X720		= 0x00010000,
	DD_VIDEO_SIZE_1600X1200		= 0x00020000,
	DD_VIDEO_SIZE_1920X1536		= 0x00040000,
	DD_VIDEO_SIZE_2048X1536		= 0x00080000,
	DD_VIDEO_SIZE_2304X1296		= 0x00100000,
	DD_VIDEO_SIZE_2560X1440		= 0x00200000,
	DD_VIDEO_SIZE_2592X1520		= 0x00400000,
	DD_VIDEO_SIZE_2592X1944		= 0x00800000,
	DD_VIDEO_SIZE_3840X2160		= 0x01000000,
    DD_VIDEO_SIZE_352x288		= 0x02000000,
}DD_VIDEO_SIZE_N9000;

const unsigned int DD_INVALID_CLIENT_ID	= (~0x0);
const unsigned int DD_LOCAL_CLIENT_ID		= 0;
const unsigned int DD_LOCAL_DEVICE_ID		= 0;


typedef enum _dd_ptz_config_e_
{
    DD_PTZ_CONFIG_PRESET    = 0x1,
    DD_PTZ_CONFIG_CRUISE,
    DD_PTZ_CONFIG_CRUISE_POINT,
}DD_PTZ_CONFIG_E;

#ifdef __CHONGQING_ZHONGRAN__

const unsigned int DD_MAX_CERTIFICATE_NUM = 64;
#else
const unsigned int DD_MAX_CERTIFICATE_NUM = 20;
#endif
#endif //__DVR_DVS_TYPEDEF_H__
//end
