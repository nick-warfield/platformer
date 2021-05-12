#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

const sf::Color TETRIMINO_L_COLOR = sf::Color(255, 153, 51);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_L = {
	sf::Vector2<int>(-1,  1),
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 1,  0),

	sf::Vector2<int>(-1, -1),
	sf::Vector2<int>( 0, -1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1),

	sf::Vector2<int>(-1,  1),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 1,  1),
	sf::Vector2<int>( 1,  0),

	sf::Vector2<int>( 0, -1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 1,  1),
};

const sf::Color TETRIMINO_J_COLOR = sf::Color(26, 26, 255);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_J = {
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 1,  0),
	sf::Vector2<int>( 1,  1),

	sf::Vector2<int>(-1,  1),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0, -1),

	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>(-1,  1),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 1,  1),

	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0, -1),
	sf::Vector2<int>( 1, -1),
};

const sf::Color TETRIMINO_Z_COLOR = sf::Color(255, 0, 0);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_Z = {
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 1,  1),

	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 1,  0),
	sf::Vector2<int>( 1, -1),
};

const sf::Color TETRIMINO_S_COLOR = sf::Color(51, 204, 51);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_S = {
	sf::Vector2<int>(-1,  1),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 1,  0),

	sf::Vector2<int>(-1, -1),
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1)
};

const sf::Color TETRIMINO_T_COLOR = sf::Color(204, 0, 255);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_T = {
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 1,  0),
	sf::Vector2<int>( 0,  1),

	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0, -1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1),

	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>(-1,  1),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 1,  1),

	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0, -1),
	sf::Vector2<int>( 1,  0)
};

const sf::Color TETRIMINO_O_COLOR = sf::Color(255, 255, 0);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_O = {
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>(-1,  1)
};

const sf::Color TETRIMINO_I_COLOR = sf::Color(0, 255, 255);
const std::initializer_list<sf::Vector2<int>> TETRIMINO_I = {
	sf::Vector2<int>(-1,  0),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 1,  0),
	sf::Vector2<int>( 2,  0),

	sf::Vector2<int>( 0, -1),
	sf::Vector2<int>( 0,  0),
	sf::Vector2<int>( 0,  1),
	sf::Vector2<int>( 0,  2)
};
