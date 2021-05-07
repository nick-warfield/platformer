#pragma once

#include <iostream>
#include <vector>
#include <queue>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Block.hpp"
#include "Tetrimino.hpp"

struct Game {
	int score = 0;
	int level = 0;
	float fall_speed = 1.0f;
	sf::Clock timer;

	Tetrimino player_tetrimino;
	Tetrimino held_tetrimino;
	std::queue<Tetrimino> next_tetriminos;

	std::vector<Block> walls;
	std::vector<Block> placed_blocks;
	sf::Vector2<int> place_position;
};

Game make_game();

bool check_collision(Game& level);

void move_player_tetrimino(Game& level, int x, int y);

Tetrimino hold_tetrimino(Game& level);

bool is_game_over(Game& level);

void generate_tetrimino_batch(Game& level);
void clear_row(Game& level);
void place_tetrimino(Game& level);

void draw_game(sf::RenderWindow& window, sf::RenderStates& states, Game& level);

void run(Game& level);
