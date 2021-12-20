//
//  engine.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_hpp
#define engine_hpp

#import "common.h"
#import "engine_interface.h"
#import "engine_provider_interface.h"
#import "file_access_provider.h"
#import "scripting_engine_provider_interface.h"

namespace engine
{
    class Engine: public EngineI
    {
    public:
        ///
        Engine(EngineProviderI &engine, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine);

        void update();

        ///
        EngineProviderI& getProvider() { return m_engineProvider; };

        ///
        FileAccessI& getFileAccess() { return m_fileAccess; };
    private:
        EngineProviderI &m_engineProvider;
        FileAccessI &m_fileAccess;
        ScriptingEngineI &m_scriptingEngine;
    };
}

#endif /* engine_hpp */
