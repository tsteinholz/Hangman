#include "sprite.h"

Sprite::Sprite(ALLEGRO_BITMAP *image, unsigned int columns, unsigned int rows)
        : _Image(image), _Columns(columns), _Rows(rows), _Playing(false) { }

Sprite::~Sprite() { }

void Sprite::Play(float x, float y, bool loop) {
    _Playing = true;
    _SpriteX = 0;
    _SpriteY = 0;
    _Loop = loop;
    _X = x;
    _Y = y;
}

void Sprite::Render() {
    if (_Playing) {
        al_draw_bitmap_region(_Image,
                              _SpriteX * (al_get_bitmap_width(_Image) / _Rows),
                              _SpriteY * (al_get_bitmap_height(_Image) / _Columns),
                              al_get_bitmap_width(_Image) / _Rows,
                              al_get_bitmap_height(_Image) / _Columns,
                              _X, _Y, 0
        );
#ifdef DEBUG
        al_draw_rectangle(_X, _Y,
                          _X + al_get_bitmap_width(_Image) / _Rows,
                          _Y + al_get_bitmap_height(_Image) / _Columns,
                          al_map_rgb(255, 0, 255), 3);

        al_draw_rectangle(_X, _Y, _X, _Y, al_map_rgb(255, 0, 255), 3);
#endif
    }
}

void Sprite::Update(ALLEGRO_EVENT *event) {
    if (_Playing) {
        if (event->type == ALLEGRO_EVENT_TIMER) {
            if (((unsigned int)_SpriteX != _Columns - 1 && (unsigned int)_SpriteY != _Rows - 1) || _Loop) {
                if ((unsigned int)_SpriteX + 1 >= _Columns - 1) {
                    _SpriteX = 0;
                    _SpriteY = (unsigned int)_SpriteY >= _Rows - 1 ? (_Loop ? 0 : _SpriteY) : _SpriteY + 1;
                } else {
                    _SpriteX++;
                }
            }
        }
    }
}

void Sprite::SetImage(ALLEGRO_BITMAP *image, unsigned int columns, unsigned int rows) {
    _Image = image;
    _Columns = columns;
    _Rows = rows;
}

void Sprite::Stop() {
    _Playing = false;
}
