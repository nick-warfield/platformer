#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Tetrimino.hpp"
#include "Block.hpp"

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
	Game game = make_game();
	sf::RenderStates states = sf::RenderStates::Default;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		// rotate blocks every 3/4th second
		if (timer.getElapsedTime().asSeconds() > 0.75f) {
			timer.restart();
		}

		run(game);

        // Clear screen
        window.clear();

        // Draw the sprite
		for (auto b : game.placed_blocks) {
			states.transform = sf::Transform::Identity;
			draw_block(window, states, b);
		}
		draw_tetrimino(window, states, game.player_tetrimino);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
