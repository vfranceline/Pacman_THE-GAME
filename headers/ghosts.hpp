#pragma once

class Ghost{

    bool use_door; //permissão para usar a porta 
    // bool movement_mode; //setar os modos entre scatter(clyde) e normal

    unsigned short animation_timer;

    unsigned char direction; //direção atual do fantasma
    unsigned char frightened_mode; //0- normal 1- assustado 2- fuga
    unsigned char frightened_speed_timer; //timer diferente para fazer o fantasma se mover mais devagar
    unsigned char id; //id dos fantasmas

    Position position;
    Position target;
    Position home; //pra onde ele vai enquanto foge
    Position home_exit; //saída da casa


public:
    Ghost(unsigned char i_id);

    bool pacman_collision(const Position& i_pacman_position);

    float get_target_distance(unsigned char i_direction);

    void draw(sf::RenderWindow& i_window);
    void reset(const Position& i_home, const Position& i_home_exit);
    void set_position(short i_x, short i_y);
    void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman);
    void update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position);

    Position get_position();
};