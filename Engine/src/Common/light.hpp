//
//  light.hpp
//  Engine
//
//  Created by krzysp on 04/02/2022.
//

#ifndef light_h
#define light_h

namespace engine
{
    struct Light
    {
        float[3]    color;
        float       ambientIntensity;

        /*
         var color: (Float, Float, Float)  // 1
         var ambientIntensity: Float       // 2

         static func size() -> Int {       // 3
           return MemoryLayout<Float>.size * 4
         }

         func raw() -> [Float] {
           let raw = [color.0, color.1, color.2, ambientIntensity]   // 4
           return raw
         }
         */
    };
};

#endif /* light_h */
