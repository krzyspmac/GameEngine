//
//  console_lights.cpp
//  Engine
//
//  Created by krzysp on 06/02/2022.
//

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

    auto& lightManager = GetMainEngine()->getLightMnaager();
    bool isDirty = false;

    ImGui::Checkbox("Lights Enabled", &lightManager.GetLightActive());
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
                        isDirty = true;
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
                        isDirty = true;
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
                        isDirty = true;
                    }
                };

                // Ambient intensity
                {
                    float ambientIntensity = light->GetAmbientIntensity();
                    ImGui::DragFloat("Ambient Intensity", &ambientIntensity, 0.005f, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);

                    if (ambientIntensity != light->GetAmbientIntensity())
                    {
                        light->SetAmbientIntensity(ambientIntensity);
                        isDirty = true;
                    }
                };

                // Diffuse intensity
                {
                    float diffuseIntensity = light->GetDiffuseIntensity();
                    ImGui::DragFloat("Diffuse Intensity", &diffuseIntensity, 0.005f, 0.0f, 300.0f, "%.3f", ImGuiSliderFlags_None);

                    if (diffuseIntensity != light->GetDiffuseIntensity())
                    {
                        light->SetDiffuseIntensity(diffuseIntensity);
                        isDirty = true;
                    }
                };

                // Diffuse size
                {
                    float diffuseSize = light->GetDiffuseSize();
                    ImGui::DragFloat("Diffuse Size", &diffuseSize, 1.f, 0.0f, std::numeric_limits<float>::max(), "%.3f", ImGuiSliderFlags_None);

                    if (diffuseSize != light->GetDiffuseSize())
                    {
                        light->SetDiffuseSize(diffuseSize);
                        isDirty = true;
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
                        isDirty = true;
                    }
                }

                ImGui::TreePop();
            }
            ++i;
        }
        ImGui::TreePop();

        if (isDirty)
        {
            lightManager.UpdateCache();
        }
    }

    ImGui::End();
}
