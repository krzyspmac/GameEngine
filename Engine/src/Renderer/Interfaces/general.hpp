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

#ifndef general_h
#define general_h

#include <iostream>
#include <vector>

namespace engine
{
    inline float sqr(float x)
    {
        return x * x;
    }

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    // break the string into parts
    static inline std::vector<std::string> explode(std::string &s, std::string delimiter) {
        std::vector<std::string> broken;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            broken.push_back(token);
            s.erase(0, pos + delimiter.length());
        }

        broken.push_back(s);

        return broken;
    }

    // replace all occurrances within a string
    static inline std::string replaceAll(std::string str, const std::string& from, const std::string& to)
    {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }

    /** map a vector of source elements S to destination elements D */
    template<typename S, typename D>
    std::vector<D> map(std::vector<S> source, std::function<D(S)> lambda)
    {
        std::vector<D> result;

        for (auto& srcItem : source)
        {
            result.push_back(lambda(srcItem));
        }

        return result;
    }

    /** filter */
    template<typename S>
    std::vector<S*> filter(std::vector<S*>& source, std::function<bool(S*)> lambda)
    {
        std::vector<S*> result;

        for (auto* srcItem : source)
        {
            if (lambda(srcItem))
            {
                result.push_back(srcItem);
            }
        }

        return result;
    }

    /** matching */
    template<typename S>
    S* matching(std::vector<S>& source, std::function<bool(S&)> lambda)
    {
        for (auto& srcItem : source)
        {
            if (lambda(srcItem))
            {
                return &srcItem;
            }
        }

        return nullptr;
    };

    template<typename S>
    S* matching(std::vector<std::unique_ptr<S>>& source, std::function<bool(S*)> lambda)
    {
        for (auto& srcItem : source)
        {
            if (lambda(srcItem.get()))
            {
                return srcItem.get();
            }
        }

        return nullptr;
    };

    /** Split into separate components */
    std::vector<std::string> split_components(std::string source, std::string splitBy);
};

#endif /* general_h */
