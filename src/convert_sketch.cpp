//converte o esboço do mapa (a array) em uma matriz de celulas

#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "../headers/convert_sketch.hpp"
#include "../headers/pacman.hpp"
#include "../headers/global.hpp"

// Função para converter o esboço do mapa em uma matriz de células
std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> 
convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, Pacman& i_pacman, std::array<Position, 4>& i_ghost_positions) {

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map{};

    for (unsigned char i = 0; i < MAP_HEIGHT; i++) {
        for (unsigned char j = 0; j < MAP_WIDTH; j++) {
            switch (i_map_sketch[i][j]) {
                case '#':
                    output_map[j][i] = Cell::Wall;
                    break;

                case '=':
                    output_map[j][i] = Cell::Door;
                    break;

                case '.':
                    output_map[j][i] = Cell::Pellets;
                    break;
                
                case 'o':
                    output_map[j][i] = Cell::Energizer;
                    break;

                case 'P':
                    i_pacman.set_position(CELL_SIZE * j, CELL_SIZE * i);
                    break;

                case '0':
                    i_ghost_positions[0].x = (CELL_SIZE * j);
                    i_ghost_positions[0].y = (CELL_SIZE * i);
                    break;
                
                case '1':
                    i_ghost_positions[1].x = (CELL_SIZE * j);
                    i_ghost_positions[1].y = (CELL_SIZE * i);
                    break;
                
                case '2':
                    i_ghost_positions[2].x = (CELL_SIZE * j);
                    i_ghost_positions[2].y = (CELL_SIZE * i);
                    break;
                
                case '3':
                    i_ghost_positions[3].x = (CELL_SIZE * j);
                    i_ghost_positions[3].y = (CELL_SIZE * i);
                    break;

                default:
                    output_map[j][i] = Cell::Empty;
                    break;
            }
        }
    }

    return output_map;
}
