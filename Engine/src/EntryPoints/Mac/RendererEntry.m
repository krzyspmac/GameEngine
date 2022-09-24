//
//  RendererEntry.m
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#import "RendererEntry.h"

@implementation RendererEntry

+ (id<RendererViewControllerProtocol>)instantiate
{
    Class rendererClass = NSClassFromString(@"RendererEntryViewController");
    id controller = [[rendererClass alloc] init];
    return controller;
}

@end
