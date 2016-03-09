#include "assetmanager.h"

AssetManager &AssetManager::GetAssetManager() {
    static AssetManager instance;
    return instance;
}

AssetManager::AssetManager() :
    _ImageMap(),
    _SoundMap(),
    _FontMap(),
    _TextMap(),
    _DictMap() {

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
    //al_reserve_samples(5);

#ifdef DEBUG
    printf("DEBUG: Creating Asset Manager Instance\n");
#endif // DEBUG
}

AssetManager::~AssetManager() {
    DiscardAll();
#ifdef DEBUG
    printf("DEBUG: Destroying Asset Manager Instance\n");
#endif // DEBUG
}

bool AssetManager::LoadImage(std::string file, std::string key) {
    key = key == "" ? file : key;
    std::shared_ptr<ALLEGRO_BITMAP> x(al_load_bitmap(file.c_str()), al_destroy_bitmap);
    if (!x) {
        fprintf(stderr, "Failed to load %s\n", file.c_str());
        return false;
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key.c_str()); //debug
#endif // DEBUG
    _ImageMap.insert(std::pair<std::string, std::shared_ptr<ALLEGRO_BITMAP>>(key, x));
    return true;
}

bool AssetManager::LoadSound(std::string file, std::string key) {
    key = key == "" ? file : key;
    std::shared_ptr<ALLEGRO_SAMPLE> x(al_load_sample(file.c_str()), al_destroy_sample);
    if (!x) {
        fprintf(stderr, "Failed to load %s\n", file.c_str());
        return false;
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key.c_str()); //debug
#endif // DEBUG
    _SoundMap.insert(std::pair<std::string, std::shared_ptr<ALLEGRO_SAMPLE>>(key, x));
    return true;
}

bool AssetManager::LoadFont(std::string file, unsigned int size, std::string key) {
    key = key == "" ? file : key;
    std::shared_ptr<ALLEGRO_FONT> x(al_load_font(file.c_str(), size, 0), al_destroy_font);
    if (!x) {
        fprintf(stderr, "Failed to load %s\n", file.c_str());
        return false;
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key.c_str()); //debug
#endif // DEBUG
    _FontMap.insert(std::pair<std::string, std::shared_ptr<ALLEGRO_FONT>>(key, x));
    return true;
}

bool AssetManager::LoadText(std::string file, std::string key) {
    key = key == "" ? file : key;
    // TODO
    //if (!x) { printf("Failed to load %s", file); return false;}
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key.c_str()); //debug
#endif // DEBUG
    return false;
}

void AssetManager::LoadDict(std::string file, std::string key) {
    key = key == "" ? file : key;
    std::vector<std::string> x;
    std::ifstream dict(file);
    std::string line = "";

    while (std::getline(dict, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);
        x.push_back(line);
    }
#ifdef DEBUG
    printf("DEBUG: Loaded %s\n", key.c_str()); //debug
#endif // DEBUG
    _DictMap.insert(std::pair<std::string, std::vector<std::string>>(key, x));
}

ALLEGRO_BITMAP *AssetManager::GetImage(std::string key) {
    return _ImageMap.find(key) != _ImageMap.end() ? _ImageMap.at(key).get() : nullptr;
}

ALLEGRO_SAMPLE *AssetManager::GetSound(std::string key) {
    return _SoundMap.find(key) != _SoundMap.end() ? _SoundMap.at(key).get() : nullptr;
}

ALLEGRO_FONT *AssetManager::GetFont(std::string key) {
    return _FontMap.find(key) != _FontMap.end() ? _FontMap.at(key).get() : nullptr;
}

std::string AssetManager::GetText(std::string key) {
    return _TextMap.find(key) != _TextMap.end() ? _TextMap.at(key) : "";
}

std::vector<std::string> AssetManager::GetDict(std::string key) {
    return _DictMap.find(key) != _DictMap.end() ? _DictMap.at(key) : std::vector<std::string>();
}

void AssetManager::DiscardImage(std::string key) {
    _ImageMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key.c_str()); //debug
#endif // DEBUG
}

void AssetManager::DiscardSound(std::string key) {
    _SoundMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key.c_str()); //debug
#endif // DEBUG
}

void AssetManager::DiscardFont(std::string key) {
    _FontMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key.c_str()); //debug
#endif // DEBUG
}

void AssetManager::DiscardText(std::string key) {
    _TextMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key.c_str()); //debug
#endif // DEBUG
}

void AssetManager::DiscardDict(std::string key) {
    _DictMap.erase(key);
#ifdef DEBUG
    printf("DEBUG: Discarded %s\n", key.c_str()); //debug
#endif // DEBUG
}

void AssetManager::DiscardAll() {
    for (auto it = _ImageMap.begin(); it != _ImageMap.end(); ++it)
        DiscardImage(it->first);
    _ImageMap.clear();
    for (auto it = _SoundMap.begin(); it != _SoundMap.end(); ++it)
        DiscardSound(it->first);
    _SoundMap.clear();
    for (auto it = _FontMap.begin(); it != _FontMap.end(); ++it)
        DiscardFont(it->first);
    _FontMap.clear();
    for (auto it = _TextMap.begin(); it != _TextMap.end(); ++it)
        DiscardText(it->first);
    _TextMap.clear();
    for (auto it = _DictMap.begin(); it != _DictMap.end(); ++it)
        DiscardDict(it->first);
    _DictMap.clear();
#ifdef DEBUG
        printf("DEBUG: Discarded All Assets\n");
#endif // DEBUG
}

void AssetManager::PrintCurrentData() {
#ifdef DEBUG
        printf("DEBUG: LISTING ALL ASSETS\n");
        for (auto it = _ImageMap.begin(); it != _ImageMap.end(); ++it)
            printf("\timage: %s \t\t- loaded %s\n", it->first.c_str(), it->second != nullptr ? "true" : "false");
        for (auto it = _SoundMap.begin(); it != _SoundMap.end(); ++it)
            printf("\tsound: %s \t\t- loaded %s\n", it->first.c_str(), it->second != nullptr ? "true" : "false");
        for (auto it = _FontMap.begin(); it != _FontMap.end(); ++it)
            printf("\tfont: %s \t\t- loaded %s\n", it->first.c_str(), it->second != nullptr ? "true" : "false");
        for (auto it = _TextMap.begin(); it != _TextMap.end(); ++it)
            printf("\ttext: %s \t\t- loaded %s\n", it->first.c_str(), it->second != "" ? "true" : "false");
        for (auto it = _DictMap.begin(); it != _DictMap.end(); ++it)
            printf("\tdict: %s \t\t- loaded %s\n", it->first.c_str(), it->second.empty() ? "false" : "true");
#endif // DEBUG
}
