//
//  ini_reader.cpp
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#include "ini_reader.hpp"
#include "key_value.hpp"
#include <stdio.h>

using namespace engine;

std::string GetSectionName(char *srcLine);

IniReader::IniReader(std::string path)
    : m_currentSectionType(UNKNOWN)
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
            if (strlen(line) < 1) { continue; };
            if (line[0] == ';') { continue; };

            if (UpdateSection(line))
            {
                continue;
            }
            else
            {
                ParseKeyValue(line);
            }

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

bool IniReader::UpdateSection(char *srcLine)
{
    // Get the section name if possible
    std::string sectionName = GetSectionName(srcLine);

    if (sectionName.empty())
    {
        return false;
    }

    // Compare to a rudimental list of sections
    static std::string types[] = { "RESOLUTION", "RENDERER" };

    for (int i = 0; i < sizeof(types); i++)
    {
        if (sectionName == types[i])
        {
            m_currentSectionType = (IniSectionType)(i + 1);
            return true;
        }
    }

    return false;
}

void IniReader::ParseKeyValue(char *line)
{
    KeyValueProperties keyValue(line);
    if (!keyValue.GetValues().size()) { return; };

    auto& values = keyValue.GetValues().at(0);
    auto& key = values.key;
    auto& val = values.value;

    switch (m_currentSectionType)
    {
        case UNKNOWN:
        {
            break;
        }
        case RESOLUTION:
        {
            if (key == "width")
            {
                m_engineSetup.resolution.width = std::stoi(val);
            }
            else if (key == "height")
            {
                m_engineSetup.resolution.height = std::stoi(val);
            }

            break;
        }
        case RENDER_CLR_COLOR:
        {
            if (key == "clear_color")
            {
                sscanf(val.c_str(), "%f,%f,%f,%f",
                       &m_engineSetup.backgroundColor.r,
                       &m_engineSetup.backgroundColor.g,
                       &m_engineSetup.backgroundColor.b,
                       &m_engineSetup.backgroundColor.a);
            }
            break;
        }
    }
}

std::string GetSectionName(char *srcLine)
{
    static std::string types[] = { "RESOLUTION" };
    std::string line(srcLine);
    trim(line);

    if (line[0] == '[' && line.at(line.size()-1) == ']')
    {
        return line.substr(1, line.size()-2);
    }

    return "";
}
