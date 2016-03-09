//-----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Thomas Steinholz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef HANGMAN_SCENE_H
#define HANGMAN_SCENE_H

#include "../util/assetmanager.h"
#include "../gameobjects/ui/button.h"

//-----------------------------------------------------------------------------
// Purpose: Represents and area in the game such as the main game, the menu or
//          just simply the credits. Works as a way to organize all of the
//          different types of screens you need in a game.
//-----------------------------------------------------------------------------
class Scene {

public:

    virtual ~Scene() { }

    //-----------------------------------------------------------------------------
    // Purpose: What-ever scene is in this variable will get handled
    //-----------------------------------------------------------------------------
    static Scene *Current;

    //-----------------------------------------------------------------------------
    // Purpose: The best way to change scene giving the scene parent class the
    //          over-watch
    //-----------------------------------------------------------------------------
    static inline void SetScene(Scene *scene) {
//        ASSET_MANAGER.DiscardAll(); // TODO : Fix asset manager
        ASSET_MANAGER.PrintCurrentData();
        delete Current;
        Current = scene;
    }

    //-----------------------------------------------------------------------------
    // Purpose: Returns the value of the executing variable since it can't be
    //          read outside of this class since it is static
    //-----------------------------------------------------------------------------
    static inline bool GetExe() {
        return Executing;
    }

    //-----------------------------------------------------------------------------
    // Purpose: Sets the value of the executing variable since outside classes cant
    //          access this variable directly
    //-----------------------------------------------------------------------------
    static inline void SetExe(bool x) {
        Executing = x;
    }

    //-----------------------------------------------------------------------------
    // Purpose: Render the scene
    //-----------------------------------------------------------------------------
    virtual void Render() = 0;

    //-----------------------------------------------------------------------------
    // Purpose: Update the scene
    //-----------------------------------------------------------------------------
    virtual void Update(ALLEGRO_EVENT *event) = 0;

protected:

    // TODO: Fix
    //virtual ~Scene() { printf("Destroyed Scene"); }

    //-----------------------------------------------------------------------------
    // Purpose: If the game is executing or not
    //-----------------------------------------------------------------------------
    static bool Executing;
};

#endif //HANGMAN_SCENE_H
