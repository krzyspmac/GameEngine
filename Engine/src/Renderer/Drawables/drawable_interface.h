//
//  drawable_interface.h
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#ifndef drawable_interface_h
#define drawable_interface_h

#include "common.h"
#include "common_engine_impl.h"

namespace engine
{
    /** Declares an abstract interface for the final object that will be drawn using the EngineProviderI.
        Different backend for different libraries might declare differently working concrete instances.

        The `drawable` is usually composed of vertex data and texture data.
     */
    class DrawableI
    {
    public:
        DrawableI(float width, float height) { };
        virtual void SetPosition(float, float) = 0;
        virtual void SetScale(float) = 0;
    };
};

#endif /* drawable_interface_h */
