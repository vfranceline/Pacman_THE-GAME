//converte o esboço do mapa (a array) em uma matriz de celulas

#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/convert_sketch.hpp"
#include "../headers/pacman.hpp"


std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, Pacman& i_pacman){

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map{};

    for(unsigned char i = 0; i < MAP_HEIGHT; i++){
        for (unsigned char j = 0; j < MAP_WIDTH; j++){
            switch (i_map_sketch[i][j]){
                case ' ':
                    output_map[j][i] = Cell::Empty;
                    break;
                
                case '#':
                    output_map[j][i] = Cell::Wall;
                    break;
                case 'P':
                    i_pacman.set_position(CELL_SIZE*j, CELL_SIZE*i);
                case '.':
                    output_map[j][i] = Cell::Pellets;
            }
        }
    }

    return output_map;
}