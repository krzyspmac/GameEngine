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

#include "console_lights.hpp"
#include "imgui.h"
#include "engine.hpp"

using namespace engine;

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

ConsoleLightManagement::ConsoleLightManagement()
    : p_open(false)
{
}

void ConsoleLightManagement::ToggleVisibility()
{
    p_open = !p_open;
}

void ConsoleLightManagement::Render()
{
    if (!p_open) { return; };

    ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
    if (!ImGui::Begin("Light Manager", &p_open))
    {
        ImGui::End();
        return;
    }

    auto& lightManager = ENGINE().getLightMnaager();

    ImGui::Checkbox("Lights Enabled", &lightManager.GetLightsActive());
    ImGui::Separator();

    if (ImGui::TreeNode("Lights List"))
    {
        // Loop through all the lights and present their attributes
        int i = 0;
        for (auto& lightPtr : lightManager.GetLights() )
        {
            // The light item
            auto* light = lightPtr.get();

            // This light's attributes
            auto& name = light->GetName();
            bool isEnabled = light->GetIsEnabled();

            if (ImGui::TreeNode((void*)(intptr_t)i, name.empty() ? "Light %d" : name.c_str(), i))
            {
                // Enabled
                {
                    ImGui::Checkbox("Enabled", &isEnabled);
                    ImGui::Spacing();

                    // Update on changes
                    if (isEnabled != light->GetIsEnabled())
                    {
                        light->SetIsEnabled(isEnabled);
                    }
                };

                // Type
                {
                    auto selectedType = light->GetType();
                    auto& lightTypesDesc = LightI::LIGHT_TYPES();
                    auto* selectedDesc = matching<LightInfo>(lightTypesDesc, [&](LightInfo& info){
                        return info.type == selectedType;
                    });

                    auto comboSelectedType = selectedDesc != nullptr ? selectedDesc->type : LIGHT_FALLOUT_TYPE_LINEAR;
                    std::string combomSelectedName = selectedDesc != nullptr ? selectedDesc->name : "[unknown]";

                    if (ImGui::BeginCombo("Falloff Type", combomSelectedName.c_str(), 0))
                    {
                        for (auto& descriptor : lightTypesDesc)
                        {
                            const bool is_selected = light->GetType() == descriptor.type;
                            if (ImGui::Selectable(descriptor.name.c_str(), is_selected))
                            {   comboSelectedType = descriptor.type;
                            }
                            if (is_selected)
                            {   ImGui::SetItemDefaultFocus();
                            }

                        }
                        ImGui::EndCombo();
                    }

                    if (comboSelectedType != selectedType)
                    {   light->SetType(comboSelectedType);
                    };
                };

                // Ambient color
                {
                    Color3 ambientColor = light->GetColor();

                    ImVec4 color = ImVec4(ambientColor.r, ambientColor.g, ambientColor.b, 1.f);
                    ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoOptions;

                    ImGui::ColorEdit3("AmbientColor", (float*)&color, misc_flags);
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    // Update on changes
                    if (color.x != ambientColor.r || color.y != ambientColor.b || color.z != ambientColor.b)
                    {
                        light->SetColor({color.x, color.y, color.z});
                    }
                };

                // Ambient intensity
                {
                    float ambientIntensity = light->GetAmbientIntensity();
                    ImGui::DragFloat("Ambient Intensity", &ambientIntensity, 0.005f, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);

                    if (ambientIntensity != light->GetAmbientIntensity())
                    {
                        light->SetAmbientIntensity(ambientIntensity);
                    }
                };

                // Diffuse intensity
                {
                    float diffuseIntensity = light->GetDiffuseIntensity();
                    ImGui::DragFloat("Diffuse Intensity", &diffuseIntensity, 0.005f, 0.0f, 300.0f, "%.3f", ImGuiSliderFlags_None);

                    if (diffuseIntensity != light->GetDiffuseIntensity())
                    {
                        light->SetDiffuseIntensity(diffuseIntensity);
                    }
                };

                // Diffuse size
                {
                    float diffuseSize = light->GetDiffuseSize();
                    ImGui::DragFloat("Diffuse Size", &diffuseSize, 1.f, 0.0f, std::numeric_limits<float>::max(), "%.3f", ImGuiSliderFlags_None);

                    if (diffuseSize != light->GetDiffuseSize())
                    {
                        light->SetDiffuseSize(diffuseSize);
                    }
                };

                // Position
                {
                    Origin position = light->GetPosition();

                    float x = static_cast<float>(position.x);
                    float y = static_cast<float>(position.y);

                    ImGui::DragFloat("x", &x, 1.f, 0.0f, std::numeric_limits<float>::max(), "%1.0f", ImGuiSliderFlags_None);
                    ImGui::DragFloat("y", &y, 1.f, 0.0f, std::numeric_limits<float>::max(), "%1.0f", ImGuiSliderFlags_None);

                    if (x != position.x || y != position.y)
                    {
                        light->SetPosition({ (int)x, (int)y });
                    }
                }

                ImGui::TreePop();
            }
            ++i;
        }
        ImGui::TreePop();
    }

    ImGui::End();
}
