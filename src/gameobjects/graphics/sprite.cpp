#include "sprite.h"

Sprite::Sprite(ALLEGRO_BITMAP* image, unsigned int columns, unsigned int rows)
        : _Image(image), _Columns(columns), _Rows(rows) { }

Sprite::~Sprite() { }

void Sprite::Play(float x, float y, bool loop) {
    _SpriteX = 0;
    _SpriteY = 0;
    _Loop = loop;
    _X = x;
    _Y = y;
}

void Sprite::Render() {
    al_draw_bitmap_region(_Image,
                          _SpriteX * (al_get_bitmap_width(_Image) / _Rows),
                          _SpriteY * (al_get_bitmap_height(_Image) / _Columns),
                          al_get_bitmap_width(_Image) / _Rows,
                          al_get_bitmap_height(_Image) / _Columns,
                          _X, _Y, 0
    );
}

void Sprite::Update(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_TIMER) {
        if ((_SpriteX != _Columns - 1 && _SpriteY != _Rows - 1) || _Loop) {
            if (_SpriteX + 1 >= _Columns - 1) {
                _SpriteX = 0;
                _SpriteY = _SpriteY >= _Rows -1 ? (_Loop ? 0 : _SpriteY) : _SpriteY + 1;
            } else {
                _SpriteX++;
            }
        }
    }
}