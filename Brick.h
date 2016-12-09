#pragma once
#include "Body.h"
#include "Constants.h"
#include "Ball.h"
#include "PowerUp.h"

class Brick :
	public Body<sf::RectangleShape>
{
private:
	int numHits;
	static const int maxNumHits = 5;
public:
	Brick();
	Brick(sf::Vector2f paramPosition, int paramNumHits);
	void BallCollision(Ball* ball);
	void PowerUpCollision(PowerUp* powerUp);
	bool IsBroken();
	~Brick();
};

