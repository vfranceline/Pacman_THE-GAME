#pragma once

class Pacman{
    bool animation_over; //utilizado para animação da morte
    bool dead;

    unsigned char direction;

    unsigned short animation_timer;
    unsigned short energizer_timer;

    Position position;

public:
    Pacman();

    bool get_animation_over();
    bool get_dead();

    unsigned char get_direction();

    unsigned short get_energizer_timer();

    void draw(bool i_victory, sf::RenderWindow& i_window);
    void reset();
    void set_animation_timer(unsigned short i_animation_timer);
    void set_dead(bool i_dead);
    void set_position(short i_x, short i_y);
    void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

    Position get_position();
};