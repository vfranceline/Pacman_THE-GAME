#pragma once

#include <cstdint> // Para tipos inteiros explícitos

constexpr unsigned CELL_SIZE = 16;        // Tamanho da célula
constexpr unsigned MAP_HEIGHT = 21;      // Altura do mapa
constexpr unsigned MAP_WIDTH = 21;       // Largura do mapa
constexpr unsigned SCREEN_RESIZE = 2;    // Fator de redimensionamento da tela

constexpr unsigned short FRAME_DURATION = 16667; // Duração do quadro em microssegundos

// Enum para representar os tipos de células do mapa
enum class Cell : uint8_t {
    Empty,
    Wall
};
