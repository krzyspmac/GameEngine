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

#ifndef sprite_atlas_manager_interface_h
#define sprite_atlas_manager_interface_h

#include "sprite_atlas_interface.h"

namespace engine
{
    /** SpriteAtlasManagerI
        \addtogroup API_GLOBALS

        A manager for sprite atlas files. Loads the textures, keeps them for
        future reference.
     */
    class SpriteAtlasManagerI
    {
    public:
        /**
         Loads sprite atlas, its texture and the json
         file for individual sprite splices.
        */
        virtual SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename) = 0;

        /**
         Gets the specific atlas item using the name provided.
        */
        virtual SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename) = 0;

        /**
        */
        virtual void SpriteAtlasUnload(SpriteAtlasI *atlas) = 0;

        /**
        */
        virtual void SpriteAtlasDisposeAll() = 0;
    };
};

#endif /* sprite_atlas_manager_interface_h */
