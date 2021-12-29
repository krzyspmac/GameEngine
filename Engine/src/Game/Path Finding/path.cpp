//
//  path.cpp
//  Engine
//
//  Created by krzysp on 28/12/2021.
//

#include "path.hpp"

using namespace engine;

std::vector<Line> Path::ToLines()
{
    std::vector<Line> result;
    size_t size = m_path.size();

    for (size_t i = 0; i < size; i++)
    {
        if (i + 1 >= size) { break; }

        Vector2 &first = m_path.at(i);
        Vector2 &second = m_path.at(i+1);
        result.push_back(Line(first, second));
    }

    return result;
}

float Path::GetDistance()
{
    float   distance = 0;
    size_t  count = m_path.size();

    for (int i = 0; i < count; i++)
    {
        if (i+1 >= count) { break; }
        distance += Vector2Distance(m_path.at(i), m_path.at(i+1));
    }

    return distance;
}

std::string Path::Description()
{
    std::string result;

    float distance = 0;

    char str[256];
    Vector2 *previous = nullptr;
    std::for_each(m_path.begin(), m_path.end(), [&](Vector2 &v) {
        sprintf(str, " [%1.0f, %1.0f]", v.x, v.y);
        result += str;
        if (previous)
        {
            distance += Vector2Distance(v, *previous);
        }
        previous = &v;
    });

    sprintf(str, "\n => distance = %f", distance);
    result += str;
    result += "\r";

    return result;
}
