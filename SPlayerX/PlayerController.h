/*
 * MPlayerX - PlayerController.h
 *
 * Copyright (C) 2009 Zongyao QU
 * 
 * MPlayerX is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * MPlayerX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MPlayerX; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#import <Cocoa/Cocoa.h>
#import "CoreController.h"
#import "OSDView.h"

///////////////////////////Notifications///////////////////////////
extern NSString * const kMPCPlayOpenedNotification;
extern NSString * const kMPCPlayOpenedURLKey;
extern NSString * const kMPCPlayLastStoppedTimeKey;
//-----------------------------------------------------------------
extern NSString * const kMPCPlayStartedNotification;
extern NSString * const kMPCPlayStartedAudioOnlyKey;
//-----------------------------------------------------------------
extern NSString * const kMPCPlayWillStopNotification;
extern NSString * const kMPCPlayStoppedNotification;
extern NSString * const kMPCPlayFinalizedNotification;
//-----------------------------------------------------------------
extern NSString * const kMPCPlayInfoUpdatedNotification;
extern NSString * const kMPCPlayInfoUpdatedKeyPathKey;
extern NSString * const kMPCPlayInfoUpdatedChangeDictKey;


@class ControlUIView, OpenURLController, CharsetQueryController;

@interface PlayerController : NSObject <NSApplicationDelegate, SubConverterDelegate, CoreControllerDelegate>
{
	NSUserDefaults *ud;
	NSNotificationCenter *notifCenter;
	
	CoreController *mplayer;
	NSURL *lastPlayedPath;
	NSURL *lastPlayedPathPre;

	BOOL kvoSetuped;
    BOOL OSDActive;

	IBOutlet OSDView *osd;
    IBOutlet ControlUIView *controlUI;
	IBOutlet OpenURLController *openUrlController;
	IBOutlet CharsetQueryController *charsetController;
  
  dispatch_semaphore_t _semaCheckingSubMatchDisable;
  BOOL subMatchDisableCheckFinished;
}

@property (readonly) NSURL *lastPlayedPath;
@property (assign, readwrite, getter=isOSDActive) BOOL OSDActive;


-(void) setupKVO;
-(BOOL) waitforSubMatchDisableCheckFinished;

-(id) setDisplayDelegateForMPlayer:(id<CoreDisplayDelegate>) delegate;
-(int) playerState;
-(BOOL) couldAcceptCommand;

-(id) mediaInfo;
-(void) setMultiThreadMode:(BOOL) mt;

-(void) loadFiles:(NSArray*)files fromLocal:(BOOL)local;
-(void) stop;

-(void) togglePlayPause;	/** 返回PlayPause是否成功 */
-(BOOL) toggleMute;			/** 返回现在的mute状态 */
-(float) setVolume:(float) vol;	/** 返回现在的音量 */
-(float) seekTo:(float) time;	/** 返回现在要去的时间 */
-(void) frameStep;

-(float) changeTimeBy:(float) delta;  /** 返回现在的时间值 */
-(float) changeSpeedBy:(float) delta; /** 返回现在的速度值 */

-(float) changeSubDelayBy:(float) delta;
-(float) changeAudioDelayBy:(float) delta;
-(float) changeSubScaleBy:(float) delta;
-(float) changeSubPosBy:(float)delta;
-(float) changeAudioBalanceBy:(float)delta;

-(float) setSubScale:(float) sc;
-(NSColor*) setSubFontColor:(NSColor*)col;

-(float) setSpeed:(float) spd;
-(float) setSubDelay:(float) sd;
-(float) setAudioDelay:(float) ad;
-(void) setAudioBalance:(float)bal;

-(void) setSubtitle:(int) subID;
-(void) set2ndSubtitle:(int) subID;
-(void) mergeSubtitle:(NSString *)subName secondSubName:(NSString *)secondSubName;
-(void) setAudio:(int) audioID;
-(void) setVideo:(int) videoID;

-(void) setLetterBox:(BOOL) renderSubInLB top:(float) topRatio bottom:(float)bottomRatio;
-(void) setEqualizer:(NSArray*) amps;

-(BOOL) loadSubFile:(NSString*)subPath;
-(NSString*) getCurrentSubtitlePath;
-(void) smartPullSubtitle;
-(void) forcePullSubtitle;
-(void) pushSubtitle;

/* for subtitle search OSD display
 */
-(void) setOSDMessage:(NSString*) msg type:(OSDTYPE)tp;
-(void) OSDResize;

@end