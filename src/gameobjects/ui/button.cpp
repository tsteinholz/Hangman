#include "button.h"

Button::Button(char *text, ALLEGRO_FONT *font, float x, float y) :
        _Text(text), _Font(font), _X(x), _Y(y), Active(false), Hover(false) { }

Button::~Button() { }

void Button::Render() {
    al_draw_text(_Font, Hover ? HOVER_COLOR : ENABLED_COLOR, _X, _Y, ALLEGRO_ALIGN_CENTER,
                 _Text);
    // DEBUG_COLOR
    al_draw_rectangle(_X + (al_get_text_width(_Font, _Text) / 2), _Y + 5,
                      _X - (al_get_text_width(_Font, _Text) / 2), _Y + (al_get_font_line_height(_Font) - 5),
                      DEBUG_COLOR, 2);
}

void Button::Update(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        Hover = ((event->mouse.x >= _X - (al_get_text_width(_Font, _Text) / 2)) &&
                 (event->mouse.x <= _X + (al_get_text_width(_Font, _Text) / 2))) &&
                ((event->mouse.y >= _Y + 5) &&
                 (event->mouse.y <= _Y + (al_get_font_line_height(_Font) - 5)));
    }
    Active = event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && Hover;
}
