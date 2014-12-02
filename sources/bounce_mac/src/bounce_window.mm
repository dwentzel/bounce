#import "bounce_window.h"
#import "engine/event.h"

@implementation BounceWindow

- (id) initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag {
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    
    return self;
}

- (void)setEventManager:(bounce::EventManager *)eventManager {
    eventManager_ = eventManager;
}

bounce::Key UnicharToKey(unichar ch)
{
    switch (ch) {
        case 'a':
            return bounce::KEY_A;
        case 'b':
            return bounce::KEY_B;
        case 'c':
            return bounce::KEY_C;
        case 'd':
            return bounce::KEY_D;
        case 'e':
            return bounce::KEY_E;
        case 'f':
            return bounce::KEY_F;
        case 'g':
            return bounce::KEY_G;
        case 'h':
            return bounce::KEY_H;
        case 'i':
            return bounce::KEY_I;
        case 'j':
            return bounce::KEY_J;
        case 'k':
            return bounce::KEY_K;
        case 'l':
            return bounce::KEY_L;
        case 'm':
            return bounce::KEY_M;
        case 'n':
            return bounce::KEY_N;
        case 'o':
            return bounce::KEY_O;
        case 'p':
            return bounce::KEY_P;
        case 'q':
            return bounce::KEY_Q;
        case 'r':
            return bounce::KEY_R;
        case 's':
            return bounce::KEY_S;
        case 't':
            return bounce::KEY_T;
        case 'u':
            return bounce::KEY_U;
        case 'v':
            return bounce::KEY_V;
        case 'w':
            return bounce::KEY_W;
        case 'x':
            return bounce::KEY_X;
        case 'y':
            return bounce::KEY_Y;
        case 'z':
            return bounce::KEY_Z;
        default:
            return bounce::NO_KEY;
    }
}

- (void)keyEvent:(NSEvent *) event {
    //NSLog(@"Pressed key");
    
    //    if (event.type == NSKeyDown || event.type == NSKeyUp)
    //    {
    //        unsigned int quals = event.modifierFlags;
    NSString* str = event.characters;
    
    //        NSString* strWithout = event.charactersIgnoringModifiers;
    
    unichar ch = str.length ? [str characterAtIndex: 0] : 0;
    //        unichar without = strWithout.length ? [strWithout characterAtIndex: 0] : 0;
    //        NSLog(@"%@", strWithout);
    
    bounce::Keysym keysym;
    keysym.mod = bounce::NO_MODIFIER;
    keysym.sym = UnicharToKey(ch);
    
    if (event.type == NSKeyDown)
        eventManager_->QueueEvent(bounce::EventPtr(new bounce::KeydownEvent(keysym)));
    else if (event.type == NSKeyUp) {
        eventManager_->QueueEvent(bounce::EventPtr(new bounce::KeyupEvent(keysym)));
    }
    //    }
}

- (void)keyUp:(NSEvent *) event {
    [self keyEvent:event];
}

- (void)keyDown:(NSEvent *) event {
    [self keyEvent:event];
}

@end