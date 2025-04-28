//
//  Player_define.h
//  Player_UI
//
//  Created by 123 on 16/6/7.
//  Copyright © 2016年. All rights reserved.
//  modifyed by zld 2017/4/22

#ifndef Player_define_h
#define Player_define_h

@protocol PLAYERMESSAGE<NSObject>
@optional

-(void)singleClick:(int)playerTag;  //单击操作
-(void)doubleClick:(int)playerTag;   //双击操作
-(void)longPressBegin:(int)playerTag;//长按开始
-(void)longPressDoDragging:(int32_t)playerTag origin:(CGPoint)origin convPoint:(CGPoint)convPoint;//长按时移动
-(void)longPressStopDragging:(int32_t)playerTag origin:(CGRect)origin curRect:(CGRect)curRect moveDistance:(CGPoint)moveDistance;
-(void)longPressCancelled:(int32_t)playerTag origin:(CGRect)origin curRect:(CGRect)curRect;
-(void)playerTouchesBegan:(int)playerTag point:(CGPoint)point;
-(void)playerTouchesMove:(int)playerTag origin:(CGPoint)pPoint;  //拖动Mediaplayer view操作
-(BOOL)playerTouchesEnded:(int)playerTag origin:(CGRect)origin curRect:(CGRect)curRect point:(CGPoint)point;//Mediaplayer view拖动结束操作
-(void)playerTouchesEndedEx:(int)playerTag origin:(CGRect)origin curRect:(CGRect)curRect;
-(void)playerTouchesCancelled:(int)playerTag origin:(CGRect)origin curRect:(CGRect)curRect;
-(void)playBackIndexFeedback:(int)iIndex; //用于回放时回复帧索引给NVMS5000平台
-(void)playBackTimeStampFeedback:(long long)lTimeStamp; //用于回放时回调当天播放的帧时间，单位是微秒
//iError:0 success  iError:1 fail
-(void)CaptureBitmapCallBack:(int)iError;
-(void)OnGetAudioRecordData:(char*)pBuffer FrameLen:(int)iFrameLen;
@end

#define BITMAPFILEHEADER_LEN 14
#define BITMAPINFOHEADER_LEN 40
#define DORP_FRAME_MAX_SIZE  20
#define INVALID_ITEM_ID		-1

#endif /* Player_define_h */
