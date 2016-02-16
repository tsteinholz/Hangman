#include "mainmenu.h"

bool Scene::Executing = true;

MainMenu::MainMenu() {
    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic-header");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 25, "cubic-credits");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 40, "league");
    ASSET_MANAGER.LoadSound("res/sound/zipclick.ogg", "gui-click");
    ASSET_MANAGER.LoadSound("res/sound/start_sound.ogg", "start sound");

    al_play_sample(ASSET_MANAGER.GetSound("start sound"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

    btn_Play = new Button((char *) "PLAY", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 250,
                          []() -> void {
                              SetScene(new Game());
                              al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                          });
    btn_Help = new Button((char *) "HELP", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 300,
                          []() -> void {
                              SetScene(new Help());
                              al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                          });
    btn_Quit = new Button((char *) "QUIT", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 350,
                          []() -> void {
                              SetExe(false);
                              al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                          });
}

MainMenu::~MainMenu() {
    // TODO - never called
    ASSET_MANAGER.DiscardAll();

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
}
