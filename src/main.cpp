#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "../headers/convert_sketch.hpp"
#include "../headers/draw_text.hpp"
#include "../headers/draw_map.hpp"
#include "../headers/ghost_manager.hpp"
#include "../headers/ghosts.hpp"
#include "../headers/global.hpp"
#include "../headers/map_collision.hpp"
#include "../headers/pacman.hpp"

int score = 0;

int main(){

	bool game_won = 0;
    
    //criando uma janela
    unsigned lag = 0;

    std::chrono::time_point<std::chrono::steady_clock>previous_time;

    std::array<std::string, MAP_HEIGHT> map_sketch = {
        " ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "

    };

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

    sf::Event event;

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "PacMan - THE GAME", sf::Style::Close);
	//Resizing the window.
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	std::array<Position, 4> ghost_positions;

	Pacman pacman;

	GhostManager ghost_manager;

	map = convert_sketch(map_sketch, pacman, ghost_positions);

	ghost_manager.reset(ghost_positions);

    //Get the current time and store it in a variable.
	previous_time = std::chrono::steady_clock::now();

    while(1 == window.isOpen()){
        //Here we're calculating the lag.
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);

		//While the lag exceeds the maximum allowed frame duration.
		while (FRAME_DURATION <= lag)
		{
			//We decrease the lag.
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						//Making sure the player can close the window.
						window.close();
					}
				}
			}

			if (0 == game_won && 0 == pacman.get_dead()){
				game_won = 1;

				pacman.update(map);

				ghost_manager.update(map, pacman);

				for (const std::array<Cell, MAP_HEIGHT>& column : map){
					for (const Cell& cell : column){
						if (Cell::Pellets == cell){
							game_won = 0;
							break;
						}
					}
					if(0 == game_won){
						break;
					}
				}

				if (1 == game_won){
					pacman.set_animation_timer(0);
				}	
			}
			else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Restarting the game.
			{
				game_won = 0;

				if (1 == pacman.get_dead())
				{
					score = 0;
				}

				map = convert_sketch(map_sketch, pacman, ghost_positions);

				ghost_manager.reset(ghost_positions);

				pacman.reset();
			}

			if (FRAME_DURATION > lag){

				window.clear();

				if(0 == game_won && 0 == pacman.get_dead()){
					draw_map(map, window);

					ghost_manager.draw(window);

					draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Score: " + std::to_string(0 + score), window);

				}

				pacman.draw(game_won, window);

				if (1 == pacman.get_animation_over()){
					if(1 == game_won){
						draw_text(1, 0, 0, "Winner!!! :)\n final score: " + std::to_string(0 + score), window);
					}
					else{
						draw_text(1, 0, 0, "you lost :/ \n press enter to restart the game \n\n final score: " + std::to_string(0 + score), window);
					}
				}

				window.display();
				
			}
        }
    }
}