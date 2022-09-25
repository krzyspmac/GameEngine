//
//  RendererEntry.h
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#import "RendererEntryViewController+Protocol.h"

@interface RendererEntry : NSObject

/** Return an opaque instance of the view controller for the initial view */
+ (id<RendererViewControllerProtocol>)instantiate;

@end
