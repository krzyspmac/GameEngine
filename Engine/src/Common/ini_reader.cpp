//
//  ini_reader.cpp
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#include "ini_reader.hpp"
#include "key_value.hpp"
#include "system_utils.hpp"
#include <stdio.h>

using namespace engine;

static std::string GetSectionName(std::string &srcLine);
static VirtualGamepadConfiguration GetVirtualGamepadButtonType(std::string &name);

IniReader::IniReader(std::string path)
    : m_currentSectionType(UNKNOWN)
{
    const char *cPath = path.c_str();
    FILE *fp = fopen(cPath, "r");
    if (fp)
    {
        // Update any defaults first
        ProcessDefaults();

        // Process the file
        ProcessFile(fp);

        fclose(fp);
    }
    else
    {
        throw "No .ini file found!";
    }
}

void IniReader::ProcessDefaults()
{
    m_engineSetup.gameFolder = IniReader::Variables::rpath();
}

void IniReader::ProcessFile(FILE *fp)
{
    char * _line = NULL;
    size_t _len = 0;
    ssize_t _read;

    while ((_read = getline(&_line, &_len, fp)) != -1)
    {
        if (strlen(_line) < 1) { continue; };

        std::string lineCut = std::string(_line);
        auto commentPos = lineCut.find(";");
        if (commentPos != std::string::npos)
        {
            lineCut = lineCut.substr(0, commentPos);
            trim(lineCut);
            lineCut += "\n";
        }

        if (UpdateSection(lineCut))
        {
            continue;
        }
        else
        {
            ParseKeyValue(lineCut);
        }

        printf("IniReader: %s\n", lineCut.c_str());
    }
}

EngineSetup IniReader::GetSetup()
{
    return m_engineSetup;
}

bool IniReader::UpdateSection(std::string &srcLine)
{
    // Get the section name if possible
    std::string sectionName = GetSectionName(srcLine);

    if (sectionName.empty())
    {
        return false;
    }

    // Compare to a rudimental list of sections
    static std::string types[] = { "RESOLUTION", "RENDERER", "INPUT", "PHONE" };

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

void IniReader::ParseKeyValue(std::string &line)
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
        case RENDERER:
        {
            if (key == "clear_color")
            {
                sscanf(val.c_str(), "%f,%f,%f,%f",
                       &m_engineSetup.backgroundColor.r,
                       &m_engineSetup.backgroundColor.g,
                       &m_engineSetup.backgroundColor.b,
                       &m_engineSetup.backgroundColor.a);
            }
            else if (key == "game_folder")
            {
                m_engineSetup.gameFolder = val;
            }
            break;
        }
        case INPUT:
        {
            if (key == "gamepad_support")
            {
                m_engineSetup.gamepad_support = val == "true";
            }
            else if (key == "gamepad_virtual_support")
            {
                m_engineSetup.gamepad_virtual_support = val == "true";
            }
            else if (key == "gamepad_virtual_buttons")
            {
                size_t configuration = GamepadConfiguration_Unknown;

                auto components = split_components(val, "|");
                for (auto it = components.begin(); it != components.end(); ++it)
                {
                    VirtualGamepadConfiguration type = GetVirtualGamepadButtonType(*it);
                    if (type != GamepadConfiguration_Unknown)
                    {
                        configuration |= (size_t)type;
                    }
                }

                m_engineSetup.gamepad_virtual_configuration = (VirtualGamepadConfiguration)configuration;
            }
            break;
        }
        case PHONE:
        {
            if (key == "orientation")
            {
                // TODO:
            }
            break;
        }
    }
}

VirtualGamepadConfiguration GetVirtualGamepadButtonType(std::string &name)
{
    auto *types = VirtualGameConfigurationButtonMapping::shared();
    for (auto it = types->begin(); it != types->end(); ++it)
    {
        if (it->name == name)
        {
            return it->mapping;
        }
    }

    return GamepadConfiguration_Unknown;
}


std::string GetSectionName(std::string &srcLine)
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
