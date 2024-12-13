#pragma once

#include "../headers/global.hpp"
#include "../headers/ghosts.hpp"

class GhostManager
{
    std::array<Ghost, 4> ghosts;
public:
    GhostManager();

    void draw(sf::RenderWindow& i_window);
    void reset(const std::array<Position, 4>& i_ghost_positions);
};
