#include "button.h"

Button::Button(char *text, ALLEGRO_FONT *font, float x, float y) :
        _Text(text), _Font(font), _X(x), _Y(y), Pressed(false), Hover(false), Enabled(true) { }

Button::~Button() {
    al_destroy_font(_Font);
}

void Button::Render() {
    al_draw_text(_Font, Hover ? HOVER_COLOR : Pressed ? CLICKED_COLOR : Enabled ? ENABLED_COLOR : DISABLED_COLOR, _X,
                 _Y,
                 ALLEGRO_ALIGN_CENTER, _Text);
//    -DEBUG [uncomment the line below]
//    al_draw_rectangle(_X + (al_get_text_width(_Font, _Text) / 2) + 2.5f, _Y + 7,
//                      _X - (al_get_text_width(_Font, _Text) / 2), _Y + (al_get_font_line_height(_Font) - 9),
//                      DEBUG_COLOR, 2);
}

void Button::Update(ALLEGRO_EVENT *event) {
    if (Enabled) {
        if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
            Hover = ((event->mouse.x >= _X - (al_get_text_width(_Font, _Text) / 2)) &&
                     (event->mouse.x <= _X + (al_get_text_width(_Font, _Text) / 2) + 2.5f)) &&
                    ((event->mouse.y >= _Y + 7) &&
                     (event->mouse.y <= _Y + (al_get_font_line_height(_Font) - 9)));
        }
        Pressed = event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && Hover;
    } else if (Pressed || Hover) {
        Pressed = false;
        Hover = false;
    }
}
