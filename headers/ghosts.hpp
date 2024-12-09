#pragma once

class Ghost{
    unsigned char direction;

    Position position;

public:
    Ghost();

    void draw(sf::RenderWindow& i_window);
    void set_position(short i_x, short i_y);
    // void update(std::array<std::array<Cell,)
};