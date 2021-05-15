#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Tetrimino.hpp"
#include "Input.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("resources/tetris_theme.ogg")) {
        return EXIT_FAILURE;
	}
	music.setVolume(50);
	music.setLoop(true);
    music.play();

	sf::Clock timer;
	std::vector<Input> command;
	command.resize(11);
	command[Command::LEFT] = make_input(sf::Keyboard::Left);
	command[Command::RIGHT] = make_input(sf::Keyboard::Right);
	command[Command::DOWN] = make_input(sf::Keyboard::Down);
	command[Command::UP] = make_input(sf::Keyboard::Up);
	command[Command::ROTATE_CW] = make_input(sf::Keyboard::Z);
	command[Command::ROTATE_CCW] = make_input(sf::Keyboard::LControl);
	command[Command::HARD_DROP] = make_input(sf::Keyboard::Space);
	command[Command::SOFT_DROP] = make_input(sf::Keyboard::Down);
	command[Command::HOLD] = make_input(sf::Keyboard::C);
	command[Command::PAUSE] = make_input(sf::Keyboard::Escape);
	command[Command::SELECT] = make_input(sf::Keyboard::Enter);

	sf::RenderStates states = sf::RenderStates::Default;
	Game game = make_game();

	// menu font is getting deleted anytime game is accessed
	// this fixes that for some reason
	game.menu.title.setFont(game.font);
	game.menu.text.setFont(game.font);


    // Start the game loop
    while (window.isOpen())
    {
		for (auto &c : command) { update_input(c); }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || game.should_quit)
                window.close();

			for (auto &c : command) { get_input(c, event.key); }
        }

		update_game(game, command);

        window.clear(sf::Color(31, 31, 46));
		draw_game(window, states, game);
        window.display();
    }
    return EXIT_SUCCESS;
}
