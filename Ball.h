#pragma once
#include "Body.h"
#include "Includes.h"
#include "Helpers.h"

class Ball :
	public Body<sf::CircleShape>
{
private:
	bool frozen;
	double prevSpeed;
	double acceleration; 
	double jerk;
	static const int blurQuality = 6;
	sf::CircleShape blur[blurQuality];
	static const int maxSpeed = 17;
	static const int maxAcceleration = 0.0014;
public:
	Ball();
	void Reset();
	void Freeze();
	void UnFreeze();
	void SetInitialPosition(sf::Vector2f);
	bool Loss();
	void OnFrame(sf::RenderWindow* pWindow);
	~Ball();
};

