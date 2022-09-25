//
//  callable_scripting.cpp
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#include "callable_scripting.hpp"

using namespace engine;

void CallableFunctionEmpty::Perform()
{
    if (m_fnc != nullptr)
    {   m_fnc();
    }
}

//void CallableFunctionParameters2::Perform()
//{
//    
//}
