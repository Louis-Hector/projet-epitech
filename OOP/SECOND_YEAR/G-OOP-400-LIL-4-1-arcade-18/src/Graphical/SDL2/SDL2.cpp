/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Sdl2
*/

#include "SDL2.hpp"

Sdl2::Sdl2(/* args */)
{
    _name = "SDL2";
    _type = LibType::DISPLAY;
}

int Sdl2::createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        return -1;
    if (SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_SHOWN, &_window, &_render) < 0) {
        SDL_Quit();
        return -1;
    }
    if(TTF_Init() == -1){
        SDL_Quit();
        return -1;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        SDL_Quit();
        TTF_Quit();
        return -1;
    }
    _font = TTF_OpenFont(FONT_PATH, 65);
    if (!_font) {
        Mix_CloseAudio();
        TTF_Quit();
        SDL_DestroyRenderer(_render);
        SDL_DestroyWindow(_window);
        _render = nullptr;
        _window = nullptr;
        SDL_Quit();
        return -1;
    }
    SDL_SetWindowTitle(_window, "Arcade");  
    _colors = {{RED, {255, 0, 0, 255}}, {GREEN, {0, 255, 0, 255}}, {BLUE, {0, 0, 255, 225}}, {WHITE, {255, 255, 255, 255}}, {BLACK, {0, 0, 0, 255}},
    {YELLOW, {255, 255, 0, 255}}, {MAGENTA, {255, 0, 255, 255}}, {CYAN, {0, 255, 255, 255}}};
    return 0;
}

std::tuple<int, int> Sdl2::recoverWindowSize()
{
    int w;
    int h;

    SDL_GetWindowSize(_window, &w, &h);
    return std::make_tuple(w, h);
}

void Sdl2::closeWindow()
{
    for (auto &map : _textures)
        if (map.second)
            SDL_DestroyTexture(map.second);
    _textures.clear();
    for (auto &map : _sounds)
        if (map.second)
            Mix_FreeChunk(map.second);
    _sounds.clear();
    if (_font)
        TTF_CloseFont(_font);
    if (_music)
        Mix_FreeMusic(_music);
    if (_render)
        SDL_DestroyRenderer(_render);
    if (_window)
        SDL_DestroyWindow(_window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return;
}

void Sdl2::clear()
{
    SDL_SetRenderDrawColor(_render, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(_render);
    return;
}

void Sdl2::display()
{
    SDL_RenderPresent(_render);
    return;
}

InputEvent Sdl2::getInput()
{
    SDL_Event event;
    InputEvent action = {};
    const std::map<SDL_Keycode, EventType> list_event_key = {
    {SDLK_l, EventType::SWITCH_DISPLAY}, {SDLK_g, EventType::SWITCH_GAME}, {SDLK_m, EventType::CALL_MENU}, {SDLK_c, EventType::ROAR}, {SDLK_SPACE, EventType::SPACE},
    {SDLK_q, EventType::QUIT}, {SDLK_ESCAPE, EventType::QUIT}, {SDLK_RETURN, EventType::ENTER}, {SDLK_r, EventType::RESTART_GAME},
    {SDLK_UP, EventType::UP_ARROW}, {SDLK_DOWN, EventType::DOWN_ARROW}, {SDLK_LEFT, EventType::LEFT_ARROW}, {SDLK_RIGHT, EventType::RIGHT_ARROW}};

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            action.event = EventType::QUIT;
            return action;
        }
        if (event.type == SDL_KEYDOWN) {
            auto elem = list_event_key.find(event.key.keysym.sym);
            if (elem == list_event_key.end())
                return action;
            action.event = elem->second;
            return action;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            action.mouse = {event.button.x / 64, event.button.y / 54};
            if (event.button.button == SDL_BUTTON_LEFT)
                action.event = EventType::LEFT_CLICK;
            if (event.button.button == SDL_BUTTON_RIGHT)
                action.event = EventType::RIGHT_CLICK;
            return action;
        }
    }
    return action;
}

void Sdl2::drawBackground(std::string background_name)
{
    int w = {};
    int h = {};

    auto elem = _textures.find(background_name);
    if (elem == _textures.end())
        return;
    SDL_QueryTexture(elem->second, nullptr, nullptr, &w, &h);
    SDL_Rect pos = {0, 0, w, h};
    SDL_RenderCopy(_render, elem->second, NULL, &pos);
    return;
}

void Sdl2::drawText(pos position, float size, std::string text, Color color)
{
    SDL_Color colordraw;
    (void)size;

    if (!_font)
        return;
    auto elem = _colors.find(color);
    if (elem == _colors.end())
        colordraw = {255, 255, 255, 255};
    else
        colordraw = elem->second;
    SDL_Surface *textsurface = TTF_RenderText_Blended(_font, text.c_str(), colordraw);
    if (!textsurface)
        return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_render, textsurface);
    if (!texture) {
        SDL_FreeSurface(textsurface);
        return;
    }

    auto sizewindow = recoverWindowSize();
    int x_d = {position.x * (std::get<0>(sizewindow) / 30)};
    if (position.x == -1)
        x_d = ((std::get<0>(sizewindow) - textsurface->w) / 2);
    int y_d = (position.y * (std::get<1>(sizewindow) / 20));
    SDL_Rect rect = {x_d, y_d, textsurface->w, textsurface->h};
    SDL_RenderCopy(_render, texture, NULL, &rect);
    SDL_FreeSurface(textsurface);
    SDL_DestroyTexture(texture);
}

void Sdl2::drawSprite(pos position, int rotation, float size, std::string name)
{
    auto elem = _textures.find(name);
    if (elem == _textures.end())
        return;
    std::tuple value = recoverWindowSize();
    auto Wwidth = std::get<0>(value) / 30;
    auto Wheight = std::get<1>(value) / 20;
    SDL_Rect pos = {position.x * Wwidth, position.y * Wheight, static_cast<int>(Wwidth * size), static_cast<int>(Wheight * size)};
    SDL_RenderCopyEx(_render, elem->second, nullptr, &pos, rotation, nullptr, SDL_FLIP_NONE);
    return;
}

int Sdl2::loadTexture(std::string game)
{
    if (!_render) {
        std::cerr << "ERROR: renderer is NULL" << std::endl;
        return -1;
    }
    std::string directory_name = "assets/" + game + "/images";
    try {
        for (const auto &Entry : std::filesystem::directory_iterator(directory_name)) {
            if (Entry.is_directory())
                continue;
            auto file = Entry.path().string();
            auto pos_exten = file.find_last_of('.');
            if (pos_exten == std::string::npos || file.substr(pos_exten + 1) != "png")
                continue;
            auto name = Entry.path().stem().string();
            SDL_Surface *surface = IMG_Load(file.c_str());
            if (!surface) {
                std::cout << SDL_GetError() << std::endl;
                continue;
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(_render, surface);
            SDL_FreeSurface(surface);
            if (!texture) {
                std::cout << SDL_GetError() << std::endl;
                continue;
            }
            _textures[name] = texture;
        }
    } catch (const std::exception &) {
        return -1;
    }
    return 0;
}

int Sdl2::loadSound(std::string game)
{
    std::string directory_name = "assets/" + game + "/sounds";
    try {
        for (const auto &Entry : std::filesystem::directory_iterator(directory_name)) {
            if (Entry.is_directory())
                continue;
            auto file = Entry.path().string();
            auto pos_extension = file.find_last_of('.');
            if (pos_extension == std::string::npos || file.substr(pos_extension + 1) != "mp3")
                continue;
            auto name = Entry.path().stem().string();
            Mix_Chunk *sound = Mix_LoadWAV(file.c_str());
            if (!sound)
                continue;
            _sounds[name] = sound;
        }
    } catch (const std::exception &) {
        return -1;
    }
    return 0;
}

std::string Sdl2::loadName()
{
    std::string name = "";
    SDL_Event event;
    bool is_name = false;
    int pos_name = {10};
    std::size_t index = {0};

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN || name.size() > 15) {
                    is_name = true;
                    break;
                }
                if ((event.key.keysym.sym) && (event.key.keysym.sym) != SDLK_SPACE) {
                    name += static_cast<char>(event.key.keysym.sym);
                    drawText({pos_name, 10}, 1, name.substr(index), BLUE);
                    pos_name += 1;
                    index += 1;
                    SDL_RenderPresent(_render);
                }
            }
        }
        if (is_name == true)
            break;
    }
    if (name.size() == 0)
        name = "Guest";
    return name;
}

int Sdl2::playSound(std::string sound_name_in_map)
{
    auto elem = _sounds.find(sound_name_in_map);
    if (elem == _sounds.end())
        return 0;
    Mix_PlayChannel(-1, elem->second, 0);
    return 0;
}

extern "C" IDisplay *entryPoint()
{
    return new Sdl2();
}
