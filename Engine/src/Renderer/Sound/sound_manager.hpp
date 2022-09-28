//
//  sound_manager.hpp
//  Engine
//
//  Created by krzysp on 09/06/2022.
//

#ifndef sound_manager_hpp
#define sound_manager_hpp

#include "common.h"
#include "sound_interfaces.h"

namespace engine
{
    /**
     SoundManager
     \addtogroup API_GLOBALS
     */
    /**
     Manages the scene's sound files.
     */
    class SoundManager: public SoundManagerI
    {
        std::vector<std::unique_ptr<SoundFileI>> m_items;
    public: // SoundManagerI
        /** @private */
        SoundManager();

        /** Loads a sound file located within the game's data folder. */
        SoundFileI* Load(std::string);

        /** Loads a selected sound file. Do not reference it again. */
        void Unload(SoundFileI*);
    };
};

#endif /* sound_manager_hpp */
