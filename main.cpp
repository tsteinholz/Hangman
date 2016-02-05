#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <cstdio>

int main() {

    const int SCREEN_W = 850, SCREEN_H = 650;

    ALLEGRO_DISPLAY *display = NULL;

    ALLEGRO_EVENT_QUEUE* queue;

    ALLEGRO_TIMER* timer;

    bool render, executing = true;

    if(!al_init())
    {
        printf("al_init Failed!\n");
        return -1;
    }
    if(!al_install_audio())
    {
        fprintf(stderr, "Failed to initialize audio!\n");
        return -1;
    }

    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "Failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Failed to reserve samples!\n");
        return -1;
    }
    if(!al_install_mouse())
    {
        fprintf(stderr, "Failed to initialize the mouse!\n");
        return -1;
    }
    if(!al_init_primitives_addon())
    {
        printf("al_init_primitives_addon Failed!\n");
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);

    if(!display)
    {
        printf("al_create_display Failed!\n");
        return -1;
    }

    srand((unsigned int) time(NULL));

    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();

    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            executing = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                executing = false;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                break;
            case ALLEGRO_EVENT_TIMER:
                render = true;
                break;
            }
        }
        if (al_is_event_queue_empty(queue) && render)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            ////////////////////////////////////////////////////////////////////


            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }
    al_destroy_display(display);

    return 0;
}
