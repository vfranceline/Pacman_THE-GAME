#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/draw_map.hpp"

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window){

    sf::CircleShape circle_shape;
    circle_shape.setFillColor(sf::Color(205, 171, 235));
    
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
            cell_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
            switch (i_map[a][b])
            {
                case Cell::Pellets:
                {
                    circle_shape.setRadius(CELL_SIZE / 8);
                    circle_shape.setPosition(CELL_SIZE * a + (CELL_SIZE / 2 - circle_shape.getRadius()), CELL_SIZE * b + (CELL_SIZE / 2 - circle_shape.getRadius())),
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