#include "PowerUp.h"



PowerUp::PowerUp()
{
	Reset();
}

PowerUp::PowerUp(sf::Vector2f pos) {
	Reset();
	SetPosition(pos);
}

void PowerUp::Reset() {
	// Initialize all properties to defaults
	double radius = 10.0;
	//direction = sf::Vector2f(std::cos(0), std::sin(0));
	direction = sf::Vector2f(std::cos(PI / 2.0), std::sin(PI / 2.0));
	//direction = sf::Vector2f(std::cos(PI / 6.0), std::sin(PI / 6.0));
	shape.setFillColor(sf::Color(10, 100, 240));
	dimensions = sf::Vector2f(radius * 2.0, radius * 2.0);
	speed = 4.0f;
	gravityVector = sf::Vector2f(0.0f, 0.0f);
	airFriction = 0.0f;
	density = 1.0f; // Initialize body properties to default
					//SetPosition(sf::Vector2f(WIDTH * 2.0 / 4.0 - dimensions.x / 2.0 + 4.0, HEIGHT * 1.0 / 4.0 - dimensions.y));
					//SetPosition(sf::Vector2f(WIDTH * 3.0 / 4.0 - dimensions.x / 2.0, HEIGHT - dimensions.y - 5.0));
	SetPosition(sf::Vector2f(WIDTH / 2.0 - radius, HEIGHT / 2.0 - radius - 10.0));
	SetGravity(sf::Vector2f(0.0, 0.007));
	shape.setRadius(radius);
	type = static_cast<TYPE>(rand() % numTypes);
	switch (type) {
	case LARGER_PADDLE:
		shape.setFillColor(sf::Color(0, 255, 255));
		break;
	case NEW_BALL:
		shape.setFillColor(sf::Color(0, 255, 0));
		break;
	case EXTRA_LIFE:
		shape.setFillColor(sf::Color(255, 0, 0));
		break;
	}
}

PowerUp::TYPE PowerUp::GetPowerUpType() {
	return type;
}

bool PowerUp::Loss() {
	if (GetPosition().y + dimensions.y > HEIGHT) {
		return true;
	}
	else {
		return false;
	}
}

PowerUp::~PowerUp()
{
}
