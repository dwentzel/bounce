#import "GameView.h"

@interface GameView()
{
    
}

@end

@implementation GameView : NSView

//@synthesize eventManager;

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)setEventManager:(bounce_mac::MacEventManager*)  newEventManager {
    eventManager = newEventManager;
}

- (void)keyDown:(NSEvent *) event {
    NSLog(@"Pressed key");
    
    if (event.type == NSKeyDown)
    {
        unsigned int quals = event.modifierFlags;
        NSString* str = event.characters;
        NSString* strWithout = event.charactersIgnoringModifiers;
        
        unichar ch = str.length ? [str characterAtIndex: 0] : 0;
        unichar without = strWithout.length ? [strWithout characterAtIndex: 0] : 0;
        
        bounce::Keysym keysym;
        
        if (ch == 'a')
            keysym.sym = bounce::Key::A;
        else if (ch == 's')
            keysym.sym = bounce::Key::S;
        else if (ch == 'd')
            keysym.sym = bounce::Key::D;
        else if (ch == 'w')
            keysym.sym = bounce::Key::W;
        
        eventManager->queueEvent(new bounce::KeydownEvent(keysym));
    }
}

@end