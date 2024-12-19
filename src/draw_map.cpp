#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/draw_map.hpp"

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window){

    sf::Sprite sprite;

    sf::Texture texture;
    texture.loadFromFile("../images/Map" + std::to_string(CELL_SIZE) + ".png");

    sprite.setTexture(texture);

    sf::CircleShape circle_shape;
    circle_shape.setFillColor(sf::Color(205, 171, 235));
    
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    sf::RectangleShape door_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/4));

    for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
            sprite.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
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

                case Cell::Door:
				{
                    // door_shape.setFillColor(sf::Color(0,0,255));
                    // i_window.draw(door_shape);
					sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
					i_window.draw(sprite);
					break;
				}
				case Cell::Energizer:
				{
					circle_shape.setRadius(CELL_SIZE / 4);
                    circle_shape.setPosition(CELL_SIZE * a + (CELL_SIZE / 2 - circle_shape.getRadius()), CELL_SIZE * b + (CELL_SIZE / 2 - circle_shape.getRadius())),
                    i_window.draw(circle_shape);
                    break;
                }
            }
        }
    }
}