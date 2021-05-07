#include "Game.hpp"


Game make_game() {
	int board_width = 10;
	int board_height = 20;
	sf::Color wall_color = sf::Color::White;

	Game game;
	game.place_position = sf::Vector2(board_width / 2, 9);
	game.player_tetrimino = make_random(game.place_position);

	// set walls
	for (int i = 1; i < board_height + 10; ++i) {
		game.walls.push_back(
				make_block(wall_color, sf::Vector2i(0, i)));
		game.walls.push_back(
				make_block(wall_color, sf::Vector2i(board_width, i)));
	}

	// set floor
	for (int i = 0; i <= board_width; ++i) {
		game.walls.push_back(
				make_block(wall_color, sf::Vector2i(i, board_height + 10)));
	}

	return game;
}

// collision check, real simple because blocks are
// grid and rotation locked, and the same size
bool check_collision(Game& level) {
	bool is_collision = false;;
	for (auto b : level.player_tetrimino.blocks) {
		for (auto p : level.walls) {
			if (p.position == level.player_tetrimino.position + b.position) {
				is_collision = true;
			}
		}
		for (auto p : level.placed_blocks) {
			if (p.position == level.player_tetrimino.position + b.position) {
				is_collision = true;
			}
		}
	}
	return is_collision;
}

void move_player_tetrimino(Game& level, int x, int y) {
	level.player_tetrimino.position.x += x;
	level.player_tetrimino.position.y += y;

	if (check_collision(level)) {
		level.player_tetrimino.position.x -= x;
		level.player_tetrimino.position.y -= y;
	}
}

// swaps the player and held tetrimno
// needs to do a check for when there is nothing held
Tetrimino hold_tetrimino(Game& level);

// returns true if a placed block over 20 blocks in height
bool is_game_over(Game& level);

// pseudo random tetrimino generation
// shuffles one of each block, and puts them in the queue
void generate_tetrimino_batch(Game& level);
void clear_row(Game& level);
void place_tetrimino(Game& level);

void draw_game(sf::RenderWindow& window, sf::RenderStates& states, Game& level) {
	for (auto b : level.walls) {
		states.transform = sf::Transform::Identity;
		draw_block(window, states, b);
	}
	for (auto b : level.placed_blocks) {
		states.transform = sf::Transform::Identity;
		draw_block(window, states, b);
	}
	draw_tetrimino(window, states, level.player_tetrimino);
}

void run(Game& level) {
	if (level.timer.getElapsedTime().asSeconds() > level.fall_speed) {
		move_player_tetrimino(level, 0, 1);
		level.timer.restart();
	}
}
