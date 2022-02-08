//
//  general.hpp
//  Engine
//
//  Created by krzysp on 29/12/2021.
//

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
};

#endif /* general_h */
