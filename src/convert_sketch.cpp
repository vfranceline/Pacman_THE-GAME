//converte o esboço do mapa (a array) em uma matriz de celulas

#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "../headers/convert_sketch.hpp"
#include "../headers/pacman.hpp"
#include "../headers/ghosts.hpp"

// Função para converter o esboço do mapa em uma matriz de células
std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> 
convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, Pacman& i_pacman, Ghost& i_ghost) {

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map{};

    for (unsigned char i = 0; i < MAP_HEIGHT; i++) {
        for (unsigned char j = 0; j < MAP_WIDTH; j++) {
            switch (i_map_sketch[i][j]) {
                case ' ':
                    output_map[j][i] = Cell::Empty;
                    break;

                case '#':
                    output_map[j][i] = Cell::Wall;
                    break;

                case '.':
                    output_map[j][i] = Cell::Pellets;
                    break; // Corrigido para evitar comportamento incorreto

                case 'P':
                    i_pacman.set_position(CELL_SIZE * j, CELL_SIZE * i);
                    break;

                case 'g':
                    i_ghost.set_position(CELL_SIZE * j, CELL_SIZE * i);
                    break;

                default:
                    break;
            }
        }
    }

    return output_map;
}
