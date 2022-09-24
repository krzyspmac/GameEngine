//
//  general.cpp
//  Engine
//
//  Created by krzysp on 21/09/2022.
//

#include "general.hpp"

std::vector<std::string> engine::split_components(std::string source, std::string splitBy)
{
    std::vector<std::string> result;

    char *valueString = (char*)malloc(strlen(source.c_str()) * sizeof(char));
    if (valueString)
    {
        strcpy(valueString, source.c_str());

        char *token;
        token = strtok(valueString, splitBy.c_str());

        while (token != NULL)
        {
            result.push_back(std::string(token));
            token = strtok (NULL, splitBy.c_str());
        }
        free(valueString);
    }

    return result;
}
