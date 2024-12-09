#pragma once

class Pacman{

    unsigned char direction;

    Position position;

public:
    Pacman();

    void draw(sf::RenderWindow& i_window);
    void set_position(short i_x, short i_y);
    void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
};