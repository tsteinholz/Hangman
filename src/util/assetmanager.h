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

#ifndef HANGMAN_ASSETMANAGER_H
#define HANGMAN_ASSETMANAGER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <cstdio>
#include <map>
#include <fstream>
#include <memory>
#include <vector>

#define ASSET_MANAGER AssetManager::GetAssetManager()

//-----------------------------------------------------------------------------
// Purpose: A singleton class that manages all the assets in the game
//-----------------------------------------------------------------------------
class AssetManager {

public:

    //-----------------------------------------------------------------------------
    // Purpose: This function returns the singleton instance of this class
    //-----------------------------------------------------------------------------
    static AssetManager &GetAssetManager();

    //-----------------------------------------------------------------------------
    // Purpose: Load a new image for the game to use. This function will store an
    //          instance of the asset in memory (in a hash map corresponding with
    //          the data type provided.
    //
    // param file: The location on disk of the asset
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static bool LoadImage(const char *file, const char *key = "");

    //-----------------------------------------------------------------------------
    // Purpose: Load a new sound for the game to use. This function will store an
    //          instance of the asset in memory (in a hash map corresponding with
    //          the data type provided.
    //
    // param file: The location on disk of the asset
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static bool LoadSound(const char *file, const char *key = "");

    //-----------------------------------------------------------------------------
    // Purpose: Load a new font for the game to use. This function will store an
    //          instance of the asset in memory (in a hash map corresponding with
    //          the data type provided.
    //
    // param file: The location on disk of the asset
    // param size: The font size you need
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static bool LoadFont(const char *file, unsigned int size, const char *key = "");

    //-----------------------------------------------------------------------------
    // Purpose: Load some text for the game to use. This function will store an
    //          instance of the asset in memory (in a hash map corresponding with
    //          the data type provided.
    //
    // param file: The location on disk of the asset
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static bool LoadText(const char *file, const char *key = "");

    //-----------------------------------------------------------------------------
    // Purpose: Load some dict for the game to use. This function will store an
    //          instance of the asset in memory (in a hash map corresponding with
    //          the data type provided.
    //
    // param file: The location on disk of the asset
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static void LoadDict(const char *file, const char *key = "");

    //-----------------------------------------------------------------------------
    // Purpose: Destroys an asset that is presumably no longer needed by the game.
    //          This function is good for performance so that you don't use more
    //          RAM than you need to.
    //
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static void DiscardImage(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Destroys an asset that is presumably no longer needed by the game.
    //          This function is good for performance so that you don't use more
    //          RAM than you need to.
    //
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static void DiscardSound(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Destroys an asset that is presumably no longer needed by the game.
    //          This function is good for performance so that you don't use more
    //          RAM than you need to.
    //
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static void DiscardFont(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Destroys an asset that is presumably no longer needed by the game.
    //          This function is good for performance so that you don't use more
    //          RAM than you need to.
    //
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static void DiscardText(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Destroys an asset that is presumably no longer needed by the game.
    //          This function is good for performance so that you don't use more
    //          RAM than you need to.
    //
    // param key: The string you use to receive this asset (defaults to the path str)
    //-----------------------------------------------------------------------------
    static void DiscardDict(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Returns the image
    //
    // param key: The string used to store the asset in memory
    //-----------------------------------------------------------------------------
    static ALLEGRO_BITMAP *GetImage(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Returns the sound
    //
    // param key: The string used to store the asset in memory
    //-----------------------------------------------------------------------------
    static ALLEGRO_SAMPLE *GetSound(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Returns the font
    //
    // param key: The string used to store the asset in memory
    //-----------------------------------------------------------------------------
    static ALLEGRO_FONT *GetFont(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Returns the text
    //
    // param key: The string used to store the asset in memory
    //-----------------------------------------------------------------------------
    static const char *GetText(const char *key);

    //-----------------------------------------------------------------------------
    // Purpose: Returns the dict
    //
    // param key: The string used to store the asset in memory
    //-----------------------------------------------------------------------------
    static std::vector<std::string> GetDict(const char *key);

    const unsigned int SCREEN_W = 850, SCREEN_H = 650;

private:

    AssetManager();

    virtual ~AssetManager();

    static std::map<const char *, std::shared_ptr<ALLEGRO_BITMAP>> _ImageMap;
    static std::map<const char *, std::shared_ptr<ALLEGRO_SAMPLE>> _SoundMap;
    static std::map<const char *, std::shared_ptr<ALLEGRO_FONT>> _FontMap;
    static std::map<const char *, const char *> _TextMap;
    static std::map<const char *, std::vector<std::string>> _DictMap;

};


#endif //HANGMAN_ASSETMANAGER_H
