#include "button.h"

Button::Button(char *text, ALLEGRO_FONT *font, float x, float y, float x2, float y2) :
        _Text(text), _Font(font), _X(x), _Y(y), _X2(x2), _Y2(y2) {

}

Button::~Button() {

}

void Button::Render() {
    al_draw_text(_Font, al_map_rgb(255, 255, 255), _X, _Y, ALLEGRO_ALIGN_CENTER, _Text);
    al_draw_rectangle(_X, _Y, _X2, _Y2, al_map_rgb(255, 0, 255), 2); // DEBUG
}

void Button::Update(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        if (event->mouse.y >= _Y && event->mouse.y <= _Y2)
            Active = event->mouse.x >= _X && event->mouse.x <= _X2;
        else
            Active = false;
    }
}
