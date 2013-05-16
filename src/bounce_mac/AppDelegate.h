#import <Cocoa/Cocoa.h>

@interface MyApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate> {
	@private NSWindow* _window;
	@private NSView* _view;
}

@property(nonatomic, retain) NSWindow* window;
@property(nonatomic, retain) NSView* view;
@end
