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

- (void)setEventManager:(bounce::EventManager*) newEventManager {
    eventManager = newEventManager;
}

- (void)keyEvent:(NSEvent *) event {
    //NSLog(@"Pressed key");
    
    if (event.type == NSKeyDown || event.type == NSKeyUp)
    {
        unsigned int quals = event.modifierFlags;
        NSString* str = event.characters;
        NSString* strWithout = event.charactersIgnoringModifiers;
        
        //NSLog(str);
        
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
        
        if (event.type == NSKeyDown)
            eventManager->queueEvent(std::unique_ptr<bounce::Event>(new bounce::KeydownEvent(keysym)));
        else if (event.type == NSKeyUp) {
            //NSLog(@"keyup");
            eventManager->queueEvent(std::unique_ptr<bounce::Event>(new bounce::KeyupEvent(keysym)));
        }
    }
}

- (void)keyUp:(NSEvent *) event {
    [self keyEvent:event];
}

- (void)keyDown:(NSEvent *) event {
    [self keyEvent:event];
}

@end