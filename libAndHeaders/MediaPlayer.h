//
//  MediaPlayer.h
//  MediaPlayer
//
//  Created by 123 on 16/6/7.
//  Copyright © 2016年. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Player_define.h"

typedef NS_ENUM(NSUInteger, FISH_EYES_MODEL_MODE) {
    FISH_EYES_COMMON_MODE,//通常
    FISH_EYES_SPHERE_MODE,//圆形
    FISH_EYES_SQUARE_MODE,//上下两行
    FISH_EYES_CYLINDER_MODE,//圆柱
    FISH_EYES_SPHERE_FOUR_MODE,//4球体
    FISH_EYES_SPHERE_VR_MODE//VR
};

@interface MediaPlayer : NSObject
{
    
}
+(void)createSharedSource;
-(id)init:(int)iTag MAC:(NSString*)imac;
-(UIView*)getPlayerView; //获取播放的view
-(CGRect)getFrame;       //获取播放的view的rect

- (void)setNewFrame:(CGRect)frame; //设置播放的view的rect
- (void)setFrame:(CGRect)frame;
- (void)SetSeleted:(BOOL)bSelected; //设置选中状态
- (BOOL)GetSeleted;        //获取选中状态
- (void)SetSeletedColor:(UIColor*)selectColor;  //设置选中的边框颜色
- (void)SetUnSeletedColor:(UIColor*)unSelectColor; //设置未选中的边框颜色

- (void)CaptureBitmap;    //抓图

- (void)StartRecord;      //开始录像
- (void)StopRecord;       //停止录像
- (BOOL)GetRecordState;  //获取录像状态

- (void)StartAudio:(int)iSeverType;   //开始音频
- (void)StopAudio;                   //关闭音频
- (BOOL)GetAudioState;               //获取音频状态

- (void)StartTalk:(int)iSeverType;   //开始对讲
- (void)StopTalk;                    //停止对讲
- (BOOL)GetTalkState;                //获取对讲状态

-(void)ReleaseAllResouse;             //释放所有资源，用于关闭播放流或者更改播放流或者回放播放完毕时调用

- (void)SetCapturePath:(NSString*)strCapturePath;  //设置抓图保存路径
- (void)SetRecordPath:(NSString*)strRecPath;       //设置录像保存路径

-(void)OnVideoDateFormatHead:(int)iChannel FORMAT:(void*)iFormat;

//NVMS5000
-(void)OnVideoDate:(int)iChannel Data:(unsigned char*)iBuffer Length:(int)iLength TimeStamp:(long long)lTimeStamp IFrame:(BOOL)bIFrame FrameIndex:(long)lFrameIndex Width:(int)iWidth Height:(int)iHeight EncodeType:(unsigned int)dwVideoEncodeType;
-(void)OnAudioDate:(int)iChannel Data:(char*)iBuffer Length:(int)iLength TimeStamp:(long long)lTimeStamp;

//DVR3.0
-(void)OnVideoDate:(unsigned long long)iChannel width:(unsigned int)width height:(unsigned int)height Data:(unsigned char*)iBuffer Length:(int)iLength TimeStamp:(long long)lTimeStamp RelTime:(long long)lRelativeTime IFrame:(BOOL)bIFrame FrameIndex:(int)lFrameIndex EncodeType:(unsigned int)dwVideoEncodeType;
-(void)OnAudioDateFormatHead:(int)iChannel FORMAT:(void*)iFormat;

-(void)OnAudioDate:(unsigned long long)iChannel Data:(char*)iBuffer Length:(int)iLength RawData:(unsigned char*)pRawBuffer RawLength:(int)iRawLength TimeStamp:(long long)lTimeStamp RelTime:(long long)relTime;

-(void)OnAudioTalkDate:(char*)iBuffer Length:(int)iLength;
-(void)SetPlayerChannel:(int)iChannel devName:(NSString*)devName;       //设置播放通道

//以下两个函数用于播放view移动时调用
-(CGRect)GetMoveBeforeRect;                  //获取播放view移动之前的rect
-(void)SetMoveBeforeRect;                    //设置播放view移动之前的rect

- (void)SetGUID:(void*)iGUID;                //设置播放视频设备GUID
- (void*)GetGUID;                            //获取播放视频设备GUID

- (void)SetAudioGUID:(void*)iGUID;          //设置播放音频设备GUID
- (void*)GetAudioGUID;                      //获取播放音频设备GUID

-(void)setPlayIdleStatus:(BOOL)bIdle;   //设置线程为空闲状态，没有视频播放(需要刷新openGL的状态)

//以下只用于回放的调用
-(void)setPlayIdle:(BOOL)bIdle;         //设置线程为空闲状态，没有视频播放(不需要刷新openGL的状态)
- (int)GetLastPlayStatus;               //获取上一个播放状态
- (int)GetPlayStatus;                   //获取当前播放状态
- (void)SetPlayStatus:(int)iPlayStatus;  //设置当前播放状态
- (void)ResumePlay; //用于暂停状态恢复到暂停前的状态继续播放
-(void)OneFramePlayback:(BOOL)bOneFramePlayback;  //单帧播放
- (BOOL)isWaitFrameHeader;   //是否在等待视频帧格式
- (void)SetWaitFrameHeader:(BOOL)bWaitFrameHeader;  //设置视频帧格式

-(void)setPlayEnd;   //设置播放完毕
-(BOOL)isPlayEnd;               //是否播放完毕
-(void)PauseRemotePlayback:(BOOL)bPause;   //暂停或者恢复播放
-(BOOL)IsPausePlayBack;         //是否暂停播放
-(void)ResetPlayTime;           //设置播放时用到的时间为初始值，用于重新播放
-(BOOL)IsIdle;  //是否空闲状态
-(void)ReleaseThread;          //释放解码显示线程
- (void)SetWaitForFrame:(BOOL)bWait;   //设置等待关键帧，用户回放拖动改变播放时间时调用
-(void)ReleaseFrameListEx;              //释放解码线程列表中的视频帧
-(void)setDelegate:(id)delegate;

-(void)setParentID:(unsigned int)dwParentID;   
-(int)getParentID;
-(void)setChannelNum:(unsigned int)channelnum;
-(unsigned int)getChannelNum;

-(void)setPlayFrameCount:(long long)playFrameCount;
-(long long)getPlayFrameCount;

-(void)setPlayDate:(NSString*)strPlayDate;      //设置播放日期
-(NSString*)getPlayDate;                        //获取播放日期
-(void)setPlayTime:(long long)strPlayTime;      //设置播放时间
-(long long)getPlayTime;                        //获取播放时间

-(void)setStartTime:(long long)lStartTime;      //设置播放的开始时间
-(long long)getStartTime;                       //获取播放的开始时间
-(void)setEndTime:(long long)lEndTime;          //设置播放的结束时间
-(long long)getEndTime;                         //获取播放的结束时间

-(void)setChangeTime:(long long)lChangeTime;       //设置播放的当前更改时间
-(long long)getChangeTime;                          //获取播放的当前更改时间
-(void)setLastTime:(long long)lLastTime;            //设置播放的上一帧时间
-(long long)getLastTime;                            //获取播放的上一帧时间

-(void)setRecEndTime:(long long)lRecEndTime;         //设置播放录像的结束时间
-(void)setRecStartTime:(long long)lRecStartTime;     //设置播放录像的开始时间

-(void)MediaShowProgressControl;                      //显示等待标志
-(void)MediaHideProgressControl;                      //隐藏等待标志
-(BOOL)IsShowMediaProgressControl;
-(void)setIndex:(int)iIndex;                           //设置播放器的索引
-(int)getIndex;
-(void)setTag:(int)iTag;                                 //设置播放器view的tag
-(long)getTag;

+(void)SetAppIsBackground:(int)backGroundStatus;         //设置应用程序是否退到后台
+ (int)GetCurrentViewMode;                               //获取当前是现场模式还是回放模式
+ (void)SetCurrentViewMode:(int)iMode;
+ (void)SetServerType:(int)iValue;                       //设置服务器类型
+ (void)SetRecordClipSize:(int)iValue;                   //设置录像文件大小
+(void)SetIsRotateing:(BOOL)bRotate;                      //设置手机当前是否在旋转
+ (void)SetReserverSize:(int)iValue;                      //设置录像磁盘预留的空间，当录像磁盘控件小于等于这个值改出提示
+(void)SetDisplayMode:(int)iDisplayMode;                  //设置分割模式，用于265解码器

-(void)setFishEyeEnable:(BOOL)bEnabled;                    //设置是否支持鱼眼
-(void)setFishEyeModel:(FISH_EYES_MODEL_MODE)model_mode;   //设置鱼眼模式
-(void)changeEyeViewMode:(FISH_EYES_MODEL_MODE)mode;
- (void)setClickOneTimeBlock:(dispatch_block_t)block;
- (void)setClickChangeFishEyeblock:(void (^)(BOOL))block ;
-(void)setfishEyeGestureEnable:(BOOL)enable;
- (void)setCruiseEnable:(BOOL)enable;
- (BOOL)getCruiseEnable;
-(int)getTalkAudioFrameSize;
-(int)GetAudioFrameSize;
-(void)ClearAudioList;
@end
