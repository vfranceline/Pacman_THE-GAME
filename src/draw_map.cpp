#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/draw_map.hpp"

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window){

    sf::Sprite sprite;

    sf::Texture texture;
    texture.loadFromFile("../images/map" + std::to_string(CELL_SIZE) + ".png");

    sprite.setTexture(texture);

    // sf::CircleShape circle_shape;
    // circle_shape.setFillColor(sf::Color(205, 171, 235));
    
    // sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
            // cell_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
            switch (i_map[a][b])
            {
                case Cell::Pellets:
                {
                    sprite.setTextureRect(sf::IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                    i_window.draw(sprite);
                    break;
                }

                case Cell::Wall:
                {
                    bool down = 0;
                    bool left = 0;
                    bool right = 0;
                    bool up = 0;

                    if (b < MAP_HEIGHT - 1)
                    {
                        if (Cell::Wall == i_map[a][1 + b])
                        {
                            down = 1;
                        }
                    }

                    //Since we have warp tunnels, we need to draw them as if they're connected.
                    if (0 < a)
                    {
                        if (Cell::Wall == i_map[a - 1][b])
                        {
                            left = 1;
                        }
                    }
                    else
                    {
                        left = 1;
                    }

                    if (a < MAP_WIDTH - 1)
                    {
                        if (Cell::Wall == i_map[1 + a][b])
                        {
                            right = 1;
                        }
                    }
                    else
                    {
                        right = 1;
                    }

                    if (0 < b)
                    {
                        if (Cell::Wall == i_map[a][b - 1])
                        {
                            up = 1;
                        }
                    }

                    //--------------------------------------------<         DISTRIBUTIVE PROPERTY!         >----------------------------
                    sprite.setTextureRect(sf::IntRect(CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CELL_SIZE, CELL_SIZE));

                    i_window.draw(sprite);
                }
            }
        }
    }
}