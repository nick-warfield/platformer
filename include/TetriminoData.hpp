#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

const int block_scale = 32;

const sf::Color TETRIMINO_L_COLOR = sf::Color::Red;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_L = {
	sf::Vector2<int>(-1,  0) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 1,  0) * block_scale,
	sf::Vector2<int>( 1,  1) * block_scale
};

const sf::Color TETRIMINO_J_COLOR = sf::Color::White;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_J = {
	sf::Vector2<int>(-1,  0) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 1,  0) * block_scale,
	sf::Vector2<int>(-1, -1) * block_scale
};

const sf::Color TETRIMINO_Z_COLOR = sf::Color::Magenta;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_Z = {
	sf::Vector2<int>(-1,  0) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 0,  1) * block_scale,
	sf::Vector2<int>( 1,  1) * block_scale
};

const sf::Color TETRIMINO_S_COLOR = sf::Color::Green;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_S = {
	sf::Vector2<int>(-1,  1) * block_scale,
	sf::Vector2<int>( 0,  1) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 1,  0) * block_scale
};

const sf::Color TETRIMINO_T_COLOR = sf::Color::Blue;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_T = {
	sf::Vector2<int>(-1,  0) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 1,  0) * block_scale,
	sf::Vector2<int>( 0,  1) * block_scale
};

const sf::Color TETRIMINO_O_COLOR = sf::Color::Yellow;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_O = {
	sf::Vector2<int>(-1,  0) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 0,  1) * block_scale,
	sf::Vector2<int>(-1,  1) * block_scale
};

const sf::Color TETRIMINO_I_COLOR = sf::Color::Cyan;
const std::initializer_list<sf::Vector2<int>> TETRIMINO_I = {
	sf::Vector2<int>(-1,  0) * block_scale,
	sf::Vector2<int>( 0,  0) * block_scale,
	sf::Vector2<int>( 1,  0) * block_scale,
	sf::Vector2<int>( 2,  0) * block_scale
};
