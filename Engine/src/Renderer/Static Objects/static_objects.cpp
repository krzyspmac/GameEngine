//
//  static_objects.cpp
//  Engine-Mac
//
//  Created by krzysp on 31/07/2022.
//

#include "static_objects.hpp"

using namespace engine;

// static values

static StaticMgr<EngineI> *static_engine = nullptr;

void StaticObjects::init()
{
    if (static_engine == nullptr)
    {   static_engine = new StaticMgr<EngineI>();
    }
}

EngineI &StaticObjects::engine()
{
    return *static_engine->get();
}

void StaticObjects::engine_provide(EngineI* value)
{
    static_engine->set(value);
}
