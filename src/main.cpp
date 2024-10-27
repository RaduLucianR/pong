#include <SFML/Graphics.hpp>

int main()
{   
    auto width = 1080u;
    auto height = 720u;
    auto window = sf::RenderWindow({width, height}, "Pong");
    window.setFramerateLimit(144);

    sf::Vector2f ball_velocity(1, 0.4);

    sf::RectangleShape player1(sf::Vector2f(20.f, 60.f));
    player1.setPosition(sf::Vector2f(width / 4, height / 2));
    player1.setFillColor(sf::Color(255, 255, 255));

    sf::RectangleShape player2(sf::Vector2f(20.f, 60.f));
    player2.setPosition(sf::Vector2f(3 * width / 4, height / 2));
    player2.setFillColor(sf::Color(255, 255, 255));

    sf::RectangleShape ball(sf::Vector2f(10.f, 10.f));
    ball.setPosition(sf::Vector2f(width / 2, height / 2));
    ball.setFillColor(sf::Color(255, 255, 255));

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player1.move(0, -3);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player1.move(0, 3);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player2.move(0, -3);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player2.move(0, 3);
        }

        if (player1.getGlobalBounds().intersects(ball.getGlobalBounds()) ||
            player2.getGlobalBounds().intersects(ball.getGlobalBounds())
        )
        {
            ball_velocity.x = ball_velocity.x * (-1);
            ball_velocity.y = ball_velocity.y * (-1);
        }

        ball.move(ball_velocity);

        window.clear();

        window.draw(player1);
        window.draw(player2);
        window.draw(ball);

        window.display();
    }
}