#include <vector>
#include <iterator>
#include <memory>


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "TetriminoData.hpp"

struct Block {
	sf::Vector2<int> position;
	std::shared_ptr<sf::Texture> image;
	sf::Color color;
};

struct Tetrimino {
	sf::Vector2<int> position;
	int rotation;
	std::vector<sf::Vector2<int>> block_positions;
	Block blocks[4];
};

void move(Tetrimino& tetrimino, int x, int y) {
	for (auto b : tetrimino.blocks) {
		b.position.x += x;
		b.position.y += y;
	}
}

void rotate(Tetrimino&);
void draw(Tetrimino&);

Tetrimino make_tetrimino(sf::Vector2<int> position, int shape) {
	Tetrimino tetrimino;
	tetrimino.position = position;
	tetrimino.rotation = 0;
	sf::Color color = sf::Color::White;
	std::vector<sf::Vector2<int>> v;

	switch (shape) {
		case 0:
			color = TETRIMINO_L_COLOR;
			TETRIMINO_L;
			break;

		case 1: 
			for (int i = 0; i < 4; ++i) {
				tetrimino.blocks[i].color = TETRIMINO_J_COLOR;
				tetrimino.blocks[i].position = TETRIMINO_J[i];
			}
			break;

		case 2: 
			for (int i = 0; i < 4; ++i) {
				tetrimino.blocks[i].color = TETRIMINO_Z_COLOR;
				tetrimino.blocks[i].position = TETRIMINO_Z[i];
			}
			break;

		case 3: 
			for (int i = 0; i < 4; ++i) {
				tetrimino.blocks[i].color = TETRIMINO_S_COLOR;
				tetrimino.blocks[i].position = TETRIMINO_S[i];
			}
			break;

		case 4: 
			for (int i = 0; i < 4; ++i) {
				tetrimino.blocks[i].color = TETRIMINO_T_COLOR;
				tetrimino.blocks[i].position = TETRIMINO_T[i];
			}
			break;

		case 5: 
			for (int i = 0; i < 4; ++i) {
				tetrimino.blocks[i].color = TETRIMINO_O_COLOR;
				tetrimino.blocks[i].position = TETRIMINO_O[i];
			}
			break;

		case 6: 
			for (int i = 0; i < 4; ++i) {
				tetrimino.blocks[i].color = TETRIMINO_I_COLOR;
				tetrimino.blocks[i].position = TETRIMINO_I[i];
			}
			break;

	}

	// set block texture
	// for (auto b : tetrimino.blocks) {
	// }

	return tetrimino;
}
Tetrimino make_random(sf::Vector2<int> position) { 
	return make_tetrimino(position, rand() % 7);
}
