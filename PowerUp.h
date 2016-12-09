#pragma once
#include "Includes.h"
#include "Body.h"
#include "Helpers.h"

class PowerUp : 
	public Body<sf::CircleShape>
{
public:
	enum TYPE {
		EXTRA_LIFE,
		NEW_BALL,
		LARGER_PADDLE
	};
	
	PowerUp();
	PowerUp(sf::Vector2f pos);
	bool Loss();
	TYPE GetPowerUpType();
	void Reset();
	~PowerUp();
private:
	TYPE type;
	static const int numTypes = 3;
};

