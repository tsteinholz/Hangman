#include "assetmanager.h"

std::map<const char *, ALLEGRO_BITMAP *> AssetManager::_ImageMap = {};
std::map<const char *, ALLEGRO_SAMPLE *> AssetManager::_SoundMap = {};
std::map<const char *, ALLEGRO_FONT *> AssetManager::_FontMap = {};
std::map<const char *, const char *> AssetManager::_TextMap = {};

AssetManager::AssetManager() {
    if (!al_init()) {
        printf("al_init Failed!\n");
        exit(-1);
    }
    if (!al_install_audio()) {
        fprintf(stderr, "Failed to initialize audio!\n");
        exit(-1);
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Failed to initialize audio codecs!\n");
        exit(-1);
    }
    if (!al_reserve_samples(1)) {
        fprintf(stderr, "Failed to reserve samples!\n");
        exit(-1);
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to initialize the mouse!\n");
        exit(-1);
    }
    if (!al_init_primitives_addon()) {
        printf("al_init_primitives_addon Failed!\n");
        exit(-1);
    }

    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();
}

AssetManager::~AssetManager() {

}

AssetManager &AssetManager::GetAssetManager() {
    static AssetManager instance;
    return instance;
}

bool AssetManager::LoadImage(const char *file, const char *key) {
    key = !key ? file : key;
    ALLEGRO_BITMAP *x = al_load_bitmap(file);
    if (!x) {
        printf("Failed to load %s\n", file);
        return false;
    }
    _ImageMap.insert(std::pair<const char *, ALLEGRO_BITMAP *>(key, x));
    return true;
}

bool AssetManager::LoadSound(const char *file, const char *key) {
    key = !key ? file : key;
    ALLEGRO_SAMPLE *x = al_load_sample(file);
    if (!x) {
        printf("Failed to load %s\n", file);
        return false;
    }
    _SoundMap.insert(std::pair<const char *, ALLEGRO_SAMPLE *>(key, x));
    return true;
}

bool AssetManager::LoadFont(const char *file, unsigned int size, const char *key) {
    key = !key ? file : key;
    ALLEGRO_FONT *x = al_load_font(file, size, 0);
    if (!x) {
        printf("Failed to load %s", file);
        return false;
    }
    _FontMap.insert(std::pair<const char *, ALLEGRO_FONT *>(key, x));
    return true;
}

bool AssetManager::LoadText(const char *file, const char *key) {
    key = !key ? file : key;
    // TODO
    //if (!x) { printf("Failed to load %s", file); return false;}
    return false;
}

ALLEGRO_BITMAP *AssetManager::GetImage(const char *key) {
    return _ImageMap.at(key);
}

ALLEGRO_SAMPLE *AssetManager::GetSound(const char *key) {
    return _SoundMap.at(key);
}

ALLEGRO_FONT *AssetManager::GetFont(const char *key) {
    return _FontMap.at(key);
}

const char *AssetManager::GetText(const char *key) {
    return _TextMap.at(key);
}
