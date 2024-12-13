#include <array>
#include <cmath>

#include "../headers/map_collision.hpp"
#include "../headers/global.hpp"

bool check_and_update_cell(int cell_x, int cell_y, bool i_collect_pellets, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
    if (cell_x >= 0 && cell_x < MAP_WIDTH && cell_y >= 0 && cell_y < MAP_HEIGHT) {
        Cell& cell = i_map[cell_x][cell_y];
        if (cell == Cell::Wall) {
            return true; // colisão detectada
        }
        if (i_collect_pellets && cell == Cell::Pellets) {
            cell = Cell::Empty; // coleta de pellet
        }
    }
    return false; // nenhuma colisão
}

bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) {
    bool output = false;

    float cell_x = i_x / static_cast<float>(CELL_SIZE);
    float cell_y = i_y / static_cast<float>(CELL_SIZE);

    for(unsigned char a = 0; a < 4; a++){
        short x = 0;
        short y = 0;

        switch (a)
        {
            case 0:{
                x = static_cast<short>(floor(cell_x));
                y = static_cast<short>(floor(cell_y));

                break;
            }
                
            case 1:{
                x = static_cast<short>(ceil(cell_x));
                y = static_cast<short>(floor(cell_y));

                break;
            }

            case 2:{
                x = static_cast<short>(floor(cell_x));
                y = static_cast<short>(ceil(cell_y));

                break;
            }

            case 3:{
                x = static_cast<short>(ceil(cell_x));
                y = static_cast<short>(ceil(cell_y));

                break;
            }        
        }

        //Making sure that the position is inside the map.
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
			if (0 == i_collect_pellets) //Here we only care about the walls.
			{
				if (Cell::Wall == i_map[x][y])
				{
					output = 1;
				}
				else if (0 == i_use_door && Cell::Door == i_map[x][y])
				{
					output = 1;
				}
			}
			else //Here we only care about the collectables.
			{
				if (Cell::Energizer == i_map[x][y])
				{
					output = 1;

					i_map[x][y] = Cell::Empty;
				}
				else if (Cell::Pellets == i_map[x][y])
				{
					i_map[x][y] = Cell::Empty;
				}
			}
		}
    }

  

    return output;
}
