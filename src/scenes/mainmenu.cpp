#include "mainmenu.h"

bool Scene::Executing = true;

MainMenu::MainMenu() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic-header");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "cubic-credits");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 40, "league");

    btn_Play = new Button((char *) "PLAY", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 250);
    btn_Help = new Button((char *) "HELP", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 300);
    btn_Quit = new Button((char *) "QUIT", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 350);
}

MainMenu::~MainMenu() {
    ASSET_MANAGER.DiscardFont("cubic");
    ASSET_MANAGER.DiscardFont("league");

    delete btn_Play;
    delete btn_Help;
    delete btn_Quit;
}

void MainMenu::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("cubic-header"), al_map_rgb(255, 255, 255), ASSET_MANAGER.SCREEN_W / 2, 25,
                 ALLEGRO_ALIGN_CENTRE, "hangman");

    al_draw_text(ASSET_MANAGER.GetFont("cubic-credits"), al_map_rgb(255, 255, 255),
                 ASSET_MANAGER.SCREEN_W - 5, ASSET_MANAGER.SCREEN_H - 30,
                 ALLEGRO_ALIGN_RIGHT, "by Thomas Steinholz");

    btn_Play->Render();
    btn_Help->Render();
    btn_Quit->Render();
}

void MainMenu::Update(ALLEGRO_EVENT *event) {
    btn_Play->Update(event);
    btn_Help->Update(event);
    btn_Quit->Update(event);
    if (btn_Play->Active)
        SetScene(new Game());
    if (btn_Help->Active)
        SetScene(new Help());
    if (btn_Quit->Active)
        Executing = false;
}
