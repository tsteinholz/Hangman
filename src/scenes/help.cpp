#include "help.h"

Help::Help() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic-header");

}

Help::~Help() {

}

void Help::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("cubic-header"), al_map_rgb(255, 255, 255), ASSET_MANAGER.SCREEN_W / 2, 25,
                 ALLEGRO_ALIGN_CENTRE, "hangman");

    //TODO : Add instructions and shit
}

void Help::Update(ALLEGRO_EVENT *event) {

}
