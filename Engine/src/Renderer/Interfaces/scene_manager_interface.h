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

#ifndef scene_manager_interface_h
#define scene_manager_interface_h

#include "scene_interface.h"

namespace engine
{
    /** SceneManagerI
        \addtogroup API_GLOBALS

        Manages the scene. Only the current screen renders its resources on-screen.
        Note that scene management does not impact game input handling nor any other
        non-scene related event observers.
     */
    class SceneManagerI
    {
    public:

        /** Creates a new scene. Removes the old one and removes it data. */
        virtual SceneI* SceneCreateNew() = 0;

        /** Get the current scene */
        virtual SceneI* SceneGetCurrent() = 0;

        /** Unload the current scene. */
        virtual void SceneUnload(SceneI*) = 0;

        /** Make active. */
        virtual void SceneMakeActive(SceneI*) = 0;
    };
};

#endif /* scene_manager_interface_h */
