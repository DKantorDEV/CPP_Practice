#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float mass;
    float radius;
};

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Simulation");
    sf::Clock clock;

    const float GRAVITY = 500.f;
    sf::Vector2f gravity(0.f, GRAVITY);
    float k = 0.01f;

    // Balls Vector
    std::vector<Ball> balls;
    
    // BALL 1
    Ball b1;
    b1.radius = 20.f;
    b1.mass = 1.f;
    b1.position = sf::Vector2f(200.f, 100.f);
    b1.velocity = sf::Vector2f(150.f, 100.f);
    b1.shape = sf::CircleShape(b1.radius);
    b1.shape.setFillColor(sf::Color::White);
    b1.shape.setPosition(b1.position);
    balls.push_back(b1);

    // BALL 2
    Ball b2;
    b2.radius = 30.f;
    b2.mass = 8.f;
    b2.position = sf::Vector2f(500.f, 100.f);
    b2.velocity = sf::Vector2f(-100.f, 80.f);
    b2.shape = sf::CircleShape(b2.radius);
    b2.shape.setFillColor(sf::Color::Red);
    b2.shape.setPosition(b2.position);
    balls.push_back(b2);

    while (window.isOpen()) {

        sf::Event event;
        float dt = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float x = static_cast<float>(event.mouseButton.x);
                    float y = static_cast<float>(event.mouseButton.y);

                    Ball b;
                    b.radius = 15.f;
                    b.mass = 1.f;
                    b.position = sf::Vector2f(x - b.radius, y - b.radius);
                    b.velocity = sf::Vector2f(200.f, -400.f);
                    b.shape = sf::CircleShape(b.radius);
                    b.shape.setFillColor(sf::Color::Green);
                    b.shape.setPosition(b.position);
                    balls.push_back(b);
                }
            }
        }

        for (auto& ball : balls) {
            float speed = sqrt(ball.velocity.x * ball.velocity.x + ball.velocity.y * ball.velocity.y);
            sf::Vector2f direction = ball.velocity / speed;
            float dragMagnitude = k * speed * speed;

            if (speed > 0.f) {
                ball.velocity -= direction * dragMagnitude * dt;
            }

            ball.velocity += gravity * dt;
            ball.position += ball.velocity * dt;
            ball.shape.setPosition(ball.position);

            if (ball.position.x <= 0 || ball.position.x >= 800 - ball.radius * 2) ball.velocity.x *= -1;
            if (ball.position.y <= 0 || ball.position.y >= 600 - ball.radius * 2) ball.velocity.y *= -1;
        }

        window.clear(sf::Color::Black);

        for (auto& ball : balls) {
            window.draw(ball.shape);
        }

        window.display();

    }

    return 0;
}