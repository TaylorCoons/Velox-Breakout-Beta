#pragma once
#include "Body.h"
#include "Includes.h"
#include "Helpers.h"
#include "Constants.h"
#include "Ball.h"
#include "PowerUp.h"

class Paddle :
	public Body<sf::RectangleShape>
{
private:
	static const int blurQuality = 8;
	sf::RectangleShape blur[blurQuality];
	sf::Clock clock;
	bool largerPaddle;
	static const int largerPaddleSize = 40;
	static const int largerPaddleTime = 10;
public:
	Paddle();
	void Reset();
	void BallCollision(Ball* ball);
	void OnFrame(sf::RenderWindow* pWindow);
	void LargerPaddle();
	bool PowerUpCollision(PowerUp* powerUp);
	~Paddle();
};


