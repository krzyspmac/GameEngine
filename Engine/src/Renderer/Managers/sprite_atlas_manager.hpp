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

#ifndef sprite_atlas_manager_hpp
#define sprite_atlas_manager_hpp

#include "sprite_atlas_interface.h"
#include "sprite_atlas_manager_interface.h"

namespace engine
{
    class SpriteAtlasManager: public SpriteAtlasManagerI
    {
    public: // SpriteAtlasManagerI
        SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename);
        
        SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename);

        void SpriteAtlasUnload(SpriteAtlasI *atlas);

        void SpriteAtlasDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteAtlasI>> m_atlas;
    };
};

#endif /* sprite_atlas_manager_hpp */
