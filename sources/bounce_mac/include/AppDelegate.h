#import <Cocoa/Cocoa.h>
#import "bounce/ApplicationContext.h"
#import "MacEventManager.h"

@interface MyApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate> {
	NSWindow* window;
	NSOpenGLContext* openGLContext;
	bounce_mac::MacEventManager* eventManager;
	//@private NSView* _view;
}

@property(assign) NSWindow* window;
@property(assign) NSOpenGLContext* openGLContext;
@property(assign) bounce_mac::MacEventManager* eventManager;
@property(assign) bounce::ApplicationContext* applicationContext;
		//@property(nonatomic, retain) NSView* view;
@end
