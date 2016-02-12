#include "game.h"

Game::Game() : _ErrorCount(0) {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 45, "league");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 125, "league-fancy");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "league-credits");
    ASSET_MANAGER.LoadDict("res/data/words.txt", "words");
    ASSET_MANAGER.LoadImage("res/animations/AddHead.png", "head");
    ASSET_MANAGER.LoadImage("res/animations/AddTorso.png", "torso");
    ASSET_MANAGER.LoadImage("res/animations/AddRArm.png", "right-arm");
    ASSET_MANAGER.LoadImage("res/animations/AddLArm.png", "left-arm");
    ASSET_MANAGER.LoadImage("res/animations/AddRLeg.png", "right-leg");
    ASSET_MANAGER.LoadImage("res/animations/AddLLeg.png", "left-leg");
    ASSET_MANAGER.LoadImage("res/animations/Death.png", "death");

    _Hangman = new Sprite(ASSET_MANAGER.GetImage("head"), 8, 8);

    float x = 125;
    for (unsigned char c = 'A'; c <= 'Z'; ++c) {
        Alphabet.push_back(std::make_shared<Button>(
                std::string(1, c), ASSET_MANAGER.GetFont("league"), x, c <= 'M' ? 500 : 550, []() -> void { }));
        x = x < 725 ? x + 50 : 125;
    }

    for (unsigned long i = 0; i < Alphabet.size(); i++) {
        Alphabet.at(i)->SetHandler([this, i]() -> void {
            Alphabet.at(i)->Enabled = false;
            HandleTurn((Alphabet.at(i)->GetText().c_str())[0]);
        });
    }
    _TheWord = ASSET_MANAGER.GetDict("words").at(rand() % ASSET_MANAGER.GetDict("words").size());
    for (unsigned long i = 0; i < _TheWord.size(); i++) _DisplayWord += _TheWord.at(i) == ' ' ? " " : "_";
}

Game::~Game() {
    ASSET_MANAGER.DiscardFont("cubic");
    ASSET_MANAGER.DiscardFont("league");
    ASSET_MANAGER.DiscardDict("res/data/words.txt");
}

void Game::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 255, 255),
                 ASSET_MANAGER.SCREEN_W - 5, ASSET_MANAGER.SCREEN_H - 30,
                 ALLEGRO_ALIGN_RIGHT, "by Thomas Steinholz");

    al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                 ASSET_MANAGER.SCREEN_W / 2, 400,
                 ALLEGRO_ALIGN_CENTER, _DisplayWord.c_str());

    for (auto x : Alphabet) x->Render();
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 075, 470, ALLEGRO_ALIGN_CENTER, "{");
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 775, 470, ALLEGRO_ALIGN_CENTER, "}");

    _Hangman->Render();

#ifdef DEBUG //==DEBUG================================================================================================//

    al_draw_text(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 0, 255), 25, 15,
                 ALLEGRO_ALIGN_LEFT, "Debug Mode");

    al_draw_textf(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 0, 255), 25, 50,
                  ALLEGRO_ALIGN_LEFT, "WORD : %s", _TheWord.c_str());

    al_draw_textf(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 0, 255), 25, 75,
                  ALLEGRO_ALIGN_LEFT, "ERROR COUNT: %i", _ErrorCount);

    al_draw_rectangle(ASSET_MANAGER.SCREEN_W / 2, ASSET_MANAGER.SCREEN_H / 2,
                      ASSET_MANAGER.SCREEN_W / 2, ASSET_MANAGER.SCREEN_H / 2, al_map_rgb(255, 0, 255), 3);


#endif //=============================================================================================================//
}

void Game::Update(ALLEGRO_EVENT *event) {
    for (unsigned long i = 0; i < Alphabet.size(); i++) {
        Alphabet.at(i)->Update(event);
    }
    _Hangman->Update(event);
}

void Game::HandleTurn(char letter) {
    if (_TheWord.find(letter) != std::string::npos) {
        for (unsigned long i = 0; i < _TheWord.size(); i++) {
            if (_DisplayWord.at(i) == '_' && _TheWord.at(i) == letter)
                std::replace(_DisplayWord.begin() + i, _DisplayWord.begin() + i + 1, '_', letter);
        }
    } else {
        _ErrorCount++;

        switch (_ErrorCount) {
            case 1: break;
            case 2: _Hangman->SetImage(ASSET_MANAGER.GetImage("torso"), 8, 8); break;
            case 3: _Hangman->SetImage(ASSET_MANAGER.GetImage("right-arm"), 8, 8); break;
            case 4: _Hangman->SetImage(ASSET_MANAGER.GetImage("left-arm"), 8, 8); break;
            case 5: _Hangman->SetImage(ASSET_MANAGER.GetImage("right-leg"), 8, 8); break;
            case 6: _Hangman->SetImage(ASSET_MANAGER.GetImage("left-leg"), 8, 8); break;
            case 7: _Hangman->SetImage(ASSET_MANAGER.GetImage("death"), 8, 8); break;
            default: break;
        }

        if (_ErrorCount <= 3) _Hangman->Play((ASSET_MANAGER.SCREEN_W / 2) - 40, 132, false);
        else _Hangman->Play((ASSET_MANAGER.SCREEN_W / 2) - 64, 132, false);

        if (_ErrorCount == 7) {
            Scene::SetScene(new MainMenu());
        }
    }
}
