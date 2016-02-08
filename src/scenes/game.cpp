#include "game.h"

Game::Game() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 45, "league");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 125, "league-fancy");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "league-credits");
    ASSET_MANAGER.LoadDict("res/data/words.txt", "words");

    for (char c = 'A'; c <= 'Z'; ++c) {
        std::string x = ""; x += c;
        Alphabet.push_back(std::make_shared<Button>(x.c_str(), ASSET_MANAGER.GetFont("league"), 125, 500,
                                     [] () -> void {  }));
    }

    _TheWord = ASSET_MANAGER.GetDict("words").at(rand() % ASSET_MANAGER.GetDict("words").size());
    for (int i = 0; i < _TheWord.size(); i++) _DisplayWord += "_";
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
//  -DEBUG
    al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 0, 255),
                 100, ASSET_MANAGER.SCREEN_H / 2,
                 ALLEGRO_ALIGN_CENTER, _TheWord.c_str());
    al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                 ASSET_MANAGER.SCREEN_W / 2, 400,
                 ALLEGRO_ALIGN_CENTER, _DisplayWord.c_str());


    for (auto x : Alphabet) x->Render();
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 75, 470, ALLEGRO_ALIGN_CENTER, "{");
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 775, 470, ALLEGRO_ALIGN_CENTER, "}");
}

void Game::Update(ALLEGRO_EVENT *event) {
    for (unsigned long i = 0; i < Alphabet.size(); i++) {
        Alphabet.at(i)->Update(event);
        /*
        if (Alphabet.at(i)->Pressed) {
            Alphabet.at(i)->Enabled = false;
            switch (i) {
                case 0:  HandleTurn('A'); break;
                case 1:  HandleTurn('B'); break;
                case 2:  HandleTurn('C'); break;
                case 3:  HandleTurn('D'); break;
                case 4:  HandleTurn('E'); break;
                case 5:  HandleTurn('F'); break;
                case 6:  HandleTurn('G'); break;
                case 7:  HandleTurn('H'); break;
                case 8:  HandleTurn('I'); break;
                case 9:  HandleTurn('J'); break;
                case 10: HandleTurn('K'); break;
                case 11: HandleTurn('L'); break;
                case 12: HandleTurn('M'); break;
                case 13: HandleTurn('N'); break;
                case 14: HandleTurn('O'); break;
                case 15: HandleTurn('P'); break;
                case 16: HandleTurn('Q'); break;
                case 17: HandleTurn('R'); break;
                case 18: HandleTurn('S'); break;
                case 19: HandleTurn('T'); break;
                case 20: HandleTurn('U'); break;
                case 21: HandleTurn('V'); break;
                case 22: HandleTurn('W'); break;
                case 23: HandleTurn('X'); break;
                case 24: HandleTurn('Y'); break;
                case 25: HandleTurn('Z'); break;
                default: break;
            }
        }
        */
    }
}

void Game::HandleTurn(char letter) {
    if (_TheWord.find(letter) != std::string::npos) {
        for (unsigned long i = 0; i < _TheWord.size(); i++) {
            if (_DisplayWord.at(i) == '_' && _TheWord.at(i) == letter)
                 std::replace(_DisplayWord.begin() + i, _DisplayWord.begin() + i + 1, '_', letter);
        }
    } else {
        // TODO : Add body part [track error count]
        // TODO : Check if the player can move on [baed on error count]
    }
}
