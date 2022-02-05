//
//  light.cpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#include "light.hpp"

using namespace engine;

SCRIPTING_INTERFACE_IMPL_NAME(Light);

std::vector<luaL_Reg> Light::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
    });
    return result;
}
