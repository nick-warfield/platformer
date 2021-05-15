#include "Menu.hpp"
#include <iostream>
#include <algorithm>

Menu make_menu() {
	Menu menu;
	menu.menu_items.push_back(MenuSelection::NEW_GAME);
	menu.menu_items.push_back(MenuSelection::QUIT);
	menu.selection = 0;
	menu.is_active = true;

	if (!menu.font.loadFromFile("resources/Pixeboy-z8XGD.ttf"))
		std::cout << "Failed to load menu font\n";
	else
		std::cout << "Successfully loaded menu font\n";

	menu.text_color = sf::Color(225, 225, 234);
	menu.background_color = sf::Color(31, 31, 46);

	menu.title.setFont(menu.font);
	menu.title.setFillColor(menu.text_color);
	menu.title.setCharacterSize(128);
	menu.title.setStyle(sf::Text::Bold);
	menu.title.setPosition(sf::Vector2f(170, 170));
	menu.title.setString("TETRIS");

	menu.text.setFont(menu.font);
	menu.text.setFillColor(menu.text_color);
	menu.text.setCharacterSize(64);
	menu.text.setPosition(sf::Vector2f(200, 375));
	menu.text.setString("New Game\nQuit");

	menu.background.setFillColor(menu.background_color);
	menu.background.setOutlineColor(menu.text_color);
	menu.background.setOutlineThickness(4);
	menu.background.setSize(sf::Vector2f(600, 900));
	menu.background.setPosition(sf::Vector2f(64, 64));

	menu.selector.setFillColor(menu.text_color);
	menu.selector.setSize(sf::Vector2f(24, 24));
	menu.selector.setPosition(sf::Vector2f(150, 410));

	return menu;
}

void make_pause_menu(Menu& menu) {
	menu.menu_items.clear();
	menu.menu_items.push_back(MenuSelection::RESUME);
	menu.menu_items.push_back(MenuSelection::NEW_GAME);
	menu.menu_items.push_back(MenuSelection::QUIT);
	menu.selection = 0;
	menu.is_active = true;
	menu.title.setString("PAUSE");
	menu.text.setString("Resume\nNew Game\nQuit");
}

void make_game_over_menu(Menu& menu) {
	menu.menu_items.clear();
	menu.menu_items.push_back(MenuSelection::NEW_GAME);
	menu.menu_items.push_back(MenuSelection::QUIT);
	menu.selection = 0;
	menu.is_active = true;
	menu.title.setString("GAME OVER");
	menu.text.setString("New Game\nQuit");
}

std::optional<MenuSelection> update_menu(
		Menu& menu,
		std::vector<Input> inputs)
{
	if (inputs[Command::DOWN].is_just_pressed) {
		menu.selection++;
		menu.selection = std::min(
				menu.selection,
				(int)menu.menu_items.size() - 1);
	}
	if (inputs[Command::UP].is_just_pressed) {
		menu.selection--;
		menu.selection = std::max(menu.selection, 0);
	}
	if (inputs[Command::SELECT].is_just_pressed) {
		return menu.menu_items[menu.selection];
	}

	menu.selector.setPosition(
			sf::Vector2f(150, 410) 
			+ sf::Vector2f(0, menu.selection * 64));
	return std::nullopt;
}

void draw_menu(
		sf::RenderWindow& window,
		sf::RenderStates& states,
		Menu& menu)
{
	if (!menu.is_active) return;

	window.draw(menu.background);
	window.draw(menu.title);
	window.draw(menu.text);
	window.draw(menu.selector);
}
