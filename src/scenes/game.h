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

#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include <memory>
#include <vector>

#include "scene.h"
#include "mainmenu.h"
#include "../gameobjects/graphics/sprite.h"

class Game : public Scene {

public:

    Game();

    ~Game();

    virtual void Render() override;

    virtual void Update(ALLEGRO_EVENT *event) override;

    typedef enum {
        Playing,
        Conclusion
    } State;

protected:

    static int _Score[2];

    void HandleTurn(char letter);

    std::vector<std::shared_ptr<Button>> Alphabet;
    std::string _TheWord, _DisplayWord;
    Sprite* _Hangman;
    Sprite* _HangmanCLONE1;
    Sprite* _HangmanCLONE2;


    unsigned int _ErrorCount;
    bool _Won;

    Button *btn_Continue, *btn_Quit;
    State _State;
};


#endif // HANGMAN_GAME_H
