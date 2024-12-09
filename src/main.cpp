#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "../headers/convert_sketch.hpp"
#include "../headers/draw_map.hpp"
#include "../headers/global.hpp"
#include "../headers/map_collision.hpp"
#include "../headers/pacman.hpp"
#include "../headers/ghosts.hpp"

int main(){
    
    //criando uma janela
    unsigned lag = 0;

    std::chrono::time_point<std::chrono::steady_clock>previous_time;

    std::array<std::string, MAP_HEIGHT> map_sketch = {
        " ################### ",
		" #        #        # ",
		" # ## ### # ### ## # ",
		" #.................# ",
		" # ## # ##### # ## # ",
		" #    #   #   #    # ",
		" #### ### # ### #### ",
		"    # #       # #    ",
		"##### # ## ## # #####",
		"        # g #        ",
		"##### # ##### # #####",
		"    # #       # #    ",
		" #### # ##### # #### ",
		" #        #        # ",
		" # ## ### # ### ## # ",
		" #  #     P     #  # ",
		" ## # # ##### # # ## ",
		" #    #   #   #    # ",
		" # ###### # ###### # ",
		" #.................# ",
		" ################### "

    };

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

    sf::Event event;

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, CELL_SIZE * MAP_HEIGHT * SCREEN_RESIZE), "PacMan - THE GAME", sf::Style::Close);
	//Resizing the window.
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, CELL_SIZE * MAP_HEIGHT)));

	Pacman pacman;

	Ghost ghost;

	map = convert_sketch(map_sketch, pacman, ghost);

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

			if (FRAME_DURATION > lag){

				window.clear();

				draw_map(map, window);
				pacman.draw(window);
				ghost.draw(window);
				pacman.update(map);
				window.display();
			}
        }
    }
}