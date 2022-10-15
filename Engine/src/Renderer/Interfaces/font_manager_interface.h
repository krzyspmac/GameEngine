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

#ifndef font_manager_interface_h
#define font_manager_interface_h

#include "font_interface.h"

namespace engine
{
    /** FontManagerI
        \addtogroup API_GLOBALS

        Keps a list of all fonts including memory handling of those.
     */
    class FontManagerI
    {
    public:
        /** Load a specified fitmap font by providing the name of the .fnt file and the texture.
            If the font was previously loaded, uses the GetFont function instead. Otherwise loads new.
         */
        virtual FontI *LoadFont(std::string fntFilename, std::string fontTexture) = 0;

        /** Get a cached version of the font.
            @private
         */
        virtual FontI *GetFont(std::string name) = 0;

        /** Unload all fonts. Be sure that you're no longer using them.
         */
        virtual void DisposeAllFonts() = 0;
    };
}

#endif /* font_manager_interface_h */
