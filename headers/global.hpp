#pragma once

#include <cstdint> // Para tipos inteiros explícitos

constexpr unsigned char CELL_SIZE = 16;        // Tamanho da célula
constexpr unsigned char MAP_HEIGHT = 21;      // Altura do mapa
constexpr unsigned char MAP_WIDTH = 21;       // Largura do mapa
constexpr unsigned char SCREEN_RESIZE = 2;    // Fator de redimensionamento da tela

constexpr unsigned char PACMAN_SPEED = 2;

constexpr unsigned short FRAME_DURATION = 16667; // Duração do quadro em microssegundos

// Enum para representar os tipos de células do mapa
enum class Cell : uint8_t {
    Empty,
    Wall,
    Pellets
};

struct Position
{
    short x;
    short y;

    bool operator==(const Position& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};

