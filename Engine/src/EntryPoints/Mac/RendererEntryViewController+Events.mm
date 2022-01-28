//
//  RendererEntryViewController+RendererEntryViewController_Helpers.m
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#import "RendererEntryViewController.h"
#include "common.h"
#include "common_engine_impl.h"

using namespace engine;

@implementation RendererEntryViewController (Events)

#pragma mark - Setup

- (void)setupEvents
{
    if (didSetupEvents) { return; };

    [self setupMouseClickEvents];
    [self setupMouseMovedEvents];
    [self setupKeyEvents];

    didSetupEvents = YES;
}

- (void)setupMouseClickEvents
{
#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseUp handler:^NSEvent * _Nullable(NSEvent * _Nonnull event) {
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
#if USES_CONSOLE
        self->m_consoleRendererProvider->HandleEvent(event);
#endif
        auto& eventsProvider = GetMainEngine()->getEventProvider();

        switch (event.type)
        {
            case NSEventTypeKeyDown:
            {
                unsigned short key = event.keyCode;
                eventsProvider.PushKeyStateChange(key, true);
                break;
            }
            case NSEventTypeKeyUp:
            {
                unsigned short key = event.keyCode;
                eventsProvider.PushKeyStateChange(key, false);
                break;
            }
            case NSFlagsChanged:
            {
                NSEventModifierFlags flags = event.modifierFlags;

                bool isShift = flags & NSEventModifierFlagShift;
                eventsProvider.PushFlagsChange(FLAG_SHIFT, isShift);

                bool isControl = flags & NSEventModifierFlagControl;
                eventsProvider.PushFlagsChange(FLAG_CONTROL, isControl);

                break;
            }
            default:
            {
                break;
            }
        }

        return event;
    }];
#endif
}

#pragma mark - Handling

- (void)handle:(NSEvent*)event
{
#if USES_CONSOLE
    m_consoleRendererProvider->HandleEvent(event);
#endif
}

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else

- (void)mouseMoved:(NSEvent *)event
{
    NSView    *view = self.view;
    CGRect    viewFrame = view.frame;
    CGPoint   locationInView = [view convertPoint:[event locationInWindow] fromView:nil];

    locationInView.y = viewFrame.size.height - locationInView.y;

    float xPer = locationInView.x / viewFrame.size.width;
    float yPer = locationInView.y / viewFrame.size.height;

    auto& viewport = m_engine->GetEngineSetup().resolution;
    Origin locationInViewport;
    locationInViewport.x = (int)(xPer * (float)viewport.width);
    locationInViewport.y = (int)(yPer * (float)viewport.height);

    m_engine->getEventProvider().PushMouseLocation(locationInViewport);

    [self handle:event];
}

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

#endif

@end
