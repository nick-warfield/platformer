#pragma once

#include <vector>
#include <queue>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Tetrimino.hpp"

struct Game {
	int score = 0;
	int level = 0;
	float fall_speed = 1.0f;

	Tetrimino player_tetrimino;
	Tetrimino held_tetrimino;
	std::queue<Tetrimino> next_tetriminos;

	std::vector<sf::Sprite> placed_blocks;
	sf::Vector2<int> place_position;
};

Game make_game(int board_width = 10, int board_height = 20) {
	Game game;
	game.place_position = sf::Vector2(board_width / 2, board_height / 2);
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

// collision check, real simple because blocks are
// grid and rotation locked, and the same size
bool check_collision(Game& level) {
	bool is_collision = false;;
	for (auto b : level.player_tetrimino.blocks) {
		for (auto p : level.placed_blocks) {
			if (p.getPosition() == b.getPosition()) {
				is_collision = true;
			}
		}
	}
	return is_collision;
}

void move_player_tetrimino(Game& level, int x, int y) {
	level.player_tetrimino.position.x += x * BLOCK_SCALE;
	level.player_tetrimino.position.y += y * BLOCK_SCALE;

	if (check_collision(level)) {
		level.player_tetrimino.position.x -= x * BLOCK_SCALE;
		level.player_tetrimino.position.y -= y * BLOCK_SCALE;
	}
}

// swaps the player and held tetrimno
// needs to do a check for when there is nothing held
Tetrimino hold_tetrimino(Game& level);

// returns true if a placed block is at the top
bool is_game_over(Game& level);

// pseudo random tetrimino generation
// shuffles one of each block, and puts them in the queue
void generate_tetrimino_batch(Game& level);
void place_tetrimino(Game& level);
