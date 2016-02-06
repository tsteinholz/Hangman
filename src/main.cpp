//-----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Thomas Steinholz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#include <allegro5/allegro.h>

#include "util/assetmanager.h"
#include "scenes/scene.h"
#include "scenes/mainmenu.h"

Scene *Scene::Current = nullptr;

int main() {

    srand((unsigned int) time(NULL));

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    display = al_create_display(ASSET_MANAGER.SCREEN_W, ASSET_MANAGER.SCREEN_H);
    if (!display) {
        printf("al_create_display Failed!\n");
        exit(-1);
    }

    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 80, "cubic");
    ASSET_MANAGER.LoadFont("res/fonts/league-gothic.ttf", 40, "league");
    ASSET_MANAGER.LoadImage("res/graphics/background.png", "background");

    bool render = true, executing = true;
    float bgx = ASSET_MANAGER.SCREEN_W / 2,
            bgy = ASSET_MANAGER.SCREEN_H / 2,
            bgvelx = rand() % 2 ? -1.5f : 1.5f,
            bgvely = rand() % 2 ? -1.5f : 1.5f;

    Scene::Current = new MainMenu();

    while (executing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        Scene::Current->Update(&event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                executing = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                executing = event.keyboard.keycode != ALLEGRO_KEY_ESCAPE;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (bgx + ASSET_MANAGER.SCREEN_W >= al_get_bitmap_width(ASSET_MANAGER.GetImage("background")))
                    bgvelx = -bgvelx;
                else if (bgx <= 5) bgvelx = -bgvelx;
                if (bgy + ASSET_MANAGER.SCREEN_H >= al_get_bitmap_height(ASSET_MANAGER.GetImage("background")))
                    bgvely = -bgvely;
                else if (bgy <= 5) bgvely = -bgvely;
                bgx += bgvelx;
                bgy += bgvely;
                render = true;
                break;
            default:
                break;
        }
        if (al_is_event_queue_empty(queue) && render) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_set_target_bitmap(al_get_backbuffer(display));
            ////////////////////////////////////////////////////////////////////

            al_draw_scaled_bitmap(
                    ASSET_MANAGER.GetImage("background"),
                    bgx, bgy,
                    ASSET_MANAGER.SCREEN_W, ASSET_MANAGER.SCREEN_H,
                    0, 0,
                    ASSET_MANAGER.SCREEN_W, ASSET_MANAGER.SCREEN_H,
                    0);

            Scene::Current->Render();

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }
    al_destroy_display(display);
    return 0;
}
