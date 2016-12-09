#pragma once
#include "Body.h"
#include "FadeText.h"
#include "Includes.h"
#include "Constants.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"

//#include "Helpers.h"

class GameClass
{
private:
    // Game state machine
    enum GAME_STATE {
        INTRO,
        INIT_ROUND,
		RESET_BALL,
        PLAYING,
        LOST,
        WON
    };

    // Round number
    int round;

    GAME_STATE gameState;
    GAME_STATE prevGameState; // Game state
    int frameRate; // Set frame rate
    int prevFrameRate; // Set previous frame rate
	Paddle paddle; // Player player paddle
	bool leftKeyDown;
	bool rightKeyDown;
	std::vector<Ball> balls;
	std::vector<Brick> bricks;
	std::vector<PowerUp> powerUps;

    sf::RenderWindow window; // Create the render window
    
    std::vector<Body<sf::CircleShape>> circles; // Create an array of bodies in the shape of circles

    int frameCounter;

    sf::Clock clock; // Set an sfml clock
    sf::Time prevElapsedTime;
    sf::Clock roundClock;

    sf::Font myFont; // Load font
    sf::Text framesText;

    FadeText updateText; // Create some text that will fade

    sf::Vector2f mouse; // Mouse variable to hold its position when its moved
    bool displayIntro; // Flag to display intro only once

	int lives;

    void Close();

public:
    GameClass();
    bool Init();
    void Run();
    ~GameClass();
};


