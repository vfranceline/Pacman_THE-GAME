#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/draw_map.hpp"

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window){
    
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (unsigned char i = 0; i < MAP_WIDTH; i++)
	{
		for (unsigned char j = 0; j < MAP_HEIGHT; j++)
		{
            cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
            switch (i_map[i][j])
            {
            case Cell::Wall:
                cell_shape.setFillColor(sf::Color(240, 158, 167));
                i_window.draw(cell_shape);
            }
        }
    }
}