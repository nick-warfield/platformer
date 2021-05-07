#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Tetrimino.hpp"
#include "Block.hpp"

int counter = 0;

struct Input {
	sf::Keyboard::Key key;
	bool is_pressed = false;
	bool is_just_pressed = false;
	bool is_released = true;
	bool is_just_released = false;
};
void reset(Input& input) {
	input.is_just_pressed = false;
	input.is_just_released = false;
}
void update_input(Input& input, const sf::Event::KeyEvent& key_event) {
	if (key_event.code != input.key) { return; }
	reset(input);

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

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");

    // Load a music to play
//    sf::Music music;
//    if (!music.openFromFile("resources/Shapeforms/Dystopia – Ambience and Drone Preview/AUDIO/AMBIENCE_SIGNAL_LOOP.wav"))
//        return EXIT_FAILURE;
//    music.play();

	sf::Clock timer;
	Input command_left, command_right, command_rotate;
	command_left.key = sf::Keyboard::Left;
	command_right.key = sf::Keyboard::Right;
	command_rotate.key = sf::Keyboard::Space;

	Game game = make_game();
	sf::RenderStates states = sf::RenderStates::Default;

    // Start the game loop
    while (window.isOpen())
    {
		counter++;
        // Process events
		reset(command_left);
		reset(command_right);
		reset(command_rotate);

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed
					|| event.key.code == sf::Keyboard::Escape)
                window.close();

			update_input(command_left, event.key);
			update_input(command_right, event.key);
			update_input(command_rotate, event.key);
        }

		if (command_left.is_just_pressed)
			move_player_tetrimino(game, -1, 0);
		if (command_right.is_just_pressed)
			move_player_tetrimino(game, 1, 0);
		if (command_rotate.is_just_pressed)
			rotate(game.player_tetrimino);

		run(game);

        // Clear screen
        window.clear();

		draw_game(window, states, game);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
