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

    // body.setColor(sf::Color(240, 158, 167));
    // face.setTextureRect(sf::IntRect(CELL_SIZE * direction, CELL_SIZE, CELL_SIZE, CELL_SIZE));


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
	//modo só os olhos dps do pacman devorar a alma do fantasma
	else
	{
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
    
    // position = home;

}

void Ghost::set_position(short i_x, short i_y){
    position = {i_x, i_y};
}

void Ghost::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman){

    bool move = 0; //o fantasma pode mover?

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

    //verificar se há obstaculo
    walls[0] = map_collision(0, use_door, speed + position.x, position.y, i_map, score);
	walls[1] = map_collision(0, use_door, position.x, position.y - speed, i_map, score);
	walls[2] = map_collision(0, use_door, position.x - speed, position.y, i_map, score);
	walls[3] = map_collision(0, use_door, position.x, speed + position.y, i_map, score);

    // no modo normal e fuga ele vai calcular o melhor caminho para o alvo, seja o pacman ou a casa
    if (1 != frightened_mode){

        unsigned char optimal_direction = 4;

        move = 1;

        for (unsigned char a = 0; a < 4; a++){
            //impede os fantasmas de virarem para tras (só se for necessario)
            if (a == (2 + direction) % 4){
                continue;
            }

            else if (0 == walls[a]){
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
                if (a == (2 + direction) % 4) continue;
                else if(0 == walls[a]) available_ways++;
            }

            //se nao tiver caminho possivel
            if (0 < available_ways){
                while (1 == walls[random_direction] || random_direction == (2 + direction) % 4){
                    random_direction = rand() % 4; //fica pegando direções aleatorias até poder ir para direção
                }

                direction = random_direction;

            }

            else {
                //se não tiver jeito, aí ele pode virar de costas para sair da posição
                direction = (2 + direction) % 4;
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
            target = home_exit; //alvo passa a ser a casa
            score += 200;
        }
    }
}

void Ghost::update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position){

    if (frightened_mode == 2) { 
        // Quando está no modo capturado, ajustar o alvo para casa
        if (position == home_exit) {
            target = home; // Vai para dentro da casa
        } else if (position == home) {
            frightened_mode = 0; // Sai do modo capturado
            use_door = true;     // Permite sair da casa
            target = home_exit;  // Alvo passa a ser a saída
        }
        return; // Não precisa calcular outros alvos
    }

    // Outros modos seguem aqui (normal ou assustado)
    switch (id) {
        case 0: // Blinky (vermelho)
            target = i_pacman_position; // Segue o Pacman
            break;

        case 1: // Pinky (rosa)
            // Direção do Pacman ajustada conforme sua posição
            target = i_pacman_position;
            switch (i_pacman_direction) {
                case 0: target.x += CELL_SIZE * GHOST_1_CHASE; break; // Direita
                case 1: target.y -= CELL_SIZE * GHOST_1_CHASE; break; // Cima
                case 2: target.x -= CELL_SIZE * GHOST_1_CHASE; break; // Esquerda
                case 3: target.y += CELL_SIZE * GHOST_1_CHASE; break; // Baixo
            }
            break;

        case 2: // Inky (azul)
            // Movimento aleatório já tratado
            break;

        case 3: // Clyde (laranja)
            // Se está longe do Pacman, persegue-o, caso contrário, volta ao canto
            if (sqrt(pow(position.x - i_pacman_position.x, 2) + pow(position.y - i_pacman_position.y, 2)) > CELL_SIZE * GHOST_3_CHASE) {
                target = i_pacman_position;
            } else {
                target = {0, CELL_SIZE * (MAP_HEIGHT - 1)}; // Ponto no canto
                if (position == target) target = {0, 0};    // Alterna entre os cantos
            }
            break;
    }
    
}

Position Ghost::get_position(){
    return position;
}