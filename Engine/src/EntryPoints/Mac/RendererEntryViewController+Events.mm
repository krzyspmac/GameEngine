//
//  RendererEntryViewController+RendererEntryViewController_Helpers.m
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#import "RendererEntryViewController.h"
#include "common.h"
#include "common_engine_impl.h"

#ifdef APPLE
#include "gamepad_apple_handle.hpp"
#endif

using namespace engine;

@implementation RendererEntryViewController (Events)

#pragma mark - Setup

- (void)setupEvents
{
    if (didSetupEvents) { return; };

    [self setupMouseClickEvents];
    [self setupMouseMovedEvents];
    [self setupKeyEvents];
    [self setupControllers];

    didSetupEvents = YES;
}

- (void)setupMouseClickEvents
{
#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseUp handler:^NSEvent * _Nullable(NSEvent * _Nonnull event) {
#if SHOW_CONSOLE
        if (!self->m_consoleRenderer->GetConsoleHidden())
        {
            bool result = self->m_consoleRendererProvider->HandleEvent(event);
            if (result) { return event; };
        }
#endif

        self->m_engine->getEventProvider().PushMouseLeftUp();
        return event;
    }];
#endif
}

- (void)setupMouseMovedEvents
{
#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
    NSView *view = self.view;
    if (mouseTrackingArea)
    {
        [view removeTrackingArea: mouseTrackingArea];
    }

    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:view.bounds
                                                        options:NSTrackingActiveInKeyWindow|NSTrackingMouseMoved
                                                          owner:self
                                                       userInfo:nil];
    [view addTrackingArea:area];
#endif
}

- (void)setupKeyEvents
{
#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
    // If we want to receive key events, we either need to be in the responder chain of the key view,
    // or else we can install a local monitor. The consequence of this heavy-handed approach is that
    // we receive events for all controls, not just Dear ImGui widgets. If we had native controls in our
    // window, we'd want to be much more careful than just ingesting the complete event stream.
    // To match the behavior of other backends, we pass every event down to the OS.
    NSEventMask eventMask = NSEventMaskKeyDown | NSEventMaskKeyUp | NSEventMaskFlagsChanged;
    [NSEvent addLocalMonitorForEventsMatchingMask:eventMask handler:^NSEvent * _Nullable(NSEvent *event)
    {
#if SHOW_CONSOLE
        if (!self->m_consoleRenderer->GetConsoleHidden())
        {
            self->m_consoleRendererProvider->HandleEvent(event);
        }
#endif
        auto& eventsProvider = ENGINE().getEventProvider();
        switch (event.type)
        {
            case NSEventTypeKeyDown:
            {
                NSString *characters = event.charactersIgnoringModifiers;
                for (NSInteger i = 0; i < characters.length; i++)
                {
                    unichar c = [characters characterAtIndex:i];
                    eventsProvider.PushKeyStateChange((unsigned short)c, true);
                }
                break;
            }
            case NSEventTypeKeyUp:
            {
                NSString *characters = event.charactersIgnoringModifiers;
                for (NSInteger i = 0; i < characters.length; i++)
                {
                    unichar c = [characters characterAtIndex:i];
                    eventsProvider.PushKeyStateChange((unsigned short)c, false);
                }
                break;
            }
            case NSFlagsChanged:
            {
                NSEventModifierFlags flags = event.modifierFlags;

                bool isShift = flags & NSEventModifierFlagShift;
                eventsProvider.PushFlagsChange(FLAG_SHIFT, isShift);

                bool isControl = flags & NSEventModifierFlagControl;
                eventsProvider.PushFlagsChange(FLAG_CONTROL, isControl);

                bool isAlt = flags & NSEventModifierFlagOption;
                eventsProvider.PushFlagsChange(FLAG_ALT, isAlt);

                bool isCommand = flags & NSEventModifierFlagCommand;
                eventsProvider.PushFlagsChange(FLAG_COMMAND, isCommand);

                break;
            }
            default:
            {
                break;
            }
        }

        // TODO: do not send all events to the system!
        return NULL;
    }];
#endif
}

#pragma mark - Handling

#if TARGET_OSX
- (void)handle:(NSEvent*)event
{
#if SHOW_CONSOLE
    if (!self->m_consoleRenderer->GetConsoleHidden())
    {
        m_consoleRendererProvider->HandleEvent(event);
    }
#endif
}
#endif

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else

- (void)mouseMoved:(NSEvent *)event
{
    NSView    *view = self.view;
    CGRect    viewFrame = view.frame;
    CGPoint   locationInView = [view convertPoint:[event locationInWindow] fromView:nil];

    /** Make the origin top, left */
    locationInView.y = viewFrame.size.height - locationInView.y;

    /** Get the desired viewport set by the engine */
    auto& viewport = m_engine->GetEngineSetup().resolution;

    /** Get the scale that was applied to the viewport in order to render it on-screen*/
    float aspect = desiredFramebufferTextureSize.x / desiredFramebufferTextureSize.y;
    float viewFrameAspect = CGRectGetWidth(viewFrame) / CGRectGetHeight(viewFrame);
    simd_float2 displayFramebufferSize;
    if (viewFrameAspect >= aspect)
    {
        displayFramebufferSize.y = viewFrame.size.height;
        displayFramebufferSize.x = displayFramebufferSize.y * aspect;
    }
    else
    {
        displayFramebufferSize.x = viewFrame.size.width;
        displayFramebufferSize.y = displayFramebufferSize.x / aspect;
    }

    /** Scale & offset the position to take into account that the viewport may be
        scaled and translated/centered in the backing window/surface. */
    locationInView.x -= ceil((CGRectGetWidth(viewFrame) - displayFramebufferSize.x)/2);
    locationInView.x = MAX(0, MIN(locationInView.x, displayFramebufferSize.x));

    locationInView.y -= ceil((CGRectGetHeight(viewFrame) - displayFramebufferSize.y)/2);
    locationInView.y = MAX(0, MIN(locationInView.y, displayFramebufferSize.y));

    float xPer = locationInView.x / displayFramebufferSize.x;
    float yPer = locationInView.y / displayFramebufferSize.y;

    /** Calcualte position in the viewport */
    Origin locationInViewport;
    locationInViewport.x = (int)(xPer * (float)viewport.width);
    locationInViewport.y = (int)(yPer * (float)viewport.height);

    /** Send the calcualted position ot the engine provider */
    m_engine->getEventProvider().PushMouseLocation(locationInViewport);

    /** Also handle other events if necessary */
    [self handle:event];
}

- (void)keyDown:(NSEvent *)event             { [self handle:event]; }
- (void)keyUp:(NSEvent *)event               { [self handle:event]; };
- (void)mouseDown:(NSEvent *)event           { [self handle:event]; }
- (void)rightMouseDown:(NSEvent *)event      { [self handle:event]; }
- (void)otherMouseDown:(NSEvent *)event      { [self handle:event]; }
- (void)mouseUp:(NSEvent *)event             { [self handle:event]; }
- (void)rightMouseUp:(NSEvent *)event        { [self handle:event]; }
- (void)otherMouseUp:(NSEvent *)event        { [self handle:event]; }
- (void)mouseDragged:(NSEvent *)event        { [self handle:event]; }
- (void)rightMouseMoved:(NSEvent *)event     { [self handle:event]; }
- (void)rightMouseDragged:(NSEvent *)event   { [self handle:event]; }
- (void)otherMouseMoved:(NSEvent *)event     { [self handle:event]; }
- (void)otherMouseDragged:(NSEvent *)event   { [self handle:event]; }
- (void)scrollWheel:(NSEvent *)event         { [self handle:event]; }

#endif // defined(TARGET_IOS) || defined(TARGET_TVOS)

- (void)setupControllers
{
#if USE_CONTROLLERS
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(didConnectController:) name:GCControllerDidConnectNotification object:nil];
    [center addObserver:self selector:@selector(didDisconnectController:) name:GCControllerDidDisconnectNotification object:nil];

    [self setupControllerHandlers];
    [self processController];
#endif
}

#if USE_CONTROLLERS

- (void)didConnectController:(NSNotification*)notification
{
    [self processController];
}

- (void)didDisconnectController:(NSNotification*)notification
{
    [self processController];
}

- (void)resetController
{
    self.controller = nil;
    self.controllerMicroProfile = nil;
    self.controllerExtendedProfile = nil;
    self.controllerDPad = nil;
    self.leftThumbstick.valueChangedHandler = nil;
    self.rightThumbstick.valueChangedHandler = nil;
}

- (void)setupControllerHandlers
{
    Engine *weakEngine = self->m_engine;

    self.leftThumbstickHandler = ^(GCControllerDirectionPad * _Nonnull dpad, float xValue, float yValue) {
        weakEngine->getEventProvider().PushLeftThumbstickAxisChange(xValue, -yValue);
    };
    self.rightThumbstickHandler = ^(GCControllerDirectionPad * _Nonnull dpad, float xValue, float yValue) {
        weakEngine->getEventProvider().PushRightThumbstickAxisChange(xValue, -yValue);
    };
    self.dpadThumbstickHandler = ^(GCControllerDirectionPad * _Nonnull dpad, float xValue, float yValue) {
        weakEngine->getEventProvider().PushDpadAxisChange(xValue, -yValue);
    };
}

- (void)processController
{
    NSArray<GCController*> *controllers = [GCController controllers];
    self.controller = [controllers firstObject];
    self.controllerMicroProfile = self.controller.microGamepad;
    self.controllerExtendedProfile = self.controller.extendedGamepad;

    if (self.controllerExtendedProfile != nil)
    {
        self.leftThumbstick = self.controllerExtendedProfile.leftThumbstick;
        self.rightThumbstick = self.controllerExtendedProfile.rightThumbstick;
        self.controllerDPad = self.controllerExtendedProfile.dpad;

        self.leftThumbstick.valueChangedHandler = self.leftThumbstickHandler;
        self.rightThumbstick.valueChangedHandler = self.rightThumbstickHandler;
        self.controllerDPad.valueChangedHandler = self.dpadThumbstickHandler;
    }
    else if (self.controllerMicroProfile != nil)
    {
        self.controllerDPad = self.controllerMicroProfile.dpad;
        self.controllerDPad.valueChangedHandler = self.dpadThumbstickHandler;
    }

    [self updateControllerScripts];
}

- (void)updateControllerScripts
{
    if (self.controllerExtendedProfile != nil)
    {
        GamepadAppleHandle *gampadHandle = new GamepadAppleHandle(self.controller);
        m_engine->getEventProvider().PushGamepadConnectionEvent(GAMEPAD_TYPE_EXTENDED, GAMEPAD_MAKE_SONY, GAMEPAD_CONNECTION_STATUS_CONNECTED, gampadHandle);
    }
    else if (self.controllerMicroProfile != nil)
    {
        GamepadAppleHandle *gampadHandle = new GamepadAppleHandle(self.controller);
        m_engine->getEventProvider().PushGamepadConnectionEvent(GAMEPAD_TYPE_EXTENDED, GAMEPAD_MAKE_SONY, GAMEPAD_CONNECTION_STATUS_CONNECTED, gampadHandle);
    }
    else
    {
        m_engine->getEventProvider().PushGamepadConnectionEvent(GAMEPAD_TYPE_EXTENDED, GAMEPAD_MAKE_SONY, GAMEPAD_CONNECTION_STATUS_DISCRONNECTED, nil);
    }
}

#endif // USE_CONTROLLERS

@end
