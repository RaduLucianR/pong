#include <SFML/Graphics.hpp>
#include <math.h> 
#include <iostream>
#include <string>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

float vlen(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float dot(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float rand_float(float lo, float hi)
{
    int minus = rand() % 2;
    int sign = minus ? (-1) : 1;
    float r = lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi - lo)));
    return sign * r;
}

sf::Vector2f rand_ball_vel()
{
    return sf::Vector2f(rand_float(2.0, 3.0), rand_float(0.3, 2.3));
}

int main()
{   
    sf::Font font;

    if (!font.loadFromFile(FONT_PATH))
    {
        std::cout << "Cannot load Pong font!" << std::endl;
        return EXIT_FAILURE;
    }

    srand(time(0));

    auto width = 1080u;
    auto height = 720u;
    auto window = sf::RenderWindow({width, height}, "Pong");

    float init_p1_x = (width / 2) / 3;
    float init_p2_x = (width / 2) * 5 / 3;
    float init_player_y = height / 2;
    float dash_height = 15;
    float dash_space = 12;
    int nrof_dashes = (int) height / (dash_height + dash_space);
    sf::Vector2f init_ball_pos(width / 2, height / 2);
    sf::Vector2f init_ball_vel(rand_ball_vel());
    sf::Vector2f ball_velocity = init_ball_vel;
    sf::Vector2f playerSize(10.f, 40.f);
    sf::Vector2f player1Pos(init_p1_x, init_player_y);
    sf::Vector2f player2Pos(init_p2_x, init_player_y);
    sf::Vector2f player1Vel(0, 3);
    sf::Vector2f player2Vel(0, 3);
    sf::RectangleShape player1(playerSize);
    sf::RectangleShape player2(playerSize);
    sf::RectangleShape ball(sf::Vector2f(10.f, 10.f));
    sf::RectangleShape dash(sf::Vector2f(5.f, dash_height));
    sf::Text scorePlayer1;
    sf::Text scorePlayer2;
    int score1 = 0;
    int score2 = 0;

    window.setFramerateLimit(144);

    scorePlayer1.setFont(font);
    scorePlayer1.setString(std::to_string(score1));
    scorePlayer1.setFillColor(sf::Color::White);
    scorePlayer1.setPosition(width / 4, 0.05 * height);
    scorePlayer1.setCharacterSize(90);

    scorePlayer2.setFont(font);
    scorePlayer2.setString(std::to_string(score2));
    scorePlayer2.setFillColor(sf::Color::White);
    scorePlayer2.setPosition(3 * width / 4, 0.05 * height);
    scorePlayer2.setCharacterSize(90);

    player1.setPosition(player1Pos);
    player1.setFillColor(sf::Color::White);

    player2.setPosition(player2Pos);
    player2.setFillColor(sf::Color::White);

    ball.setPosition(sf::Vector2f(width / 2, height / 2));
    ball.setFillColor(sf::Color::White);

    dash.setFillColor(sf::Color::White);

    sf::Vector2f curr_ball_pos = ball.getPosition();
    sf::Vector2f curr_p1_pos = player1.getPosition();
    sf::Vector2f curr_p2_pos = player2.getPosition();
    sf::Vector2u curr_window_size = window.getSize();
    sf::FloatRect player1Bounds = player1.getGlobalBounds();
    sf::FloatRect player2Bounds = player2.getGlobalBounds();
    sf::FloatRect ballBounds = ball.getGlobalBounds();
    float player1Bottom = player1Bounds.top + player1Bounds.height;
    float player2Bottom = player2Bounds.top + player2Bounds.height;
    float ballBottom = ballBounds.top + ballBounds.height;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        curr_ball_pos = ball.getPosition();
        curr_window_size = window.getSize();
        player1Bounds = player1.getGlobalBounds();
        player2Bounds = player2.getGlobalBounds();
        ballBounds = ball.getGlobalBounds();
        player1Bottom = player1Bounds.top + player1Bounds.height;
        player2Bottom = player2Bounds.top + player2Bounds.height;
        ballBottom = ballBounds.top + ballBounds.height;
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (player1Bounds.top > 0)
            {
                player1Vel.y = -3;
                player1.move(player1Vel);
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player1Bottom = player1Bounds.top + player1Bounds.height;

            if (player1Bottom < curr_window_size.y)
            {
                player1Vel.y = 3;
                player1.move(player1Vel);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (player2Bounds.top > 0)
            {
                player2Vel.y = -3;
                player2.move(player2Vel);
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player2Bottom = player2Bounds.top + player2Bounds.height;

            if (player2Bottom < curr_window_size.y)
            {
                player2Vel.y = 3;
                player2.move(player2Vel);
            }
        }

        if (player1Bounds.intersects(ballBounds))
        {
            ball_velocity.x *= -1.1;
        }

        if (player2Bounds.intersects(ballBounds))
        {
            ball_velocity.x *= -1.1;
        }

        // Round is over, Player 2 wins
        if (curr_ball_pos.x < 0)
        {   
            player1.setPosition(init_p1_x, init_player_y);
            player2.setPosition(init_p2_x, init_player_y);
            ball.setPosition(init_ball_pos);
            ball_velocity = rand_ball_vel();
            score2 += 1;
            scorePlayer2.setString(std::to_string(score2));
        }

        // Round is over, Player 1 wins
        if (curr_ball_pos.x > (float) curr_window_size.x)
        {
            player1.setPosition(init_p1_x, init_player_y);
            player2.setPosition(init_p2_x, init_player_y);
            ball.setPosition(init_ball_pos);
            ball_velocity = rand_ball_vel();
            score1 += 1;
            scorePlayer1.setString(std::to_string(score1));
        }

        // Bounce off window top or bottom
        if (curr_ball_pos.y < 0 || 
            ballBottom > (float) curr_window_size.y
        )
        {
            ball_velocity.y *= -1;
        }

        ball.move(ball_velocity);
        
        // Drawing section
        window.clear();
        
        for (int i = 1; i < nrof_dashes - 1; i ++)
        {
            dash.setPosition(width / 2, i * (dash_height + dash_space));
            window.draw(dash);
        }

        window.draw(scorePlayer1);
        window.draw(scorePlayer2);
        window.draw(player1);
        window.draw(player2);
        window.draw(ball);

        window.display();
    }

    return EXIT_SUCCESS;
}