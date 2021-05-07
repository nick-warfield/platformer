#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tetrimino.hpp"

struct Game {
	int score = 0;

	float down_timer = 1.0f;

	// rather than bounds, I can use invisible blocks
	int left_bound = 0 * BLOCK_SCALE;
	int right_bound = 10 * BLOCK_SCALE;
	int lower_bound = 0 * BLOCK_SCALE;
	int upper_bound = 20 * BLOCK_SCALE;

	Tetrimino player_tetrimino;
	Tetrimino held_tetrimino;
	std::vector<sf::Sprite> placed_blocks;
};

Game make_game(int board_width = 10, int board_height = 20) {
	Game game;
	sf::Texture t;
	t.loadFromFile("resources/block.png");
	sf::Color wall_color = sf::Color::White;

	// set walls
	for (int i = 1; i < board_height; ++i) {
		sf::Sprite block1(t);
		block1.setColor(wall_color);
		block1.setPosition(0, i * BLOCK_SCALE);

		sf::Sprite block2(t);
		block2.setColor(wall_color);
		block2.setPosition(board_width * BLOCK_SCALE, i * BLOCK_SCALE);

		game.placed_blocks.push_back(block1);
		game.placed_blocks.push_back(block2);
	}

	// set floor and ceiling
	for (int i = 0; i <= board_width; ++i) {
		sf::Sprite block1(t);
		block1.setColor(wall_color);
		block1.setPosition(i * BLOCK_SCALE, 0);

		sf::Sprite block2(t);
		block2.setColor(wall_color);
		block2.setPosition(i * BLOCK_SCALE, board_height * BLOCK_SCALE);

		game.placed_blocks.push_back(block1);
		game.placed_blocks.push_back(block2);
	}

	return game;
}

bool move(Game& level, int x, int y) {
	bool is_collision = false;
	level.player_tetrimino.position.x += x * BLOCK_SCALE;
	level.player_tetrimino.position.y += y * BLOCK_SCALE;

	// collision check, real simple because blocks are
	// grid and rotation locked, and the same size
	for (auto b : level.player_tetrimino.blocks) {
		for (auto p : level.placed_blocks) {
			if (p.getPosition() == b.getPosition()) {
				level.player_tetrimino.position.x -= x * BLOCK_SCALE;
				level.player_tetrimino.position.y -= y * BLOCK_SCALE;
				is_collision = true;
			}
		}
	}

	return is_collision;
}

