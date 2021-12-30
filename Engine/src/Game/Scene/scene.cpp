//
//  scene.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "scene.hpp"

using namespace engine;

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::RenderScene()
{

}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(Scene);

std::vector<luaL_Reg> Scene::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
    });
    return result;
}
