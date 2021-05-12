#pragma once

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "TetriminoData.hpp"
#include "Block.hpp"

struct Tetrimino {
	sf::Vector2<int> position;
	int rotation;
	std::vector<sf::Vector2<int>> block_positions;
	Block blocks[4];
};

Tetrimino make_tetrimino(sf::Vector2<int> position, int shape);

void draw_tetrimino(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		const Tetrimino& tetrimino);
