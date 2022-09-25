//
//  callable_scripting.hpp
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#ifndef callable_scripting_hpp
#define callable_scripting_hpp

#include "common.h"

namespace engine
{

    class MyCallableBase
    {

    };

    class CallableFunctionEmpty: public MyCallableBase
    {
    private:
        void (*m_fnc) (void);
    public:
        CallableFunctionEmpty(void (*fnc) (void))
            : MyCallableBase()
            , m_fnc(fnc)
        { };

        void Perform();
    };

    template <typename X, typename Y>
    class CallableFunctionParameters2: public MyCallableBase
    {
    private:
        void (*m_fnc) (X, Y);
    public:
        CallableFunctionParameters2()
            : MyCallableBase()
            , m_fnc(nullptr)
        { };
        
        CallableFunctionParameters2(void (*fnc) (X, Y))
            : MyCallableBase()
            , m_fnc(fnc)
        { };

        void Perform();
    };
};

#endif /* callable_scripting_hpp */
