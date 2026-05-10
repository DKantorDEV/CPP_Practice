#include <SFML/Graphics.hpp>

int main() {

    // Create Window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Physics Sim");

    // While loop to run program so long as the window is open
    while (window.isOpen()) {

        // Declare the event for pollEvent
        sf::Event event;

        // Drain Event Queue
        while (window.pollEvent(event)) {
            // If the type is equal to being closed, then close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    
            // Update simulation state here


            // Clear back buffer
            window.clear(sf::Color::Black);

            // Draw everything


            // Display (swap buffers)
            window.display();

    }

    return 0;

}