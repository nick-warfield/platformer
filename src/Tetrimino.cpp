#include "Tetrimino.hpp"

void rotate(Tetrimino& tetrimino) {
	tetrimino.rotation += 4;
	tetrimino.rotation = tetrimino.rotation % tetrimino.block_positions.size();

	for (int i = 0; i < 4; i++) {
		tetrimino.blocks[i].position
			= tetrimino.block_positions[i + tetrimino.rotation];
	}
}


void draw_tetrimino(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		const Tetrimino& tetrimino) {
	for (auto b : tetrimino.blocks) {
		sf::Transform trans;
		trans.translate((sf::Vector2f)(tetrimino.position * PIXELS_PER_BLOCK));
		states.transform = trans;
		draw_block(window, states, b);
	}
}

Tetrimino make_tetrimino(sf::Vector2<int> position, int shape) {
	Tetrimino tetrimino;
	tetrimino.position = position;
	tetrimino.rotation = 0;
	sf::Color color = sf::Color::White;

	switch (shape) {
		case 0:
			color = TETRIMINO_L_COLOR;
			tetrimino.block_positions = TETRIMINO_L;
			break;

		case 1: 
			color = TETRIMINO_J_COLOR;
			tetrimino.block_positions = TETRIMINO_J;
			break;

		case 2: 
			color = TETRIMINO_S_COLOR;
			tetrimino.block_positions = TETRIMINO_S;
			break;

		case 3: 
			color = TETRIMINO_Z_COLOR;
			tetrimino.block_positions = TETRIMINO_Z;
			break;

		case 4: 
			color = TETRIMINO_T_COLOR;
			tetrimino.block_positions = TETRIMINO_T;
			break;

		case 5: 
			color = TETRIMINO_O_COLOR;
			tetrimino.block_positions = TETRIMINO_O;
			break;

		case 6: 
			color = TETRIMINO_I_COLOR;
			tetrimino.block_positions = TETRIMINO_I;
			break;

	}

	for (int i = 0; i < 4; ++i) {
		tetrimino.blocks[i] = make_block(color, tetrimino.block_positions[i]);
	}

	return tetrimino;
}
Tetrimino make_random(sf::Vector2<int> position) { 
	return make_tetrimino(position, rand() % 7);
}
