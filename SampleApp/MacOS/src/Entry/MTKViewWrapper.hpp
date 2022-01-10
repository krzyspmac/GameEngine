//
//  MTKViewWrapper.hpp
//  SampleApp
//
//  Created by krzysp on 10/01/2022.
//

#ifndef MTKViewWrapper_hpp
#define MTKViewWrapper_hpp

#include <Metal/Metal.hpp>

#if __OBJC__
#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>

#define CPP_METAL_VALIDATE_SIZE( lhs, rhs ) \
    _Static_assert( sizeof( lhs ) == sizeof( rhs ), "mismatching size " # lhs " <> " # rhs "!" )

#define CPP_METAL_CLASS_ALIAS( typename ) \
    namespace CPPMetalInternal                                   \
    {                                                            \
        using typename = MTL ## typename *;                      \
        CPP_METAL_VALIDATE_SIZE( MTL ## typename *, CFTypeRef ); \
    }

#define CPP_METAL_PROTOCOL_ALIAS( typename ) \
    namespace CPPMetalInternal                                       \
    {                                                                \
        using typename = id< MTL ## typename >;                      \
        CPP_METAL_VALIDATE_SIZE( id <MTL ## typename >, CFTypeRef ); \
    }

#define CPP_METALKIT_CLASS_ALIAS( typename ) \
    namespace CPPMetalInternal                                   \
    {                                                            \
        using typename = MTK ## typename *;                      \
        CPP_METAL_VALIDATE_SIZE( MTK ## typename *, CFTypeRef ); \
    }

namespace CPPMetalInternal
{
    using ObjCObj = NSObject;
}

#else // if (!__OBJC__)

#include <objc/message.h>


#define CPP_METAL_CLASS_ALIAS( typename ) \
    namespace CPPMetalInternal            \
    {                                     \
        using typename = id;              \
    }

#define CPP_METAL_PROTOCOL_ALIAS( typename ) \
    namespace CPPMetalInternal               \
    {                                        \
        using typename = id;                 \
    }

#define CPP_METALKIT_CLASS_ALIAS( typename ) \
    namespace CPPMetalInternal               \
    {                                        \
        using typename = id;                 \
    }

namespace CPPMetalInternal
{
    using ObjCObj = CFTypeRef;
}

#endif // !__OBJC__

#if __OBJC__ && __has_feature(objc_arc)

#define CPP_METAL_PROCESS_LABEL( string, funcname )                                            \
{                                                                                              \
    CFStringRef cfString = CFStringCreateWithCString(nullptr, string, kCFStringEncodingASCII); \
    funcname(cfString);                                                                        \
}

#else

#define CPP_METAL_PROCESS_LABEL( string, funcname )                                            \
{                                                                                              \
    CFStringRef cfString = CFStringCreateWithCString(nullptr, string, kCFStringEncodingASCII); \
    funcname(cfString);                                                                        \
    CFRelease(cfString);                                                                       \
}

#endif

#define CPP_METAL_MOVE_CONSTRUCTOR_AND_OPERATOR_OVERLOAD_IMPLEMENTATION( classname ) \
    inline classname::classname(classname && rhs)                                   \
    : m_objCObj(rhs.m_objCObj)                                                      \
    , m_device(rhs.m_device)                                                        \
    {                                                                               \
        rhs.m_objCObj = nullptr;                                                    \
        rhs.m_device = nullptr;                                                     \
    }                                                                               \
                                                                                    \
    inline classname & classname::operator=(classname && rhs)                       \
    {                                                                               \
        m_objCObj = rhs.m_objCObj;                                                  \
        m_device = rhs.m_device;                                                    \
        rhs.m_objCObj = nullptr;                                                    \
        rhs.m_device = nullptr;                                                     \
                                                                                    \
        return *this;                                                               \
    }

#define CPP_METAL_OBJCOBJ_GETTER_IMPLEMENATATION( classname )       \
    inline CPPMetalInternal::classname classname::objCObj() const \
    {                                                             \
        return m_objCObj;                                         \
    }

#define CPP_METAL_DECLARE_FUNCTION_POINTER( methodName ) \
    methodName ## Type methodName

#define CPP_METAL_VIRTUAL virtual

CPP_METAL_PROTOCOL_ALIAS( Device );
CPP_METALKIT_CLASS_ALIAS( View );

//CPP_METAL_OBJCOBJ_GETTER_IMPLEMENATATION(Device);

namespace engine
{
    class MTKViewWrapper
    {
        CPPMetalInternal::View m_objCObj;
        MTL::Device *m_device;

    public:

        MTKViewWrapper(CPPMetalInternal::View objCObj, MTL::Device & device);
        virtual ~MTKViewWrapper();

        void Draw();
    };
};

#endif /* MTKViewWrapper_hpp */
