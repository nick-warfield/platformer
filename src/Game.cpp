#include <iostream>
#include <vector>
#include <algorithm>

#include "Game.hpp"

Game make_game() {
	int board_width = 10;
	int board_height = 20;
	sf::Color wall_color = sf::Color(225, 225, 234);

	Game game;
	auto rd = std::random_device();
	game.rng = std::default_random_engine(rd());
	fill_bag(game);

	game.place_position = sf::Vector2(6, 9);
	game.player_tetrimino = game.next_tetriminos.front();
	game.next_tetriminos.pop_front();
	game.player_tetrimino.position = game.place_position;

	game.font.loadFromFile("resources/Pixeboy-z8XGD.ttf");
	game.text.setFont(game.font);
	game.text.setCharacterSize(64);
	game.text.setFillColor(wall_color);

	game.max_height_line.setSize(sf::Vector2f(384, 4));
	game.max_height_line.setPosition(sf::Vector2f(0, 10 * 32));
	wall_color.a = 150;
	game.max_height_line.setFillColor(wall_color);
	wall_color.a = 255;

	// set walls
	for (int i = 1; i < board_height + 10; ++i) {
		game.walls.push_back(
				make_block(wall_color, sf::Vector2i(0, i)));
		game.walls.push_back(
				make_block(wall_color, sf::Vector2i(board_width + 1, i)));
	}

	// set floor
	for (int i = 0; i <= board_width + 1; ++i) {
		game.walls.push_back(
				make_block(wall_color, sf::Vector2i(i, board_height + 10)));
	}

	game.menu = make_menu();

	return game;
}

// collision check, real simple because blocks are
// grid and rotation locked, and all the same size
std::optional<sf::Vector2i> check_collision(const Game& level) {
	for (auto b : level.player_tetrimino.blocks) {
		for (auto w : level.walls) {
			if (w.position == level.player_tetrimino.position + b.position) {
				return std::optional<sf::Vector2i>(w.position);
			}
		}
		for (auto &[_, pb] : level.placed_blocks) {
			for (auto p : pb) {
				if (p.position == 
						level.player_tetrimino.position
						+ b.position) {
					return std::optional<sf::Vector2i>(p.position);
				}
			}
		}
	}
	return std::optional<sf::Vector2i>();
}

bool move_player_tetrimino(Game& level, int x, int y) {
	level.player_tetrimino.position.x += x;
	level.player_tetrimino.position.y += y;

	bool collision = check_collision(level).has_value();
	if (collision) {
		level.player_tetrimino.position.x -= x;
		level.player_tetrimino.position.y -= y;
	}
	return collision;
}

void rotate_player_tetrimino(Game& level, bool is_cw) {
	if (is_cw) { level.player_tetrimino.rotation += 4; }
	else { level.player_tetrimino.rotation -= 4; }

	level.player_tetrimino.rotation = 
		level.player_tetrimino.rotation
		% level.player_tetrimino.block_positions.size();

	for (int i = 0; i < 4; i++) {
		level.player_tetrimino.blocks[i].position
			= level.player_tetrimino.block_positions[i + level.player_tetrimino.rotation];
	}

	auto col = check_collision(level);
	if (col) {
		auto dir = level.player_tetrimino.position - *col;
		move_player_tetrimino(level, dir.x, dir.y);
	}
}

void hold_tetrimino(Game& level) {
	if (!level.held_tetrimino.has_value()) {
		level.held_tetrimino = level.next_tetriminos.front();
		level.next_tetriminos.pop_front();
	}
	std::swap(level.player_tetrimino, *level.held_tetrimino);
	level.player_tetrimino.position = level.held_tetrimino->position;
	level.held_tetrimino->position = sf::Vector2i(15, 21);

	auto col = check_collision(level);
	while (col) {
		auto dir = level.player_tetrimino.position - *col;
		dir.x = std::min( 1, dir.x);
		dir.x = std::max(-1, dir.x);
		dir.y = std::min( 1, dir.y);
		dir.y = std::max(-1, dir.y);
		level.player_tetrimino.position += dir;
		std::cout << dir.x << ", " << dir.y << std::endl;
		col = check_collision(level);
	}
}

void fill_bag(Game& level) {
	std::vector<Tetrimino> bag;
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 0));
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 1));
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 2));
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 3));
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 4));
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 5));
	bag.push_back(make_tetrimino(sf::Vector2i(-10, -10), 6));

	std::shuffle(bag.begin(), bag.end(), level.rng);

	for (auto t : bag) {
		level.next_tetriminos.push_back(t);
	}
}

void place_tetrimino(Game& level) {
	// place blocks
	auto pos = level.player_tetrimino.position;
	for (auto b : level.player_tetrimino.blocks) {
		b.position += pos;
		level.placed_blocks[b.position.y].push_back(b);
	}

	// clear lines
	int lines_cleared = 0;
	for (auto &[_, blocks] : level.placed_blocks) {
		if (blocks.size() >= 10) {
			blocks.clear();
			lines_cleared++;
		}
	}

	// move rows down as needed
	for (auto &[row, blocks] : level.placed_blocks) {
		if (!blocks.empty()) continue;

		for (int next_row = row - 1; next_row > 0; next_row--) {
			for (auto &b : level.placed_blocks[next_row]) {
				b.position.y++;
			}

			std::swap(level.placed_blocks[next_row + 1],
					level.placed_blocks[next_row]);
		}

	}

	// scoring and leveling up
	switch (lines_cleared) {
		case 1: level.score += level.level *  800; break;
		case 2: level.score += level.level * 1200; break;
		case 3: level.score += level.level * 1800; break;
		case 4: level.score += level.level * 2000; break;
	}
	level.lines_cleared += lines_cleared;
	while (level.lines_cleared >= level.level * 5) {
		level.level++;
		if (level.fall_speed > 100.0f) level.fall_speed -= 33.3f;
	}

	// check game over
	bool game_over = false;
	for (auto &[row, blocks] : level.placed_blocks) {
		// inverted y access + an offset for the max height
		if (row < 10 && blocks.size() > 0) { game_over =  true; }
	}

	if (game_over) {
		make_game_over_menu(level.menu);
		return;
	}

	// grab next tetrimino
	level.player_tetrimino = level.next_tetriminos.front();
	level.next_tetriminos.pop_front();
	if (level.next_tetriminos.size() < 7) {
		fill_bag(level);
	}

	sf::Vector2i offset(0, 0);
	for (int i = 13; i > 0; --i) {
		if (!level.placed_blocks[i].empty()) offset.y++;
	}
	level.player_tetrimino.position = level.place_position - offset;

	level.timer.restart();
}

void draw_game(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		Game& level)
{
	window.draw(level.max_height_line);

	for (auto b : level.walls) {
		states.transform = sf::Transform::Identity;
		draw_block(window, states, b);
	}

	for (auto &[_, blocks] : level.placed_blocks) {
		for (auto b : blocks) {
			states.transform = sf::Transform::Identity;
			draw_block(window, states, b);
		}
	}

	level.ghost_tetrimino = level.player_tetrimino;
	for (auto &b : level.ghost_tetrimino.blocks) {
		for (int i = 0; i < 4; ++i) {
			b.verticies[i].color.a = 150;
		}
	}
	while (!move_player_tetrimino(level, 0, 1)) { }
	std::swap(level.player_tetrimino.position,
			level.ghost_tetrimino.position);

	draw_tetrimino(window, states, level.ghost_tetrimino);
	draw_tetrimino(window, states, level.player_tetrimino);

	level.text.setString("Score: " + std::to_string(level.score));
	level.text.setPosition(sf::Vector2f(420, 64));
	window.draw(level.text);

	level.text.setString("Level: " + std::to_string(level.level));
	level.text.setPosition(sf::Vector2f(420, 128));
	window.draw(level.text);

	level.text.setString("Next");
	level.text.setPosition(sf::Vector2f(420, 192));
	window.draw(level.text);

	auto t = level.next_tetriminos.begin();
	for (int i = 0; i < 3; ++i) {
		t->position = sf::Vector2i(15, 9 + 3 * i);
		draw_tetrimino(window, states, *t);
		t++;
	}

	level.text.setString("Hold");
	level.text.setPosition(sf::Vector2f(420, 576));
	window.draw(level.text);
	if (level.held_tetrimino.has_value())
		draw_tetrimino(window, states, *level.held_tetrimino);

	if (level.menu.is_active)
		draw_menu(window, states, level.menu);
}

void update_game(Game& level, std::vector<Input> inputs) {
	if (level.menu.is_active) {
		auto selection = update_menu(level.menu, inputs);
		if (selection == std::nullopt) { return; }
		switch (*selection) {
			case MenuSelection::RESUME:
				level.menu.is_active = false;
				break;

			case MenuSelection::NEW_GAME:
				level.placed_blocks.clear();
				level.score = 0;
				level.level = 1;
				level.lines_cleared = 0;
				level.fall_speed = 1000.0f;
				level.menu.is_active = false;
				level.timer.restart();
				level.next_tetriminos.clear();
				fill_bag(level);
				level.player_tetrimino = level.next_tetriminos.front();
				level.player_tetrimino.position = level.place_position;
				level.next_tetriminos.pop_front();
				level.held_tetrimino = std::nullopt;
				break;

			case MenuSelection::QUIT:
				level.should_quit = true;
				break;
		};

		return;
	}

	if (level.timer.getElapsedTime().asMilliseconds() > level.fall_speed) {
		bool collision = move_player_tetrimino(level, 0, 1);
		level.timer.restart();
		if (collision) place_tetrimino(level);
	}

	if (inputs[Command::LEFT].is_just_pressed) {
		move_player_tetrimino(level, -1, 0);
	}
	if (inputs[Command::RIGHT].is_just_pressed) {
		move_player_tetrimino(level, 1, 0);
	}
	if (inputs[Command::ROTATE_CW].is_just_pressed) {
		rotate_player_tetrimino(level, true);
	}
	if (inputs[Command::ROTATE_CCW].is_just_pressed) {
		rotate_player_tetrimino(level, false);
	}
	if (inputs[Command::HARD_DROP].is_just_pressed) {
		while (!move_player_tetrimino(level, 0, 1)) { }
		place_tetrimino(level);
	}
	if (inputs[Command::SOFT_DROP].is_just_pressed) {
		level.soft_drop_timer.restart();
	}
	if (inputs[Command::SOFT_DROP].is_pressed
			&& level.soft_drop_timer.getElapsedTime().asMilliseconds()
			> level.soft_drop_speed) {
		move_player_tetrimino(level, 0, 1);
		level.soft_drop_timer.restart();
	}
	if (inputs[Command::HOLD].is_just_pressed) {
		hold_tetrimino(level);
	}
	if (inputs[Command::PAUSE].is_just_pressed) {
		make_pause_menu(level.menu);
	}
}
