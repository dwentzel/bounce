#import <Cocoa/Cocoa.h>
#import "bounce/application_context.h"

@interface MyApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate> {
	NSWindow* window;
	NSOpenGLContext* openGLContext;
	bounce::EventManager* eventManager;
	//@private NSView* _view;
}

@property(assign) NSWindow* window;
@property(assign) NSOpenGLContext* openGLContext;
@property(assign) bounce::EventManager* eventManager;
@property(assign) bounce::ApplicationContext* applicationContext;
		//@property(nonatomic, retain) NSView* view;
@end
