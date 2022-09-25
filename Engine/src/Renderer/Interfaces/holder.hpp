//
//  holder.hpp
//  Engine
//
//  Created by krzysp on 12/08/2022.
//

#ifndef holder_h
#define holder_h

namespace engine
{
    template<typename T>
    class Holder1
    {
        T m_value;
    public:
        Holder1(T value) { m_value = value; }
        ~Holder1() { };
        T& Get() { return m_value; }
    };
};

#endif /* holder_h */
