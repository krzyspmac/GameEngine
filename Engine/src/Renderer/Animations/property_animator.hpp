//
//  property_animator.hpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef property_animator_hpp
#define property_animator_hpp

#include "scripting_engine_provider_interface.h"
#include "value_animator.hpp"
#include "sprite_draw_interface.h"
#include "animation_interface.h"
#include "property_animator_interface.h"
#include "memory.h"

namespace engine
{
    /**
     Provides a way to animate one value.
     */
    class PropertyAnimator: public PropertyAnimatorI
    {
        std::unique_ptr<ValueAnimator> m_valueAnimator;
        SpriteRepresentationI *m_sprite;

    public:
        PropertyAnimator(AnimatablePropertiesI *sprite, ValueAnimator *valueAnimator);
        virtual ~PropertyAnimator();
        
    public: // AnimatableI
        void Start();
        void Stop();
        
    public: // MemoryI
        void FreeMem();

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(PropertyAnimator);
    };
};

#endif /* property_animator_hpp */
