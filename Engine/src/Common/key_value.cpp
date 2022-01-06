//
//  key_value.cpp
//  Engine
//
//  Created by krzysp on 06/01/2022.
//

#include "key_value.hpp"

using namespace engine;

std::string KeyValueLine::GetFirstWord(std::string s, size_t *outEnd)
{
    std::string delim = " ";

    auto start = 0U;
    auto end = s.find(delim);
    if (end != std::string::npos)
    {
        if (outEnd) { *outEnd = end; };

        return s.substr(start, end - start);
    }
    else
    {
        if (outEnd) { *outEnd = -1; };

        return "";
    }
}

KeyValueProperties::KeyValueProperties(std::string s)
{
    // The first word is the type
    size_t lineStartPos = 0;
    m_type = KeyValueLine::GetFirstWord(s, &lineStartPos);
    if (m_type == "" || lineStartPos < 1) { return; };

    // The rest is the key value type line.
    std::string delim = "=";
    std::string line = s.substr(lineStartPos+1, s.size());
    line.append(" ");

    size_t count = line.size();
    size_t startPos = 0;
    KeyValue kv;
    bool quoted = false;

    for (size_t i = 0; i < count; i++)
    {
        char c = line.at(i);

        if (c == '"') { quoted = !quoted; };

        if (!quoted && c == '=') // split
        {
            kv.key = line.substr(startPos, i-startPos);
            trim(kv.key);
            startPos = i+1;
        }

        if (!quoted && (c == ' ' || c == '\t')) // split
        {
            kv.value = line.substr(startPos, i-startPos);
            trim(kv.value);
            m_values.push_back(kv);
            kv.key = "";
            kv.value = "";
            startPos = i+1;
        }
    }
}

std::string KeyValueProperties::GetStringValueFor(std::string key)
{
    for (auto& kv: m_values)
    {
        if (kv.key == key)
        {
            return kv.value;
        }
    }
    return "";
}

int KeyValueProperties::GetNumberValueFor(std::string key)
{
    auto str = GetStringValueFor(key);
    if (!str.empty())
    {
        return std::stoi(str);
    }
    else
    {
        return 0;
    }
}

Vector2 KeyValueProperties::GetVectorValueFor(std::string key)
{
    auto str = GetStringValueFor(key);
    if (!str.empty())
    {
        return VectorMake(str);
    }
    else
    {
        return Vector2Zero;
    }
}
