/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-18
** File description:
** Sfml
*/

#include "Sfml.hpp"

Sfml::Sfml()
{
    _name = "Sfml";
    _type = LibType::DISPLAY;
    _font = nullptr;
}

int Sfml::createWindow()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade");
    if (!_window.isOpen())
        return -1;
    if (!_font)
        _font = new sf::Font();
    if (!_font->loadFromFile(FONT_PATH))
        return -1;
    _colors = {
        {RED, sf::Color::Red},
        {GREEN, sf::Color::Green},
        {BLUE, sf::Color::Blue},
        {YELLOW, sf::Color::Yellow},
        {BLACK, sf::Color::Black},
        {WHITE, sf::Color::White},
        {MAGENTA, sf::Color::Magenta},
        {CYAN, sf::Color::Cyan}
    };
    return 0;
}

void Sfml::closeWindow()
{
    if (_font) {
        delete _font;
        _font = nullptr;
    }
    _window.close();
}

void Sfml::clear()
{
    _window.clear(sf::Color(0, 0, 0, 255));
}

void Sfml::display()
{
    _window.display();
}

InputEvent Sfml::getInput()
{
    sf::Event event;
    InputEvent action = {};
    const std::map<sf::Keyboard::Key, EventType> list_key_event = {{sf::Keyboard::Q, EventType::QUIT}, {sf::Keyboard::Escape, EventType::QUIT}, {sf::Keyboard::Enter, EventType::ENTER},
        {sf::Keyboard::R, EventType::RESTART_GAME}, {sf::Keyboard::M, EventType::CALL_MENU}, {sf::Keyboard::L, EventType::SWITCH_DISPLAY}, {sf::Keyboard::G, EventType::SWITCH_GAME}, {sf::Keyboard::Space, EventType::SPACE},
        {sf::Keyboard::Up, EventType::UP_ARROW}, {sf::Keyboard::Down, EventType::DOWN_ARROW}, {sf::Keyboard::Left, EventType::LEFT_ARROW}, {sf::Keyboard::Right, EventType::RIGHT_ARROW}};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            action.event =  EventType::QUIT;
            return action;
        }
        if (event.type == sf::Event::KeyPressed) {
            auto elem = list_key_event.find(event.key.code);
            if (elem == list_key_event.end())
                return action;
            action.event = elem->second;
            return action;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f vector = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
            action.mouse = {static_cast<int>(vector.x / 64), static_cast<int>(vector.y / 54)};
            if (event.mouseButton.button == sf::Mouse::Left)
                action.event = EventType::LEFT_CLICK;
            if (event.mouseButton.button == sf::Mouse::Right)
                action.event = EventType::RIGHT_CLICK;
        }
    }
    return action;
}

void Sfml::drawBackground(std::string background_name)
{
    auto elem = _textures.find(background_name);
    if (elem == _textures.end())
        return;
    sf::Sprite sprite(elem->second);
    sprite.setPosition(0, 0);
    _window.draw(sprite);
}

void Sfml::drawText(pos position, float size, std::string text, Color color) 
{
    sf::Color colordraw;

    if (!_font)
        return;
    sf::Text textdraw;
    textdraw.setFont(*_font);
    textdraw.setCharacterSize(40 * size);
    textdraw.setString(text);
    auto elem = _colors.find(color);
    if (elem == _colors.end())
        colordraw = sf::Color::White;
    else
        colordraw = elem->second;
    textdraw.setFillColor(colordraw);
    textdraw.setStyle(sf::Text::Bold | sf::Text::Underlined);
    auto sizeWindow = recoverWindowSize();
    int x_d = {position.x* (std::get<0>(sizeWindow) / 30)};
    if (position.x == -1) {
        sf::FloatRect vector = textdraw.getGlobalBounds();
        x_d = ((std::get<0>(sizeWindow) - vector.width) / 2);
    }
    int y_d = position.y * (std::get<1>(sizeWindow) / 20);
    textdraw.setPosition(x_d, y_d);
    _window.draw(textdraw);
}

void Sfml::drawSprite(pos position, int rotation, float size, std::string name)
{
    auto elem = _textures.find(name);
    if (elem == _textures.end())
        return;
    sf::Sprite sprite(elem->second);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    float boundX = static_cast<float>(64)  / sprite.getLocalBounds().width;
    float boundY = static_cast<float>(54) / sprite.getLocalBounds().height;
    sprite.setScale(boundX * size, boundY * size);
    sprite.setPosition(position.x * 64 + 64 / 2 - 64/2, position.y * 54 + 54 / 2 - 54/2);
    sprite.setRotation(rotation);
    _window.draw(sprite);
}

int Sfml::loadTexture(std::string game)
{
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
            sf::Texture texture;
            if (!texture.loadFromFile(file))
                continue;
            _textures[name] = texture;
        }
    } catch (const std::exception &) {
        return -1;
    }
    return 0;
}

int Sfml::loadSound(std::string game)
{
    std::string directory_name = "assets/" + game + "/sounds";
    try {
        for (const auto &Entry : std::filesystem::directory_iterator(directory_name)) {
            if (Entry.is_directory())
                continue;
            auto file = Entry.path().string();
            auto pos_exten = file.find_last_of('.');
            if (pos_exten == std::string::npos || file.substr(pos_exten + 1) != "mp3")
                continue;
            auto name = Entry.path().stem().string();
            sf::SoundBuffer sound_buf;
            if (!sound_buf.loadFromFile(file))
                continue;
            _sounds[name] = sound_buf;
        }
    } catch (const std::exception &) {
        return -1;
    }
    return 0;
}

int Sfml::playSound(std::string sound_name_in_map)
{
    auto elem = _sounds.find(sound_name_in_map);
    if (elem == _sounds.end())
        return 0;
    sf::Sound sound;
    sound.setBuffer(elem->second);
    _playsound.push_back(sound);
    _playsound.back().play();
    for (auto it = _playsound.begin(); it != _playsound.end();) {
        if (it->getStatus() == sf::Sound::Stopped)
            it = _playsound.erase(it);
        else
            ++it;
    }
    return 0;
}

std::string Sfml::loadName()
{
    std::string name = "";
    sf::Event event;
    bool is_name = false;
    int pos = {10};
    std::size_t index = {0};

    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                is_name = true;
                break;
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && name.size() < 15 && event.text.unicode != 32) {
                    name += static_cast<char>(event.text.unicode);
                    drawText({pos, 10}, 1.0, name.substr(index), BLUE);
                    pos += 1;
                    index += 1;
                    _window.display();
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

std::tuple<int, int>  Sfml::recoverWindowSize()
{
    return std::make_tuple(1920, 1080);
}

extern "C" IDisplay *entryPoint()
{
    return new Sfml();
}
