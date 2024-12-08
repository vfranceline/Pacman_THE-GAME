#include <array>
#include <cmath>

#include "../headers/map_collision.hpp"
#include "../headers/global.hpp"

bool check_and_update_cell(int cell_x, int cell_y, bool i_collect_pellets, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
    if (cell_x >= 0 && cell_x < MAP_WIDTH && cell_y >= 0 && cell_y < MAP_HEIGHT) {
        Cell& cell = i_map[cell_x][cell_y];
        if (cell == Cell::Wall) {
            return true; // colisão detectada
        }
        if (i_collect_pellets && cell == Cell::Pellets) {
            cell = Cell::Empty; // coleta de pellet
        }
    }
    return false; // nenhuma colisão
}

bool map_collision(bool i_collect_pellets, short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
    bool output = false;

    float cell_x = i_x / static_cast<float>(CELL_SIZE);
    float cell_y = i_y / static_cast<float>(CELL_SIZE);

    int floor_x = static_cast<int>(floor(cell_x));
    int floor_y = static_cast<int>(floor(cell_y));
    int ceil_x = static_cast<int>(ceil(cell_x));
    int ceil_y = static_cast<int>(ceil(cell_y));

    output |= check_and_update_cell(floor_x, floor_y, i_collect_pellets, i_map);
    output |= check_and_update_cell(ceil_x, floor_y, i_collect_pellets, i_map);
    output |= check_and_update_cell(floor_x, ceil_y, i_collect_pellets, i_map);
    output |= check_and_update_cell(ceil_x, ceil_y, i_collect_pellets, i_map);

    return output;
}
