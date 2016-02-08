#include "game.h"

Game::Game() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 45, "league");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 125, "league-fancy");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "league-credits");
    ASSET_MANAGER.LoadDict("res/data/words.txt", "words");

    Alphabet = {
            std::make_shared<Button>((char *) "A", ASSET_MANAGER.GetFont("league"), 125, 500), // 0
            std::make_shared<Button>((char *) "B", ASSET_MANAGER.GetFont("league"), 175, 500), // 1
            std::make_shared<Button>((char *) "C", ASSET_MANAGER.GetFont("league"), 225, 500), // 2
            std::make_shared<Button>((char *) "D", ASSET_MANAGER.GetFont("league"), 275, 500), // 3
            std::make_shared<Button>((char *) "E", ASSET_MANAGER.GetFont("league"), 325, 500), // 4
            std::make_shared<Button>((char *) "F", ASSET_MANAGER.GetFont("league"), 375, 500), // 5
            std::make_shared<Button>((char *) "G", ASSET_MANAGER.GetFont("league"), 425, 500), // 6
            std::make_shared<Button>((char *) "H", ASSET_MANAGER.GetFont("league"), 475, 500), // 7
            std::make_shared<Button>((char *) "I", ASSET_MANAGER.GetFont("league"), 525, 500), // 8
            std::make_shared<Button>((char *) "J", ASSET_MANAGER.GetFont("league"), 575, 500), // 9
            std::make_shared<Button>((char *) "K", ASSET_MANAGER.GetFont("league"), 625, 500), // 10
            std::make_shared<Button>((char *) "L", ASSET_MANAGER.GetFont("league"), 675, 500), // 11
            std::make_shared<Button>((char *) "M", ASSET_MANAGER.GetFont("league"), 725, 500), // 12

            std::make_shared<Button>((char *) "N", ASSET_MANAGER.GetFont("league"), 125, 550), // 13
            std::make_shared<Button>((char *) "O", ASSET_MANAGER.GetFont("league"), 175, 550), // 14
            std::make_shared<Button>((char *) "P", ASSET_MANAGER.GetFont("league"), 225, 550), // 15
            std::make_shared<Button>((char *) "Q", ASSET_MANAGER.GetFont("league"), 275, 550), // 16
            std::make_shared<Button>((char *) "R", ASSET_MANAGER.GetFont("league"), 325, 550), // 17
            std::make_shared<Button>((char *) "S", ASSET_MANAGER.GetFont("league"), 375, 550), // 18
            std::make_shared<Button>((char *) "T", ASSET_MANAGER.GetFont("league"), 425, 550), // 19
            std::make_shared<Button>((char *) "U", ASSET_MANAGER.GetFont("league"), 475, 550), // 20
            std::make_shared<Button>((char *) "V", ASSET_MANAGER.GetFont("league"), 525, 550), // 21
            std::make_shared<Button>((char *) "W", ASSET_MANAGER.GetFont("league"), 575, 550), // 22
            std::make_shared<Button>((char *) "X", ASSET_MANAGER.GetFont("league"), 625, 550), // 23
            std::make_shared<Button>((char *) "Y", ASSET_MANAGER.GetFont("league"), 675, 550), // 24
            std::make_shared<Button>((char *) "Z", ASSET_MANAGER.GetFont("league"), 725, 550)  // 25
    };

    _TheWord = ASSET_MANAGER.GetDict("words").at(rand() % ASSET_MANAGER.GetDict("words").size());
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
                 ASSET_MANAGER.SCREEN_W / 2, ASSET_MANAGER.SCREEN_H / 2,
                 ALLEGRO_ALIGN_CENTER, _TheWord.c_str());


    for (auto x : Alphabet) x->Render();
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 75, 470, ALLEGRO_ALIGN_CENTER, "{");
    al_draw_text(ASSET_MANAGER.GetFont("league-fancy"), al_map_rgb(255, 255, 255), 775, 470, ALLEGRO_ALIGN_CENTER, "}");
}

void Game::Update(ALLEGRO_EVENT *event) {
    for (auto x : Alphabet) {
        x->Update(event);
        if (x->Pressed) x->Enabled = false;
    }
}
