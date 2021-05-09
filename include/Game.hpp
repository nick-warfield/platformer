#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <optional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Block.hpp"
#include "Tetrimino.hpp"
#include "Input.hpp"

struct Game {
	int score = 0;
	int level = 0;
	int lines_cleared = 0;
	float fall_speed = 1.0f;
	sf::Clock timer;

	Tetrimino player_tetrimino;
	std::optional<Tetrimino> held_tetrimino;
	std::queue<Tetrimino> next_tetriminos;

	std::vector<Block> walls;
	// maps row number to the blocks placed in that row
	std::map<int, std::vector<Block>> placed_blocks;
	sf::Vector2<int> place_position;
};

Game make_game();

bool check_collision(Game& level);

void move_player_tetrimino(Game& level, int x, int y);
void rotate_player_tetrimino(Game& level);

void hold_tetrimino(Game& level);

bool is_game_over(const Game& level);

void fill_bag(Game& level);
void clear_rows(Game& level);
void place_tetrimino(Game& level);

void draw_game(sf::RenderWindow& window, sf::RenderStates& states, Game& level);

void update_game(Game& level, std::vector<Input> inputs);
