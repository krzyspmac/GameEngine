//
//  engine_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_interface_h
#define engine_interface_h

namespace engine
{
    class EngineI
    {
    public:
        ///
        EngineI() { }

        ///
        virtual void update() = 0;
    };
};

#endif /* engine_interface_h */
