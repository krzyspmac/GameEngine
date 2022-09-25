//
//  key_value.hpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#ifndef key_value_hpp
#define key_value_hpp

#include "common.h"
#include "interfaces.h"

namespace engine
{
    typedef struct
    {
        std::string key;
        std::string value;
    } KeyValue;

    class KeyValueLine
    {
    public:
        static std::string GetFirstWord(std::string s, size_t *outEnd);
    };

    class KeyValueProperties
    {
        std::vector<KeyValue> m_values;
        std::string m_type;
    public:
        KeyValueProperties(std::string line);

        auto& GetType() { return m_type; };
        auto& GetValues() { return m_values; };

        std::string GetStringValueFor(std::string);
        int GetNumberValueFor(std::string);
        Vector2 GetVectorValueFor(std::string);
    };
};

#endif /* key_value_hpp */
