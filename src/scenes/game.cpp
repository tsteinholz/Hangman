#include "game.h"

int Game::_Score[2] = {0, 0};

Game::Game() :
    _ErrorCount(0),
    _Won(false),
    _State(Playing)
    {

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
    ASSET_MANAGER.LoadSound("res/sound/zipclick.ogg", "gui-click");
    ASSET_MANAGER.LoadSound("res/sound/spring.ogg", "spring");
    ASSET_MANAGER.LoadSound("res/sound/stab.ogg", "stab");

    _Hangman = new Sprite(ASSET_MANAGER.GetImage("head"), 8, 8);
    _HangmanCLONE1 = new Sprite(ASSET_MANAGER.GetImage("death"), 8, 8);
    _HangmanCLONE2 = new Sprite(ASSET_MANAGER.GetImage("death"), 8, 8);

    btn_Continue = new Button("Continue", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W-300, 525, [this]() -> void {
        al_stop_samples();
        al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        SetScene(new Game());
    });
    btn_Quit = new Button("Quit", ASSET_MANAGER.GetFont("league"), 300, 525, [this]() -> void {
        al_stop_samples();
        al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        SetScene(new MainMenu());
    });

    float x = 125, i = 0;
    for (unsigned char c = 'A'; c <= 'Z'; ++c) {
        Alphabet.push_back(std::make_shared<Button>(
                std::string(1, c), ASSET_MANAGER.GetFont("league"), x, c <= 'M' ? 500 : 550, [this, i, c]() -> void {
            Alphabet.at((unsigned long) i)->Enabled = false;
            HandleTurn(c);
        }));
        x = x < 725 ? x + 50 : 125;
        i++;
    }

    _TheWord = ASSET_MANAGER.GetDict("words").at(rand() % ASSET_MANAGER.GetDict("words").size());
    for (unsigned long i = 0; i < _TheWord.size(); i++) _DisplayWord += _TheWord.at(i) == ' ' ? " " : "_";
}

Game::~Game() {
    delete _Hangman;
    delete _HangmanCLONE1;
    delete _HangmanCLONE2;
    ASSET_MANAGER.DiscardFont("cubic");
    ASSET_MANAGER.DiscardFont("league");
    ASSET_MANAGER.DiscardDict("res/data/words.txt");
}

void Game::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 255, 255),
                 ASSET_MANAGER.SCREEN_W - 5, ASSET_MANAGER.SCREEN_H - 30,
                 ALLEGRO_ALIGN_RIGHT, "by Thomas Steinholz");

    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 075, 470, ALLEGRO_ALIGN_CENTER, "{");
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 775, 470, ALLEGRO_ALIGN_CENTER, "}");

    switch (_State) {
        case Playing:
            al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                         ASSET_MANAGER.SCREEN_W / 2, 400,
                         ALLEGRO_ALIGN_CENTER, _DisplayWord.c_str());

            for (auto x : Alphabet) x->Render();
            break;
        case Conclusion:
            al_draw_text(ASSET_MANAGER.GetFont("cubic"), al_map_rgb(255, 255, 255),
                         ASSET_MANAGER.SCREEN_W / 2, 50,
                         ALLEGRO_ALIGN_CENTER, _Won ? "YOU WON!" : "YOU LOSE!");
            al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                         ASSET_MANAGER.SCREEN_W / 2, 400,
                         ALLEGRO_ALIGN_CENTER, _TheWord.c_str());
            al_draw_textf(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                          (ASSET_MANAGER.SCREEN_W / 2) - 200, 400,
                         ALLEGRO_ALIGN_CENTER, "Wins: %i", _Score[0]);
            al_draw_textf(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                          (ASSET_MANAGER.SCREEN_W / 2) + 200, 400,
                         ALLEGRO_ALIGN_CENTER, "Losses: %i", _Score[1]);

            btn_Continue->Render();
            btn_Quit->Render();
            break;
    }

    _Hangman->Render();
//    if (_ErrorCount >= 0) {
    _HangmanCLONE1->Render();
    _HangmanCLONE2->Render();
//    }


#ifdef DEBUG //==DEBUG===============================================================================================//

    al_draw_text(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 0, 255), 25, 15,
                 ALLEGRO_ALIGN_LEFT, "Debug Mode");

    al_draw_textf(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 0, 255), 25, 50,
                  ALLEGRO_ALIGN_LEFT, "WORD : %s", _TheWord.c_str());

    al_draw_textf(ASSET_MANAGER.GetFont("league-credits"), al_map_rgb(255, 0, 255), 25, 75,
                  ALLEGRO_ALIGN_LEFT, "ERROR COUNT: %i", _ErrorCount);

    al_draw_rectangle(ASSET_MANAGER.SCREEN_W / 2, ASSET_MANAGER.SCREEN_H / 2,
                      ASSET_MANAGER.SCREEN_W / 2, ASSET_MANAGER.SCREEN_H / 2, al_map_rgb(255, 0, 255), 3);


#endif //============================================================================================================//
}

void Game::Update(ALLEGRO_EVENT *event) {
    _Hangman->Update(event);
    _HangmanCLONE1->Update(event);
    _HangmanCLONE2->Update(event);
    if (_State == Conclusion) {
        btn_Continue->Update(event);
        btn_Quit->Update(event);
    } else {
        for (unsigned long i = 0; i < Alphabet.size(); i++) {
            Alphabet.at(i)->Update(event);
        }
    }
}

void Game::HandleTurn(char letter) {
    al_stop_samples();
    if (_TheWord.find(letter) != std::string::npos) {
        al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        for (unsigned long i = 0; i < _TheWord.size(); i++) {
            if (_DisplayWord.at(i) == '_' && _TheWord.at(i) == letter) {
                std::replace(_DisplayWord.begin() + i, _DisplayWord.begin() + i + 1, '_', letter);
            }
        }
        if (_TheWord.compare(_DisplayWord) == 0) {
            _Won = true;
            _Score[0]++;
            _State = Conclusion;
        }
    } else {
        al_play_sample(ASSET_MANAGER.GetSound("stab"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        _ErrorCount++;

        switch (_ErrorCount) {
            case 2: _Hangman->SetImage(ASSET_MANAGER.GetImage("torso"), 8, 8); break;
            case 3: _Hangman->SetImage(ASSET_MANAGER.GetImage("right-arm"), 8, 8); break;
            case 4: _Hangman->SetImage(ASSET_MANAGER.GetImage("left-arm"), 8, 8); break;
            case 5: _Hangman->SetImage(ASSET_MANAGER.GetImage("right-leg"), 8, 8); break;
            case 6: _Hangman->SetImage(ASSET_MANAGER.GetImage("left-leg"), 8, 8); break;
            case 7: _Hangman->SetImage(ASSET_MANAGER.GetImage("death"), 8, 8); break;
            default: break;
        }

        // TODO : Fix animation sizes
        if (_ErrorCount <= 3) _Hangman->Play((ASSET_MANAGER.SCREEN_W / 2) - 40, 132, false);
        else _Hangman->Play((ASSET_MANAGER.SCREEN_W / 2) - 64, 132, false);

        if (_ErrorCount == 7) {
            al_stop_samples();
            al_play_sample(ASSET_MANAGER.GetSound("spring"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            _HangmanCLONE1->Play(_Hangman->_X + 500, 132, true);
            _HangmanCLONE2->Play(_Hangman->_X - 500, 132, true);
            _Score[1]++;
            _State = Conclusion;
        }
    }
}
