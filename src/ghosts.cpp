#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>

#include "../headers/global.hpp"
#include "../headers/pacman.hpp"
#include "../headers/ghosts.hpp"
#include "../headers/map_collision.hpp"

// construtor
Ghost::Ghost(unsigned char i_id): // i_id para saber qual dos ghosts é 
    id(i_id)
{

}

bool Ghost::pacman_collision(const Position& i_pacman_position){
    // verificar se as coordenadas do ghost estao dentro de uma area ao redor da posiçao 
    // do pacman (definida pelo tamanho de uma cell do map)
    if (position.x > i_pacman_position.x - CELL_SIZE && position.x < CELL_SIZE + i_pacman_position.x){
        if (position.y > i_pacman_position.y - CELL_SIZE && position.y < CELL_SIZE + i_pacman_position.y){
            return 1; //true se colidir
        }
    }

    return 0;
}

float Ghost::get_target_distance(unsigned char i_direction){
    // calcular a distancia entre o ghost e o alvo
    short x = position.x;
    short y = position.y;
    
    switch (i_direction)
    {
        case 0:
        {
            x += GHOST_SPEED; //direita
            break;
        }
        case 1:
        {
            y -= GHOST_SPEED; //cima
            break;
        }
        case 2:
        {
            x -= GHOST_SPEED; //esquerda
            break;
        }
        case 3:
        {
            y += GHOST_SPEED; //baixo
            break;
        }
    }

    return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));

}

void Ghost::draw(sf::RenderWindow& i_window){
    // desenhar os fantasmas

    unsigned char body_frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(GHOST_ANIMATION_SPEED)));

    sf::Sprite body;
    sf::Sprite face;

    sf::Texture texture;
    texture.loadFromFile("../images/Ghost" + std::to_string(CELL_SIZE) + ".png");

    body.setTexture(texture);
    body.setPosition(position.x, position.y);

    body.setTextureRect(sf::IntRect(CELL_SIZE * body_frame, 0, CELL_SIZE, CELL_SIZE));

	face.setTexture(texture);
	face.setPosition(position.x, position.y);

    body.setColor(sf::Color(240, 158, 167));
    face.setTextureRect(sf::IntRect(CELL_SIZE * direction, CELL_SIZE, CELL_SIZE, CELL_SIZE));


    // modo normal
    if (0 == frightened_mode)
	{
		switch (id)
		{
			case 0:
			{
				//Blinky
				body.setColor(sf::Color(255, 0, 0));

				break;
			}
			case 1:
			{
				//Pinky
				body.setColor(sf::Color(255, 182, 255));

				break;
			}
			case 2:
			{
				//Inky
				body.setColor(sf::Color(0, 255, 255));

				break;
			}
			case 3:
			{
				//Clyde
				body.setColor(sf::Color(255, 182, 85));
			}
			
		}

		face.setTextureRect(sf::IntRect(CELL_SIZE * direction, CELL_SIZE, CELL_SIZE, CELL_SIZE));

		i_window.draw(body);
	}

    //modo assustado 
	else if (1 == frightened_mode)
	{
		body.setColor(sf::Color(36, 36, 255));
		face.setTextureRect(sf::IntRect(4 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));

		if (0 == body_frame % 2)
		{
			body.setColor(sf::Color(255, 255, 255));
			face.setColor(sf::Color(255, 0, 0));
		}
		else
		{
			body.setColor(sf::Color(36, 36, 255));
			face.setColor(sf::Color(255, 255, 255));
		}

		i_window.draw(body);
	}
	//modo dps do pacman devorar a alma do fantasma
	else
	{
		//We only draw the face because Pacman stole the body.
		face.setTextureRect(sf::IntRect(CELL_SIZE * direction, 2 * CELL_SIZE, CELL_SIZE, CELL_SIZE));
	}

	i_window.draw(face);
    
    //evitar overflow
	animation_timer = (1 + animation_timer) % (GHOST_ANIMATION_FRAMES * GHOST_ANIMATION_SPEED);

}

void Ghost::reset(const Position& i_home, const Position& i_home_exit){
    // redefinir os estados dos fantasmas

    use_door = 0 < id; //todos podem usar a porta, menos o vermelho que já começa do lado de fora

    direction = 0;
    frightened_mode = 0;
    frightened_speed_timer = 0;

    animation_timer = 0;

    home = i_home;
    home_exit = i_home_exit;
    target = i_home_exit;

}

void Ghost::set_position(short i_x, short i_y){
    position = {i_x, i_y};
}

void Ghost::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman){

    bool move = 0; //o fantasma pode mover

    //se for maior doq 1, o fantasma está em uma interseção
    //n considera a volta como um caminho possivel
    unsigned char available_ways = 0;
    unsigned char speed = GHOST_SPEED;

    std::array<bool, 4> walls{}; //declarando array para guardar as info das paredes

    // ajustando quando ele começa e para o modo assustado

    //se ele estiver normal e o pacman comer um energizer
    if (0 == frightened_mode && i_pacman.get_energizer_timer() == ENERGIZER_DURATION){
        frightened_speed_timer = GHOST_FRIGHTENED_SPEED;
        frightened_mode = 1; // está no modo assustado
    }
    else if (0 == i_pacman.get_energizer_timer() && 1 == frightened_mode){
        frightened_mode = 0;
    }

    //se o fantasma está fugindo para a "casa" (modo 2), ajusta sua velocidade
	if (2 == frightened_mode && 0 == position.x % GHOST_ESCAPE_SPEED && 0 == position.y % GHOST_ESCAPE_SPEED)
	{
		speed = GHOST_ESCAPE_SPEED;
	}

    update_target(i_pacman.get_direction(), i_ghost_0.get_position(), i_pacman.get_position());

// tem q mudar a função map_collision
    //verificar se há obstaculo
    walls[0] = map_collision(0, use_door, speed + position.x, position.y, i_map);
	walls[1] = map_collision(0, use_door, position.x, position.y - speed, i_map);
	walls[2] = map_collision(0, use_door, position.x - speed, position.y, i_map);
	walls[3] = map_collision(0, use_door, position.x, speed + position.y, i_map);

    // no modo normal e fuga ele vai calcular o melhor caminho para o alvo, seja o pacman ou a casa
    if (1 != frightened_mode){

        unsigned char optimal_direction = 4;

        move = 1;

        for (unsigned char a = 0; a < 4; a++){
            if (0 == walls[a]){
                if (4 == optimal_direction){
                    //direção otima é a mais perto do alvo
                    optimal_direction = a;
                }

                available_ways++;
                if (get_target_distance(a) < get_target_distance(optimal_direction)){
                    optimal_direction = a;
                }
            }
        }

        if (1 < available_ways){
            //se o fantasma estiver em uma interseção (mais de 1 caminho possivel), vai escolher a melhor direção
            direction = optimal_direction;
        }
        else{

            if(4 == optimal_direction) direction = (2 + direction) % 4;
            else direction = optimal_direction;
        }
    }

    // no modo assustado ele vai andar aleatoriamente
    else {
        unsigned char random_direction = rand() % 4;

        if (0 == frightened_speed_timer){
            //mover o fantasma dps de x numeros de frames
            move = 1;

            frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

            for(unsigned char a = 0; a < 4; a++){
                if(0 == walls[a]) available_ways++;
            }

            //se nao tiver caminho possivel
            if (0 < available_ways){
                while (1 == walls[random_direction]){
                    random_direction = rand() % 4; //fica pegando direções aleatorias até poder ir para direção
                }

                direction = random_direction;

            }
        }

        else {
            frightened_speed_timer--;
        }

    }

    //pode mover o fantasma
    if (1 == move){
        switch (direction)
        {
            case 0:
                position.x += speed;
                break;
            
            case 1:
                position.y -= speed;
                break;
            
            case 2:
                position.x -= speed;
                break;
            
            case 3:
                position.y += speed;
        }

        //logica de entrar por um lado e sair do outro do mapa
        if (-CELL_SIZE >= position.x){
		position.x = CELL_SIZE * MAP_WIDTH - speed;
        }
        else if (CELL_SIZE * MAP_WIDTH <= position.x){
            position.x = speed - CELL_SIZE;
        }
    }

    //checar quando colidir com o pacman
    if (1 == pacman_collision(i_pacman.get_position())){

        //se o fantasma tava no modo normal, o pacman morre
        if (0 == frightened_mode) {
            i_pacman.set_dead(1);
        }
        //caso não, o fantasma entra no modo fuga (volta pra casa)
        else {
            use_door = 1; //habilita o uso da porta
            frightened_mode = 2; //ativa o modo fuga
            target = home; //alvo passa a ser a casa
        }
    }
}

void Ghost::update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position){
    
    //se o fantasma pode usar a porta 
    //apenas no modo fuga, dps do pacman comer ele
    //ou quando ele precisa sair da casa
    if (1 == use_door){
        if (position == target){
            //se o objetivo dele era passar pela porta
            if (home_exit == target){
                use_door = 0; //ele não pode mais usar a porta
            }
            //se o objetivo dele era voltar pra casa (dps do pacman comer ele)
            else if (home == target){
                frightened_mode = 0; //volta para o normal

                target = home_exit; //objetivo passa a ser sair da casa
            }
        }
    }

    //enquanto ele estiver no modo normal e assustado 
    else{
        switch (id)
        {
            case 0: //blinky (vermelho)
                target = i_pacman_position; //vai seguir o pacman
                break;
            
            case 1: //pinky (rosa)
            {
                target = i_pacman_position;

                switch (i_pacman_direction){
                    case 0:
                    {
                        target.x += CELL_SIZE * GHOST_1_CHASE;
                        break;
                    }
                    case 1:
                    {
                        target.y -= CELL_SIZE * GHOST_1_CHASE;
                        break;
                    }
                    case 2:
                    {
                        target.x -= CELL_SIZE * GHOST_1_CHASE;
                        break;
                    }
                    case 3:
                    {
                        target.y += CELL_SIZE * GHOST_1_CHASE;
                    }
                }

                break;
            }

            case 2: // inky (azul)
                break; //ele vai estar sempre aleatorio

            case 3: //clyde (laranja)
            {
                if (CELL_SIZE * GHOST_3_CHASE <= sqrt(pow(position.x - i_pacman_position.x, 2) + pow(position.y - i_pacman_position.y, 2))){
                    target = i_pacman_position;
                }
                else{
                    target = {0, CELL_SIZE * (MAP_HEIGHT - 1)};
                }
            }
        }
    }
}

Position Ghost::get_position(){
    return position;
}