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
		sf::Vector2<int> position = sf::Vector2<int>(0, 0)) {
	Block b;
	b.position = position;
	sf::Texture t;
	t.loadFromFile("resources/block.png");
	b.verticies[0] = sf::Vertex(
			sf::Vector2f(0, 0),
			color,
			sf::Vector2f(0, 0));
	b.verticies[1] = sf::Vertex(
			sf::Vector2f(0, PIXELS_PER_BLOCK),
			color,
			sf::Vector2f(0, PIXELS_PER_BLOCK));
	b.verticies[2] = sf::Vertex(
			sf::Vector2f(PIXELS_PER_BLOCK, PIXELS_PER_BLOCK),
			color,
			sf::Vector2f(PIXELS_PER_BLOCK, PIXELS_PER_BLOCK));
	b.verticies[3] = sf::Vertex(
			sf::Vector2f(PIXELS_PER_BLOCK, 0),
			color,
			sf::Vector2f(PIXELS_PER_BLOCK, 0));

	return b;
}

// requires state transform to be set beforehand
void draw_block(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		const Block& block) {
	states.texture = &block.texture;
	states.transform.translate((sf::Vector2f)(block.position * PIXELS_PER_BLOCK));
	window.draw(block.verticies, 4, sf::Quads, states);
}
