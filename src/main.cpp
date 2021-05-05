#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Tetrimino.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("./resources/block.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("resources/Shapeforms/Dystopia – Ambience and Drone Preview/AUDIO/AMBIENCE_SIGNAL_LOOP.wav"))
        return EXIT_FAILURE;
    music.play();

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
        window.draw(sprite);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
