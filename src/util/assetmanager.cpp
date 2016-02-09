#include "assetmanager.h"

std::map<const char *, std::shared_ptr<ALLEGRO_BITMAP>> AssetManager::_ImageMap = {};
std::map<const char *, std::shared_ptr<ALLEGRO_SAMPLE>> AssetManager::_SoundMap = {};
std::map<const char *, std::shared_ptr<ALLEGRO_FONT>> AssetManager::_FontMap = {};
std::map<const char *, const char *> AssetManager::_TextMap = {};
std::map<const char *, std::vector<std::string>> AssetManager::_DictMap = {};

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
        fprintf(stderr, "al_init_primitives_addon Failed!\n");
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
    std::shared_ptr<ALLEGRO_BITMAP> x(al_load_bitmap(file), al_destroy_bitmap);
    if (!x) {
        fprintf(stderr, "Failed to load %s\n", file);
        return false;
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key); //debug
#endif
    _ImageMap.insert(std::pair<const char *, std::shared_ptr<ALLEGRO_BITMAP>>(key, x));
    return true;
}

bool AssetManager::LoadSound(const char *file, const char *key) {
    key = !key ? file : key;
    std::shared_ptr<ALLEGRO_SAMPLE> x(al_load_sample(file), al_destroy_sample);
    if (!x) {
        fprintf(stderr, "Failed to load %s\n", file);
        return false;
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key); //debug
#endif
    _SoundMap.insert(std::pair<const char *, std::shared_ptr<ALLEGRO_SAMPLE>>(key, x));
    return true;
}

bool AssetManager::LoadFont(const char *file, unsigned int size, const char *key) {
    key = !key ? file : key;
    std::shared_ptr<ALLEGRO_FONT> x(al_load_font(file, size, 0), al_destroy_font);
    if (!x) {
        fprintf(stderr, "Failed to load %s\n", file);
        return false;
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key); //debug
#endif
    _FontMap.insert(std::pair<const char *, std::shared_ptr<ALLEGRO_FONT>>(key, x));
    return true;
}

bool AssetManager::LoadText(const char *file, const char *key) {
    key = !key ? file : key;
    // TODO
    //if (!x) { printf("Failed to load %s", file); return false;}
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key); //debug
#endif
    return false;
}

void AssetManager::LoadDict(const char *file, const char *key) {
    key = !key ? file : key;
    std::vector<std::string> x;
    std::ifstream dict(file);
    std::string line = "";

    while (std::getline(dict, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);
        x.push_back(line);
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key); //debug
#endif
    _DictMap.insert(std::pair<const char *, std::vector<std::string>>(key, x));
}

ALLEGRO_BITMAP *AssetManager::GetImage(const char *key) {
    return _ImageMap.at(key).get();
}

ALLEGRO_SAMPLE *AssetManager::GetSound(const char *key) {
    return _SoundMap.at(key).get();
}

ALLEGRO_FONT *AssetManager::GetFont(const char *key) {
    return _FontMap.at(key).get();
}

const char *AssetManager::GetText(const char *key) {
    return _TextMap.at(key);
}

std::vector<std::string> AssetManager::GetDict(const char *key) {
    return _DictMap.at(key);
}

void AssetManager::DiscardImage(const char *key) {
    _ImageMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key); //debug
#endif
}

void AssetManager::DiscardSound(const char *key) {
    _SoundMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key); //debug
#endif
}

void AssetManager::DiscardFont(const char *key) {
    _FontMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key); //debug
#endif
}

void AssetManager::DiscardText(const char *key) {
    _TextMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key); //debug
#endif
}

void AssetManager::DiscardDict(const char *key) {
    _DictMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key); //debug
#endif
}
