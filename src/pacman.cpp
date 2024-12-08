#include <SFML/Graphics.hpp>
#include <array>
#include<cmath>
#include <iostream>

#include "../headers/global.hpp"
#include "../headers/pacman.hpp"
#include "../headers/map_collision.hpp"

Pacman::Pacman():
    direction(0),
    position({0, 0})
{

}

void Pacman::draw(sf::RenderWindow& i_window){
    sf::CircleShape circle(CELL_SIZE /2);
    circle.setFillColor(sf::Color(246, 202, 148));
    circle.setPosition(position.x, position.y);

    i_window.draw(circle);
}

void Pacman::set_position(short i_x, short i_y){
    position = {i_x, i_y};
}

void Pacman::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map){

    std::array<bool, 4> walls{};
	walls[0] = map_collision(0, PACMAN_SPEED + position.x, position.y, i_map);
	walls[1] = map_collision(0, position.x, position.y - PACMAN_SPEED, i_map);
	walls[2] = map_collision(0, position.x - PACMAN_SPEED, position.y, i_map);
	walls[3] = map_collision(0, position.x, PACMAN_SPEED + position.y, i_map);


    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if (0 == walls[3])
		{
			direction = 3;
		}
    }
    else if (1 ==sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if (0 == walls[2])
		{
			direction = 2;
		}
    }
    else if (1 ==sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if (0 == walls[0])
		{
			direction = 0;
		}
    }
    else if (1 ==sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if (0 == walls[1])
		{
			direction = 1;
		}
    }

    if (0 == walls[direction]){
        switch (direction)
        {
            case 0:
                position.x += PACMAN_SPEED;
                break;
            
            case 1:
                position.y -= PACMAN_SPEED;
                break;
            
            case 2:
                position.x -= PACMAN_SPEED;
                break;
            
            case 3:
                position.y += PACMAN_SPEED;
                break;
        }
    }

    if (-CELL_SIZE >= position.x){
		position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	}
	else if (CELL_SIZE * MAP_WIDTH <= position.x){
		position.x = PACMAN_SPEED - CELL_SIZE;
	}

    // Coleta de pellets
    if (map_collision(true, position.x, position.y, i_map)){
        //add lógica para incrementar pontuação aqui.
        std::cout << "Pellet coletado!" << std::endl;
    }
    
}