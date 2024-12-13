#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>

#include "../headers/global.hpp"
#include "../headers/pacman.hpp"
#include "../headers/ghosts.hpp"
#include "../headers/ghost_manager.hpp"

GhostManager::GhostManager():
    ghosts({Ghost(0), Ghost(1), Ghost(2), Ghost(3)})
{

}

void GhostManager::draw(sf::RenderWindow& i_window){
    for (Ghost& ghost : ghosts){
        ghost.draw(i_window);
    }
}

void GhostManager::reset(const std::array<Position, 4>& i_ghost_positions) {
    for (unsigned char i = 0; i < 4; i++) {
        ghosts[i].set_position(i_ghost_positions[i].x, i_ghost_positions[i].y);
    }
}

void GhostManager::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman){
    for (Ghost& ghost : ghosts)
	{
		ghost.update(i_map, ghosts[0], i_pacman);
	}
}
