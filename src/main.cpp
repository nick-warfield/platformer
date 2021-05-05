#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Tetrimino.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");

    // Load a sprite to display
//    sf::Texture texture;
//    if (!texture.loadFromFile("./resources/block.png"))
//        return EXIT_FAILURE;
//    sf::Sprite sprite(texture);

    // Load a music to play
//    sf::Music music;
//    if (!music.openFromFile("resources/Shapeforms/Dystopia – Ambience and Drone Preview/AUDIO/AMBIENCE_SIGNAL_LOOP.wav"))
//        return EXIT_FAILURE;
//    music.play();

	std::vector<Tetrimino> tetri;
	tetri.push_back(make_tetrimino(sf::Vector2<int>(400, 300), 0));
	tetri.push_back(make_tetrimino(sf::Vector2<int>(800, 300), 1));
	tetri.push_back(make_tetrimino(sf::Vector2<int>(1200, 300), 2));
	tetri.push_back(make_tetrimino(sf::Vector2<int>(300, 600), 3));
	tetri.push_back(make_tetrimino(sf::Vector2<int>(600, 600), 4));
	tetri.push_back(make_tetrimino(sf::Vector2<int>(900, 600), 5));
	tetri.push_back(make_tetrimino(sf::Vector2<int>(1200, 600), 6));

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
        // Clear screen
        window.clear();
        // Draw the sprite
		for (auto t : tetri) { draw_tetrimino(t, window); }
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
