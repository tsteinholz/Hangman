#include "mainmenu.h"

MainMenu::MainMenu() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic-header");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "cubic-credits");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 40, "league");
}

MainMenu::~MainMenu() {
    ASSET_MANAGER.DiscardFont("cubic");
    ASSET_MANAGER.DiscardFont("league");
}

void MainMenu::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("cubic-header"), al_map_rgb(255, 255, 255), ASSET_MANAGER.SCREEN_W / 2, 25,
                 ALLEGRO_ALIGN_CENTRE, "haNGmaN");

    al_draw_text(ASSET_MANAGER.GetFont("cubic-credits"), al_map_rgb(255, 255, 255),
                 ASSET_MANAGER.SCREEN_W - 5, ASSET_MANAGER.SCREEN_H - 30,
                 ALLEGRO_ALIGN_RIGHT, "by Thomas Steinholz");

    // TODO : Add buttons
    al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255), (ASSET_MANAGER.SCREEN_W / 2), 250,
                 ALLEGRO_ALIGN_CENTRE, "PLAY");

}

void MainMenu::Update(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        Current = new Game();
}
