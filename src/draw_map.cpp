#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/draw_map.hpp"

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window){

    sf::CircleShape circle_shape;
    circle_shape.setFillColor(sf::Color(205, 171, 235));
    
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (unsigned char i = 0; i < MAP_WIDTH; i++)
	{
		for (unsigned char j = 0; j < MAP_HEIGHT; j++)
		{
            cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
            switch (i_map[i][j])
            {
            case Cell::Pellets:
            {
                circle_shape.setRadius(CELL_SIZE / 8);
                circle_shape.setPosition(CELL_SIZE * i + (CELL_SIZE / 2 - circle_shape.getRadius()), CELL_SIZE * j + (CELL_SIZE / 2 - circle_shape.getRadius())),
                i_window.draw(circle_shape);
                break;
            }

            case Cell::Wall:
            {
                cell_shape.setFillColor(sf::Color(240, 158, 167));
                i_window.draw(cell_shape);
                break;
            }
            }
        }
    }
}