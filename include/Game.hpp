#pragma once

#include <map>
#include <vector>
#include <list>
#include <optional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Block.hpp"
#include "Tetrimino.hpp"
#include "Input.hpp"

struct Game {
	sf::Font font;
	sf::Text text;

	int score = 0;
	int level = 1;
	int lines_cleared = 0;
	float fall_speed = 1000.0f;		// milliseconds
	sf::Clock timer;

	float soft_drop_speed = 75.0f;	// milliseconds
	sf::Clock soft_drop_timer;

	Tetrimino player_tetrimino;
	Tetrimino ghost_tetrimino;
	std::optional<Tetrimino> held_tetrimino;
	std::list<Tetrimino> next_tetriminos;

	sf::RectangleShape max_height_line;
	std::vector<Block> walls;
	// maps row number to the blocks placed in that row
	std::map<int, std::vector<Block>> placed_blocks;
	sf::Vector2<int> place_position;
};

Game make_game();

bool move_player_tetrimino(Game& level, int x, int y);
void rotate_player_tetrimino(Game& level, bool is_cw);
void hold_tetrimino(Game& level);

void fill_bag(Game& level);
void place_tetrimino(Game& level);
std::optional<sf::Vector2i> check_collision(const Game& level);

void update_game(Game& level, std::vector<Input> inputs);
void draw_game(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		Game& level);
