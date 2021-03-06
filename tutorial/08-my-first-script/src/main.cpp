/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/Minko.hpp"
#include "minko/MinkoSDL.hpp"
#include "minko/MinkoLua.hpp"

using namespace minko;
using namespace minko::math;
using namespace minko::component;

const uint WINDOW_WIDTH = 800;
const uint WINDOW_HEIGHT = 600;

int
main(int argc, char** argv)
{
    auto canvas = Canvas::create("Minko Tutorial - My first script", WINDOW_WIDTH, WINDOW_HEIGHT);
    auto sceneManager = component::SceneManager::create(canvas);
    auto root = scene::Node::create("root")->addComponent(sceneManager);

    // initialization of Lua context
    LuaContext::initialize(argc, argv, root, canvas);

    // add a LuaScriptManager to the root node
    root->addComponent(LuaScriptManager::create());

    sceneManager->assets()->loader()->options()->registerParser<file::LuaScriptParser>("lua");
    sceneManager->assets()->loader()->queue("script/my_script.lua");

    auto complete = sceneManager->assets()->loader()->complete()->connect([&](file::Loader::Ptr loader)
    {
		root->addComponent(sceneManager->assets()->script("script/my_script.lua"));

        auto numFrames = 0;
        auto enterFrame = canvas->enterFrame()->connect([&](Canvas::Ptr canvas, float t, float dt)
        {
            ++numFrames;
            if (numFrames == 5)
                root->removeComponent(sceneManager->assets()->script("script/my_script.lua"));

            sceneManager->nextFrame(t, dt);
        });

        canvas->run();
    });

    // actually begin loading operations
    sceneManager->assets()->loader()->load();

    return 0;
}