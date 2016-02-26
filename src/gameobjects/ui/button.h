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

#ifndef HANGMAN_BUTTON_H
#define HANGMAN_BUTTON_H

#include "../gameobject.h"

//-----------------------------------------------------------------------------
// Purpose: Represents a button for the user interface
//-----------------------------------------------------------------------------
class Button : public GameObject {

public:

    Button(std::string text, ALLEGRO_FONT *font, float x, float y, const std::function <void()> f);

    virtual ~Button();

    bool Pressed, Hover, Enabled;

    virtual void Render();

    virtual void Update(ALLEGRO_EVENT *event);

    void SetHandler(const std::function <void()> f);

    std::string GetText();

    //-----------------------------------------------------------------------------
    // Purpose: Default Color Theme for Buttons
    //-----------------------------------------------------------------------------
    ALLEGRO_COLOR ENABLED_COLOR = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR DISABLED_COLOR = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR HOVER_COLOR = al_map_rgb(119, 144, 232);
    ALLEGRO_COLOR CLICKED_COLOR = al_map_rgb(0, 0, 255); // TODO
    ALLEGRO_COLOR DEBUG_COLOR = al_map_rgb(255, 0, 255);

protected:
    std::string _Text;
    ALLEGRO_FONT *_Font;
    float _X, _Y;
    std::function <void()>_HandleFunction;
};

#endif //HANGMAN_BUTTON_H
