//
//  callable_interface.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef callable_interface_h
#define callable_interface_h

#include "memory.h"

namespace engine
{
    /**
     Defines an interface for the callback to either the scripting engine
     or just a lambda.
     */
    class CallableI
    {
    public:
        virtual ~CallableI() { };
    };

    /**
     Abstract definition for a callable to a curve function that can give proper animation values when progressing from one value to another.
     Available only in C++.
     @private
     */
    template <typename R, typename V>
    class CallableCurveI: public CallableI
    {
    public:
        CallableCurveI(): CallableI() { };
        virtual ~CallableCurveI() { };
        virtual V GetMin() = 0;
        virtual V GetMax() = 0;
        virtual R f(V progress) = 0;
    };

    /**
     Curve lambda. Provide your own implementation of the curve
     to be used in animation/translator.
     Available only in C++
     @private
     */
    class CallableCurveLamba: public CallableCurveI<float, float>
    {
        float m_min;
        float m_max;
        float m_diff;
        std::function<float(float, float, float)> m_lambda;
    public:
        CallableCurveLamba(float min, float max, std::function<float(float, float, float)> lambda);
    public:
        float GetMin() { return m_min; };
        float GetMax() { return m_max; };
        float GetDiff() { return m_diff; };

        void SetMin(float value) { m_min = value; };
        void SetMax(float value) { m_max = value; };
        float f(float progress);
    };

    /**
     An abstract definition of the callable function to be used in the script when
     specified by the documentation. Various script related functionality will
     extend this interface to provide their own definitions.
     */
    class CallableScriptFunctionI: public CallableI, public MemoryI
    {
    public:
        /** Additional holder for a script function index. Not needed in C++ */
        typedef int CallableScriptFunctionRef;

        CallableScriptFunctionI() : CallableI(), MemoryI() { };
        CallableScriptFunctionI(CallableScriptFunctionRef) : CallableI(), MemoryI() { };
        virtual ~CallableScriptFunctionI() { };
        
        /**
         Available only in C++
         @private
         */
        CallableScriptFunctionRef GetFunctionRef() { return -1; };

        /**
         Available only in C++
         @private
         */
        virtual bool CanCall() = 0;
    };

    /** A wrapper for the empty callable function */
    class CallableParametersEmpty: public CallableScriptFunctionI
    {
        typedef std::function<void(void)> FunctionType;

        FunctionType m_fnc;
    public:
        CallableParametersEmpty()
            : m_fnc(nullptr)
        { };
        CallableParametersEmpty(FunctionType fnc)
            : CallableScriptFunctionI()
            , m_fnc(fnc)
        {
        };

        virtual ~CallableParametersEmpty() { };
        
        bool CanCall() {
            return m_fnc != nullptr;
        };
        void Call() {
            if (CanCall()) {
                m_fnc();
            }
        };
    };

    typedef CallableParametersEmpty CallbackEmpty;

    /** A wrapper for the 1 param callable function */
    template <typename A>
    class CallableParameters1: public CallableScriptFunctionI
    {
        typedef std::function<void(A)> FunctionType;

        FunctionType m_fnc;
    public:
        CallableParameters1()
            : m_fnc(nullptr)
        { };
        CallableParameters1(FunctionType fnc)
            : CallableScriptFunctionI()
            , m_fnc(fnc)
        { };
        virtual ~CallableParametersEmpty() {};
        bool CanCall() { return m_fnc != nullptr; };
        void Call(A p1) { if (CanCall()) m_fnc(p1); };
    };

    /** A wrapper for the 2 params callable function */
    template <typename A, typename B>
    class CallableParameters2: public CallableScriptFunctionI
    {
        std::function<void(A, B)> m_fnc;
    public:
        CallableParameters2()
            : CallableScriptFunctionI()
            , m_fnc(nullptr)
        { };
        CallableParameters2(std::function<void(A, B)> fnc)
            : m_fnc(fnc)
        { };
        virtual ~CallableParametersEmpty() {

        };
        bool CanCall() { return m_fnc != nullptr; }; //return m_fnc != nullptr; };
        void Call(A p1, B p2) { if (CanCall()) m_fnc(p1, p2); };

        static std::shared_ptr<CallableParameters2<A, B>> make_shared(std::function<void(A, B)> fnc) {
            return std::shared_ptr<CallableParameters2<A, B>>(
                  new CallableParameters2<A, B>(fnc)
            );
            return nullptr;
        }
    };

    /** A wrapper for the 3 params callable function */
    template <typename A, typename B, typename C>
    class CallableParameters3: public CallableScriptFunctionI
    {
        std::function<void(A, B, C)> m_fnc;
    public:
        CallableParameters3()
            : CallableScriptFunctionI()
            , m_fnc(nullptr)
        { };
        CallableParameters3(std::function<void(A, B, C)> fnc)
            : m_fnc(fnc)
        { };
        virtual ~CallableParametersEmpty() { };
        bool CanCall() { return m_fnc != nullptr; };
        void Call(A p1, B p2, C p3) { if (CanCall()) m_fnc(p1, p2, p3); };
    };
};

#endif /* callable_interface_h */
