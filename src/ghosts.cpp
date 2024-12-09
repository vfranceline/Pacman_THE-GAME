#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>

#include "../headers/global.hpp"
#include "../headers/ghosts.hpp"
#include "../headers/map_collision.hpp"

Ghost::Ghost():
    direction(0),
    position({0, 0})
{

}

void Ghost::draw(sf::RenderWindow& i_window){
    sf::CircleShape ghost_circle(CELL_SIZE/2);
    ghost_circle.setFillColor(sf::Color(255, 0, 0));
    ghost_circle.setPosition(position.x, position.y);

    sf::RectangleShape ghost_rectang (sf::Vector2f(CELL_SIZE/2, CELL_SIZE/4));
    
    i_window.draw(ghost_circle);
    i_window.draw(ghost_rectang);

}

void Ghost::set_position(short i_x, short i_y){
    position = {i_x, i_y};
}