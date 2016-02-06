#include "assetmanager.h"

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
    return false;
}

bool AssetManager::LoadSound(const char *file, const char *key) {
    key = !key ? file : key;

    return false;
}

bool AssetManager::LoadFont(const char *file, const char *key) {
    key = !key ? file : key;

    return false;
}

bool AssetManager::LoadText(const char *file, const char *key) {
    key = !key ? file : key;

    return false;
}

ALLEGRO_BITMAP *AssetManager::GetImage(const char *key) {
    return nullptr;
}

ALLEGRO_SAMPLE *AssetManager::GetSound(const char *key) {
    return nullptr;
}

ALLEGRO_FONT *AssetManager::GetFont(const char *key) {
    return nullptr;
}

const char *AssetManager::GetText(const char *key) {
    return nullptr;
}
