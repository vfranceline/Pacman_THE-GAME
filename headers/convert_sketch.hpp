#pragma once

#include "../headers/global.hpp"
#include "../headers/pacman.hpp"

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch, Pacman& i_pacman);