#pragma once

#include <SFML/Window.hpp>

struct Input {
	sf::Keyboard::Key key;
	bool is_pressed = false;
	bool is_just_pressed = false;
	bool is_released = true;
	bool is_just_released = false;
};

Input make_input(sf::Keyboard::Key key);
void reset(Input& input);
void update_input(Input& input);
void get_input(Input& input, const sf::Event::KeyEvent& key_event);

enum Command {
	LEFT,
	RIGHT,
	ROTATE_CW,
	ROTATE_CCW,
	HARD_DROP,
	HOLD,
	PAUSE,
	SELECT
};
