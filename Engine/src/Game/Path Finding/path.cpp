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
        if (i + 1 >= size)
        {
            break;
        }

        Vector2 &first = m_path.at(i);
        Vector2 &second = m_path.at(i+1);
        result.push_back(Line(first, second));
    }

    return result;
}
