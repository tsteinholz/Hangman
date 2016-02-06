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

#include <cstdio>

#include "util/assetmanager.h"

const unsigned int SCREEN_W = 850, SCREEN_H = 650;

int main() {

    srand((unsigned int) time(NULL));

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    ASSET_MANAGER; // Create the asset manager instance

    display = al_create_display(SCREEN_W, SCREEN_H);
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

    ASSET_MANAGER.LoadFont("res/fonts/cubic.ttf", 50, "cubic");
    ASSET_MANAGER.LoadImage("res/graphics/background.png", "background");

    bool render = true, executing = true;
    float bgx = SCREEN_W / 2, bgy = SCREEN_H / 2, bgvelx = -2 + (rand() % 4), bgvely = -2 + (rand() % 4);

    while (executing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                executing = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                executing = !event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;
                break;
            case ALLEGRO_EVENT_TIMER:
                render = true;
                if (bgx + SCREEN_W >= al_get_bitmap_width(ASSET_MANAGER.GetImage("background"))) bgvelx = -bgvelx;
                if (bgx <= 5) bgvelx = -bgvelx;
                if (bgy + SCREEN_H >= al_get_bitmap_height(ASSET_MANAGER.GetImage("background"))) bgvely = -bgvely;
                if (bgy <= 5) bgvely = -bgvely;
                bgx += bgvelx;
                bgy += bgvely;
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
                    SCREEN_W, SCREEN_H,
                    0, 0,
                    SCREEN_W, SCREEN_H,
                    0);

            al_draw_text(ASSET_MANAGER.GetFont("cubic"), al_map_rgb(255, 255, 255), (SCREEN_W / 2), 25,
                         ALLEGRO_ALIGN_CENTRE, "Hangman");

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }
    al_destroy_display(display);

    return 0;
}
