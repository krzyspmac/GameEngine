//
//  ini_reader.cpp
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#include "ini_reader.hpp"
#include <stdio.h>

using namespace engine;

IniReader::IniReader(std::string path)
    : m_currentSectionName("")
{
    const char *cPath = path.c_str();
    FILE *fp = fopen(cPath, "r");
    if (fp)
    {
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%s\n", line);
        }
        fclose(fp);
    }
    else
    {
        throw "No .ini file found!";
    }
}

EngineSetup IniReader::GetSetup()
{
    return m_engineSetup;
}

void IniReader::ParseResolutionSection()
{

}
