#include "button.h"

Button::Button(std::string text, ALLEGRO_FONT *font, float x, float y, const std::function <void()> f) :
        Pressed(false),
        Hover(false),
        Enabled(true),
        _Text(text),
        _Font(font),
        _X(x),
        _Y(y),
        _HandleFunction(f)
        { }

Button::~Button() { }

void Button::Render() {
    al_draw_text(_Font, Hover ? HOVER_COLOR : Pressed ? CLICKED_COLOR : Enabled ? ENABLED_COLOR : DISABLED_COLOR,
                 _X,_Y, ALLEGRO_ALIGN_CENTER, _Text.c_str());
#ifdef DEBUG
        al_draw_rectangle(_X + (al_get_text_width(_Font, _Text.c_str()) / 2) + 2.5f, _Y + 7,
                      _X - (al_get_text_width(_Font, _Text.c_str()) / 2), _Y + (al_get_font_line_height(_Font) - 9),
                      DEBUG_COLOR, 2);
#endif
}

void Button::Update(ALLEGRO_EVENT *event) {
    if (Enabled) {
        if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
            Hover = ((event->mouse.x >= _X - (al_get_text_width(_Font, _Text.c_str()) / 2)) &&
                     (event->mouse.x <= _X + (al_get_text_width(_Font, _Text.c_str()) / 2) + 2.5f)) &&
                    ((event->mouse.y >= _Y + 7) &&
                     (event->mouse.y <= _Y + (al_get_font_line_height(_Font) - 9)));
        }
        if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && Hover) _HandleFunction();
    } else if (Pressed || Hover) {
        Pressed = false;
        Hover = false;
    }
}

void Button::SetHandler(const std::function<void()> f) {
    _HandleFunction = f;
}

std::string Button::GetText() {
    return _Text;
}
