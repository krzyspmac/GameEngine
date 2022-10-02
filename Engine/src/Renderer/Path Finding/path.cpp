// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "path.hpp"

using namespace engine;

Path::Path(Vector2 from, Vector2 to)
: PathI(from, to)
{
    m_path.push_back(from);
    m_path.push_back(to);
}

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
