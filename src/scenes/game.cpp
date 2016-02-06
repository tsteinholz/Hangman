#include "game.h"

Game::Game() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic");

}

Game::~Game() {
    ASSET_MANAGER.DiscardFont("cubic");

}

void Game::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("cubic"), al_map_rgb(255, 255, 255), (ASSET_MANAGER.SCREEN_W / 2), 25,
                 ALLEGRO_ALIGN_CENTRE, "game");

}

void Game::Update(ALLEGRO_EVENT *event) {

}
