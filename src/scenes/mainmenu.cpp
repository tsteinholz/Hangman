#include "mainmenu.h"

bool Scene::Executing = true;

MainMenu::MainMenu() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic-header");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "cubic-credits");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 40, "league");

    Play = new Button((char *) "PLAY", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 250, 60, 36);
    Help = new Button((char *) "HELP", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 300, 60, 36);
    Quit = new Button((char *) "QUIT", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 350, 60, 36);
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

    Play->Render();
    Help->Render();
    Quit->Render();
}

void MainMenu::Update(ALLEGRO_EVENT *event) {
    Play->Update(event);
    Help->Update(event);
    Quit->Update(event);
    if (Play->Active)
        Current = new Game();
    if (Quit->Active)
        Executing = false;
}
