#pragma once

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Input.hpp"

// Title
// *Resume
// New Game
// Quit

enum MenuSelection {
	RESUME,
	NEW_GAME,
	QUIT
};

struct Menu {
	bool is_active;
	std::vector<MenuSelection> menu_items;
	int selection;

	sf::Font font;
	sf::Color text_color;
	sf::Color background_color;

	sf::Text title;
	sf::Text text;
	sf::RectangleShape selector;
	sf::RectangleShape background;
};

Menu make_menu();
std::optional<MenuSelection> update_menu(Menu& menu, std::vector<Input>);
void draw_menu(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		Menu& menu);
