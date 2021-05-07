#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <memory>

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

void rotate(Tetrimino& tetrimino);


void draw_tetrimino(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		const Tetrimino& tetrimino);

Tetrimino make_tetrimino(sf::Vector2<int> position, int shape);
Tetrimino make_random(sf::Vector2<int> position);
