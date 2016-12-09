#include "Brick.h"



Brick::Brick() {
	// Initialize all properties to defaults
	direction = sf::Vector2f(0.0f, 0.0f);
	shape.setFillColor(sf::Color(255, 255, 255));
	dimensions = sf::Vector2f(60.0f, 20.0f);
	speed = 0.0f;
	gravityVector = sf::Vector2f(0.0f, 0.0f);
	airFriction = 0.0f;
	density = 1.0f; // Initialize body properties to default
	SetPosition(sf::Vector2f(WIDTH / 2.0 - dimensions.x / 2.0, HEIGHT / 2.0 - dimensions.y / 2.0));
	//SetPosition(sf::Vector2f(WIDTH / 2.0, HEIGHT / 2.0));
	shape.setSize(dimensions);
	numHits = 1;
}

Brick::Brick(sf::Vector2f paramPosition, int paramNumHits) {
	if (paramNumHits <= maxNumHits && paramNumHits > 0) {
		numHits = paramNumHits;
	}
	else if (paramNumHits > maxNumHits) {
		numHits = maxNumHits;
	}
	else if (paramNumHits <= 0) {
		numHits = 1;
	}
	// Initialize all properties to defaults
	direction = sf::Vector2f(0.0f, 0.0f);
	int colorChannel = hf::Map(1, maxNumHits, 0, 255, numHits);
	shape.setFillColor(sf::Color(colorChannel, 0, 255 - colorChannel));
	dimensions = sf::Vector2f(60.0f, 15.0f);
	speed = 0.0f;
	gravityVector = sf::Vector2f(0.0f, 0.0f);
	airFriction = 0.0f;
	density = 1.0f; // Initialize body properties to default
	SetPosition(paramPosition);
	//SetPosition(sf::Vector2f(WIDTH / 2.0, HEIGHT / 2.0));
	shape.setSize(dimensions);
}

void Brick::BallCollision(Ball* ball) {
	sf::Vector2f ballDim = ball->GetDimensions();
	float ballSpeed = ball->GetSpeed();
	sf::Vector2f ballDir = ball->GetDirection();
	sf::Vector2f ballPos = ball->GetPosition();
	sf::Vector2f brickPos = GetPosition();

	if (ballPos.x < dimensions.x + brickPos.x && ballPos.x + ballDim.x > brickPos.x && ballPos.y + ballDim.y > brickPos.y && ballPos.y < brickPos.y + dimensions.y) {
		if ((std::abs(ballPos.y + ballDim.y - brickPos.y) < std::abs(ballPos.x + ballDim.x - brickPos.x) && std::abs(ballPos.y + ballDim.y - brickPos.y) < std::abs(brickPos.x + dimensions.x - ballPos.x)) ||
			(std::abs(brickPos.y + dimensions.y - ballPos.y) < std::abs(ballPos.x + ballDim.x - brickPos.x) && std::abs(brickPos.y + dimensions.y - ballPos.y) < std::abs(brickPos.x + dimensions.x - ballPos.x))) {
			ballDir.y *= -1;
			if (std::abs(ballPos.y + ballDim.y - brickPos.y) < std::abs(brickPos.y + dimensions.y - ballPos.y)) {
				ballPos.y = brickPos.y - ballDim.y - 1;
			}
			else {
				ballPos.y = brickPos.y + dimensions.y + 1;
			}
		}
		else {
			ballDir.x *= -1;
			if (std::abs(ballPos.x + ballDim.x - brickPos.x) < std::abs(brickPos.x + dimensions.x - ballPos.x)) {
				ballPos.x = brickPos.x - ballDim.x - 1;
			}
			else {
				ballPos.x = brickPos.x + dimensions.x + 1;
			}
		}
		numHits--;
		int colorChannel = hf::Map(1, maxNumHits, 0, 255, numHits);
		shape.setFillColor(sf::Color(colorChannel, 0, 255 - colorChannel));
	}

	ball->SetDirection(ballDir);
	ball->SetPosition(ballPos);
}

void Brick::PowerUpCollision(PowerUp * powerUp) {
	sf::Vector2f powerUpDim = powerUp->GetDimensions();
	float powerUpSpeed = powerUp->GetSpeed();
	sf::Vector2f powerUpDir = powerUp->GetDirection();
	sf::Vector2f powerUpPos = powerUp->GetPosition();
	sf::Vector2f brickPos = GetPosition();

	if (powerUpPos.x < dimensions.x + brickPos.x && powerUpPos.x + powerUpDim.x > brickPos.x && powerUpPos.y + powerUpDim.y > brickPos.y && powerUpPos.y < brickPos.y + dimensions.y) {
		if ((std::abs(powerUpPos.y + powerUpDim.y - brickPos.y) < std::abs(powerUpPos.x + powerUpDim.x - brickPos.x) && std::abs(powerUpPos.y + powerUpDim.y - brickPos.y) < std::abs(brickPos.x + dimensions.x - powerUpPos.x)) ||
			(std::abs(brickPos.y + dimensions.y - powerUpPos.y) < std::abs(powerUpPos.x + powerUpDim.x - brickPos.x) && std::abs(brickPos.y + dimensions.y - powerUpPos.y) < std::abs(brickPos.x + dimensions.x - powerUpPos.x))) {
			powerUpDir.y *= -1;
			if (std::abs(powerUpPos.y + powerUpDim.y - brickPos.y) < std::abs(brickPos.y + dimensions.y - powerUpPos.y)) {
				powerUpPos.y = brickPos.y - powerUpDim.y - 1;
			}
			else {
				powerUpPos.y = brickPos.y + dimensions.y + 1;
			}
		}
		else {
			powerUpDir.x *= -1;
			if (std::abs(powerUpPos.x + powerUpDim.x - brickPos.x) < std::abs(brickPos.x + dimensions.x - powerUpPos.x)) {
				powerUpPos.x = brickPos.x - powerUpDim.x - 1;
			}
			else {
				powerUpPos.x = brickPos.x + dimensions.x + 1;
			}
		}
		int colorChannel = hf::Map(1, maxNumHits, 0, 255, numHits);
		shape.setFillColor(sf::Color(colorChannel, 0, 255 - colorChannel));
	}

	powerUp->SetDirection(powerUpDir);
	powerUp->SetPosition(powerUpPos);
}

bool Brick::IsBroken() {
	if (numHits) {
		return false;
	}
	else {
		return true;
	}
}

Brick::~Brick() {

}
