/*
 * MPlayerX - ControlUIView.h
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
#import <WebKit/WebKit.h>
#import "DOMProxySPlayer.h"

@class RootLayerView, PlayerController, FloatWrapFormatter, ArrowTextField, ResizeIndicator, OsdText, TitleView, TimeFormatter;

@interface ControlUIView : NSView
{
	NSUserDefaults *ud;
	NSNotificationCenter *notifCenter;

	// button images
	NSDictionary *fillScreenButtonAllImages;
	NSArray *volumeButtonImages;
	
	NSGradient *fillGradient;
	NSColor *backGroundColor;
	NSColor *backGroundColor2;

	// formatters
	TimeFormatter *timeFormatter;
	FloatWrapFormatter *floatWrapFormatter;

	// autohide things
	NSTimeInterval autoHideTimeInterval;
	BOOL shouldHide;
	NSTimer *autoHideTimer;
		
    NSString* shareUriCurrent;
    NSString* nextAuthURLString;
    NSString* nextShareURLString;
  
    DOMProxySPlayer* wsoSPlayer;
    DOMProxySPlayer* wsoSPlayerAuth;
    IBOutlet NSButton *closeOAuthButton;
  
	float volStep;
	float orgHeight;

	IBOutlet PlayerController *playerController;
	IBOutlet RootLayerView *dispView;
	IBOutlet NSButton *fillScreenButton;
	IBOutlet NSButton *fullScreenButton;
	IBOutlet NSButton *playPauseButton;
	IBOutlet NSButton *volumeButton;
	IBOutlet NSSlider *volumeSlider;
	IBOutlet NSTextField *timeText;
	IBOutlet NSTextField *timeTextAlt;
	
	IBOutlet NSSlider *timeSlider;
	IBOutlet NSTextField *hintTime;
	
	IBOutlet NSView *accessaryContainer;
	IBOutlet NSButton *toggleAcceButton;
    IBOutlet NSButton *toggleShareButton;

	IBOutlet ArrowTextField *speedText;
	IBOutlet ArrowTextField *subDelayText;
	IBOutlet ArrowTextField *audioDelayText;
	
	IBOutlet ResizeIndicator *rzIndicator;
	IBOutlet OsdText *osd;
	IBOutlet TitleView *title;
	
    IBOutlet WebView* webView;
    IBOutlet WebView* webViewAuth;
    
    // list for sub/audio/video
	NSMenu *subListMenu;
	NSMenu *audioListMenu;
	NSMenu *videoListMenu;
    
    // Playback Menu
    IBOutlet NSMenu *menuPlayback;
    IBOutlet NSMenuItem *menuPlayFromLastStoppedPlace;
    IBOutlet NSMenuItem *menuSwitchVideo;
    IBOutlet NSMenuItem *menuToggleLockAspectRatio;
    IBOutlet NSMenuItem *menuResetLockAspectRatio;
    IBOutlet NSMenuItem *menuSizeInc;
    IBOutlet NSMenuItem *menuSizeDec;
    IBOutlet NSMenuItem *menuPlaySpeedInc;
    IBOutlet NSMenuItem *menuPlaySpeedDec;
    IBOutlet NSMenuItem *menuSwitchAudio;
    IBOutlet NSMenuItem *menuVolInc;
	IBOutlet NSMenuItem *menuVolDec;
    IBOutlet NSMenuItem *menuAudioDelayInc;
	IBOutlet NSMenuItem *menuAudioDelayDec;
    IBOutlet NSMenuItem *menuSnapshot;
    
    IBOutlet NSMenuItem *menuPlaySpeedReset;
    IBOutlet NSMenuItem *menuAudioDelayReset;
    
    // Subtitle Menu
    IBOutlet NSMenu *menuSubtitle;
	IBOutlet NSMenuItem *menuSwitchSub;
    IBOutlet NSMenuItem *menuToggleLetterBox;
	IBOutlet NSMenuItem *menuSubScaleInc;
	IBOutlet NSMenuItem *menuSubScaleDec;
    IBOutlet NSMenuItem *menuSubtitleDelayInc;
	IBOutlet NSMenuItem *menuSubtitleDelayDec;
    IBOutlet NSMenuItem *menuSubtitleMatch;
    IBOutlet NSMenuItem *menuSubtitleSearchOnWeb;
    
    IBOutlet NSMenuItem *menuSubtitleDelayReset;
    
    // Window Menu	
    IBOutlet NSMenu *menuWindow;
	IBOutlet NSMenuItem *menuShowMediaInfo;
}

@property (retain) NSString* shareUriCurrent;

////////////////////////////////显示相关////////////////////////////////
extern NSString * const kFillScreenButtonImageLRKey;
extern NSString * const kFillScreenButtonImageUBKey;


-(void) setFillScreenMode:(NSString*)modeKey state:(NSInteger) state;

-(void) displayStarted;
-(void) displayStopped;

//////////////////////////////自动隐藏相关/////////////////////////////
-(void) showUp;
-(void) updateHintTime;
-(void) doHide;
-(void) refreshBackgroundAlpha;
-(void) refreshAutoHideTimer;
-(void) refreshOSDSetting;

//////////////////////////////其他控件相关/////////////////////////////
-(IBAction) togglePlayPause:(id)sender;
-(IBAction) toggleMute:(id)sender;

-(IBAction) setVolume:(id)sender;
-(IBAction) changeVolumeBy:(id)sender;

-(IBAction) seekTo:(id) sender;
-(void) changeTimeBy:(float) delta;

-(IBAction) toggleFullScreen:(id)sender;
-(IBAction) toggleFillScreen:(id)sender;

-(IBAction) toggleShareControls:(id)sender;
-(IBAction) hideShareControls:(id)sender;

-(IBAction) showOAuthView:(id)sender Url:(NSString*) url;
-(IBAction) hideOAuthView:(id)sender;

-(void) hideAndTrash:(NSView*)sender;

-(IBAction) toggleAccessaryControls:(id)sender;
-(IBAction) changeSpeed:(id) sender;
-(IBAction) changeAudioDelay:(id) sender;
-(IBAction) changeSubDelay:(id)sender;

-(IBAction) stepSubtitles:(id)sender;
-(IBAction) setSubWithID:(id)sender;

-(IBAction) changeSubScale:(id)sender;

-(IBAction) stepAudios:(id)sender;
-(IBAction) setAudioWithID:(id)sender;

-(IBAction) stepVideos:(id)sender;
-(IBAction) setVideoWithID:(id)sender;

-(IBAction) changeSubPosBy:(id)sender;
-(IBAction) changeAudioBalanceBy:(id)sender;

-(IBAction) toggleLockAspectRatio:(id)sender;
-(IBAction) resetAspectRatio:(id)sender;

-(IBAction) toggleLetterBox:(id)sender;

-(IBAction) stepWindowSize:(id)sender;

-(IBAction) showMediaInfo:(id)sender;

-(void) setOSDMessage:(NSString*) msg;


//delegate of DOMProxySPlayerDelegate
- (NSString*)dom_snapshot:(WebView *)hostWebView;
- (NSString*)dom_movie_curtime:(WebView *)hostWebView;
- (NSString*)dom_movie_totaltime:(WebView *)hostWebView;
- (NSString*)dom_window_closeoauth:(WebView *)hostWebView;
- (NSString*)dom_window_close:(WebView *)hostWebView;
- (NSString*)dom_window_open:(NSString*)url HostWebView:(WebView *)hostWebView;
- (NSString*)dom_window_openoauth:(NSString*)url HostWebView:(WebView *)hostWebView;

@end