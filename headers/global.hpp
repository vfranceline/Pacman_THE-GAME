#pragma once

#include <cstdint> // Para tipos inteiros explícitos

//utilizando unsigned char para economizar memoria

constexpr unsigned char CELL_SIZE = 16;        // Tamanho da célula
constexpr unsigned char MAP_HEIGHT = 21;      // Altura do mapa
constexpr unsigned char MAP_WIDTH = 21;       // Largura do mapa
constexpr unsigned char SCREEN_RESIZE = 2;    // Fator de redimensionamento da tela
constexpr unsigned char FONT_HEIGHT = 16;

//
constexpr unsigned char GHOST_1_CHASE = 2; //pink - cell a frente do pacman q vai ser o alvo
constexpr unsigned char GHOST_3_CHASE = 4; //laranja - cell q determina quando vai ficar no modo scatter ou no chase

constexpr unsigned char PACMAN_SPEED = 2;
constexpr unsigned char GHOST_SPEED = 1;
constexpr unsigned char GHOST_FRIGHTENED_SPEED = 3;
constexpr unsigned char GHOST_ESCAPE_SPEED = 4;


constexpr unsigned char PACMAN_DEATH_FRAMES = 4;
constexpr unsigned char PACMAN_ANIMATION_FRAMES = 6;
constexpr unsigned char PACMAN_ANIMATION_SPEED = 4;
constexpr unsigned char GHOST_ANIMATION_FRAMES = 6;
constexpr unsigned char GHOST_ANIMATION_SPEED = 4;


constexpr unsigned short FRAME_DURATION = 16667; // Duração do quadro em microssegundos
constexpr unsigned short ENERGIZER_DURATION = 512;

// Enum para representar os tipos de células do mapa
enum class Cell : uint8_t {
    Empty,
    Wall,
    Pellets,
    Energizer,
    Door,
    Home
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

