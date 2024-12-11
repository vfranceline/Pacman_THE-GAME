#pragma once

class Pacman{

    unsigned char direction;
    unsigned short animation_timer;

    Position position;

public:
    Pacman();

    void draw(sf::RenderWindow& i_window);
    void reset();
    void set_animation_timer(unsigned short i_animation_timer);
    void set_position(short i_x, short i_y);
    void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

    Position get_position();
};