#include "game.h"

Game::Game() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 45, "league");

    Alphabet = {
            std::make_shared<Button>((char *) "A", ASSET_MANAGER.GetFont("league"), 250, 500),
            std::make_shared<Button>((char *) "B", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "C", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "D", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "E", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "F", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "G", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "H", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "I", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "J", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "K", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "L", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "M", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "N", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "O", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "P", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "Q", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "R", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "S", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "T", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "U", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "V", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "W", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "X", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "Y", ASSET_MANAGER.GetFont("league"), 0, 0),
            std::make_shared<Button>((char *) "Z", ASSET_MANAGER.GetFont("league"), 0, 0)
    };
}

Game::~Game() {
    ASSET_MANAGER.DiscardFont("cubic");

}

void Game::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("cubic"), al_map_rgb(255, 255, 255), (ASSET_MANAGER.SCREEN_W / 2), 25,
                 ALLEGRO_ALIGN_CENTRE, "game");

    for (auto x : Alphabet) {
        x->Render();
    }
}

void Game::Update(ALLEGRO_EVENT *event) {
    for (auto x : Alphabet) {
        x->Update(event);
    }
}
