#pragma once

#include <vector>
#include <iterator>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "TetriminoData.hpp"

struct Tetrimino {
	sf::Vector2<int> position;
	int rotation;
	std::vector<sf::Vector2<int>> block_positions;
	sf::Sprite blocks[4];
	sf::Color color;
};

void rotate(Tetrimino& tetrimino) {
	tetrimino.rotation += 4;
	tetrimino.rotation = tetrimino.rotation % tetrimino.block_positions.size();

	for (int i = 0; i < 4; i++) {
		tetrimino.blocks[i].setPosition(
				tetrimino.block_positions[i + tetrimino.rotation].x,
				tetrimino.block_positions[i + tetrimino.rotation].y);
	}
}


void draw_tetrimino(const Tetrimino& tetrimino, sf::RenderWindow& window) {
	for (auto b : tetrimino.blocks) {
		b.setPosition(
				b.getPosition().x + tetrimino.position.x,
				b.getPosition().y + tetrimino.position.y);
		window.draw(b);
	}
}

Tetrimino make_tetrimino(sf::Vector2<int> position, int shape) {
	Tetrimino tetrimino;
	tetrimino.position = position;
	tetrimino.rotation = 0;
	tetrimino.color = sf::Color::White;

	switch (shape) {
		case 0:
			tetrimino.color = TETRIMINO_L_COLOR;
			tetrimino.block_positions = TETRIMINO_L;
			break;

		case 1: 
			tetrimino.color = TETRIMINO_J_COLOR;
			tetrimino.block_positions = TETRIMINO_J;
			break;

		case 2: 
			tetrimino.color = TETRIMINO_S_COLOR;
			tetrimino.block_positions = TETRIMINO_S;
			break;

		case 3: 
			tetrimino.color = TETRIMINO_Z_COLOR;
			tetrimino.block_positions = TETRIMINO_Z;
			break;

		case 4: 
			tetrimino.color = TETRIMINO_T_COLOR;
			tetrimino.block_positions = TETRIMINO_T;
			break;

		case 5: 
			tetrimino.color = TETRIMINO_O_COLOR;
			tetrimino.block_positions = TETRIMINO_O;
			break;

		case 6: 
			tetrimino.color = TETRIMINO_I_COLOR;
			tetrimino.block_positions = TETRIMINO_I;
			break;

	}

	// set block texture
	for (int i = 0; i < 4; ++i) {
		sf::Texture t;
		t.loadFromFile("resources/block.png");
		tetrimino.blocks[i].setTexture(t);
		tetrimino.blocks[i].setColor(tetrimino.color);
		tetrimino.blocks[i].setPosition(
				tetrimino.block_positions[i].x,
				tetrimino.block_positions[i].y);
	}

	return tetrimino;
}
Tetrimino make_random(sf::Vector2<int> position) { 
	return make_tetrimino(position, rand() % 7);
}
