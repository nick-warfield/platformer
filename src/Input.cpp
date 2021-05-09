#include "Input.hpp"

Input make_input(sf::Keyboard::Key key) {
	Input i;
	i.key = key;
	return i;
}

void update_input(Input& input) {
	input.is_just_pressed = false;
	input.is_just_released = false;
}

void get_input(Input& input, const sf::Event::KeyEvent& key_event) {
	if (key_event.code != input.key) { return; }

	if (sf::Keyboard::isKeyPressed(input.key)) {
		input.is_just_pressed = !input.is_pressed;
		input.is_pressed = true;
		input.is_just_released = false;
		input.is_released = false;
	}
	else {
		input.is_just_pressed = false;
		input.is_pressed = false;
		input.is_just_released = !input.is_released;
		input.is_released = true;
	}
}

