
#ifndef _DVR_NET_SDK_H_
#define _DVR_NET_SDK_H_

#include "base_type_define.h"
#include "dvrdvstypedef.h"
#include "dvrdvsconfig.h"
#include "dvrdvsdefine.h"
#include "FrameInfo.h"
#include "DisplayDefine.h"

#ifdef WIN32

#define CALL_METHOD __stdcall

#ifdef __cplusplus
#define __EXTERN_C extern "C"
#else
#define __EXTERN_C extern
#endif

#ifdef DVR_NET_SDK_EXPORTS
#define NET_SDK_API __EXTERN_C __declspec(dllexport)
#else
#ifndef __STATIC__
#define NET_SDK_API __EXTERN_C __declspec(dllimport)
#else
#define NET_SDK_API
#endif
#endif

#else

#define CALL_METHOD
#define NET_SDK_API __attribute__ ((visibility("default")))

#endif

#if __cplusplus
extern "C"{
#endif

//#define gettid() syscall(__NR_gettid)

// 错误码
typedef enum
{
    NET_SDK_SUCCESS,                             // 没有错误
    NET_SDK_PASSWORD_ERROR,                      // 用户名或密码错误
    NET_SDK_NOENOUGH_AUTH,                       // 权限不足
    NET_SDK_NOINIT,                              // 没有初始化
    NET_SDK_CHANNEL_ERROR,                       // 通道号错误
    NET_SDK_OVER_MAXLINK,                        // 连接到设备的客户端个数超过最大
    NET_SDK_LOGIN_REFUSED,                       // SDK登陆被拒绝
    NET_SDK_VERSION_NOMATCH,                     // SDK版本不匹配
    NET_SDK_NETWORK_FAIL_CONNECT,                // 链接服务器失败
    NET_SDK_NETWORK_NOT_CONNECT,                 // 服务器未链接上
    NET_SDK_NETWORK_SEND_ERROR,                  // 向服务器发送失败
    NET_SDK_NETWORK_RECV_ERROR,                  // 从服务器接收数据失败
    NET_SDK_NETWORK_RECV_TIMEOUT,                // 从服务器接收数据超时
    NET_SDK_NETWORK_ERRORDATA,                   // 传输的数据有误
    NET_SDK_ORDER_ERROR,                         // 调用次序错误
    NET_SDK_OPER_BY_OTHER,                       // 操作方式有误
    NET_SDK_OPER_NOPERMIT,                       // 无此权限
    NET_SDK_COMMAND_TIMEOUT,                     // 命令执行超时
    NET_SDK_ERROR_SERIALPORT,                    // 串口号错误
    NET_SDK_ERROR_ALARMPORT,                     // 报警端口错误
    NET_SDK_PARAMETER_ERROR,                     // 参数错误
    NET_SDK_CHAN_EXCEPTION,                      // 服务器通道处于错误状态
    NET_SDK_NODISK,                              // 没有硬盘
    NET_SDK_ERROR_DISKNUM,                       // 硬盘号错误
    NET_SDK_DISK_FULL,                           // 服务器硬盘已满
    NET_SDK_DISK_ERROR,                          // 服务器硬盘出现错误
    NET_SDK_NOSUPPORT,                           // 服务器不支持
    NET_SDK_BUSY,                                // 服务器忙
    NET_SDK_MODIFY_FAIL,                         // 服务器修改失败
    NET_SDK_PASSWORD_FORMAT_ERROR,               // 密码格式有误
    NET_SDK_DISK_FORMATING,                      // 硬盘正在格式化，不能启动操作
    NET_SDK_DVR_NORESOURCE,                      // 设备资源不足
    NET_SDK_DVR_OPRATE_FAILED,                   // 操作失败
    NET_SDK_OPEN_HOSTSOUND_FAIL,                 // 打开PC机声音失败
    NET_SDK_DVR_VOICEOPENED,                     // 服务器语音对讲被占用
    NET_SDK_TIME_INPUTERROR,                     // 时间输入错误
    NET_SDK_NOSPECFILE,                          // 回放时服务器没有指定的文件
    NET_SDK_CREATEFILE_ERROR,                    // 创建文件出错
    NET_SDK_FILEOPENFAIL,                        // 打开文件失败
    NET_SDK_OPERNOTFINISH,                       // 上次的操作还没有完成
    NET_SDK_GETPLAYTIMEFAIL,                     // 获取当前播放的时间出错
    NET_SDK_PLAYFAIL,                            // 播放出错
    NET_SDK_FILEFORMAT_ERROR,                    // 文件格式错误
    NET_SDK_DIR_ERROR,                           // 路径错误
    NET_SDK_ALLOC_RESOURCE_ERROR,                // 资源分配错误
    NET_SDK_AUDIO_MODE_ERROR,                    // 音频模式错误
    NET_SDK_NOENOUGH_BUF,                        // 缓冲区太小
    NET_SDK_CREATESOCKET_ERROR,                  // 创建socket出错
    NET_SDK_SETSOCKET_ERROR,                     // 设置socket出错
    NET_SDK_MAX_NUM,                             // 个数达到最大
    NET_SDK_USERNOTEXIST,                        // 用户不存在
    NET_SDK_WRITEFLASHERROR,                     // 写入flash出错
    NET_SDK_UPGRADEFAIL,                         // 升级失败
    NET_SDK_CARDHAVEINIT,                        // 解码卡已经初始化过
    NET_SDK_PLAYERFAILED,                        // 调用播放库中某个函数失败
    NET_SDK_MAX_USERNUM,                         // 设备端用户数达到最大
    NET_SDK_GETLOCALIPANDMACFAIL,                // 获得客户端的IP地址或物理地址失败
    NET_SDK_NOENCODEING,                         // 该通道没有编码
    NET_SDK_IPMISMATCH,                          // IP地址不匹配
    NET_SDK_MACMISMATCH,                         // 物理地址不匹配
    NET_SDK_UPGRADELANGMISMATCH,                 // 升级文件语言不匹配
    NET_SDK_MAX_PLAYERPORT,                      // 播放器路数达到最大
    NET_SDK_NOSPACEBACKUP,                       // 备份设备中没有足够空间进行备份
    NET_SDK_NODEVICEBACKUP,                      // 没有找到指定的备份设备
    NET_SDK_PICTURE_BITS_ERROR,                  // 图像素位数不符，限24色
    NET_SDK_PICTURE_DIMENSION_ERROR,             // 图片高*宽超限， 限128*256
    NET_SDK_PICTURE_SIZ_ERROR,                   // 图片大小超限，限100K
    NET_SDK_LOADPLAYERSDKFAILED,                 // 载入当前目录下Player SDK出错
    NET_SDK_LOADPLAYERSDKPROC_ERROR,             // 找不到Player SDK中某个函数入口
    NET_SDK_LOADDSSDKFAILED,                     // 载入当前目录下DS SDK出错
    NET_SDK_LOADDSSDKPROC_ERROR,                 // 找不到DS SDK中某个函数入口
    NET_SDK_DSSDK_ERROR,                         // 调用硬解码库DS SDK中某个函数失败
    NET_SDK_VOICEMONOPOLIZE,                     // 声卡被独占
    NET_SDK_JOINMULTICASTFAILED,                 // 加入多播组失败
    NET_SDK_CREATEDIR_ERROR,                     // 建立日志文件目录失败
    NET_SDK_BINDSOCKET_ERROR,                    // 绑定套接字失败
    NET_SDK_SOCKETCLOSE_ERROR,                   // socket连接中断，此错误通常是由于连接中断或目的地不可达
    NET_SDK_USERID_ISUSING,                      // 注销时用户ID正在进行某操作
    NET_SDK_PROGRAM_EXCEPTION,                   // 程序异常
    NET_SDK_WRITEFILE_FAILED,                    // 写文件失败
    NET_SDK_FORMAT_READONLY,                     // 禁止格式化只读硬盘
    NET_SDK_WITHSAMEUSERNAME,                    // 用户配置结构中存在相同的用户名
    NET_SDK_DEVICETYPE_ERROR,                    // 导入参数时设备型号不匹配
    NET_SDK_LANGUAGE_ERROR,                      // 导入参数时语言不匹配
    NET_SDK_PARAVERSION_ERROR,                   // 导入参数时软件版本不匹配
    NET_SDK_FILE_SUCCESS,                        // 文件已经创建成功
    NET_SDK_FILE_NOFIND,                         // 找不到该文件
    NET_SDK_NOMOREFILE,                          // 没有更多的相关文件
    NET_SDK_FILE_EXCEPTION,                      // 文件异常
    NET_SDK_TRY_LATER,                           // 梢后尝试
    NET_SDK_DEVICE_OFFLINE,                      // 设备下线
    NET_SDK_CREATEJPEGSTREAM_FAIL,               // 创建JPEG流失败
    NET_SDK_USER_ERROR_NO_USER,                  // 用户不存在
    NET_SDK_USER_ERROR_USER_OR_PASSWORD_IS_NULL, // 输入用户名或者密码为空
    NET_SDK_USER_ERROR_ALREDAY_LOGIN,            // 用户已登录
    NET_SDK_USER_ERROR_SYSTEM_BUSY,              // 设备正忙
    NET_SDK_DEVICE_NOT_SUPPROT,                  // DEVICE不支持
    NET_SDK_USER_ERROR_SYSTEM_NO_READY,          // N9K设备还没有准备好 刚刚登录获取预置点巡航线list还未成功
    NET_SDK_CHANNEL_OFFLINE,                     // 预览N9K设备时通道不在线
    NET_SDK_GETREADYINFO_FAIL,                   // 获取N9K能力集失败
    NET_SDK_NORESOURCE,                          // SDK资源不足
    NET_SDK_DEVICE_QUERYSYSTEMCAPS_FAIL,         // 查询系统配置信息失败
    NET_SDK_INBUFFER_TOSMALL,                    // 输入BUF不足
    NET_SDK_NO_PASSWORD_STRENGTH,                // 密码强度错误
    NET_SDK_FILE_NOT_MATCH_PRODUCT,              // 产品型号与升级文件不匹配
} NET_SDK_ERROR;

// 设备状态
enum NET_DEVICE_STATUS
{
    NET_DEVICE_STATUS_CONNECTED,  // 设备连接状态
    NET_DEVICE_STATUS_DISCONNECT, // 设备断开状态
};

// 码流类型
enum NET_SDK_STREAM_TYPE
{
    NET_SDK_MAIN_STREAM = 0, // 主码流
    NET_SDK_SUB_STREAM,      // 子码流
    NET_SDK_THIRD_STREAM,    // 第三码流
    NET_SDK_FOURTH_STREAM,   // 第四码流
};

// 播放控制命令
enum NET_SDK_PLAYCTRL_TYPE
{
	NET_SDK_PLAYCTRL_PAUSE,       // 暂停
	NET_SDK_PLAYCTRL_FF,          // 快进
	NET_SDK_PLAYCTRL_REW,         // 后退
	NET_SDK_PLAYCTRL_RESUME,      // 恢复
	NET_SDK_PLAYCTRL_STOP,        // 停止
	NET_SDK_PLAYCTRL_FRAME,       // 单帧播放
	NET_SDK_PLAYCTRL_NORMAL,      // 正常播放
	NET_SDK_PLAYCTRL_STARTAUDIO,  // 该控制类型及以下两个控制类型只有在SDK内部解码显示时才会起作用
	NET_SDK_PLAYCTRL_STOPAUDIO,   // 停止语音
	NET_SDK_PLAYCTRL_AUDIOVOLUME, // 调节语音音量，此时通过NET_SDK_PlayBackControl函数中的dwInValue参数实现语音调节
	NET_SDK_PLAYCTRL_SETPOS,      // 播放进度,以1970年1月1日起的秒数计算
	NET_SDK_PLAYCTRL_PREVIOUS,    // 单帧回放
};

enum NET_SDK_RPB_SPEED
{
	NET_SDK_RPB_SPEED_1_32X = 1,
	NET_SDK_RPB_SPEED_1_16X,
	NET_SDK_RPB_SPEED_1_8X,		//1/8
	NET_SDK_RPB_SPEED_1_4X,		//1/4
	NET_SDK_RPB_SPEED_1_2X,		//1/2
	NET_SDK_RPB_SPEED_1X,		//1
	NET_SDK_RPB_SPEED_2X,
	NET_SDK_RPB_SPEED_4X,
	NET_SDK_RPB_SPEED_8X,
	NET_SDK_RPB_SPEED_16X,
	NET_SDK_RPB_SPEED_32X,
};

const int MAX_NAMELEN = 36;     // 名称最大长度。
const int MAX_CONTENTLEN = 512; // 最大内容长度。

#pragma pack(4)
// 对应NET_SDK_DEVICEINFO中function。
typedef struct _net_sdk_devicefunction_ipc
{
    unsigned int intelist_enable : 1;        // 表示该结构体是否包含智能能力集列表(后面31位)。
    unsigned int intelist_Perimeter : 1;     // 是否支持区域入侵, 1表示支持, 0表示不支持。
    unsigned int intelist_Tripwire : 1;      // 是否支持绊线侦测, 1表示支持, 0表示不支持。
    unsigned int intelist_Osc : 1;           // 是否支持物品看护, 1表示支持, 0表示不支持。
    unsigned int intelist_Avd : 1;           // 是否支持异常侦测, 1表示支持, 0表示不支持。
    unsigned int intelist_Cpc : 1;           // 是否支持人流量统计, 1表示支持, 0表示不支持。
    unsigned int intelist_Cdd : 1;           // 是否支持人群密度检测, 1表示支持, 0表示不支持。
    unsigned int intelist_Ipd : 1;           // 是否支持人员入侵侦测, 1表示支持, 0表示不支持。
    unsigned int intelist_Vfd : 1;           // 是否支持人脸抓拍, 1表示支持, 0表示不支持。
    unsigned int intelist_Vfd_Match : 1;     // 是否支持人脸比对, 1表示支持, 0表示不支持。
    unsigned int intelist_Vehice : 1;        // 是否支持车牌检测, 1表示支持, 0表示不支持。
    unsigned int intelist_AoiEntry : 1;      // 是否支持进入区域, 1表示支持, 0表示不支持。
    unsigned int intelist_AoiLeave : 1;      // 是否支持离开区域, 1表示支持, 0表示不支持。
    unsigned int intelist_PassLineCount : 1; // 是否支持过线统计, 1表示支持, 0表示不支持。
    unsigned int intelist_Vfd_Detect : 1;    // 是否支持人脸侦测, 1表示支持, 0表示不支持。
    unsigned int intelist_Traffic : 1;       // 是否支持流量统计, 1表示支持, 0表示不支持。
    unsigned int intelist_Thermal : 1;       // 是否支持热成像测温, 1表示支持, 0表示不支持。
    unsigned int intelist_reserver : 15;     // 预留智能功能。
    unsigned int resvFunction[7];            // 预留功能描述。
} NET_SDK_DEVICE_FUNC_IPC;

// 设备信息。
typedef struct _net_sdk_deviceinfo
{
    unsigned char localVideoInputNum;   // 本地视频输入通道数目。
    unsigned char audioInputNum;        // 音频输入通道数目。
    unsigned char sensorInputNum;       // 传感器输入通道数目。
    unsigned char sensorOutputNum;      // 继电器输出数目。
    unsigned int displayResolutionMask; // 监视器可选择的分辨率。
    unsigned char videoOuputNum;        // 视频输出数目（及支持回放最大通道数）。
    unsigned char netVideoOutputNum;    // 网络回放最大通道数目。
    unsigned char netVideoInputNum;     // 数字信号接入通道数目。
    unsigned char IVSNum;               // 智能分析通道数目。
    unsigned char presetNumOneCH;       // 每个通道预置点数目。
    unsigned char cruiseNumOneCH;       // 每个通道巡航线数目。
    unsigned char presetNumOneCruise;   // 每个巡航线的预置点数目。
    unsigned char trackNumOneCH;        // 每个通道轨迹数目。
    unsigned char userNum;              // 用户数目。
    unsigned char netClientNum;         // 最多客户端数目。
    unsigned char netFirstStreamNum;    // 主码流传输的通道最大数目，即同时可以有几个客户端查看主码流。
    unsigned char deviceType;           // NET_SDK_DEVICE_TYPE。
    unsigned char doblueStream;         // 是否有提供双码流。
    unsigned char audioStream;          // 是否有提供音频流。
    unsigned char talkAudio;            // 是否有对讲功能: 1表示有对讲功能;0表示没有。
    unsigned char bPasswordCheck;       // 操作是否要输入密码。
    unsigned char defBrightness;        // 缺省亮度。
    unsigned char defContrast;          // 缺省对比度。
    unsigned char defSaturation;        // 缺省饱和度。
    unsigned char defHue;               // 缺省色调。
    unsigned short videoInputNum;       // 视频输入通道数目（本地加网络）。
    unsigned short deviceID;            // 设备ID号。
    unsigned int videoFormat;           // 系统当前制式。
    unsigned int function[8];           // 功能描述。
    unsigned int deviceIP;              // 设备网络地址。
    unsigned char deviceMAC[6];         // 设备物理地址。
    unsigned short devicePort;          // 设备端口。
    unsigned int buildDate;             // 创建日期:year<<16 + month<<8 + mday。
    unsigned int buildTime;             // 创建时间:hour<<16 + min<<8 + sec。
    char deviceName[36];                // 设备名称。
    char firmwareVersion[36];           // 固件版本。
    char kernelVersion[64];             // 内核版本。
    char hardwareVersion[36];           // 硬件版本。
    char MCUVersion[36];                // 单片机版本。
    char firmwareVersionEx[64];         // 固件版本扩展，主要针对新产品。
    unsigned int softwareVer;           // 软件协议版本，目前用于IPC的版本兼容。
    char szSN[32];                      // sn。
    char deviceProduct[28];             // 设备型号。
} NET_SDK_DEVICEINFO, * LPNET_SDK_DEVICEINFO;

// 设备支持的功能，仅支持IPC。
typedef struct _net_sdk_dev_support_
{
    unsigned int supportThermometry : 1; // 支持口罩跟体温
    unsigned int supportVfd : 1;         // 人脸检测
    unsigned int supportVfdMatch : 1;    // 人脸比对
    unsigned int supportThermal : 1;     // 热成像
    unsigned int supportPassLine : 1;    // 过线统计
    unsigned int supportresv : 27;       // 待填入
    unsigned int resv[15];               // 预留参数，暂时未用上
} NET_SDK_DEV_SUPPORT;

    // 数据帧头定义。
    typedef struct _net_sdk_frame_info
    {
        unsigned int deviceID;    // 设备ID号，SDK用来区分设备。
        unsigned int channel;     // 通道号。
        unsigned int frameType;   // 参考DD_FRAME_TYPE。
        unsigned int length;      // 帧数据长度。
        unsigned int keyFrame;    // 0：非关键帧 1：关键帧。
        unsigned int width;       // 数据帧宽度。
        unsigned int height;      // 数据帧高度。
        unsigned int frameIndex;  // 数据帧索引。
        unsigned int frameAttrib; // 数据帧属性，参考DD_FRAME_ATTRIB。
        unsigned int streamID;    // 数据流ID号。
        LONGLONG time;            // 绝对时间，从1970年1月1日0点0分0秒开始的绝对时间，单位微秒,在改变设备时间时会变化。
        LONGLONG relativeTime;    // 相对时间，单位微秒,在改变设备时间时不会变化，是个连续的时间。
    } NET_SDK_FRAME_INFO;

    // 根据时间录像文件信息结构体。
    typedef struct _net_sdk_rec_time
    {
        DWORD dwChannel;   // 通道号。
        DD_TIME startTime; // 该段录像开始时间。
        DD_TIME stopTime;  // 该段录像停止时间。
    } NET_SDK_REC_TIME;

typedef struct _net_sdk_rec_file
{
	DWORD			dwChannel;
	DWORD			bFileLocked;
	DD_TIME			startTime;
	DD_TIME			stopTime;
	DWORD			dwRecType;
	DWORD			dwPartition;
	DWORD			dwFileIndex;
}NET_SDK_REC_FILE;

typedef struct _net_sdk_rec_event
{
	DWORD			dwChannel;
	DD_TIME			startTime;
	DD_TIME			stopTime;
	DWORD			dwRecType;	//DD_RECORD_TYPE
}NET_SDK_REC_EVENT;

    // 设备日志信息结构体。
    typedef struct _net_sdk_log
    {
        DD_TIME strLogTime;            // 日志时间。
        DWORD dwMajorType;             // 主要类型。
        DWORD dwMinorType;             // 次要类型。
        char sNetUser[MAX_NAMELEN];    // 网络用户。
        DWORD dwRemoteHostAddr;        // 远程主机地址。
        char sContent[MAX_CONTENTLEN]; // 详细信息。
    } NET_SDK_LOG, * LPNET_SDK_LOG;

    // 事件信息结构体。
    typedef struct _net_sdk_event
    {
        unsigned short chnn; // 事件对应的通道。
        unsigned short type; // 事件类型。
        DD_TIME startTime;   // 事件产生的开始时间。
        DD_TIME endTime;     // 事件的结束时间。
    } NET_SDK_EVENT, * LPNET_SDK_EVENT;

typedef struct _net_sdk_clientinfo
{
	LONG    lChannel;
	LONG    streamType;
	HWND    hPlayWnd;
    int     bNoDecode; //0:½âÂë£¬ 1£º²»½âÂë ½öÕë¶ÔwinÆ½Ì¨£¬Ä¬ÈÏ0

}NET_SDK_CLIENTINFO, *LPNET_SDK_CLIENTINFO;

//Éè±¸ÉÏ´«ÐÅÏ¢ÀàÐÍ
enum NET_SDK_DEVICE_MSG_TYPE
{
	NET_SDK_ALARM,		//Éè±¸±¨¾¯ÏûÏ¢
	NET_SDK_RECORD,		//Éè±¸Â¼ÏñÐÅÏ¢
	NET_SDK_IVM_RULE,	//ÖÇÄÜÐÐÎª·ÖÎöÐÅÏ¢(ÔÝÊ±±£Áô)
	NET_SDK_TRADEINFO,	//ATM½»Ò×ÐÅÏ¢(ÔÝÊ±±£Áô)
	NET_SDK_IPCCFG,		//»ìºÏÐÍDVRµÄIPCÐÅÏ¢±ä¸ü(ÔÝÊ±±£Áô)
};

//Éè±¸ÉÏ´«ÐÅÏ¢Îª±¨¾¯ÀàÐÍÊ±µÄ¾ßÌå±¨¾¯ÀàÐÍ
enum NET_SDK_ALARM_TYPE
{
	NET_SDK_ALARM_TYPE_MOTION,		//ÒÆ¶¯Õì²â
	NET_SDK_ALARM_TYPE_SENSOR,		//ÐÅºÅÁ¿±¨¾¯
	NET_SDK_ALARM_TYPE_VLOSS,		//ÐÅºÅ¶ªÊ§
	NET_SDK_ALARM_TYPE_SHELTER,		//ÕÚµ²±¨¾¯
	NET_SDK_ALARM_TYPE_DISK_FULL,	//Ó²ÅÌÂú
	NET_SDK_ALARM_TYPE_DISK_UNFORMATTED,//Ó²ÅÌÎ´¸ñÊ½»¯
	NET_SDK_ALARM_TYPE_DISK_WRITE_FAIL,	//¶ÁÐ´Ó²ÅÌ³ö´í
	NET_SDK_ALARM_TYPE_EXCEPTION,
};


//Éè±¸ÉÏ´«ÐÅÏ¢ÎªÖÇÄÜ±¨¾¯µÄÊÂ¼þÀàÐÍ
enum NET_SDK_IVM_RULE_TYPE
{
    NET_SDK_IVM_RULE_TYPE_VFD, //ÈËÁ³Ê¶±ð±¨¾¯  NET_SDK_IVM_STATUS_INFO
    NET_SDK_IVM_RULE_TYPE_AVD_SCENE, //ÊÓÆµÒì³£Õï¶Ï³¡¾°±ä»¯  NET_SDK_IVM_STATUS_INFO
    NET_SDK_IVM_RULE_TYPE_AVD_CLARITY, //ÊÓÆµÒì³£Õï¶ÏÊÓÆµÄ£ºý  NET_SDK_IVM_STATUS_INFO
    NET_SDK_IVM_RULE_TYPE_AVD_COLOR, //ÊÓÆµÒì³£Õï¶ÏÊÓÆµÆ«É«  NET_SDK_IVM_STATUS_INFO
};


/************************************************************************/
    /*  ¶¨Òå±¨¾¯ÊäÈëºÍÊä³öµÄ×ÊÔ´    ÔÚºÜ¶àµØ·½Ê¹ÓÃÕâ¸öÃ¶¾ÙÖµµÄÊ±ºò¶¨ÒåµÄ±äÁ¿¶¼ÊÇBYTEµÄËùÒÔÕâÀï
    ÒªÐ¡ÐÄ¶¨Òå*/
    /************************************************************************/

    // 报警类型
    enum NET_SDK_N9000_ALARM_TYPE
    {
        NET_SDK_N9000_ALARM_TYPE_RANGE_BEGIN,              // 开始标志。
        NET_SDK_N9000_ALARM_TYPE_MOTION = 0x01,            // 移动侦测报警输入。
        NET_SDK_N9000_ALARM_TYPE_SENSOR,                   // 传感器报警输入。
        NET_SDK_N9000_ALARM_TYPE_VLOSS,                    // 视频丢失报警输入。
        NET_SDK_N9000_ALARM_TYPE_FRONT_OFFLINE,            // 前端设备掉线报警。
        NET_SDK_N9000_ALARM_TYPE_OSC,                      // 物品看护侦测报警。
        NET_SDK_N9000_ALARM_TYPE_AVD,                      // 视频异常侦测报警。
        NET_SDK_N9000_ALARM_TYPE_AVD_SCENE,                // 视频场景变化，（仅IPC）。
        NET_SDK_N9000_ALARM_TYPE_AVD_CLARITY,              // 视频模糊，（仅IPC）。
        NET_SDK_N9000_ALARM_TYPE_AVD_COLOR,                // 视频色彩变化，（仅IPC）。
        NET_SDK_N9000_ALARM_TYPE_PEA_TRIPWIRE,             // 越界侦测报警。
        NET_SDK_N9000_ALARM_TYPE_PEA_PERIMETER,            // 区域入侵侦测报警。
        NET_SDK_N9000_ALARM_TYPE_VFD,                      // 人脸侦测（目前仅IPC）。
        NET_SDK_N9000_ALARM_TYPE_CDD,                      // Crowdy density。
        NET_SDK_N9000_ALARM_TYPE_IPD,                      // people intrusion。
        NET_SDK_N9000_ALARM_TYPE_CPC,                      // people counting。
        NET_SDK_N9000_ALARM_TYPE_FACE_MATCH,               // 人脸比对报警 for nvr 9000。
        NET_SDK_N9000_ALARM_TYPE_FACE_MATCH_FOR_IPC,       // 人脸比对报警 for ipc。
        NET_SDK_N9000_ALARM_TYPE_PEA_FOR_IPC,              // 越界侦测与区域入侵侦测。
        NET_SDK_N9000_ALARM_TYPE_TRAJECT,                  // 目标跟踪轨迹(Event事件)。// 已不再使用
        NET_SDK_N9000_ALARM_TYPE_VEHICE,                   // 车牌识别(Event事件)。 for ipc(Event事件)
        NET_SDK_N9000_ALARM_TYPE_AOIENTRY,                 // 进入区域。
        NET_SDK_N9000_ALARM_TYPE_AOILEAVE,                 // 离开区域。
        NET_SDK_N9000_ALARM_TYPE_PASSLINE,                 // 过线统计。for ipc
        NET_SDK_N9000_ALARM_TYPE_TRAFFIC,                  // 流量统计（指定区域）。for ipc
        NET_SDK_N9000_ALARM_TYPE_DOOR_BELL,                // 按门铃报警 only IPC。
        NET_SDK_N9000_ALARM_TYPE_PVD,                      // 违停检测。
        NET_SDK_N9000_ALARM_TYPE_LOITER,                   // 徘徊检测。
        NET_SDK_N9000_ALARM_TYPE_ASD,                      // 音频异常。
        NET_SDK_N9000_ALARM_TYPE_EXCEPTION = 0x41,         // 异常报警。
        NET_SDK_N9000_ALARM_TYPE_IP_CONFLICT,              // IP地址冲突。
        NET_SDK_N9000_ALARM_TYPE_DISK_IO_ERROR,            // 磁盘IO错误。
        NET_SDK_N9000_ALARM_TYPE_DISK_FULL,                // 磁盘满。
        NET_SDK_N9000_ALARM_TYPE_RAID_SUBHEALTH,           // 阵列亚健康。
        NET_SDK_N9000_ALARM_TYPE_RAID_UNAVAILABLE,         // 阵列不可用。
        NET_SDK_N9000_ALARM_TYPE_ILLEIGAL_ACCESS,          // 非法访问。
        NET_SDK_N9000_ALARM_TYPE_NET_DISCONNECT,           // 网络断开。
        NET_SDK_N9000_ALARM_TYPE_NO_DISK,                  // 盘组下没有磁盘。
        NET_SDK_N9000_ALARM_TYPE_SIGNAL_SHELTER,           // 信号遮挡。// 目前没有
        NET_SDK_N9000_ALARM_TYPE_HDD_PULL_OUT,             // 前面板硬盘拔出。
        NET_SDK_N9000_ALARM_TYPE_ALARM_OUT = 0x51,         // 报警输出的类型，报警输出也有状态需要管理。
        NET_SDK_N9000_ALARM_TYPE_DISARM,                   // 设备撤防告警。
        NET_SDK_N9000_ALARM_TYPE_ARM,                      // 设备布防告警。
        NET_SDK_N9000_ALARM_TYPE_TEMPERATURE_ALARM = 0x61, // AI告警，温度检测。
        NET_SDK_N9000_ALARM_TYPE_FIREPOINT,                // AI告警，火点检测。
        NET_SDK_N9000_ALARM_TYPE_RANGE_END = 0xFF,         // 不能超过这个值，否则会出错。
    };


//Éè±¸ÉÏ´«ÐÅÏ¢Îª±¨¾¯ÀàÐÍÊ±µÄÉÏ´«ÐÅÏ¢½á¹¹
typedef struct _net_sdk_alarminfo
{
	DWORD		dwAlarmType;
	DWORD		dwSensorIn;		//´«¸ÐÆ÷±¨¾¯ÊäÈë¶Ë¿ÚºÅ
    DWORD		dwChannel;		//ÔÚ±¨¾¯ÓëÍ¨µÀÏà¹ØÊ±£¬±íÊ¾±¨¾¯µÄÍ¨µÀºÅ;£¨µ±±¨¾¯ÀàÐÍÎªNET_SDK_ALARM_TYPE_SENSORÊ±£¬¿É×÷Îªpop video£¬>=0ÉúÐ§£©
	DWORD		dwDisk;			//ÔÚ´ÅÅÌ±¨¾¯Ê±£¬±íÊ¾²úÉú±¨¾¯µÄ´ÅÅÌºÅ
}NET_SDK_ALARMINFO;
typedef struct _net_sdk_alarminfo_ex
{
	DWORD		dwAlarmType;
	DWORD		dwSensorIn;		//´«¸ÐÆ÷±¨¾¯ÊäÈë¶Ë¿ÚºÅ
	DWORD		dwChannel;		//ÔÚ±¨¾¯ÓëÍ¨µÀÏà¹ØÊ±£¬±íÊ¾±¨¾¯µÄÍ¨µÀºÅ;£¨µ±±¨¾¯ÀàÐÍÎªNET_SDK_ALARM_TYPE_SENSORÊ±£¬¿É×÷Îªpop video£¬>=0ÉúÐ§£©
	DWORD		dwDisk;			//ÔÚ´ÅÅÌ±¨¾¯Ê±£¬±íÊ¾²úÉú±¨¾¯µÄ´ÅÅÌºÅ
	char		sensorName[36]; //ÔÚ´«¸ÐÆ÷±¨¾¯Ê±£¬´«¸ÐÆ÷µÄÃû³Æ
	char        alarmTime[20];  //±¨¾¯´¥·¢Ê±¼ä
	char		resv[128];      //Ô¤Áô
}NET_SDK_ALARMINFO_EX;
typedef struct _net_sdk_record_status
{
	DWORD		dwRecordType;		//DD_RECORD_TYPE
	DWORD		dwChannel;
}NET_SDK_RECORD_STATUS;
typedef struct _net_sdk_record_status_ex
{
	DWORD		dwRecordType;		//DD_RECORD_TYPE
	DWORD		dwChannel;
	DWORD		dwRecordStatus;
}NET_SDK_RECORD_STATUS_EX;
typedef struct _net_sdk_IVM_rule_status
{
    DWORD		dwIVMType;		//NET_SDK_IVM_RULE_TYPE
    DWORD		dwIVMSize;      //NET_SDK_IVM_RULE_TYPEÖÐÊÂ¼þ¶ÔÓ¦µÄ½á¹¹Ìå´óÐ¡
}
NET_SDK_IVM_RULE_STATUS;

//ÈËÁ³¼ì²â¸æ¾¯ÉÏ±¨
typedef struct _net_sdk_IVM_status_info
{
    DWORD		dwAlarmType;    //NET_SDK_IVM_RULE_TYPE
    DWORD		dwChannel;		//¸æ¾¯Í¨µÀºÅ

}NET_SDK_IVM_STATUS_INFO;


typedef enum _net_sdk_disk_status
{	
	NET_SDK_DISK_NORMAL,				//Õý³£ 
	NET_SDK_DISK_NO_FORMAT,				//Î´¸ñÊ½»¯
    NET_SDK_DISK_FORMATTING,				//ÕýÔÚ¸ñÊ½»¯
    NET_SDK_DISK_EXCEPTION,				//  exception
}NET_SDK_DISK_STATUS;

typedef enum _net_sdkdisk_property
{
	NET_SDK_DISK_READ_WRITE = 0,			//¿ÉÕý³£¶ÁÐ´
	NET_SDK_DISK_ONLY_READ,					//Ö»ÄÜ¶Á£¬²»ÄÜÐ´
	NET_SDK_DISK_REDUNDANCY					//ÈßÓà
}NET_SDK_DISK_PROPERTY;

typedef enum _net_sdk_connect_type
{
	NET_SDK_CONNECT_TCP		= 0,			//TCP·½Ê½µÇÂ½
	NET_SDK_CONNECT_NAT		= 1,			//NAT·½Ê½µÇÂ½
    NET_SDK_CONNECT_NAT20	= 2,			//NAT2·½Ê½µÇÂ½

	NET_SDK_CONNECT_END
}NET_SDK_CONNECT_TYPE;

typedef enum _net_sdk_camera_type
{
	NET_SDK_NOT_SUPPORT_PTZ		= 0,		//²»Ö§³ÖÔÆÌ¨µÄÇ¹»ú
	NET_SDK_DOME_SUPPORT_PTZ	= 1,		//Ö§³ÖÔÆÌ¨µÄÇ¹»ú
	NET_SDK_SUPPORT_PTZ			= 2,		//Ö§³ÖÔÆÌ¨µÄÇò»ú
	NET_SDK_PTZ_END
}NET_SDK_CAMERA_TYPE;

typedef struct _net_sdk_disk_info
{
	LONG		diskIndex;			//´ÅÅÌ±àºÅ
	short		diskStatus;			//´ÅÅÌ×´Ì¬£¬²Î¿¼NET_SDK_DISK_STATUS
	short		diskProperty;		//´ÅÅÌ×´Ì¬£¬²Î¿¼NET_SDK_DISK_PROPERTY
	DWORD		diskTotalSpace;		//´ÅÅÌ×Ü¿Õ¼ä£¬µ¥Î»MB
	DWORD		diskFreeSpace;		//´ÅÅÌÊ£Óà¿Õ¼ä£¬µ¥Î»MB
}NET_SDK_DISK_INFO;

typedef struct
{
	WORD     wPicSize;
	WORD     wPicQuality;
}NET_SDK_JPEGPARA,*LPNET_SDK_JPEGPARA;

typedef enum _net_sdk_exception_type
{
	NETWORK_DISCONNECT = 0,
	NETWORK_RECONNECT,
	NETWORK_CH_DISCONNECT,	//Í¨µÀµôÏß
	NETWORK_CH_RECONNECT,	//Í¨µÀÉÏÏß
}NET_SDK_EXCEPTION_TYPE;

enum NET_SDK_DEVICE_TYPE
{
	NET_SDK_DVR,
	NET_SDK_DVS,
	NET_SDK_IPCAMERA,
	NET_SDK_NVR,
	NET_SDK_SUPERDVR,
	NET_SDK_DECODER,
    NET_SDK_N_DVR,//N9000µÄDVR
};

typedef enum _net_sdk_device_firmware_type
{
	NET_SDK_DEVICE_FIRMWARE_V3,			
	NET_SDK_DEVICE_FIRMWARE_IPC,		
	NET_SDK_DEVICE_FIRMWARE_NVMS_V1,
	NET_SDK_DEVICE_FIRMWARE_OTHER,
}NET_SDK_DEVICE_FIRMWARE_TYPE;

typedef struct _net_sdk_device_discovery_info
{
	unsigned int		deviceType;		//NET_SDK_DEVICE_TYPE
	char				productType[16];
	char				strIP[16];
	char				strNetMask[16];
	char				strGateWay[16];
	unsigned char		byMac[8];
	unsigned short		netPort;
	unsigned short		httpPort;
	unsigned int		softVer;
	unsigned int		softBuildDate;
	unsigned char		ucIPMode;			//0 ¾²Ì¬IP 1 dhcp
	char				dwSecondIP[16];
	char				dwSecondMask[16];
}NET_SDK_DEVICE_DISCOVERY_INFO;

typedef struct _net_sdk_device_ip_info_
{
	char szMac[36];					//Éè±¸µ±Ç°macµØÖ·
	char szIpAddr[64];				//ÒªÐÞ¸Ä³ÉµÄip
	char szMark[36];
	char szGateway[36];
	char szPassword[64];			//adminÓÃ»§µÄÃÜÂë
	char szDdns1[36];
	char szDdns2[36];
	char ucIPMode;					//0Îª¾²Ì¬IP, 1ÎªDHCP
}NET_SDK_DEVICE_IP_INFO;

typedef struct _net_sdk_ipc_device_info_
{
	unsigned int	deviceID;				//Éè±¸ID(ÔÝÊ±Î´ÓÃÉÏ)
	unsigned short	channel;				//¸ÃÍøÂçÉè±¸ÔÚ±¾µØ·ÖÅäµÄÍ¨µÀ(´Ó0¿ªÊ¼)
	unsigned short	status;					//Á¬½Ó×´Ì¬£¨0´ú±íÀëÏß£¬1±íÊ¾ÔÚÏß£©
	char			szEtherName[16];		//Èç¹ûÎª¿Õ£¬Ä¬ÈÏÎªeth0
	char			szServer[64];			//ÍøÂçÉè±¸IPµØÖ·
	unsigned short	nPort;					//ÍøÂçÉè±¸¶Ë¿ÚºÅ
	unsigned short	nHttpPort;				//HTTP¶Ë¿Ú
	unsigned short	nCtrlPort;				//¿ØÖÆ¶Ë¿Ú£¬Ò»°ãÓënPortÏàÍ¬
	char			szID[64];				//ÍøÂçÉè±¸±êÊ¶(»òÊÇMACµØÖ·)
	char			username[36];			//ÓÃ»§Ãû

	unsigned int	manufacturerId;			//Éè±¸³§ÉÌID(ÔÝÊ±Î´ÓÃÉÏ)
	char			manufacturerName[36];	//Éè±¸³§ÉÌÃû(ÔÝÊ±Î´ÓÃÉÏ)
	char			productModel[36];		//²úÆ·ÐÍºÅ(ÔÝÊ±Î´ÓÃÉÏ)
	unsigned char	bUseDefaultCfg;			//ÔÝÊ±Î´ÓÃÉÏ
	unsigned char	bPOEDevice;				//ÔÝÊ±Î´ÓÃÉÏ
	unsigned char	resv[2];				//ÔÝÊ±Î´ÓÃÉÏ
	char			szChlname[36];			//Í¨µÀÃû³Æ
}NET_SDK_IPC_DEVICE_INFO;

//×¥Í¼ÀàÐÍ
enum IMAGE_EVENT_TYPE
{
    IMAGE_TYPE_ALARM,
    IMAGE_TYPE_MANUAL,
};
//·µ»ØÅÅÁÐË³Ðò
enum IMAGE_SORT_TYPE
{
    IMAGE_SORT_ASC,
    IMAGE_SORT_DESC,
};


typedef struct _net_sdk_image_
{
    DWORD			dwChannel; //×¥Í¼Í¨µÀ
    DWORD			dwImageType; //×¥Í¼ÀàÐÍ IMAGE_EVENT_TYPE
    DD_TIME_EX			captureTime;//Ê±¼ä
    DWORD			totalNum;//Í¼Æ¬×ÜÊý
    unsigned char	resv[8];
}NET_SDK_IMAGE;

typedef struct _net_sdk_image_sreach
{
    DWORD			dwChannel;//×¥Í¼Í¨µÀ
    DD_TIME_EX			StartTime; //Ê±¼ä
    DD_TIME_EX			StopTime; //Ê±¼ä
    DWORD			pageIndex;//µÚ¼¸Ò³
    DWORD			pageSize;//Ã¿Ò³Êý
    unsigned int sort; //·µ»ØÅÅÁÐË³Ðò //IMAGE_SORT_TYPE
    unsigned char	resv[8];
}NET_SDK_IMAGE_SREACH;


//Í¼Æ¬ÀàÐÍ
enum IMAGE_MODE
{
    IMAGE_MODE_JPG,
    IMAGE_MODE_PNG,
    IMAGE_MODE_BMP,
};
typedef struct _net_sdk_image_info
{
    unsigned int	imageSize;
    unsigned int		imageMode; //IMAGE_MODE Í¼Æ¬¸ñÊ½
    unsigned char	resv[8];
}NET_SDK_IMAGE_INFO;

typedef enum __Channel_type__
{
    E_NULL_CHL_TYPE,
    E_DIGITAL_CHL_TYPE,     //Êý×ÖÍ¨µÀ
    E_ANALOG_CHL_TYPE,      //Ä£ÄâÍ¨µÀ
    E_ALARMOUT_CHL_TYPE,	  //±¨¾¯Êä³öÍ¨µÀ
    E_SENSOR_CHL_TYPE,	  //´«¸ÐÆ÷Í¨µÀ
}CHANNEL_TYPE;

typedef struct _net_sdk_channel_ptz
{
    unsigned int	dwChannel;
    unsigned int      eChanneltype;//CHANNEL_TYPE
    unsigned char	resv[8];
}NET_SDK_CHANNEL_PTZ;

typedef enum __IVM_rule_config_type__
{
    IVM_RULE_VFD_CONFIG, //ÈËÁ³Ê¶±ðÅäÖÃ
    IVM_RULE_VFD_TRIGGER_CONFIG, //ÈËÁ³Ê¶±ðÁª¶¯ÅäÖÃ
    IVM_RULE_VFD_SCHEDULE_CONFIG, //ÈËÁ³Ê¶±ðÅÅ³Ì
    IVM_RULE_AVD_CONFIG, //Òì³£ÊÓÆµÅäÖÃ

}IVM_RULE_CONFIG_TYPE;

typedef struct _rectangle_
{
    unsigned int X1;
    unsigned int Y1;
    unsigned int X2;
    unsigned int Y2;
}RECTANGLE;
//IVM_RULE_VFD_CONFIG
typedef struct _net_sdk_Vfd_Config
{
    unsigned int      bSwitch; //Ê¹ÄÜ£¬0 or 1
    unsigned int      alarmHoldTime;//±¨¾¯³ÖÐøÊ±¼ä
    unsigned int      saveFacePicture;//±£´æÈËÁ³¼ì²âÁ³Í¼Æ¬
    unsigned int      saveSourcePicture;//±£´æÈËÁ³¼ì²âÔ´Í¼Æ¬
    unsigned int      rectangleNum;
    RECTANGLE	rectangle;
    unsigned char	resv[40];
}NET_SDK_VFD_CONFIG;

//IVM_RULE_VFD_TRIGGER_CONFIG
typedef struct _net_sdk_Vfd_trigger_Config
{
    unsigned short    snapCHNum ; //Ö§³Ö×î´ó×¥Í¼Í¨µÀÊý
    unsigned char     snapChannelId;//×¥Í¼Í¨µÀ
    unsigned char     snapBswitch ;//×¥Í¼Ê¹ÄÜ
    unsigned short    recordCHNum ; //Ö§³Ö×î´óÂ¼ÏñÍ¨µÀÊý
    unsigned char     recordChannelId;//Â¼ÏñÍ¨µÀ
    unsigned char     recordBswitch ;//Â¼ÏñÊ¹ÄÜ
    unsigned short    alarmOutCHNum ; //Ö§³Ö×î´ó±¨¾¯Êä³öÊý
    unsigned char     alarmOutChannelId;//±¨¾¯Êä³öÍ¨µÀ
    unsigned char     alarmOutBswitch ;//±¨¾¯Êä³öÊ¹ÄÜ
    unsigned char     Resv[256];//±£Áô£¬½«À´ÓÃÓÚÀ©Õ¹¶àÍ¨µÀ

}NET_SDK_VFD_TRIGGER_CONFIG;

typedef struct
{
    unsigned char    byStartHour;
    unsigned char    byStartMin;
    unsigned char    byStopHour;
    unsigned char    byStopMin;
}NET_DVR_SCHEDTIME, *LPNET_DVR_SCHEDTIME;

typedef struct
{
    unsigned char    mounth;
    unsigned char    day;
    unsigned char    Resv[2];
    NET_DVR_SCHEDTIME sScheduleTime;

}NET_DVR_SCHEDDATE, *LPNET_DVR_SCHEDDATE; //°´ÌØ¶¨ÈÕÆÚ¶©µÄÅÅ³Ì

typedef struct
{
    unsigned int    wDay; //ÔÚÐÇÆÚÖÐµÄÌìÊý£¬ÖÜÌìÎª0£¬£¬£¬ÖÜÁùÎª6
    NET_DVR_SCHEDTIME sScheduleTime;

}NET_DVR_SCHEDWEEK, *LPNET_DVR_SCHEDWEEK;//¸ù¾ÝÐÇÆÚÊý¶©µÄÅÅ³Ì

//IVM_RULE_VFD_SCHEDULE_CONFIG
typedef struct
{
    unsigned int wDayCount; //sScheduleWeekÓÐÐ§¸öÊý
    unsigned int dayCount;  //sScheduleDate ÓÐÐ§¸öÊý
    NET_DVR_SCHEDWEEK sScheduleWeek[70]; //×î¶à¿ÉÒÔ¶©70¸ö
    NET_DVR_SCHEDDATE sScheduleDate[31]; //×î¶à¿ÉÒÔ¶©31¸ö  Öµ´óÐ¡À´×ÔipcµÄÐ­Òé

}NET_SDK_VFD_SCHEDULE_CONFIG;

//Óë±¸·ÝÏà¹Ø
typedef enum _net_sdk_backup_data_type
{
    NET_DVR_BACKUP_DATA_TYPE_DVR,
    NET_DVR_BACKUP_DATA_TYPE_AVI,
    NET_DVR_BACKUP_DATA_TYPE_NULL,
}NET_DVR_BACKUP_DATA_TYPE;

typedef struct _download_sdk_frame_info
{
    unsigned int		nLength;	//Ö¡Êý¾Ý³¤¶È
    unsigned short		frameType;	//²Î¿¼DD_FRAME_TYPE
    unsigned short		keyFrame;	//0£º·Ç¹Ø¼üÖ¡ 1£º¹Ø¼üÖ¡
    unsigned short		nWidth;		//»­Ãæ¿í, µ¥Î»ÏñËØ, Èç¹ûÊÇÒôÆµÊý¾ÝÔòÎª0
    unsigned short		nHeight;	//»­Ãæ¸ß, Èç¹ûÊÇÒôÆµÊý¾ÝÔòÎª0
    LONGLONG			nStamp;		//Ö¡Ê±¼ä, µ¥Î»ºÁÃë, ´Ó1970Äê1ÔÂ1ÈÕ0µã0·Ö0Ãë¿ªÊ¼µÄ¾ø¶ÔÊ±¼ä
}NET_DVR_DOWNlOAD_FRAME_INFO;

typedef enum _net_sdk_backup_status
{
    NET_DVR_BACKUP_STOP,
    NET_DVR_BACKUP_END,

}NET_DVR_BACKUP_STATUS;

typedef struct
{
    char                            serverAddress[256];             // ¶©ÔÄ±êÊ¶ ºóÆÚµÄÐø¶©ºÍÍË¶©Ê¹ÓÃ
    long long                          currentTime;                    // µ±Ç°Ê±¼ä
    long long                          terminationTime;                // ÖÕÖ¹Ê±¼ä
    char                            resv[64];                       // ºóÆÚÀ©Õ¹ÓÃ
}NET_DVR_SUBSCRIBE_REPLY;


// ÖÇÄÜÊÂ¼þÀàÐÍ
typedef enum
{
    NET_DVR_SMART_AVD = 0,            // ÊÓÆµÒì³£Õï¶Ï¹¦ÄÜ¼ì²â
    NET_DVR_SMART_VFD,            // ÈËÁ³¼ì²â
    NET_DVR_SMART_VFD_MATCH,    //ÈËÁ³±È¶Ô
    NET_DVR_SMART_PEA,                  // ÇøÓòÈëÇÖ
    NET_DVR_SMART_OSC,                  // ÎïÆ·ÒÅÁô¼°¶ªÊ§
    NET_DVR_SMART_CPC,                  // ÈËÁ÷Á¿Í³¼Æ
    NET_DVR_SMART_CDD,                  // ÈËÈºÃÜ¶È¼ì²â
    NET_DVR_SMART_IPD,                  // ÈËÔ±ÈëÇÖÕì²â
	NET_IPC_SMART_VIHICLE,				//³µÅÆÊ¶±ð
	NET_IPC_SMART_AOIENTRY,             //½øÈëÇøÓò
	NET_IPC_SMART_AOILEAVE,             //Àë¿ªÇøÓò
	NET_DVR_SMART_VFD_MATCH_FAILED,    //ÈËÁ³±È¶ÔÊ§°Ü¡£Õë¶ÔÄ°ÉúÈË
	NET_IPC_SMART_PASSLINE,             //¹ýÏßÍ³¼Æ

}NET_DVR_SMART_TYPE;

typedef struct
{
    int X;
    int Y;
}NET_DVR_IVE_POINT_T;
typedef struct
{
    LONGLONG      time;            //¼ì²âÔ´Êý¾Ýµ±Ç°Ê±¼ä /* Î¢Ãë¼¶ */
    LONGLONG      relativeTime;    //¼ì²âÔ´Êý¾ÝÏà¶ÔÊ±¼ä /* Î¢Ãë¼¶ */
    unsigned int     detectDataLen;   //¼ì²âÔ´Êý¾Ý³¤¶È
    unsigned int     softwareVersion; //Èí¼þ°æ±¾ºÅ, 0xABCDEFGH,AB£º³§¼Ò CD£ºÖ÷°æ±¾ EFGH£º×Ó°æ±¾ ³§ÉÌ 1:Å·Ä·Áú °æ±¾:V5.00
    unsigned int     softwareBuildDate;//Èí¼þÉú³ÉÈÕÆÚ,0xYYYYMMDD
    unsigned int     faceCnt;         //ÈËÁ³µÄ¸öÊý£¬×î´ó40¸ö
    unsigned int     faceDataLen[40]; //Ã¿¸öÈËÁ³µÄ³¤¶È
}NET_DVR_IVE_VFD_RESULT_HEAD_T;

typedef struct
{
    unsigned int     type;  ///<: 0, JPG; 1, YUV
    unsigned int     status; ///<:0, INVALID; 1, VALID; 2, SAVED
    unsigned int     width;
    unsigned int     height;
    unsigned int     dataLen;
}NET_DVR_IVE_VFD_RESULT_DATA_INFO_T;

typedef struct
{
    int                      faceId;         /* face ID Number */
    unsigned int                     ptWidth;        /*×ø±ê±ÈÀý¿í*/
    unsigned int                     ptHeight;       /*×ø±ê±ÈÀý¸ß*/
    NET_DVR_IVE_POINT_T                 ptLeftTop;      /* Left-Top     Face Coordinates    */
    NET_DVR_IVE_POINT_T                 ptRightTop;     /* Right-Top    Face Coordinates    */
    NET_DVR_IVE_POINT_T                 ptLeftBottom;   /* Left-Bottom  Face Coordinates    */
    NET_DVR_IVE_POINT_T                 ptRightBottom;  /* Right-Bottom Face Coordinates    */
    int                      nPose;          /* Face Pose                        */
    int                      nConfidence;    /* Confidence Degree                */
    int                      age;
    int                      sex;
    int                      dtFrames;
    int                         featureSize;
    NET_DVR_IVE_POINT_T                 stPosFaceImg;  //ÈËÁ³×óÉÏ½Ç×ø±ê(ÔÚ¼ì²âÔ´Í¼Æ¬µÄÎ»ÖÃ)

	//begin ÐÂÔöËã·¨²¿·Ö¸øµÄ²ÎÊý 
	float                       feature_score;      // ÌØÕ÷ÖµÅÐ¶ÏÈËÁ³¿ÉÐÅ¶È0~100

	/*ÒÔÏÂ±äÁ¿ÎªIFaceDetectorEx½Ó¿ÚÖ§³Ö£¬Îª¸ºÊýÊ±ÎªÎÞÐ§×´Ì¬*/
	short                       eye_dist;           // Ë«ÑÛ¾àÀë
	short                       blur;               // Ä£ºý¶È

	char                        pose_est_score;     // ÈËÁ³×ËÌ¬ÆÀ¹À·ÖÊý0~100
	char                        detect_score;       // ¼ì²âËã·¨ÅÐ¶ÏÈËÁ³¿ÉÐÅ¶È0~100
	char                        illumination;       // ¿ÙÍ¼ÇøÓòÆ½¾ùÁÁ¶È
	char                        faceliveness;       // »îÌå0~100  

	char                        completeness;       // ÕÚµ²0~100
	char                        glasses;            // ÊÇ·ñ´÷ÑÛ¾µ
	char                        wearmask;           // ÊÇ·ñ´÷¿ÚÕÖ:0ÊÇÎ´¼ì²â£¬1ÊÇÎ´´÷¿ÚÕÖ 2ÊÇ´÷¿ÚÕÖ
	char                        reserved1[1];

	float                       comprehensive_score;   // ×ÛºÏÆÀ·Ö [90,100)ÊÇÓÅÐã£¬ [80,90)ÊÇÁ¼ºÃ£¬[70,80)ÊÇÒ»°ã£¬[60,70)ÊÇºÏ¸ñ£¬[50,60)¿ÉÑ¡£¬[0,50)²î¡£
	//end ÐÂÔöËã·¨²¿·Ö¸øµÄ²ÎÊý 
	int                      temperature;        //ÌåÎÂ

	int                      foreheadX;          //¶îÍ·×ø±ê£¨ÁÙÊ±Ìí¼Ó£©
	int                      foreheadY;          //¶îÍ·×ø±ê£¨ÁÙÊ±Ìí¼Ó£©

	NET_DVR_IVE_POINT_T      stHotLeftTop;       //ÈÈ³ÉÏñÈËÁ³×óÉÏ×ø±ê
	NET_DVR_IVE_POINT_T      stHotRightBottom;   //ÈÈ³ÉÏñÈËÁ³ÓÒÏÂ×ø±ê
	char                     cTemperatureMode;   //ÈÈ³ÉÏñ²âÎÂÄ£Ê½£¬0±íÊ¾Õý³£²âÎÂÄ£Ê½£¬1±íÊ¾ÎÂ¶È½ÃÕýÄ£Ê½
	char                     tempUnitsType;      //ÎÂ¶Èµ¥Î»£¬0ÉãÊÏ¶È£¬1»ªÊÏ¶È
	char                     cTemperatureStatus; //ÌåÎÂ×´Ì¬£¬0ÌåÎÂÕý³££¬1µÍÎÂÒì³££¬2¸ßÎÂÒì³£

	char                      reserved[5];
    NET_DVR_IVE_VFD_RESULT_DATA_INFO_T  stFaceImgData;
}NET_DVR_IVE_VFD_RESULT_FACE_DATA_INFO_T;


//IVM_RULE_AVD_CONFIG
typedef struct _net_sdk_AVD_Config
{
    unsigned int      alarmHoldTime; //±¨¾¯³ÖÐøÊ±¼ä
    unsigned int      sceneChangeSwitch;//³¡¾°±ä¸üÊ¹ÄÜ£¬0 or 1
    unsigned int      clarityAbnormalSwitch;//ÊÓÆµÄ£ºýÊ¹ÄÜ£¬0 or 1
    unsigned int      colorAbnormalSwitch;//ÊÓÆµÆ«É«Ê¹ÄÜ£¬0 or 1
    unsigned int      sensitivity;
    unsigned int      maxSensitivity;
    unsigned int      minSensitivity;
    char              resv[40];

}NET_SDK_AVD_CONFIG;

typedef struct
{
    unsigned int      eventId;               // ÊÂ¼þID
    unsigned int      status;                // ±¨¾¯×´Ì¬,0:none 1:start 2:end 3:procedure
    unsigned int      type;                  // ±¨¾¯ÀàÐÍ,0:none 1:Scene 2:Clarity 3:Color
}NET_SDK_IVE_AVD_INFO_T;

typedef struct
{
    unsigned int          count;             // ¸öÊý
    NET_SDK_IVE_AVD_INFO_T   avdInfo[32];       // Òì³£Õì²âÐÅÏ¢
}NET_SDK_IVE_AVD_T;

typedef struct
{
    unsigned int X1;   // ×óÉÏ½Çx×ø±ê
    unsigned int Y1;   // ×óÉÏ½Çy×ø±ê
    unsigned int X2;   // ÓÒÏÂ½Çx×ø±ê
    unsigned int Y2;   // ÓÒÏÂ½Çy×ø±ê
}NET_SDK_IVE_RECT_T;

typedef struct
{
    unsigned int X1;   // Æðµãx×ø±ê
    unsigned int Y1;   // Æðµãy×ø±ê
    unsigned int X2;   // ÖÕµãx×ø±ê
    unsigned int Y2;   // ÖÕµãy×ø±ê
}NET_SDK_IVE_LINE_T;

typedef struct
{
    int X;
    int Y;
}NET_SDK_IVE_POINT_T;

typedef struct
{
    unsigned int       length;               // ¹ì¼£³¤¶È£¬¼´¸öÊý
    NET_SDK_IVE_POINT_T   points[32];           // ÖÐÐÄµã×ø±ê
}NET_SDK_IVE_TRAJECT_T;

typedef struct
{
    unsigned int          targetId;          // Ä¿±êID
    NET_SDK_IVE_POINT_T      point;             // µ±Ç°Î»ÖÃÖÐÐÄµã×ø±ê
    NET_SDK_IVE_RECT_T       rect;              // Ä¿±êÂÖÀª¾ØÐÎ¿ò
    unsigned int           velocity;          // ËÙ¶È
    unsigned int           direction;         // ·½Ïò
    NET_SDK_IVE_TRAJECT_T    traject;           // ¹ì¼£
}NET_SDK_IVE_TGT_INFO_T;

typedef struct
{
    unsigned int         targetNum;          // ¸öÊý
    NET_SDK_IVE_TGT_INFO_T  targetInfo[32];
}NET_SDK_IVE_TARGET_T;                          // Ä¿±êÐÅÏ¢£¬¼´¹ì¼£

typedef struct
{
    unsigned int      pointNum;              // ÇøÓò°üº¬µãµÄ¸öÊý£¨0»ò3µ½8£©
    NET_SDK_IVE_POINT_T  point[32];             // µãµÄ×ø±êÐÅÏ¢
}NET_SDK_IVE_RULE_BOUNDARY_T;

typedef struct
{
    unsigned int                eventId;     // ÊÂ¼þID
    unsigned int                status;      // ±¨¾¯×´Ì¬,0:none 1:start 2:end 3:procedure
    unsigned int                targetId;    // Ä¿±êID
    NET_SDK_IVE_RULE_BOUNDARY_T    boundary;    // ÇøÓòÈëÓò¹æÔòÐÅÏ¢
    NET_SDK_IVE_RECT_T             rect;        // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_PER_INFO_T;

typedef struct
{
    unsigned int          count;             // ¸öÊý
    NET_SDK_IVE_PER_INFO_T   perInfo[32];       // ÇøÓòÈëÇÖ·ÖÎö½á¹ûÐÅÏ¢
}NET_SDK_IVE_PERIMETER_T;

typedef struct
{
    unsigned int         eventId;            // ÊÂ¼þID
    unsigned int         status;             // ±¨¾¯×´Ì¬,0:none 1:start 2:end 3:procedure
    unsigned int         targetId;           // Ä¿±êID
    NET_SDK_IVE_LINE_T      line;               // °íÏß¹æÔòÐÅÏ¢
    NET_SDK_IVE_RECT_T      rect;               // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_TRIP_INFO_T;

typedef struct
{
    unsigned int          count;             // ¸öÊý
    NET_SDK_IVE_TRIP_INFO_T  tripInfo[32];      // °íÏß·ÖÎö½á¹ûÐÅÏ¢
}NET_SDK_IVE_TRIPWIRE_T;

typedef struct
{
    NET_SDK_IVE_PERIMETER_T   perimeter;        // ÇøÓòÈëÇÖ
    NET_SDK_IVE_TRIPWIRE_T    tripwire;         // °íÏß¼ì²â
}NET_SDK_IVE_PEA_T;
typedef struct
{
    unsigned int      eventId;               // ÊÂ¼þID
    unsigned int      status;                // 0:none 1:start 2:end 3:procedure
    unsigned int      targetId;              // Ä¿±êID
    NET_SDK_IVE_RECT_T   rect;                  // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_OSC_INFO_T;

typedef struct
{
    unsigned int          count;             // ¸öÊý
    NET_SDK_IVE_OSC_INFO_T   oscInfo[32];       // ÎïÆ·¿´»¤ÐÅÏ¢
}NET_SDK_IVE_OSC_T;

typedef struct
{
    NET_SDK_IVE_RECT_T              stRectInfo;                     // Ä¿±ê¾ØÐÎ¿ò
    unsigned char                  iCrossLineType;                 // ¿çÏßÀàÐÍ
}NET_SDK_IVE_CPC_INFO_T;

typedef struct
{
    unsigned long long                  iRelativeTick;                  // Ê±¼ä´Á
//    IVE_RECT_T              stRectInfo;                     // Ä¿±ê¾ØÐÎ¿ò
//    IVE_LINE_T              stLineInfo;                     // Ïß¶ÎÐÅÏ¢
    unsigned int                 iCrossInNum;                    // ¿çÏßÀàÐÍIµÄÈËÊý
    unsigned int                 iCrossOutNum;                   // ¿çÏßÀàÐÍIIµÄÈËÊý
}NET_SDK_IVE_CPC_HEAD_INFO_T;

typedef struct
{
    unsigned int                 iRatio;                         // ÈËÈºÃÜ¶ÈµÈ¼¶
    NET_SDK_IVE_RECT_T              rect;                           // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_CDD_INFO_T;

typedef struct
{
    unsigned int                 iTargerId;                      // Ä¿±êIDºÅ
    NET_SDK_IVE_RECT_T              rect;                           // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_IPD_INFO_T;

typedef struct
{
    unsigned long long                  iRelativeTick;                  // Ê±¼ä´Á
    bool                    bTriggerAlarm;                  // ÊÇ·ñ´¥·¢ÁË±¨¾¯
//    IVE_RECT_T              stRectInfo;                     // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_IPD_HEAD_INFO_T;

typedef struct
{
    DD_TIME_EX  frameTime;   //Ö¡Ê±¼ä
	unsigned int dwRealFaceID;  //×¥ÅÄÈËÁ³ID
	unsigned int dwGrpID;       //ÌØÕ÷×éID
	unsigned int dwLibFaceID;   //ÌØÕ÷¿âÈËÁ³ID
	unsigned int dwSimilar;     //ÏàËÆ¶È
	unsigned char byName[32]; //ÐÕÃû
    unsigned int Channel;         //Í¨µÀID
	#ifdef __CHONGQING_ZHONGRAN__
	char    szCredential[DD_MAX_CERTIFICATE_NUM];  //Ö¤¼þºÅÂë, '\0' ½áÊø,¾ßÓÐÎ¨Ò»ÐÔ
	char    serialNumber[32];  //ÐòÁÐºÅ
	
	#endif
	unsigned int imgLen;      //ÈËÁ³Êý¾Ý³¤¶È
	#ifdef __CHONGQING_ZHONGRAN__
	unsigned int BackLen;     //±³¾°´óÍ¼Êý¾Ý³¤¶È
	#endif
}NET_SDK_IVE_FACE_MATCH_T;
//ÈËÁ³ÌØÕ÷¿âÕªÒªÐÅÏ¢
typedef struct _net_sdk_tag_avp_store_face_abstract_info
{
	char szName[32];                                    //Ãû³Æ
	unsigned int dwBirth;                    //³öÉúÈÕÆÚ,Èç19991234
	char szNativePlace[16];             //¼®¹á
	char szNote[16];                  //±¸×¢
	unsigned char byPicNum;                    //Í¼Æ¬ÊýÁ¿£¬×î´ó5ÕÅ
	unsigned char byTypeCredential;            //Ö¤¼þÀàÐÍ
	unsigned char bySex;                       //ÐÔ±ð 0 male      1 female
	unsigned char byGroupCount;                //ËùÊô×éID
	unsigned char byGroupID[4];
	union
	{
		struct
		{
			unsigned int dwStartTime;
			unsigned int dwReserve[3];
			unsigned int dwEndTime;
			unsigned char  byReserve[11];
			unsigned char  byContentType;/////0=V1,1=V2......
		}PeriodV1;

		struct
		{
			unsigned int  byWeekOrDate;////everyday  date,   1  2   3  4   5   6  7
			unsigned int  dwReserve[3];
			unsigned short  wStartTime;
			unsigned short  wEndTime;
			unsigned short  wReserve[5];
			unsigned char   byMode;////byWeek   byDate
			unsigned char   byContentType;/////0=V1,1=V2......
		}PeriodV2;

		struct
		{
			unsigned char  dwReserve[31];
			unsigned char  byContentType;/////0=V1,1=V2......
		}PlaceHolder;
	}TimeCycle;////

	char szCredential[32];              //Ö¤¼þºÅÂë, '\0' ½áÊø     ¾ßÓÐÎ¨Ò»ÐÔ
	unsigned char   byPhoneNum[16];            //ÊÖ»úºÅÂë
	unsigned char   byIDParam[16];             /////¾ßÓÐÎ¨Ò»ÐÔ
}NET_SDK_AVPSTORE_FACE_ABSTRACT_INFO;

typedef struct _net_sdk_tag_TLV_buffer_description 
{
	unsigned char ucID;                        //1B,Êý¾ÝID,ÓÉÓ¦ÓÃ·½¶¨Òå
	unsigned char ucVersion;        //1B,Êý¾Ý°æ±¾,ÓÉÓ¦ÓÃ·½¶¨Òå
	unsigned short usNumber;        //2B,µ¥Î»ÊýÁ¿,×î¶à65535
	unsigned int dwSize;            //4B,µ¥¸öÐÅÏ¢´óÐ¡, ×Ü³¤¶È=usNumber*dwSize
}NET_SDK_TLV_BUFFER_DESC;
typedef struct
{
	unsigned short usPureFeatureSize; //²»°üº¬±¾½á¹¹Ìå 
	unsigned char byAlgVersion1;
	unsigned char byFeatureType; //Feature_Type

	unsigned char byManufactory;//Feature_Manufactory
	unsigned char byHeaderSize;
	unsigned char byAlgVersion2;
	unsigned char byReserved; //set it to be zero
}NET_SDK_FEATURE_DATA_HEADER; //´ËÍ·³¤¶È²»µÃ³¬¹ý NVMS_DEFINE::SERIALIZED_FEATUR_HEADER_MAX_SIZE

typedef struct
{
    unsigned int          minValue;             // ×îÐ¡Öµ
    unsigned int          maxValue;             // ×î´óÖµ
    unsigned int          curValue;             // µ±Ç°Öµ
    unsigned int          defaultValue;             // Ä¬ÈÏÖµ

}NET_SDK_IMAGE_EFFECT_T;

typedef struct _net_sdk_ch_device_status_
{
    unsigned short	channel;				//Í¨µÀ(´Ó0¿ªÊ¼)
    unsigned short	status;					//Á¬½Ó×´Ì¬£¨0:offline£¬videoloss. 1: online,signal£©
    unsigned int    chlType;               //E_DIGITAL_CHL_TYPE,Êý×ÖÍ¨µÀ E_ANALOG_CHL_TYPE,Ä£ÄâÍ¨µÀ
    char	         name [DD_MAX_CAMERA_NAME_BUF_LEN];
    unsigned char	resv[32];				//ÔÝÊ±Î´ÓÃÉÏ
}NET_SDK_CH_DEVICE_STATUS;

typedef struct _net_sdk_ch_device_support_
{
	unsigned short	channel;				//Í¨µÀ(´Ó0¿ªÊ¼)
	unsigned char	supportFisheye;				//ÊÇ·ñÖ§³ÖÓãÑÛ

	unsigned char	resv[33];				//ÔÝÊ±Î´ÓÃÉÏ

}NET_SDK_CH_DEVICE_SUPPORT;


//ÈËÁ³¶Ô±È
typedef enum _net_sdk_face_info_group__property_type
{
    NET_SDK_FACE_INFO_GROUP_PROPERTY_ALLOW,
    NET_SDK_FACE_INFO_GROUP_PROPERTY_REJECT,
    NET_SDK_FACE_INFO_GROUP_PROPERTY_LIMITED,

}NET_SDK_FACE_INFO_GROUP_PROPERTY_TYPE;

typedef struct _net_sdk_face_info_group_item_
{
    unsigned char	guid[48];				//GROUP GUID
    char	         name[DD_MAX_NAME_LEN];//GROUP NAME
    unsigned int	property;		//NET_SDK_FACE_INFO_GROUP_PROPERTY_TYPE
    unsigned int    groupId;               //
    unsigned int    enableAlarmSwitch;

}NET_SDK_FACE_INFO_GROUP_ITEM;

typedef struct _net_sdk_face_info_group_add_
{
    char	         name[DD_MAX_NAME_LEN];//GROUP NAME
    unsigned int	property;		//NET_SDK_FACE_INFO_GROUP_PROPERTY_TYPE
}NET_SDK_FACE_INFO_GROUP_ADD;

typedef struct _net_sdk_face_info_group_del_
{
    unsigned char	guid[48];				//GROUP GUID
}NET_SDK_FACE_INFO_GROUP_DEL;

//Á½Õß¿ÉÈÎÑ¡ÆäÒ»
typedef struct _net_sdk_face_info_group_del_ex_
{
    unsigned int	groupId;				//GROUP ID ¹úÄÚ¶¨ÖÆ°æ±¾ÓÃ´Ë²ÎÊý
    unsigned char   guid[48];				//GROUP GUID Í¨ÓÃ°æ±¾ÓÃ´Ë²ÎÊý
}NET_SDK_FACE_INFO_GROUP_DEL_EX;

typedef struct _net_sdk_face_info_list_get_
{			
    unsigned int	pageIndex;		//±ØÌî1¡¢2¡¢3...
    unsigned int    pageSize;   //±ØÌî
    unsigned int    groupId;//±ØÌî 1¡¢2¡¢3....

    char	        name[DD_MAX_NAME_LEN];//²»ÌîÊ±Çå¿Õ NET_SDK_FACE_INFO_LIST_ITEMÖÐµÄname
    unsigned int    itemId;				//²»ÌîÊ±ÇåÁã NET_SDK_FACE_INFO_LIST_ITEMÖÐµÄitemId
    #ifdef __CHONGQING_ZHONGRAN__
    char	        certificateNum[DD_MAX_CERTIFICATE_NUM];		//
    #endif
}NET_SDK_FACE_INFO_LIST_GET;

typedef struct _net_sdk_face_info_list_item_groups_
{
    unsigned int    groupId;        //GROUP id »ñÈ¡Ä¿±êlist·µ»ØµÄÊ±ºòÃ»ÓÐ guid
    unsigned char	guid[48];				//GROUP GUID Ôö¼Ó£¬±à¼­Ä¿±ê±ØÐëÒªÓÃ guid
    DD_TIME_EX    validStartTime;//propertyÎªlimitedÊ±²ÅÓÐvalidStartTime£¬validEndTime
    DD_TIME_EX    validEndTime;//propertyÎªlimitedÊ±²ÅÓÐvalidStartTime£¬validEndTime
}NET_SDK_FACE_INFO_LIST_ITEM_GROUPS;

typedef struct _net_sdk_face_info_list_item_
{
    unsigned int    itemId;				//id
    char	        name[DD_MAX_NAME_LEN];		//±ØÌî
    unsigned int    sex; //0:male 1:female
    unsigned int    birthday;//eg:19900707
    char	        nativePlace[DD_MAX_NAME_LEN];		//
    unsigned int    certificateType; //0:idCard
    char	        certificateNum[DD_MAX_CERTIFICATE_NUM];		//
    char	        mobile[20];		//
    char	        number[20];		//
    unsigned int    faceImgCount;
    NET_SDK_FACE_INFO_LIST_ITEM_GROUPS    groups[DD_MAX_FACE_INFO_GROUPS];

}NET_SDK_FACE_INFO_LIST_ITEM;

typedef struct _net_sdk_face_info_list_
{
    unsigned int    totalNum;				//
    unsigned int    listNum;//return NET_SDK_FACE_INFO_LIST_ITEM num
    NET_SDK_FACE_INFO_LIST_ITEM *pFaceInfoListItem;
}NET_SDK_FACE_INFO_LIST;

typedef struct _net_sdk_face_img_info_ch_
{
    DD_TIME_EX         frameTime;
    unsigned int    snapImgId;//×¥ÅÄÍ¼Æ¬id
	unsigned int    targetImgId;//Ä¿±êÍ¼Æ¬id
    unsigned int    chl; //·µ»ØÖµ 255 ±íÊ¾ÒÑ¾­É¾³ýµÄÍ¨µÀ
	unsigned char   isPanorama;//0±íÊ¾×¥ÅÄÍ¼Æ¬£¬1±íÊ¾È«¾°Í¼
    unsigned char   resv[7];//±£Áô

}NET_SDK_FACE_IMG_INFO_CH;

typedef struct _net_sdk_face_info_add_
{

    NET_SDK_FACE_INFO_LIST_ITEM sFaceInfoItem;
    unsigned int                imgNum;
    NET_SDK_FACE_IMG_INFO_CH       sFaceImgInfo[DD_MAX_FACE_INFO_IMG];//×î´ó5ÕÅ
    unsigned int                haveImgData;//0¡¢1
    unsigned int                imgWidth;//haveImgData ==1 ÓÐÐ§
    unsigned int                imgHeight;//haveImgData ==1 ÓÐÐ§
    unsigned int                imgLen;//haveImgData ==1 ÓÐÐ§
    unsigned char               *imgData;//haveImgData ==1 ÓÐÐ§
}NET_SDK_FACE_INFO_ADD;

typedef struct _net_sdk_face_info_edit_
{
    unsigned int            delFaceImgs[DD_MAX_FACE_INFO_IMG];
    NET_SDK_FACE_INFO_ADD   sFaceInfoItem;

}NET_SDK_FACE_INFO_EDIT;
typedef struct _net_sdk_face_info_copy_
{

	unsigned int    itemId;				//id   Í¨¹ý´ËidÈ¥»ñÈ¡Í¼Æ¬
	char	        name[DD_MAX_NAME_LEN];		//±ØÌî
	unsigned int    sex; //0:male 1:female
	unsigned int    birthday;//eg:19900707
	char	        nativePlace[DD_MAX_NAME_LEN];		//
	unsigned int    certificateType; //0:idCard
	char	        certificateNum[DD_MAX_CERTIFICATE_NUM];		//
	char	        mobile[20];		//
	char	        number[20];		//

	//NET_SDK_FACE_INFO_LIST_ITEM_GROUPS    groups¡¾0¡¿.guid
	unsigned char	guid[48];				//GROUP GUID Ôö¼Ó£¬±à¼­Ä¿±ê±ØÐëÒªÓÃ guid     Ä¿±ê¿âµÄguid



}NET_SDK_FACE_INFO_COPY;

typedef struct _net_sdk_face_info_del_
{
    unsigned int    faceInfoListItemId;//NET_SDK_FACE_INFO_LIST_ITEMÖÐµÄitemId
    unsigned int    groupsId[DD_MAX_FACE_INFO_GROUPS];//NET_SDK_FACE_INFO_LIST_ITEMÖÐµÄitemId-->groups-->groupId

}NET_SDK_FACE_INFO_DEL;

typedef struct _net_sdk_face_match_alarm_trigger_
{
    unsigned char	guid[48];	//GROUP GUID
    unsigned int    groupId;    //×éID
    unsigned char    groupSwitch;//ÆôÓÃ
    unsigned char    alarmOutSwitch;//Áª¶¯±¨¾¯Êä³ö
    unsigned char    alarmOut[16];//Áª¶¯±¨¾¯Êä³öÄ¬ÈÏ×î¶à16¸ö ÏÂ±ê´Ó1¿ªÊ¼
    unsigned char    recSwitch;//Â¼Ïñ
    unsigned int    recCH[128];//Áª¶¯Â¼ÏñÍ¨µÀ ÏÂ±ê´Ó1¿ªÊ¼
    unsigned char    snapSwitch;//×¥Í¼
    unsigned int    snapCH[128];//Áª¶¯×¥Í¼Í¨µÀ ÏÂ±ê´Ó1¿ªÊ¼
    unsigned int    popVideo;//ÊÓÆµµ¯³ö
    unsigned char    msgPushSwitch;
    unsigned char    buzzerSwitch;
    unsigned char    popMsgSwitch;
    unsigned char    emailSwitch;

}NET_SDK_FACE_MATCH_ALARM_TRIGGER;

typedef struct _net_sdk_face_match_chan_group_
{
	unsigned int    faceFeatureGroupsNum;  //Í¨µÀÓµÓÐµÄÄ¿±ê×é¸öÊý
    unsigned int    pfaceFeatureGroupIDs[16]; //Í¨µÀÓµÓÐµÄÄ¿±ê×éIDÁÐ±í,ÓÐÐ§¸öÊýÎªfaceFeatureGroupsNum
}NET_SDK_FACE_MATCH_CHAN_GROUP;

typedef struct _net_sdk_face_match_alarm_
{
    unsigned int    similarity;//ÏàËÆ¶È
    unsigned int    enableCH[128];//¡¾¿ªÆôÍ¨µÀ¡¿ Í¨µÀÏÂ±ê´Ó1¿ªÊ¼
	#ifdef __CHONGQING_ZHONGRAN__
	NET_SDK_FACE_MATCH_CHAN_GROUP FaceMatchChanGroup[128]; //Óë¡¾¿ªÆôÍ¨µÀ¡¿ÑÏ¸ñ¶ÔÓ¦
	#endif
    unsigned int    faceFeatureGroupsNum;//Ä¿±ê×é¸öÊý
    NET_SDK_FACE_MATCH_ALARM_TRIGGER *pFaceMatchAlarmTrigger;

}NET_SDK_FACE_MATCH_ALARM;

typedef struct _net_sdk_face_info_img_get_
{

    unsigned int    itemId;	//Ä¿±êid
    unsigned int    index;//faceImgCountÖÐµÄindex 1¿ªÊ¼

}NET_SDK_FACE_INFO_IMG_GET;

typedef struct _net_sdk_face_info_img_data_
{
    unsigned int                imgLen;//Ä¿±êÍ¼Æ¬³¤¶È
	unsigned int				grade;//ÈËÁ³ÆÀ·Ö
    unsigned char               *imgData;//Ä¿±êÍ¼Æ¬Êý¾Ý

}NET_SDK_FACE_INFO_IMG_DATA;

typedef enum _net_sdk_search_image_by_image_type_
{
    SEARCH_IMAGE_BY_FACE_FEATURES,//Í¨¹ýÈËÁ³ÌØÕ÷ËÑË÷
    SEARCH_IMAGE_BY_FACE_IMAGES,//Í¨¹ýÈËÁ³Í¼Æ¬ËÑË÷
    SEARCH_IMAGE_BY_FACE_FEATURE_GROUPS,//Í¨¹ýÈËÁ³ÌØÕ÷·Ö×éËÑË÷
    SEARCH_IMAGE_BY_RECONGNIZED_FILTER,//Í¨¹ýÓëÖ¸¶¨ÈËÁ³ÌØÕ÷·Ö×é±È¶ÔÊÇ·ñÊ¶±ð½øÐÐ¹ýÂË
    SEARCH_IMAGE_BY_FACE_IMAGE_DATA,//Í¨¹ýÍ¼Æ¬Êý¾Ý½øÐÐËÑË÷

}NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE;


typedef struct _net_sdk_search_image_by_image_
{
    unsigned int	pageIndex;		//±ØÌî1¡¢2¡¢3...
    unsigned int    pageSize;   //±ØÌî
    unsigned int    similarity;		//ÏàËÆ¶È
    unsigned int    resultCountLimit;		//½á¹û¸öÊýÏÞÖÆ
    DD_TIME_EX    startTime;
    DD_TIME_EX    endTime;
    unsigned int searchType;//NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE
    struct
    {
       unsigned int itemId;	//Ä¿±êid
    } sfaceFeatures;//SEARCH_IMAGE_BY_FACE_FEATURES
    NET_SDK_FACE_IMG_INFO_CH sfaceImgs;//SEARCH_IMAGE_BY_FACE_IMAGES

    struct
    {
       unsigned int	groupsId;				//GROUP Id
    }sfaceFeatureGroups ;//SEARCH_IMAGE_BY_FACE_FEATURE_GROUPS

    struct
    {
       unsigned int     isContainRecognized; //0 or 1
       unsigned int     isContainNotRecognized; //0 or 1
       unsigned int     groupsId;				//GROUP Id
    }srecognizedFilter ;//SEARCH_IMAGE_BY_RECONGNIZED_FILTER
    struct
    {
        unsigned int                imgWidth;//
        unsigned int                imgHeight;//
        unsigned int                imgLen;//
        unsigned char               *imgData;//
    }sfaceImgData;//SEARCH_IMAGE_BY_FACE_IMAGE_DATA

}NET_SDK_SEARCH_IMAGE_BY_IMAGE;

typedef struct _net_sdk_search_image_by_image_v2
{
	unsigned int    limitNum;   //±ØÌî
	DD_TIME_EX    startTime;
	DD_TIME_EX    endTime;

	unsigned int    similarity;		//ÏàËÆ¶È
	unsigned int searchType;//NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE_V2
	unsigned int imgSourceType;//Í¼Æ¬À´Ô´£¬µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±ÓÃµ½£¬NET_SDK_SEARCH_IMAGE_SOURCE_V2

	unsigned int imgNum;//Í¼Æ¬idÊýÁ¿£¬µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_ALBUMÓÃµ½
	unsigned int *imgId;//Í¼Æ¬id£¬µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_ALBUMÓÃµ½
	unsigned int eventType;//µ±searchTypeÎªSEARCH_IMAGE_BY_EVENTÊ±ÓÃµ½£¬NET_SDK_SEARCH_IMAGE_BY_EVENT_TYPE_V2

	unsigned int groupsNum;//Ä¿±ê¿âÊýÁ¿£¬µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_GROUPÓÃµ½
	unsigned int *groupsId;	//Ä¿±ê¿âId£¬µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_GROUPÓÃµ½

	unsigned int sfaceImgsNum;//Í¼Æ¬ÊýÁ¿£¬µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_SNAPÓÃµ½
	NET_SDK_FACE_IMG_INFO_CH *sfaceImgs;//SEARCH_IMAGE_BY_FACE_IMAGES,µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_SNAPÓÃµ½

	struct
	{
		unsigned int                imgWidth;//
		unsigned int                imgHeight;//
		unsigned int                imgLen;//
		unsigned char               *imgData;//
	}sfaceImgData;//µ±searchTypeÎªSEARCH_IMAGE_BY_IMAGEÊ±,imgSourceTypeÎªFROM_EXTERNALÓÃµ½

}NET_SDK_SEARCH_IMAGE_BY_IMAGE_V2;
typedef enum _net_sdk_search_image_by_image_type_v2
{
	SEARCH_IMAGE_BY_IMAGE,//Í¨¹ýÈËÁ³Í¼Æ¬ËÑË÷
	SEARCH_IMAGE_BY_EVENT,//Í¨¹ýÊÂ¼þËÑË÷

}NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE_V2;
typedef enum _net_sdk_search_image_by_event_v2
{
	BY_ALL,//ËÑË÷¡°ËùÓÐ¡± byAll
	BY_WHITELIST,//ËÑË÷¡°³£¹æ¡± byWhiteList
	BY_STRANGERLIST,//ËÑË÷¡°Ä°ÉúÈË¡±byStrangerList
	BY_BLACKLIST,//ËÑË÷¡°ºÚÃûµ¥¡±byBlackList
}NET_SDK_SEARCH_IMAGE_BY_EVENT_TYPE_V2;
typedef enum _net_sdk_search_image_source_v2
{
	FROM_ALBUM,//Í¼Æ¬À´×ÔÄ¿±ê¿â
	FROM_SNAP,//Í¼Æ¬À´×Ô×¥ÅÄ
	FROM_GROUP,//Í¼Æ¬À´×ÔÕû¸öÄ¿±ê¿âËùÓÐÄ¿±ê
	FROM_EXTERNAL,//Í¼Æ¬À´×Ô×ÔÑ¡Í¼Æ¬½öÖ§³ÖÒ»ÕÅ£¬´óÐ¡²»ÄÜ³¬¹ý200KB
}NET_SDK_SEARCH_IMAGE_SOURCE_V2;

typedef struct _net_sdk_search_image_item_
{
    DD_TIME_EX     recStartTime;
    DD_TIME_EX     recEndTime;
    unsigned int    similarity;		//ÏàËÆ¶È
    unsigned int    faceFeatureId; //Í¨¹ýÈËÁ³ÌØÕ÷ËÑË÷Ê±£¬ºÍÄÄ¸öÌØÕ÷Æ¥Åä
    NET_SDK_FACE_IMG_INFO_CH sfaceImg; //Í¨¹ýÈËÁ³Í¼Æ¬ËÑË÷Ê±£¬ºÍÄÄ¸öÍ¼Æ¬Æ¥Åä
    unsigned char       resv[4];//±£Áô

}NET_SDK_SEARCH_IMAGE_ITEM;

typedef struct _net_sdk_search_image_by_image_list_
{
    unsigned int    bEnd; //Îª1±íÊöËÑÍ¼¸öÊýÒÑ½áÊø£¬ 0±íÊ¾ºóÃæ»¹ÓÐ
    unsigned int    listNum;//return NET_SDK_SEARCH_IMAGE_ITEM num
    NET_SDK_SEARCH_IMAGE_ITEM *pSearchImageItem;
}NET_SDK_SEARCH_IMAGE_BY_IMAGE_LIST;


typedef struct _net_sdk_ch_snap_face_img_list_
{
    unsigned int    bEnd; //Îª1±íÊöËÑÍ¼¸öÊýÒÑ½áÊø£¬ 0±íÊ¾ºóÃæ»¹ÓÐ
    unsigned int    listNum;//return NET_SDK_FACE_IMG_INFO_CH num
    NET_SDK_FACE_IMG_INFO_CH *pCHFaceImgItem;
}NET_SDK_CH_SNAP_FACE_IMG_LIST;

typedef struct _net_sdk_ch_snap_face_img_list_sreach_
{
    DWORD			dwChannel;//×¥Í¼Í¨µÀ
    DD_TIME_EX			startTime; //Ê±¼ä
    DD_TIME_EX			endTime; //Ê±¼ä
    DWORD			pageIndex;//µÚ¼¸Ò³
    DWORD			pageSize;//Ã¿Ò³Êý

    unsigned char	resv[8];
}NET_SDK_CH_SNAP_FACE_IMG_LIST_SEARCH;
typedef struct _net_sdk_search_smart_target
{
	unsigned int    limitNum;   //±ØÌî
	DD_TIME_EX    startTime;
	DD_TIME_EX    endTime;
	unsigned char faceDetection;
	unsigned char faceMatchWhiteList;
	unsigned char faceMatchBlackList;
	unsigned char faceMatchStrangerList;
	unsigned char intrusion;
	unsigned char tripwire;
	unsigned char car;
	unsigned char motor;
	unsigned char male;
	unsigned char female;	
	unsigned char	resv[22];

}NET_SDK_SEARCH_SMART_TARGET;
typedef struct _net_sdk_smart_target_snap_img_
{
	DD_TIME_EX         frameTime;
	unsigned int    imgId;
	unsigned int    chl; //·µ»ØÖµ 255 ±íÊ¾ÒÑ¾­É¾³ýµÄÍ¨µÀ
	unsigned char	pathGUID[48];//Êý¾ÝËùÔÚµÄ´æ´¢GUID
	unsigned int	sectionNo;
	unsigned int	fileIndex;
	unsigned int	blockNo;
	unsigned int	offset;
	unsigned int	eventType;
	unsigned char   isPanorama;//0±íÊ¾×¥ÅÄÍ¼Æ¬£¬1±íÊ¾È«¾°Í¼
	unsigned char   resv[7];//±£Áô

}NET_SDK_SMART_TARGET_SNAP_IMG;
typedef struct _net_sdk_smart_target_snap_img_list_
{
	unsigned int    bEnd; //Îª1±íÊöËÑÍ¼¸öÊýÒÑ½áÊø£¬ 0±íÊ¾ºóÃæ»¹ÓÐ
	unsigned int    listNum;//return NET_SDK_SMART_TARGET_SNAP_IMG num
	NET_SDK_SMART_TARGET_SNAP_IMG *pImgItem;
}NET_SDK_SMART_TARGET_SNAP_IMG_LIST;
typedef enum _net_sdk_timequantum_type
{
	ONE_DAY,
	ONE_WEEK,
	ONE_MONTH,
	ONE_SEASON,
}NET_SDK_TIMEQUANTUM_TYPE;
typedef struct _net_sdk_face_img_statistic_v2
{
	unsigned int    limitNum;   //
	DD_TIME_EX    startTime;
	DD_TIME_EX    endTime;
	unsigned int  timeQuantum;//NET_SDK_TIMEQUANTUM_TYPE
	unsigned char faceDetection;
	unsigned char faceMatchWhiteList;
	unsigned char faceMatchBlackList;
	unsigned char faceMatchStranger;
	unsigned char intrusion;
	unsigned char tripwire;
	unsigned char car;
	unsigned char motor;
	unsigned char male;
	unsigned char female;	
	unsigned char	resv[22];

}NET_SDK_FACE_IMG_STATISTIC_V2;

typedef struct _net_sdk_face_img_statistic_result_chl
{
	unsigned int chlId;//
	unsigned int imageNum;

}NET_SDK_FACE_IMG_STATISTIC_RESULT_CHL;
typedef struct _net_sdk_face_img_statistic_result
{
	unsigned int imageTotalNum;
	unsigned int chlNum;
	NET_SDK_FACE_IMG_STATISTIC_RESULT_CHL *pItem;

}NET_SDK_FACE_IMG_STATISTIC_RESULT;
typedef struct _net_sdk_face_img_statistic_result_list
{
	unsigned int    resNum;//return NET_SDK_FACE_IMG_STATISTIC_RESULT num
	NET_SDK_FACE_IMG_STATISTIC_RESULT *pItem;
}NET_SDK_FACE_IMG_STATISTIC_RESULT_LIST;
//ÈËÁ³¿âÏà¹Ø
typedef enum _net_sdk_face_match_operate_type
{
    NET_SDK_GET_FACE_MATCH_SUPPORT=0x01,//in:NULL, out:DWORD
    //Ä¿±ê×é
    NET_SDK_GET_FACE_INFO_GROUP_LIST,//queryFacePersonnalInfoGroupList in:NULL, out:NET_SDK_FACE_INFO_GROUP_ITEM list
    NET_SDK_ADD_FACE_INFO_GROUP,//createFacePersonnalInfoGroup in:NET_SDK_FACE_INFO_GROUP_ADD out:NULL
    NET_SDK_SET_FACE_INFO_GROUP,//editFacePersonnalInfoGroup in:NET_SDK_FACE_INFO_GROUP_ITEM  out:NULL
    NET_SDK_DEL_FACE_INFO_GROUP,//delFacePersonnalInfoGroups in:NET_SDK_FACE_INFO_GROUP_DEL  out:NULL
    //Ä¿±ê
    NET_SDK_GET_FACE_INFO_LIST,//queryFacePersonnalInfoList in:NET_SDK_FACE_INFO_LIST_GET, out:NET_SDK_FACE_INFO_LIST
    NET_SDK_ADD_FACE_INFO,//createFacePersonnalInfo in:NET_SDK_FACE_INFO_ADD out:DWORD
    NET_SDK_SET_FACE_INFO,//editFacePersonnalInfo in:NET_SDK_FACE_INFO_EDIT out:NULL
    NET_SDK_DEL_FACE_INFO,//delFacePersonnalInfo in:NET_SDK_FACE_INFO_DEL  out:NULL
    //¶Ô±È±¨¾¯ÅäÖÃ
    NET_SDK_GET_FACE_MATCH_ALARM,//queryFaceMatchAlarm  in:NULL out:NET_SDK_FACE_MATCH_ALARM
    NET_SDK_SET_FACE_MATCH_ALARM,//editFaceMatchAlarm in:NET_SDK_FACE_MATCH_ALARM out:NULL
    //ÇëÇóÈËÁ³Ä¿±êÍ¼Æ¬
    NET_SDK_GET_FACE_INFO_IMG,//requestFacePersonnalInfoImage in:NET_SDK_FACE_INFO_IMG_GET out:NET_SDK_FACE_INFO_IMG_DATA
    //ÒÔÍ¼ËÑÍ¼ searchImageByImage
    NET_SDK_SEARCH_IMAGE_BY_IMG, //searchImageByImage in:NET_SDK_SEARCH_IMAGE_BY_IMAGE out:NET_SDK_SEARCH_IMAGE_BY_IMAGE_LIST
    //²éÑ¯Í¨µÀÈËÁ³Í¼Æ¬
    NET_SDK_SEARCH_CH_SNAP_FACE_IMG_LIST,//queryChSnapFaceImageList in:NET_SDK_CH_SNAP_FACE_IMG_LIST_SEARCH out:NET_SDK_CH_SNAP_FACE_IMG_LIST
    //ÇëÇóÍ¨µÀÈËÁ³Í¼Æ¬Êý¾Ý
    NET_SDK_SEARCH_CH_SNAP_FACE_IMG,//requestChSnapFaceImage in:NET_SDK_FACE_IMG_INFO_CH out:NET_SDK_FACE_INFO_IMG_DATA
    //For IPC£¬Ä¿±ê
//    -----------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO_T		|
//    -----------------------------------------
//    |	Í¼Æ¬Êý¾Ý							|
//    -----------------------------------------
    NET_SDK_ADD_FACE_IPC, //in:NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO out: NET_SDK_NET_REPLY_RESULT
    NET_SDK_DEL_FACE_IPC,//in:NET_SDK_IVE_FACE_MATCH_DELE_ALBUM_INFO out: NET_SDK_NET_REPLY_RESULT
//    -----------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO_T		|
//    ---------------------------------------------
//    |	Í¼Æ¬Êý¾Ý(Èç¹ûÎ´ÐÞ¸ÄÍ¼Æ¬, ÔòÃ»ÓÐ´Ë²¿·Ö)	|
    NET_SDK_EDIT_FACE_IPC, //in:NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO out: NET_SDK_NET_REPLY_RESULT

//    ÇëÇó:
//    ---------------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO		|
//    ---------------------------------------------
//    »Ø¸´:
//    -------------------------------------------------
//    |	int32	·ûºÏ²éÑ¯Ìõ¼þµÄ×ÜÊýÄ¿				|
//    -------------------------------------------------
//    |	int32	µ±Ç°´Î·µ»ØµÄ½á¹ûÌõÄ¿Êý				|
//    -------------------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO		|
//    -------------------------------------------------
//    |	Í¼Æ¬Êý¾Ý									|
//    -------------------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO		|
//    -------------------------------------------------
//    |	Í¼Æ¬Êý¾Ý									|
//    -------------------------------------------------
//    |	...											|
//    -------------------------------------------------
 //   ¸½¼ÓËµÃ÷: Êý¾Ý¶ÎÇ°1-4¸ö×Ö½Ú(int32)±íÊ¾·ûºÏÌõ¼þµÄ×ÜÌõÄ¿Êý, Ê§°Ü·µ»Ø<=0£¬¹Ì¶¨´æÔÚ; Êý¾Ý¶Î5-8¸ö×Ö½Ú(int32)±íÊ¾µ±Ç°´Î·µ»ØµÄÌõÄ¿Êý, ¹Ì¶¨´æÔÚ¡£
    NET_SDK_GET_FACE_IPC_LIST, //in:NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO out:¼ûÉÏ×¢ÊÍ

	NET_SDK_COPY_FACE_INFO,//
	NET_SDK_SEARCH_IMAGE_BY_IMG_V2,//
	NET_SDK_SEARCH_SMART_TARGET_LIST,//ËÑË÷Ä¿±ê
	NET_SDK_SEARCH_SMART_TARGET_IMG,//ËÑË÷Ä¿±êÍ¼Æ¬
	NET_SDK_GET_FACE_IMG_STATISTIC_V2,//ÇëÇóÍ³¼Æ
	NET_SDK_GET_FACE_INFO,//»ñÈ¡Ö¸¶¨idµÄÈËÁ³Ä¿±êÍ¼Æ¬ÐÅÏ¢

}NET_SDK_FACE_MATCH_OPERATE_TYPE;



typedef struct NET_SDK_IVE_BASE_INFO_T
{
	long long            i64SnapTime;               // ×¥ÅÄÊ±¼ä.
	unsigned int             iSnapPicId;                // ×¥ÅÄID.

	int                 iSimilarity;               // ÈËÁ³±È¶ÔÏàËÆ¶È.(0-100)
	int                 iPersonId;                 // ÈËÔ±ID.
	int                 iType;                     // Ãûµ¥ÀàÐÍ 0:Ä°ÉúÈË 1:°×Ãûµ¥ 2:ºÚÃûµ¥.
	char                szName[128];               // ÐÕÃû.
	int                 iMale;                     // ÐÔ±ð 1:male 0:female.
	int                 iAge;                      // ÄêÁä.
	char                szIdentifyNum[128];        // Éí·ÝÊ¶±ðºÅ.
	char                szTel[64];                 // µç»°.
	char                szRes[128];                // reserve

	int                 iSnapPicQuality;           // ×¥ÅÄÈËÁ³ÖÊÁ¿.
	int                 iSnapPicAge;               // ×¥ÅÄÈËÁ³ÄêÁä.
	int                 iSnapPicSex;               // ×¥ÅÄÈËÁ³ÐÔ±ð.

	char                livingBody;                     // ÊÇ·ñÊÇ»îÌå 1»îÌå,0·Ç»î
	char                comparisonRes;                  // ±È¶Ô½á¹û 1³É¹¦,0Ê§°Ü
    char                wearmask;                  // ÊÇ·ñ´÷¿ÚÕÖ:0ÊÇÎ´¼ì²â£¬1ÊÇÎ´´÷¿ÚÕÖ 2ÊÇ´÷¿ÚÕÖ
    char                tempUnitsType;             // ÎÂ¶Èµ¥Î» 0ÉãÊÏ¶È 1»ªÊÏ¶È
	int                 temperature;                    // ÌåÎÂ

	char                keyID[36];                  //ÈËÁ³¿âÖ÷¼ü
	char                szReserve[20];

}NET_SDK_IVE_BASE_INFO;


typedef struct NET_SDK_IVE_PICTURE_INFO_T
{
	int                 iWidth;                    // Í¼Æ¬¿í.
	int                 iHeight;                   // Í¼Æ¬¸ß.
	int                 iPicFormat;                // Í¼Æ¬¸ñÊ½.
	int                 iPicSize;                  // Í¼Æ¬´óÐ¡.

}NET_SDK_IVE_PICTURE_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO_T
{
    int                 iType;                     // Ãûµ¥ÀàÐÍ 0:Ä°ÉúÈË 1:°×Ãûµ¥ 2:ºÚÃûµ¥.
    char                szName[128];               // ÐÕÃû.
    int                 iMale;                     // ÐÔ±ð 1:male 0:female.
    int                 iAge;                      // ÄêÁä.
    char                szIdentifyNum[128];        // Éí·ÝÊ¶±ðºÅ.
    char                szTel[64];                 // µç»°.
    int                 iWidth;                    // Í¼Æ¬¿í.
    int                 iHeight;                   // Í¼Æ¬¸ß.
    int                 iPicFormat;                // Í¼Æ¬¸ñÊ½.
    int                 iPicSize;                  // Í¼Æ¬´óÐ¡.
    char                szRes[128];                // reserve

}NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO;
typedef struct _net_sdk_net_reply
{
    unsigned int dwResult;
}NET_SDK_NET_REPLY_RESULT;

typedef struct _net_sdk_ive_face_match_add_face_reply_t
{
	unsigned int             dwResult;
	int                 iPersonId;                 // ÈËÔ±ID.
	char                szRes[32];
}NET_SDK_IVE_FACE_MATCH_ADD_FACE_REPLY_T;


typedef struct NET_SDK_IVE_FACE_MATCH_DELE_ALBUM_INFO_T
{
    bool                bUseKeyFilter;             // Ê¹ÓÃ¼üÖµ¹ýÂËÉ¾³ý.
    int              iKey;                      // ¼üÖµ.
    bool                bUseTypeFilter;            // Ê¹ÓÃºÚ°×Ãûµ¥¹ýÂËÉ¾³ý.
    int              iType;                     // Ãûµ¥ÀàÐÍ 0:Ä°ÉúÈË 1:°×Ãûµ¥ 2:ºÚÃûµ¥.
    bool                bUseSexFilter;             // Ê¹ÓÃÐÔ±ð¹ýÂËÉ¾³ý.
    int              iMale;                     // ÐÔ±ð 1:male 0:female.
    bool                bUseName;                  // Ê¹ÓÃÐÕÃûÄ£ºý²éÑ¯.
    char                szName[128];
    bool                bUseIdentify;              // Ê¹ÓÃIDÆ¥Åä.
    char                szIdentifyNum[128];
    /* ¿ÉÒÀ¾ÝÐèÇóÀ©Õ¹¹ýÂËÌõ¼þ, ½øÐÐÄ£ºýÉ¾³ý */
}NET_SDK_IVE_FACE_MATCH_DELE_ALBUM_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO_T
{
    int              				iKey;      // ¼üÖµ.
    NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO		stBaseInfo;// »ù±¾ÐÅÏ¢.
}NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO_T
{
    int				iPageNum;				   // Ò³Âë(´Ó0¿ªÊ¼).
    int				iPageSize;				   // Ã¿Ò³ÌõÄ¿Êý.(·¶Î§1-10)
    bool                bUseKeyFilter;             // Ê¹ÓÃ¼üÖµ¹ýÂËÉ¾³ý.
    int              iKey;                      // ¼üÖµ.
    bool                bUseNameFilter;            // Ê¹ÓÃÐÕÃû¹ýÂË²éÑ¯.
    char                szName[128];               // ÐÕÃû.
    bool                bUseTypeFilter;            // Ê¹ÓÃºÚ°×Ãûµ¥¹ýÂË²éÑ¯.
    int              iType;                     // Ãûµ¥ÀàÐÍ 0:Ä°ÉúÈË 1:°×Ãûµ¥ 2:ºÚÃûµ¥.
    bool                bUseSexFilter;             // Ê¹ÓÃÐÔ±ð¹ýÂË²éÑ¯.
    int              iMale;                     // ÐÔ±ð 1:male 0:female.
    bool                bUseIdentify;              // Ê¹ÓÃIDÆ¥Åä.
    char                szIdentifyNum[128];
    /* ¿ÉÒÀ¾ÝÐèÇóÀ©Õ¹¹ýÂËÌõ¼þ, ½øÐÐÄ£ºý²éÑ¯ */
    /* ÈôÃ»ÓÐ¹ýÂËÌõ¼þÔò°´Ë³Ðò·µ»ØÏà²á¿âÐÅÏ¢ */
}NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO_T
{
    int              				iKey;      // ¼üÖµ.
    NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO		stBaseInfo;// »ù±¾ÐÅÏ¢.
}NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO;
typedef enum upgrade_file_type
{
	SOFTWARE = 0,//Èí¼þÉý¼¶
	KERNEL,//ÄÚºËÉý¼¶
	UBOOT,//ubootÉý¼¶
	AILIB,//ÖÇÄÜ¿âÉý¼¶
}UPGRADE_FILE_TYPE;

typedef struct _usb_backup_process
{
	int process;//±¸·Ý½ø¶È0-100, the process of the backup 0-100
	int status;//±¸·Ý×´Ì¬£¬¼ûusb_backup_status,
}NET_SDK_USB_BACKUP_PROCESS;

typedef struct _usb_backup_process_ex
{	
	DD_TIME_EX			startTime; //±¸·ÝÂ¼Ïñ¿ªÊ¼Ê±¼ä the start time of the record
	DD_TIME_EX			endTime; //±¸·ÝÂ¼Ïñ½áÊøÊ±¼ä the end time of the record
	unsigned int        dataSize;//±¸·ÝÎÄ¼þ´óÐ¡MB  the size of the record
	unsigned char       backupPath[64]; //±¸·ÝÂ·¾¶ the usb path of the backup
	unsigned char       creator[36];//±¸·ÝÈÎÎñ´´½¨Õß the creator of the backup task
	unsigned int        progress;//±¸·Ý½ø¶È0-100, the process of the backup 0-100
	unsigned int        backupFileFormat;//refer to usb_backup_format
	unsigned int        status;//±¸·Ý×´Ì¬£¬¼ûrefer to usb_backup_status,
	unsigned int        eventType;//±¸·ÝÂ¼ÏñÎÄ¼þÀàÐÍ  the record type, refer to usb_backup_record_type
	unsigned char		chls[64];//±¸·ÝÍ¨µÀ the channel of the backup
	unsigned int        chlNum;//Êµ¼Ê±¸·ÝÍ¨µÀÊýÁ¿ the actual number of the channels

}NET_SDK_USB_BACKUP_PROCESS_EX;
typedef enum usb_backup_status
{
	ONGOING = 0,//ongoing
	COMPLETE,//complete		
}USB_BACKUP_STATUS;
typedef enum usb_backup_format
{
	AVI = 0,
	PRIVATE,
}USB_BACKUP_FORMAT;

// ³µÅÆÏà»úÐ­Òé
typedef struct 
{
	unsigned int begin_flag;       //¿ªÊ¼±êÊ¶£¬0x5a5a5a5a
	unsigned int item_cnt;         /// NET_SDK_IVE_VEHICE_ITEM_INFOµÄ¸öÊý
	unsigned int plate_cnt;        /// ¼ì²âµ½³µÅÆ¸öÊý
	long long  relativeTime;     /// ¼ì²âÔ´Êý¾ÝÏà¶ÔÊ±¼ä,Ïà¶ÔÊ±¼ä
	long long  absoluteTime;     /// ¼ì²âÔ´Êý¾Ýµ±Ç°Ê±¼ä,¾ø¶ÔÊ±¼ä
	unsigned int softwareVersion;  /// Èí¼þ°æ±¾ºÅ, 0xABCDEFGH,AB£º³§¼Ò CD£ºÖ÷°æ±¾ EFGH£º×Ó°æ±¾ ³§ÉÌ 1:Å·Ä·Áú °æ±¾:V5.00
	unsigned int softwareBuildDate;/// Èí¼þÉú³ÉÈÕÆÚ,0xYYYYMMDD
	unsigned int resver[2];
	unsigned int end_flag;         //½áÊø±êÊ¶£¬0xa5a5a5a5
}NET_SDK_IVE_VEHICE_HEAD_INFO;

typedef struct
{
	unsigned int     begin_flag;         //¿ªÊ¼±êÊ¶£¬0x5a5a5a5

	unsigned int     data_type;          //0£ºJPG,1:YUV
	unsigned int     image_type;         //0:Ô­Í¼£¬1£º³µÅÆ

	// ³µÅÆ, ³µÅÆ×ø±ê, ³µÅÆÖÃÐÅ¶È
	unsigned int     plateId;            /// ID£¬×÷Îª±êÊ¶ÓÃ£¨¿É²Î¿¼ÈËÁ³IDµÄÊµÏÖ·½Ê½£©

	unsigned int     plateCharCount;     // ³µÅÆ×Ö·û¸öÊý
	char       plate[32];	        // ³µÅÆºÅÂë, utf8±àÂë
	char       plateCharConfid[32];   // ³µÅÆ×Ö·ûÖÃÐÅ¶È
	NET_SDK_IVE_RECT_T  ptPlateCharRect[32]; // ³µÅÆ×Ö·û×óÉÏ½Ç×ø±ê

	unsigned int		ptWidth;            // ×ø±ê±ÈÀý¿í£¨ÓÃÓÚ»­³µÅÆ¸ú×Ù¿ò£¬»òÔÚ»­ÃæÖÐÈ¦³ö³µÅÆµÄÎ»ÖÃ£©
	unsigned int		ptHeight;           // ×ø±ê±ÈÀý¸ß
	NET_SDK_IVE_POINT_T	ptLeftTop;          // ³µÅÆ×óÉÏ½Ç×ø±ê
	NET_SDK_IVE_POINT_T	ptRightTop;         // ³µÅÆÓÒÉÏ½Ç×ø±ê
	NET_SDK_IVE_POINT_T	ptLeftBottom;       // ³µÅÆ×óÏÂ½Ç×ø±ê
	NET_SDK_IVE_POINT_T	ptRightBottom;      // ³µÅÆÓÒÏÂ½Ç×ø±ê

	unsigned short     plateWidth;            //³µÅÆ×¥ÅÄÍ¼Æ¬¿í¶È
	unsigned short     plateHeight;           //³µÅÆ×¥ÅÄÍ¼Æ¬¸ß¶È

	unsigned int     plateConfidence;       //ÖÃÐÅ¶È

	unsigned int     plateIntensity;     //³µÅÆÁÁ¶È
	unsigned char      plateColor;         // ³µÅÆÑÕÉ« // 0-À¶É« 1-ºÚÉ« 2-»ÆÉ« 3-°×É« 4-ÂÌÉ« 5-ºìÉ« 6-»ÒÉ« 7-×ÏÉ«(KISE)
	unsigned char      plateStyle;         // ³µÁ¾ÀàÐÍ
	unsigned char      PlateColorRate;     // ÑÕÉ«Æ¥Åä³Ì¶È£»    
	unsigned char      vehicleColor;       // ³µÉíÑÕÉ«
	unsigned int     plateAngleH;        //³µÅÆË®Æ½ÇãÐ±½Ç¶È
	unsigned int     plateAngleV;        //³µÅÆÊúÖ±ÇãÐ±½Ç¶È

	unsigned int     jpeg_len;           //JpegÍ¼Æ¬Êµ¼Ê³¤¶È
	unsigned int     jpeg_vir_len;       //JpegÍ¼Æ¬Êý¾Ý°´32¸ö×Ö½Ú¶ÔÆëµÄ×Ü³¤¶È
	char        owner[32];          //³µÖ÷Ãû
	int         listType;           //Ãûµ¥ÀàÐÍ,0-Î´±È¶Ô³É¹¦£¬1-Ä°Éú³µÁ¾£¬2-°×Ãûµ¥£¬3-ºÚÃûµ¥£¬²úÉú±È¶ÔÀàÐÍ¡¾1-24¡¿£¬Ã¿¸ö·ÖÀàÔ¤Áô8¸ö¿Õ¼ä,Î´±È¶Ô¡¾0,25-31¡¿£¬Î´±È¶Ô¿Õ¼äÀ©Õ¹µ½8
	unsigned long long     beginTime;           //¿ªÊ¼Ê±¼ä
	unsigned long long     endTime;             //½áÊøÊ±¼ä
	unsigned char      iVehicleDirect;    //³µÁ¾ÐÐÊ»·½Ïò£¬1Î´Öª 2¿¿½ü  3Ô¶Àë
	unsigned char      resrv[11];
	unsigned int     end_flag;           //½áÊø±êÊ¶£¬0ax5a5a5a5
}NET_SDK_IVE_VEHICE_ITEM_INFO;

typedef struct
{
	unsigned int         eventId;            // ÊÂ¼þID
	unsigned char          status;             // ±¨¾¯×´Ì¬,0:none 1:start 2:end 3:procedure
	unsigned char          reserve[3];         // Ô¤Áô
	unsigned int         targetId;           // Ä¿±êID
	NET_SDK_IVE_LINE_T      line;               // °íÏß¹æÔòÐÅÏ¢
	NET_SDK_IVE_RECT_T      rect;               // Ä¿±ê¾ØÐÎ¿ò
}NET_SDK_IVE_PASSLINECOUNT_INFO_T;

//NET_SDK_N9000_ALARM_TYPE_PASSLINE
typedef struct
{

	unsigned int           enterCarCount; //½øÈë³µÁ¾Êý
	unsigned int           enterPersonCount;//½øÈëÈËÊý
	unsigned int           enterBikeCount;//½øÈë×ÔÐÐ³µÊý
	unsigned int           leaveCarCount; //Àë¿ª³µÁ¾Êý£¬Èç¹ûµ¥Ïò¼ÆÊý£¬´Ë×Ö¶ÎÖµÎª0
	unsigned int           leavePersonCount;//Àë¿ªÈËÊý£¬Èç¹ûµ¥Ïò¼ÆÊý£¬´Ë×Ö¶ÎÖµÎª0
	unsigned int           leaveBikeCount;//Àë¿ª×ÔÐÐ³µÊý£¬Èç¹ûµ¥Ïò¼ÆÊý£¬´Ë×Ö¶ÎÖµÎª0
	unsigned int           existCarCount;//Áô´æ³µÁ¾Êý£¬Èç¹ûµ¥Ïò¼ÆÊý£¬´Ë×Ö¶ÎÖµÎª0
	unsigned int           existPersonCount;//Áô´æÈËÊý£¬Èç¹ûµ¥Ïò¼ÆÊý£¬´Ë×Ö¶ÎÖµÎª0
	int						existBikeCount;//Áô´æ×ÔÐÐ³µÊý£¬Èç¹ûµ¥Ïò¼ÆÊý£¬´Ë×Ö¶ÎÖµÎª0
	unsigned int          count;         //·ÖÎö½á¹û¸öÊý
	NET_SDK_IVE_PASSLINECOUNT_INFO_T  passLineInfo[32];      // °íÏß·ÖÎö½á¹ûÐÅÏ¢
}NET_SDK_IVE_PASSLINECOUNT_T;

typedef struct _searched_deviceInfo
{	
	char			series[64];
	char			devName[64];
	char	        deviceType[16];
	char			szproductModel[16];
	char			szVersion[32];
	char			szFactoryName[16];
	char            szEthName[16];
	unsigned short	netport;
	unsigned short	nHttpPort;
	unsigned int			ipaddr;
	unsigned int			gateway;
	unsigned int			netmask;
	unsigned int			dns1;
	unsigned int			dns2;
	unsigned short  nChannelCount;  //NVR Í¨µÀÊý
	unsigned int	dwSecondIP;
	unsigned int	dwSecondMask;
}SEARCHED_DEVICE_INFO;

typedef struct _net_sdk_nvr_diskrec_date_item
{
	unsigned int    diskCount;
	unsigned int    diskIndex;
	char            szDiskSizeGB[16];
	char	        szStartDate[32];
	char	        szEndDate[32];		
}NET_SDK_NVR_DISKREC_DATE_ITEM;

typedef enum
{
	_SEARCH_STANDARD	=0x001,
	_SEARCH_ONVIF		=0x002,
	_SEARCH_UPNP			=0x004,
	_SEARCH_AIPSTAR		=0x008,
	_SEARCH_DAHUA		=0x010,
	_SEARCH_HIK			=0x020,
	_SEARCH_UNIVIEW		=0x040,
	_SEARCH_YCX          =0x080,
	_SEARCH_SPECO		=0x100,
	_SEARCH_ALL          =0xffff//È«²¿Éè±¸ÀàÐÍ
}SEARCH_DEVICE_TYPE;
typedef enum
{ //ÈÕÖ¾¼¶±ð
	YLOG_FATAL   = 0,    //ÑÏÖØ´íÎó
	YLOG_ERROR   = 1,    //´íÎó
	YLOG_WARN    = 2,    //¾¯¸æ
	YLOG_INFO    = 3,    //ÐÅÏ¢
	YLOG_DEBUG   = 4,    //µ÷ÊÔ
	YLOG_BUFF    = 5,    //ÂëÁ÷
}YLOG_LEVEL;
typedef struct _reg_login_info
{
	unsigned int deviceId;//×¢²áÉè±¸id
	char m_szUserName[36];//×¢²áÉè±¸ÓÃ»§Ãû
	char m_szPasswd[36];//×¢²áÉè±¸ÃÜÂë
}REG_LOGIN_INFO;
typedef struct _net_sdk_vehicle_pic_info
{
	unsigned int     vehicleId; 
	char       plate[32];	        // ³µÅÆºÅÂë
	unsigned long long     lTime;           //Ê±¼ä
}NET_SDK_VEHICLE_PIC_INFO;


#pragma pack()

////////////////////////////////////////»Øµ÷º¯Êý¶¨Òå////////////////////////////////////////
typedef void (CALLBACK *EXCEPTION_CALLBACK)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
typedef void (CALLBACK *DRAW_FUN_CALLBACK)(POINTERHANDLE lLiveHandle, HDC hDC, void *pUser);
typedef void (CALLBACK *LIVE_DATA_CALLBACK)(POINTERHANDLE lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser);
typedef void (CALLBACK *YUV_DATA_CALLBACK)(POINTERHANDLE lLiveHandle, DECODE_FRAME_INFO frameInfo, void *pUser);
typedef void (CALLBACK *LIVE_DATA_CALLBACK_EX)(POINTERHANDLE lLiveHandle, UINT dataType, BYTE *pBuffer, UINT dataLen, void *pUser);
typedef BOOL (CALLBACK *NET_MESSAGE_CALLBACK)(LONG lCommand, LONG lUserID, char *pBuf, DWORD dwBufLen, void *pUser);
typedef BOOL (CALLBACK *NET_MESSAGE_CALLBACK_EX)(LONG lCommand, LONG lUserID, char *pBuf, DWORD dwBufLen, void *pUser);
typedef void (CALLBACK *PLAY_DATA_CALLBACK)(POINTERHANDLE lPlayHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser);
typedef void (CALLBACK* PLAY_YUV_DATA_CALLBACK)(POINTERHANDLE lPlayHandle, DECODE_FRAME_INFO frameInfo, void* pUser);
typedef void (CALLBACK *TALK_DATA_CALLBACK)(POINTERHANDLE lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag, void *pUser);
typedef void (CALLBACK *ACCEPT_REGISTER_CALLBACK)(LONG lUserID, LONG lRegisterID, LPNET_SDK_DEVICEINFO pDeviceInfo, void *pUser);
typedef void (CALLBACK *ACCEPT_UNREGISTER_CALLBACK)(LONG lUserID, LONG lRegisterID, LPNET_SDK_DEVICEINFO pDeviceInfo, void *pUser);
typedef void (CALLBACK *BACKUP_DATA_CALLBACK)(POINTERHANDLE lFileHandle, UINT dataType, BYTE *pBuffer, UINT dataLen, void *pUser);

typedef void (CALLBACK *IPTool_SearchDataCallBack)(char* hwaddr, char *szDevIP, int opt, const char* szXmlData, void *pParam, const char *szRecvFromNIC);
typedef void (CALLBACK *IPTool_SearchDataCallBackEx)(char* hwaddr, char *szDevIP, int opt, const SEARCHED_DEVICE_INFO *pData, void *pParam, const char *szRecvFromNIC);
typedef void (CALLBACK *Nat2LogOutCallback)(char *logBuf);

////////////////////////////////////////////////////////////////////////////////
/********************************SDK½Ó¿Úº¯ÊýÉùÃ÷*********************************/
////////////////////////////////////////»ù±¾ÐÅÏ¢¼°µÇÂ¼Éè±¸////////////////////////////////////////
//SDK³õÊ¼»¯¼°ÍË³ö
NET_SDK_API BOOL CALL_METHOD NET_SDK_Init();
NET_SDK_API BOOL CALL_METHOD NET_SDK_Cleanup();
//ÉèÖÃÖØÁ¬²ÎÊý
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetReconnect(DWORD dwInterval = 5000, BOOL bEnableRecon = TRUE);
//¾ÖÓòÍøÇ°¶ËÉè±¸·¢ÏÖ
NET_SDK_API int CALL_METHOD NET_SDK_DiscoverDevice(NET_SDK_DEVICE_DISCOVERY_INFO *pDeviceInfo, int bufNum, int waitSeconds);
//SDK±»¶¯½ÓÊÕDVR×¢²á µÄ±¾µØ¶Ë¿ÚºÅ
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetRegisterPort(WORD wRegisterPort,REG_LOGIN_INFO* pLoginInfo = NULL, unsigned int deviceNum = 0);
NET_SDK_API BOOL CALL_METHOD NET_SDK_AddRegisterDeviceInfo(REG_LOGIN_INFO* pLoginInfo, unsigned int deviceNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetRegisterCallback(ACCEPT_REGISTER_CALLBACK fRegisterCBFun, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetUnRegisterCallback(ACCEPT_UNREGISTER_CALLBACK fUnRegisterCBFun, void *pUser);
//Òì³£ÏûÏ¢»Øµ÷º¯Êý
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetSDKMessageCallBack(UINT nMessage, HWND hWnd, EXCEPTION_CALLBACK fExceptionCallBack, void *pUser);
//°æ±¾ÐÅÏ¢
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetSDKVersion();
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetSDKBuildVersion();
//´íÎó²éÑ¯
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetLastError();

//µÇÂ¼µÇ³öÉè±¸
NET_SDK_API LONG CALL_METHOD NET_SDK_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_SDK_DEVICEINFO lpDeviceInfo);
NET_SDK_API LONG CALL_METHOD NET_SDK_LoginEx(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_SDK_DEVICEINFO lpDeviceInfo, NET_SDK_CONNECT_TYPE eConnectType, const char *sDevSN = NULL);
NET_SDK_API BOOL CALL_METHOD NET_SDK_Logout(LONG lUserID);

//ÉèÖÃp2p2.0µÄ·þÎñµØÖ·Óë¶Ë¿Ú
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetNat2Addr(char *sServerAddr,WORD wDVRPort);
NET_SDK_API void CALL_METHOD NET_SDK_SetIsWifi(bool bWifi);

////////////////////////////////////////Éè±¸±¨¾¯ÐÅÏ¢////////////////////////////////////////
//Éè±¸±¨¾¯»ò×´Ì¬»Øµ÷
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRMessageCallBack(NET_MESSAGE_CALLBACK fMessageCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRMessageCallBackEx(NET_MESSAGE_CALLBACK_EX fMessageCallBack, void *pUser);
NET_SDK_API LONG CALL_METHOD NET_SDK_SetupAlarmChan(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseAlarmChan(LONG lAlarmHandle);
//Ö÷¶¯²éÑ¯µ±Ç°±¨¾¯ÐÅÏ¢£ºN9000µ±Ç°±¨¾¯£¬ IPC£¬3.0Éè±¸Ö÷¶¯ÉÏ±¨µÄ±¨¾¯
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAlarmStatus(LONG lUserID, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//DD_ALARM_STATUS_INFO_Ex*n+DD_ALARM_STATUS_INFO*m  [n,m >= 0]
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAlarmStatusEx(LONG lUserID, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, int *exStructNum);
//ÊÖ¶¯¿ªÆô\¹Ø±Õ±¨¾¯
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDeviceManualAlarm(LONG lUserID, LONG *pAramChannel, LONG *pValue, LONG lAramChannelCount, BOOL bAlarmOpen);


////////////////////////////////////////»ñÈ¡Éè±¸ÐÅÏ¢////////////////////////////////////////
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceTime(LONG lUserID,DD_TIME *pTime);//»ñÈ¡Éè±¸µ±Ç°Ê±¼ä
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceIPCInfo(LONG lUserID, NET_SDK_IPC_DEVICE_INFO* pDeviceIPCInfo, LONG lBuffSize, LONG* pIPCCount);//»ñÈ¡NVRµÄIPCÍ¨µÀÐÅÏ¢
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceCHStatus(LONG lUserID, NET_SDK_CH_DEVICE_STATUS* pDeviceCHStatus, LONG lBuffSize, LONG* pCHCount);//»ñÈ¡NVRµÄÍ¨µÀ×´Ì¬

NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceCHSupportFunction(LONG lUserID, NET_SDK_CH_DEVICE_SUPPORT* pDeviceCHSupport, LONG lBuffSize, LONG* pCHCount);//»ñÈ¡ipc/NVRÖ§³Ö¹¦ÄÜ

////////////////////////////////////////Ô¤ÀÀÏà¹Ø½Ó¿Ú////////////////////////////////////////
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_LivePlay(LONG lUserID, LPNET_SDK_CLIENTINFO lpClientInfo, LIVE_DATA_CALLBACK fLiveDataCallBack = NULL, void* pUser = NULL);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_LivePlayEx(LONG lUserID, LPNET_SDK_CLIENTINFO lpClientInfo, LIVE_DATA_CALLBACK_EX fLiveDataCallBack = NULL, void* pUser = NULL);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopLivePlay(POINTERHANDLE lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLiveDataCallBack(POINTERHANDLE lLiveHandle, LIVE_DATA_CALLBACK fLiveDataCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLiveDataCallBackEx(POINTERHANDLE lLiveHandle, LIVE_DATA_CALLBACK_EX fLiveDataCallBack, void *pUser);
//Ô¤ÀÀÖ§³ÖÂëÁ÷Êý
NET_SDK_API unsigned int CALL_METHOD NET_SDK_SupportStreamNum(LONG lUserID, LONG lChannel);

// ÉèÖÃYUV»Øµ÷ºó£¬¿ÉÔÚ»Øµ÷´¦½ÓÊÕYUVÊý¾Ý£¬´¦ÀíÐè¾¡¿ì·µ»Ø£¬·ñÔò»á×èÈûµ×²ã½âÂëÏß³Ì¡££¨ÎÞÐèSDKÏÔÊ¾Ê±£¬µ÷ÓÃNET_SDK_LivePlayÊ±£¬´°¿Ú¾ä±ú´«NULL¼´¿É£©
// ×¢Òâ£º¸Ã¹¦ÄÜÄ¿Ç°½öÔÚwindows°æ±¾ÓÐÐ§
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetYUVCallBack(POINTERHANDLE lLiveHandle, YUV_DATA_CALLBACK fYuvCallBack, void *pUser);

//¶¯Ì¬Éú³ÉIÖ¡
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrame(LONG lUserID, LONG lChannel);//Ö÷ÂëÁ÷
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrameSub(LONG lUserID, LONG lChannel);//×ÓÂëÁ÷
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrameEx(LONG lUserID, LONG lChannel, unsigned int streamType);//
//Ô¤ÀÀÊ±½âÂëÐ§¹ûµÄ¿ØÖÆ²ÎÊý
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayerBufNumber(POINTERHANDLE lLiveHandle, DWORD dwBufNum);
//»­Ãæµþ¼Ó×Ö·ûºÍÍ¼Ïñ
NET_SDK_API BOOL CALL_METHOD NET_SDK_RegisterDrawFun(POINTERHANDLE lLiveHandle, DRAW_FUN_CALLBACK fDrawFun, void *pUser);
//¼àÌý
NET_SDK_API BOOL CALL_METHOD NET_SDK_OpenSound(POINTERHANDLE lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseSound();
NET_SDK_API BOOL CALL_METHOD NET_SDK_Volume(POINTERHANDLE lLiveHandle, WORD wVolume);
//±£´æ±¾µØÂ¼Ïñ
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveLiveData(POINTERHANDLE lLiveHandle, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopSaveLiveData(POINTERHANDLE lLiveHandle);
//Ô¤ÀÀÏÔÊ¾²ÎÊýÅäÖÃ
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVideoEffect_Ex(LONG lUserID, LONG lChannel, NET_SDK_IMAGE_EFFECT_T *pBrightValue, NET_SDK_IMAGE_EFFECT_T *pContrastValue, NET_SDK_IMAGE_EFFECT_T *pSaturationValue, NET_SDK_IMAGE_EFFECT_T *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVideoEffect_Ex(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);


////////////////////////////////////////ÊÓÆµ×¥Í¼
//JPEG×¥Í¼µ½ÄÚ´æ
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGData_V2(LONG lUserID, LONG lChannel, char *sJpegPicBuffer, DWORD dwPicSize, LPDWORD lpSizeReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGFile_V2(LONG lUserID, LONG lChannel, char *sPicFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGPicture(LONG lUserID, LONG lChannel, LPNET_SDK_JPEGPARA lpJpegPara, char *sJpegPicBuffer, DWORD dwPicSize, LPDWORD lpSizeReturned);
//Éè±¸ÉÏµÄÍ¼Æ¬£¬N9000Ö§³Ö
NET_SDK_API BOOL CALL_METHOD NET_SDK_SearchPictures(LONG lUserID, NET_SDK_IMAGE_SREACH sInSreachImage, LONG lInImageBufferSize, NET_SDK_IMAGE *pOutImageInfo, LONG *pOutImageNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_RemoteSnap(LONG lUserID, int lChannel);//Ô¶³Ì×¥Í¼
NET_SDK_API BOOL CALL_METHOD NET_SDK_DownLoadPicture(LONG lUserID, NET_SDK_IMAGE captureImage, NET_SDK_IMAGE_INFO *pOutImageInfo, char* pOutBuffer, int outBufferSize);


////////////////////////////////////////Éè±¸Â¼ÏñÎÄ¼þ»Ø·Å¡¢ÏÂÔØºÍËø¶¨////////////////////////////////////////
//¸ù¾ÝÎÄ¼þÊ±¼ä²éÕÒÂ¼ÏñÎÄ¼þ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindFile(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextFile(POINTERHANDLE lFindHandle, NET_SDK_REC_FILE *lpFindData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindClose(POINTERHANDLE lFindHandle);
//¸ù¾ÝÈÕÆÚ²éÕÒÂ¼ÏñÎÄ¼þ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindRecDate(LONG lUserID);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextRecDate(POINTERHANDLE lFindHandle, DD_DATE *lpRecDate);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindRecDateClose(POINTERHANDLE lFindHandle);
//¸ù¾ÝÊÂ¼þ²éÕÒÂ¼ÏñÎÄ¼þ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindEvent(LONG lUserID, LONG lChannel, DWORD dwRecType, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextEvent(POINTERHANDLE lFindHandle, NET_SDK_REC_EVENT *lpRecEvent);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindEventClose(POINTERHANDLE lFindHandle);
//¸ù¾ÝÊ±¼ä²éÕÒÂ¼ÏñÎÄ¼þ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindTime(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextTime(POINTERHANDLE lFindHandle, NET_SDK_REC_TIME *lpRecTime);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindTimeClose(POINTERHANDLE lFindHandle);
//°´Ê±¼ä»Ø·ÅÂ¼ÏñÎÄ¼þ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_PlayBackByTime(LONG lUserID, LONG *pChannels, LONG channelNum, DD_TIME *lpStartTime, DD_TIME *lpStopTime, HWND *hWnds);//main stream
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_PlayBackByTimeEx(LONG lUserID, LONG *pChannels, LONG channelNum, DD_TIME *lpStartTime, DD_TIME *lpStopTime, HWND *hWnds, BOOL bFirstStream);
NET_SDK_API int CALL_METHOD NET_SDK_PlayBackByTimeSync(LONG lUserID, LONG *pChannels, LONG channelNum, DD_TIME *lpStartTime, DD_TIME *lpStopTime, HWND *hWnds, BOOL bFirstStream);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackControl(POINTERHANDLE lPlayHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackControlSync(DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBack(POINTERHANDLE lPlayHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBackSync();
//×¢²á»Øµ÷º¯Êý£¬²¶»ñÂ¼ÏñÊý¾Ý
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayDataCallBack(POINTERHANDLE lPlayHandle, PLAY_DATA_CALLBACK fPlayDataCallBack, void *pUser);
//²¶»ñ»Ø·ÅµÄÂ¼ÏñÊý¾Ý£¬²¢±£´æ³ÉÎÄ¼þ
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackSaveData(POINTERHANDLE lPlayHandle, LONG lChannel, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBackSave(POINTERHANDLE lPlayHandle, LONG lChannel);
//»Ø·ÅµÄÆäËü²Ù×÷
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPlayBackOsdTime(POINTERHANDLE lPlayHandle, DD_TIME *lpOsdTime);//»ñÈ¡Â¼Ïñ»Ø·ÅÊ±ÏÔÊ¾µÄOSDÊ±¼ä
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackCaptureFile(POINTERHANDLE lPlayHandle, LONG lChannel, char *sFileName);//Â¼Ïñ»Ø·ÅÊ±×¥Í¼£¬²¢±£´æÔÚÎÄ¼þÖÐ
NET_SDK_API BOOL CALL_METHOD NET_SDK_RefreshPlay(POINTERHANDLE lPlayHandle);//Ë¢ÐÂÏÔÊ¾»Ø·Å´°¿Ú
//ÏÂÔØÂ¼ÏñÎÄ¼þ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_GetFileByTime(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime, char *sSavedFileName);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_GetFileByTimeEx(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime, char *sSavedFileName, BOOL bCustomFormat, BOOL bUseCallBack=false, BACKUP_DATA_CALLBACK fBackupDataCallBack= NULL, void* pUser = NULL); //bCustomFormat£ºÊÇ·ñÊ¹ÓÃË½ÓÐÎÄ¼þ¸ñÊ½
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_GetFileByTimeExV2(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime, char *sSavedFileName, char recFormat, BOOL bFirstStream, BOOL bUseCallBack=false, BACKUP_DATA_CALLBACK fBackupDataCallBack= NULL, void* pUser = NULL); //bCustomFormat£ºÊÇ·ñÊ¹ÓÃË½ÓÐÎÄ¼þ¸ñÊ½

NET_SDK_API BOOL CALL_METHOD NET_SDK_StopGetFile(POINTERHANDLE lFileHandle);
NET_SDK_API int CALL_METHOD NET_SDK_GetDownloadPos(POINTERHANDLE lFileHandle);
//Â¼ÏñÎÄ¼þËø¶¨¡¢½âËø¡¢É¾³ý
NET_SDK_API BOOL CALL_METHOD NET_SDK_LockFile(LONG lUserID, NET_SDK_REC_FILE *pFileToLock, LONG fileNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_UnlockFile(LONG lUserID, NET_SDK_REC_FILE *pFileToUnlock, LONG fileNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_DeleteRecFile(LONG lUserID, NET_SDK_REC_FILE *pFileToUnlock, LONG fileNum);
//Ô¶³Ì¿ØÖÆÉè±¸¶ËÊÖ¶¯Â¼Ïñ
NET_SDK_API BOOL CALL_METHOD NET_SDK_StartDVRRecord(LONG lUserID, LONG lChannel, LONG lRecordType);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopDVRRecord(LONG lUserID, LONG lChannel);


////////////////////////////////////////ÔÆÌ¨¿ØÖÆÏà¹Ø½Ó¿Ú////////////////////////////////////////
//ÔÆÌ¨¿ØÖÆ
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl(POINTERHANDLE lLiveHandle, DWORD dwPTZCommand, DWORD dwSpeed);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCommand, DWORD dwSpeed);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_3D(POINTERHANDLE lLiveHandle, LONG lChannel, PTZ_3D_POINT_INFO *pPtz3DInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_3D_Ex(LONG lUserID, LONG lChannel, PTZ_3D_POINT_INFO *pPtz3DInfo);//²»Ô¤ÀÀ3D¿ØÖÆ£¬½öÖ§³ÖÇò»úÔÆÌ¨
//Ô¤ÖÃµã
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZPreset(POINTERHANDLE lLiveHandle, DWORD dwPTZPresetCmd, DWORD dwPresetIndex);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZPreset_Other(LONG lUserID, LONG lChannel, DWORD dwPTZPresetCmd, DWORD dwPresetIndex);
//Ñ²º½Ïß
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZCruise(POINTERHANDLE lLiveHandle, DWORD dwPTZCruiseCmd, BYTE byCruiseRoute);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZCruise_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCruiseCmd, BYTE byCruiseRoute);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZSetCruise(POINTERHANDLE lLiveHandle, BYTE byCruiseRoute, DD_CRUISE_POINT_INFO *pCruisePoint, WORD pointNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZSetCruise_Other(LONG lUserID, LONG lChannel, BYTE byCruiseRoute, DD_CRUISE_POINT_INFO *pCruisePoint, WORD pointNum);
//¹ì¼£
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZTrack(POINTERHANDLE lLiveHandle, DWORD dwPTZTrackCmd);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZTrack_Other(LONG lUserID, LONG lChannel, DWORD dwPTZTrackCmd);
//×Ô¶¯É¨ÃèºÍËæ»úÉ¨Ãè¶¼Õâ¸ö½Ó¿Ú,bIsAutoScan = true,×Ô¶¯É¨Ãè¡£
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZAutoScan(POINTERHANDLE lLiveHandle, DWORD dwPTZAutoScanCmd, DWORD dwSpeed, BOOL bIsAutoScan = TRUE);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZAutoScan_Other(LONG lUserID, LONG lChannel, DWORD dwPTZAutoScanCmd);
//»ñÈ¡ÔÆÌ¨ÐÅÏ¢£º»ñÈ¡Ô¤ÖÃµãºÍÑ²º½Ïßget Preset or Cruise
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPTZConfig(LONG lUserID, LONG lChannel, DWORD dwPTZCmd,LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//»ñÈ¡Í¨µÀÖ§³ÖPTZµÄÁÐ±í
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetSupportPtzList(LONG lUserID, int listNum, NET_SDK_CHANNEL_PTZ* pOutChannelPtz, int *returnListNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPTZCameraType(LONG lUserID, NET_SDK_CAMERA_TYPE *pCameraType);


////////////////////////////////////////ÓïÒô¶Ô½²ºÍ×ª·¢////////////////////////////////////////
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_StartVoiceCom(LONG lUserID, BOOL bNeedCBNoEncData, TALK_DATA_CALLBACK fVoiceDataCallBack, void* pUser, LONG lChannel = -1);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAudioInfo(POINTERHANDLE lVoiceComHandle, void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVoiceComClientVolume(POINTERHANDLE lVoiceComHandle, WORD wVolume);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopVoiceCom(POINTERHANDLE lVoiceComHandle);
//ÓïÒô×ª·¢
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_StartVoiceCom_MR(LONG lUserID, BOOL bNeedNoEncodeData, TALK_DATA_CALLBACK fVoiceDataCallBack, void* pUser, LONG lChannel = -1);
NET_SDK_API BOOL CALL_METHOD NET_SDK_VoiceComSendData(POINTERHANDLE lVoiceComHandle, char *pSendBuf, DWORD dwBufSize);
//ÒôÆµ½âÂë
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_InitAudioDecoder(void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_DecodeAudioFrame(POINTERHANDLE lDecHandle, unsigned char *pInBuffer, LONG inLen, unsigned char *pOutBuffer, int *pOutLen);
NET_SDK_API void CALL_METHOD NET_SDK_ReleaseAudioDecoder(POINTERHANDLE lDecHandle);
//ÒôÆµ±àÂë
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_InitAudioEncoder(void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_EncodeAudioFrame(POINTERHANDLE lEncodeHandle, unsigned char *pInBuffer, LONG inLen, unsigned char *pOutBuffer, int *pOutLen);
NET_SDK_API void CALL_METHOD NET_SDK_ReleaseAudioEncoder(POINTERHANDLE lEncodeHandle);


////////////////////////////////////////Éè±¸Î¬»¤¹ÜÀí////////////////////////////////////////
//Éý¼¶
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_Upgrade(LONG lUserID, char *sFileName);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_UpgradeEx(LONG lUserID, char *sFileName);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_UpgradeIPC(LONG lUserID, char *sFileName, unsigned int fileType);
NET_SDK_API int CALL_METHOD NET_SDK_GetUpgradeState(POINTERHANDLE lUpgradeHandle);
NET_SDK_API int CALL_METHOD NET_SDK_GetUpgradeProgress(POINTERHANDLE lUpgradeHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseUpgradeHandle(POINTERHANDLE lUpgradeHandle);
//ÈÕÖ¾²éÕÒ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindDVRLog(LONG lUserID, DWORD dwType, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextLog(POINTERHANDLE lLogHandle, LPNET_SDK_LOG lpLogData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindLogClose(POINTERHANDLE lLogHandle);
//ÊÂ¼þËÑË÷
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindEventInfo(LONG lUserID, DWORD dwType, ULONGLONG channlMask, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextEventInfo(POINTERHANDLE lEventHandle, LPNET_SDK_EVENT lpEventData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindEventInfoClose(POINTERHANDLE lEventHandle);
//»Ö¸´Ä¬ÈÏÖµ
NET_SDK_API BOOL CALL_METHOD NET_SDK_RestoreConfig(LONG lUserID);
//ÅäÖÃÎÄ¼þµ¼³öµ¼Èë
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetConfigFile(LONG lUserID, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetConfigFile(LONG lUserID, char *sFileName);
//¹Ø»úºÍÖØÆô
NET_SDK_API BOOL CALL_METHOD NET_SDK_ShutDownDVR(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_RebootDVR(LONG lUserID);
//Ô¶³Ì²éÑ¯Ó²ÅÌ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindDisk(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetNextDiskInfo(POINTERHANDLE lDiskHandle, NET_SDK_DISK_INFO *pDiskInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindDiskClose(POINTERHANDLE lDiskHandle);
//¸ñÊ½»¯Ó²ÅÌ
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FormatDisk(LONG lUserID, LONG lDiskNumber);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetFormatProgress(POINTERHANDLE lFormatHandle, LONG *pCurrentFormatDisk, LONG *pCurrentDiskPos, LONG *pFormatStatic);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseFormatHandle(POINTERHANDLE lFormatHandle);


////////////////////////////////////////Éè±¸²ÎÊýÅäÖÃ////////////////////////////////////////
NET_SDK_API LONG CALL_METHOD NET_SDK_EnterDVRConfig(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);
NET_SDK_API BOOL CALL_METHOD NET_SDK_ExitDVRConfig(LONG lUserID);

NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig_SubStreamEncodeInfo(LONG lUserID, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);	//For N9000
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRConfig_SubStreamEncodeInfo(LONG lUserID, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);													//For N9000
//Ïà¶ÔNET_SDK_GetDVRConfig_SubStreamEncodeInfo£¬·µ»Ø½á¹¹ÌåÖÐ¶àÁËÖ§³ÖµÄÂëÂÊÑ¡Ïî; ·µ»ØµÄÊÇÖ§³ÖµÄ±àÂëÐÅÏ¢
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig_SubStreamEncodeInfo_Ex(LONG lUserID, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);	//For N9000
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveConfig(LONG lUserID);//±£´æ²ÎÊý
NET_SDK_API BOOL CALL_METHOD NET_SDK_ChangTime(LONG lUserID, unsigned int time);//ÐÞ¸ÄÉè±¸ÏµÍ³Ê±¼ä
//NET_SDK_API BOOL CALL_METHOD NET_SDK_ModifyDeviceNetInfo(NET_SDK_DEVICE_IP_INFO *pDeviceIPInfo);//ÐÞ¸ÄÉè±¸IP
NET_SDK_API void CALL_METHOD NET_SDK_FormatTime(LONGLONG intTime, DD_TIME *pFormatTime);//ÕûÐÍÊ±¼ä×ª»»Îª¸ñÊ½»¯µÄÊ±¼ä

NET_SDK_API BOOL CALL_METHOD NET_SDK_UserManage(LONG lUserID, DD_OPERATE_TYPE dwCommand, char *userName, DD_USER_GROUP userType, char *password, char* email, BOOL allowModifyPwd, char *newName=NULL, BOOL closePermissionCtrl=FALSE);

////////////////////////////////////////ÖÇÄÜ±¨¾¯£¨Ö»Õë¶ÔÖÇÄÜIPC£©////////////////////////////////////////
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetIVMRuleConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetIVMRuleConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);
//dwCommand NET_DVR_SMART_TYPE
//NET_DVR_IVE_VFD_RESULT_HEAD_T+[NET_DVR_IVE_VFD_RESULT_DATA_INFO_T+Ô´Êý¾Ý]+[NET_DVR_IVE_VFD_RESULT_FACE_DATA_INFO_T+ÈËÁ³Êý¾Ý+ÈËÁ³Ä¿±êÖµ]+...+[NET_DVR_IVE_VFD_RESULT_FACE_DATA_INFO_T+ÈËÁ³Êý¾Ý+ÈËÁ³Ä¿±êÖµ]
typedef void (CALLBACK *SUBSCRIBE_CALLBACK)(LONG lUserID, DWORD dwCommand, char *pBuf, DWORD dwBufLen, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetSubscribCallBack(SUBSCRIBE_CALLBACK fSubscribCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SmartSubscrib(LONG lUserID, DWORD dwCommand, LONG lChannel, NET_DVR_SUBSCRIBE_REPLY *pOutBuffer);
NET_SDK_API BOOL CALL_METHOD NET_SDK_UnSmartSubscrib(LONG lUserID, DWORD dwCommand, LONG lChannel, char *pInServerAddress, int *dwResult);
//FaceMatch NET_SDK_FACE_MATCH_OPERATE_TYPE
NET_SDK_API BOOL CALL_METHOD NET_SDK_FaceMatchOperate(LONG lUserID, DWORD dwCommand,LPVOID lpInBuffer, DWORD dwInBufferSize,LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//Í¸´«API½Ó¿Úº¯Êý£¬ÊµÏÖÓëÉè±¸¶ËÖ±½Óxml»¥Í¨
NET_SDK_API BOOL CALL_METHOD NET_SDK_ApiInterface(LONG lUserID, char *sendXML, char *strUrl, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//Í¸´«½Ó¿Úº¯Êý£¬
NET_SDK_API BOOL CALL_METHOD NET_SDK_TransparentConfig(LONG lUserID, char *sendXML, char *strUrl, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);

NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveFileToUsbByTime(LONG lUserID,NET_SDK_REC_FILE* recordFile, USB_BACKUP_FORMAT recFormat);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetSaveFileToUsbProcess(LONG lUserID, NET_SDK_USB_BACKUP_PROCESS_EX* pUsbBackProcess, unsigned int lBuffSize, unsigned int* taskCount);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceSupportFunction(LONG lUserID, NET_SDK_DEV_SUPPORT* pDevSupport);//»ñÈ¡ipcÖ§³Ö¹¦ÄÜ
#ifdef WIN32
#ifdef DVR_NET_SDK_EXPORTS
//¿ªÊ¼ËÑË÷Éè±¸ SearchTypeMask please refer to SEARCH_DEVICE_TYPE
NET_SDK_API unsigned int CALL_METHOD NET_SDK_DiscoverDeviceStart(IPTool_SearchDataCallBack SearchCallBack,IPTool_SearchDataCallBackEx SearchCallBackEx, void *pParam, unsigned int SearchTypeMask, int nMaxRecordCount);
//Í£Ö¹ËÑË÷Éè±¸
NET_SDK_API void CALL_METHOD NET_SDK_DiscoverDeviceStop(unsigned int hSearch);
#endif
#endif // WIN32

NET_SDK_API int CALL_METHOD NET_SDK_GetSha1Encrypt(LONG lUserID,const void *pIn, int iLenIn, void *szOut, int outLen, int *lpBytesReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetRtspUrl(LONG lUserID,LONG lChannel,LONG lStreamType,char *sRtspUrl);
//¸ù¾ÝÎÄ¼þÊ±¼ä²éÕÒÂ¼ÏñÎÄ¼þ
//NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindVehiclePic(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
//NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextVehiclePic(POINTERHANDLE lFindHandle, NET_SDK_VEHICLE_PIC_INFO *lpFindData);
//NET_SDK_API BOOL CALL_METHOD NET_SDK_FindVehiclePicClose(POINTERHANDLE lFindHandle);

////////////////////The following interfaces will stop updating, they are not recommended.
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceFirmwareType(LONG lUserID, NET_SDK_DEVICE_FIRMWARE_TYPE *pFirmwareType);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceIPByName(char *sSerIP,DWORD wSerPort,char *sDvrName,char *sDvrIP);//Í¨¹ýÉè±¸Ãû³Æ»ñÈ¡IPµØÖ·
NET_SDK_API LONG CALL_METHOD NET_SDK_GetProductSubID(char *sDVRIP,WORD wDVRPort);
NET_SDK_API char* CALL_METHOD NET_SDK_GetErrorMsg(LONG *pErrorNo = NULL);
NET_SDK_API LONG CALL_METHOD NET_SDK_GetDeviceTypeName(LONG lUserID, char *pNameBuffer, int bufferLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLogToFile(BOOL bLogEnable = FALSE, char *strLogDir = NULL, BOOL bAutoDel = TRUE,int logLevel = YLOG_DEBUG);//ÆôÓÃÈÕÖ¾ÎÄ¼þÐ´Èë½Ó¿Ú
NET_SDK_API BOOL CALL_METHOD NET_SDK_ChangeDiskProperty(LONG lUserID, LONG lDiskNumber, short newProperty);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVideoEffect(LONG lUserID, LONG lChannel, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVideoEffect(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDefaultVideoEffect(LONG lUserID, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveVideoEffect(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CapturePicture(POINTERHANDLE lLiveHandle, char *sPicFileName);//bmp
NET_SDK_API BOOL CALL_METHOD NET_SDK_CapturePicture_Other(LONG lUserID, LONG lChannel,char *sPicFileName);//bmp
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJpeg(LONG lUserID, LONG lChannel, LONG dwResolution, char *sJpegPicBuffer, DWORD dwPicBufSize, LPDWORD lpSizeReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVehicleConfig(LONG lUserID);


//ÉèÖÃÓãÑÛÐ£ÕýÄ£Ê½£¬½øÈëÓãÑÛÐ£ÕýÄ£Ê½ÓëÍË³öÓãÑÛÐ£ÕýÄ£Ê½¶¼ÐèÒªµ÷ÓÃ´Ë½Ó¿Ú,½öµ¥´°¿ÚÄ£Ê½Ê¹ÓÃ
//ÊäÈë²ÎÊý£º
//lPlayHandle£º ²¥·Å¾ä±ú
//fishEyeMode£º°²×°Ä£Ê½+Ð£ÕýÄ£Ê½
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetFishEyeAdjust(POINTERHANDLE lPlayHandle, FISHEYE_MODE fishEyeMode);

//ÉèÖÃ½¹µã£¬ÓÃÓÚÅÐ¶Ïµ±Ç°²Ù×÷×÷ÓÃÓÚÓãÑÛÐ£ÕýµÄÄÄ¸ö·Ö¸îÇøÓò
//ÊäÈë²ÎÊý£º
//lPlayHandle£º ²¥·Å¾ä±ú
//nX£ºµ±Ç°½¹µãµÄX×ø±êÖµ£¬Ïà¶ÔÓÚµ±Ç°²¥·Å´°¿Ú×ø±êÏµ
//nY£ºµ±Ç°½¹µãµÄY×ø±êÖµ£¬Ïà¶ÔÓÚµ±Ç°²¥·Å´°¿Ú×ø±êÏµ
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustFocus(POINTERHANDLE lPlayHandle, int nX, int nY);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustFocusEx(POINTERHANDLE lPlayHandle, int nX, int nY, int &nIndex);
//µç×ÓÔÆÌ¨ÒÆ¶¯£¬Ö»ÓÐ½øÈëÓãÑÛÐ£ÕýÄ£Ê½ÏÂ£¬ÊôÓÚµç×ÓÔÆÌ¨µÄ·Ö¸î²Å¿ÉÒÔÒÆ¶¯
//ÊäÈë²ÎÊý£º
//lPlayHandle£º ²¥·Å¾ä±ú
//nMoveX：鼠标左键拖拽时相对于起点之X坐标轴上的水平偏移量，向右为正，向左为负，以起点为原点
//nMoveY：鼠标左键拖拽时相对于起点之Y坐标轴上的垂直偏移量，向上为正，向下为负，以起点为原点
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustMove(POINTERHANDLE lPlayHandle, int nMoveX, int nMoveY);

//»ñÈ¡µ±Ç°½¹µãËùÔÚµÄÐ£ÕýÇøÓòÎ»ÖÃ
//ÊäÈë²ÎÊý£º
//lPlayHandle£º ²¥·Å¾ä±ú
//Êä³ö²ÎÊý
//AreaRect£ºµ±Ç°½¹µãËùÔÚÐ£ÕýÇøÓòµÄÎ»ÖÃ£¬Ïà¶ÔÓÚµ±Ç°²¥·Å´°¿Ú×ø±êÏµ
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustGetArea(POINTERHANDLE lPlayHandle, RECT &AreaRect);

//µç×ÓÔÆÌ¨·Å´ó£¬Ö»ÓÐ½øÈëÓãÑÛÐ£ÕýÄ£Ê½ÏÂ£¬ÊôÓÚµç×ÓÔÆÌ¨µÄ·Ö¸î²Å¿ÉÒÔ·Å´ó
//ÊäÈë²ÎÊý£º
//lPlayHandle£º ²¥·Å¾ä±ú
//ZoomRect£º Ö¸¶¨Òª·Å´óµÄÇøÓòÎ»ÖÃÐÅÏ¢£¬Ïà¶ÔÓÚµ±Ç°²¥·Å´°¿Ú×ø±êÏµ
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustZoom(POINTERHANDLE lPlayHandle, const RECT &ZoomRect);


//²éÑ¯NVRµÄÂ¼ÏñÌìÊý½Ó¿Ú
//ÊäÈë²ÎÊý:
//lUserID Éè±¸ID
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetNvrRecordDays(LONG lUserID, NET_SDK_NVR_DISKREC_DATE_ITEM* pDiskRecDateInfo, LONG lBuffSize, LONG* pDISKCount);
/**
 * @description: 门禁开门。
 * @param {LONG} lUserID [in]预览句柄，NET_SDK_LivePlay或NET_SDK_LivePlayEx的返回值。
 * @param {LONG} lChannel [in]通道编号，从0开始，IPC设备此参数无效。
 * @return {BOOL} 成功返回TRUE,失败返回FALSE。
 */
NET_SDK_API BOOL CALL_METHOD NET_SDK_UnlockAccessControl(LONG lUserID, LONG lChannel);
#ifdef __cplusplus
}
#endif

#endif
