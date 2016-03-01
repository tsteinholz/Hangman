#include "help.h"
#include "mainmenu.h"

Help::Help() {

    printf("DEBUG: Help constructor\n");


    printf("cubic-header is loaded: %s\n", ASSET_MANAGER.GetFont("cubic-header") != nullptr ? "true" : "false");
    printf("league is loaded: %s\n", ASSET_MANAGER.GetFont("league") != nullptr ? "true" : "false");
    printf("background is loaded: %s\n", ASSET_MANAGER.GetImage("background") != nullptr ? "true" : "false");
    printf("gui-click is loaded: %s\n", ASSET_MANAGER.GetFont("gui-click") != nullptr ? "true" : "false");

    btn_Back = new Button("BACK", ASSET_MANAGER.GetFont("league"), ASSET_MANAGER.SCREEN_W / 2, 550, [this]() -> void {
        al_stop_samples();
        al_play_sample(ASSET_MANAGER.GetSound("gui-click"), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        SetScene(new MainMenu());
    });
}

Help::~Help() {
    delete btn_Back;
}

void Help::Render() {
    al_draw_text(ASSET_MANAGER.GetFont("cubic-header"), al_map_rgb(255, 255, 255), ASSET_MANAGER.SCREEN_W / 2, 25,
                 ALLEGRO_ALIGN_CENTRE, "hangman");

    const char *content[8] = {
            "Hangman is a pretty fun and simple game, to play",
            "all you have to do is guess the word. Every word",
            "you guess wrong adds a body part to the hang man",
            "if you guess too many incorrectly, he will be hung!",
            "To win, the man must still be alive (not hung)",
            "by the time you guess the word. If you mess up too",
            "many times, then the man will be hung and you",
            "would have lost. GOOD LUCK! :)"
    };

    for (unsigned int i = 0; i < 8; i++) {
        al_draw_text(ASSET_MANAGER.GetFont("league"), al_map_rgb(255, 255, 255),
                     ASSET_MANAGER.SCREEN_W / 2, 125 + (50 * i),
                     ALLEGRO_ALIGN_CENTER, content[i]);
    }

    btn_Back->Render();
}

void Help::Update(ALLEGRO_EVENT *event) {
    btn_Back->Update(event);
}
