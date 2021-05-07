#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

const int PIXELS_PER_BLOCK = 32;

struct Block {
	sf::Vector2<int> position;

	// these can be shared by all blocks
	sf::Texture texture;
	sf::Vertex verticies[4];
};

Block make_block(
		sf::Color color,
		sf::Vector2<int> position = sf::Vector2<int>(0, 0));

// requires state transform to be set beforehand
void draw_block(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		const Block& block);
