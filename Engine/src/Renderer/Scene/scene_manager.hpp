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

#ifndef scene_manager_hpp
#define scene_manager_hpp

#include "scene_interface.h"
#include "scene_manager_interface.h"

namespace engine
{
    class SceneManager: public SceneManagerI
    {
    public:
        SceneManager()
        :   m_current(nullptr)
        { };

    public: // SceneManagerI
        SceneI* SceneCreateNew();
        SceneI* SceneGetCurrent();
        void SceneUnload(SceneI*);
        void SceneMakeActive(SceneI*);

    private:
        std::vector<std::unique_ptr<SceneI>>::iterator GetFor(SceneI*);

    private:
        std::vector<std::unique_ptr<SceneI>> m_scenes;
        SceneI* m_current;
    };
};

#endif /* scene_manager_hpp */
