#include "button.h"

Button::Button(char *text, ALLEGRO_FONT *font, float x, float y, float width, float height) :
        _Text(text), _Font(font), _X(x), _Y(y), _Width(width), _Height(height), Active(false), Hover(false) {

}

Button::~Button() {

}

void Button::Render() {
    al_draw_text(_Font, Hover ? al_map_rgb(0, 255, 255) : al_map_rgb(255, 255, 255), _X, _Y, ALLEGRO_ALIGN_CENTER,
                 _Text);
//    al_draw_rectangle(_X + (_Width / 2), _Y + 5, _X - (_Width / 2), _Y + (_Height) + 5, al_map_rgb(255, 0, 255), 2);
}

void Button::Update(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        Hover = ((event->mouse.x >= _X - (_Width / 2)) && (event->mouse.x <= _X + (_Width / 2))) &&
                ((event->mouse.y >= _Y) && (event->mouse.y <= _Y + (_Width / 2)));
    }
    Active = event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && Hover;
}
