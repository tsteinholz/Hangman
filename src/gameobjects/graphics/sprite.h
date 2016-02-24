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

#ifndef HANGMAN_SPRITE_H
#define HANGMAN_SPRITE_H

#include "../gameobject.h"

//-----------------------------------------------------------------------------
// Purpose: Displays a sprite animation
//-----------------------------------------------------------------------------
class Sprite : public GameObject {
public:
    Sprite(ALLEGRO_BITMAP* image, unsigned int columns, unsigned int rows);

    virtual ~Sprite();

    //-----------------------------------------------------------------------------
    // Purpose: Play the animation
    //
    // param x: The horizontal coordinate to render the animation
    // param y: The vertical coordinate to render the animation
    // param loop: if the animation will loop or not
    //-----------------------------------------------------------------------------
    void Play(float x, float y, bool loop);

    //-----------------------------------------------------------------------------
    // Purpose: Set a new image to animate
    //-----------------------------------------------------------------------------
    void SetImage(ALLEGRO_BITMAP* image, unsigned int columns, unsigned int rows);

    //-----------------------------------------------------------------------------
    // Purpose: Stops playing the animation
    //-----------------------------------------------------------------------------
    void Stop();

    virtual void Render();

    virtual void Update(ALLEGRO_EVENT *event);

    float _X, _Y;

protected:
    ALLEGRO_BITMAP* _Image;
    int _SpriteX, _SpriteY;
    unsigned int _Columns, _Rows;
    bool _Loop, _Playing;
private:
};

#endif // HANGMAN_SPRITE_H
