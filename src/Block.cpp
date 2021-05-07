#include "Block.hpp"

Block make_block(
		sf::Color color,
		sf::Vector2<int> position) {
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
