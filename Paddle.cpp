#pragma once
#include "Paddle.h"

Paddle::Paddle() {
	Reset();
}

void Paddle::BallCollision(Ball* ball) {
	sf::Vector2f ballDim = ball->GetDimensions();
	float ballSpeed = ball->GetSpeed();
	sf::Vector2f ballDir = ball->GetDirection();
	sf::Vector2f ballPos = ball->GetPosition();
	sf::Vector2f paddlePos = GetPosition();

	if (ballPos.x < dimensions.x + paddlePos.x && ballPos.x + ballDim.x > paddlePos.x && ballPos.y + ballDim.y > paddlePos.y && ballPos.y < paddlePos.y + dimensions.y) {
		if ((std::abs(ballPos.y + ballDim.y - paddlePos.y) < std::abs(ballPos.x + ballDim.x - paddlePos.x) && std::abs(ballPos.y + ballDim.y - paddlePos.y) < std::abs(paddlePos.x + dimensions.x - ballPos.x)) ||
			(std::abs(paddlePos.y + dimensions.y - ballPos.y) < std::abs(ballPos.x + ballDim.x - paddlePos.x) && std::abs(paddlePos.y + dimensions.y - ballPos.y) < std::abs(paddlePos.x + dimensions.x - ballPos.x))) {
			ballDir.y *= -1;

			if (std::abs(ballPos.y + ballDim.y - paddlePos.y) < std::abs(paddlePos.y + dimensions.y - ballPos.y)) {
				ballPos.y = paddlePos.y - ballDim.y - 1;
				ballDir.x += -hf::Map(0, std::abs(dimensions.x / 2.0), -0.5, 0.5, std::abs((paddlePos.x + dimensions.x) / 2.0 - (ballPos.x + ballDim.x) / 2.0));
				ballDir = hf::Normalize(ballDir);
			}
			else {
				ballPos.y = paddlePos.y + dimensions.y + 1;
			}
		}
		else {
			ballDir.x *= -1;
			if (std::abs(ballPos.x + ballDim.x - paddlePos.x) < std::abs(paddlePos.x + dimensions.x - ballPos.x)) {
				ballPos.x = paddlePos.x - ballDim.x - 1;
			}
			else {
				ballPos.x = paddlePos.x + dimensions.x + 1;
			}
		}
	}

	ball->SetDirection(ballDir);
	ball->SetPosition(ballPos);
}

void Paddle::OnFrame(sf::RenderWindow * pWindow) {
	if (clock.getElapsedTime().asSeconds() > largerPaddleTime && largerPaddle) {
		largerPaddle = false;
		dimensions.x -= largerPaddleSize;
		shape.setSize(dimensions);
		for (int i = 0; i < blurQuality; i++) {
			blur[i].setSize(dimensions);
		}
	}
	for (int i = 0; i < blurQuality; i++) {
		if (i != blurQuality - 1) {
			blur[i] = blur[i + 1];
		}
		else {
			blur[i].setSize(dimensions);
			blur[i].setPosition(shape.getPosition());
			sf::Color color = shape.getFillColor();
			color.a = hf::Map(0, blurQuality, 90, 10, i);
			blur[i].setFillColor(color);
		}
		pWindow->draw(blur[i]);
	}
	Body::OnFrame(pWindow);
}

bool Paddle::PowerUpCollision(PowerUp * powerUp) {
	sf::Vector2f powerUpDim = powerUp->GetDimensions();
	float powerUpSpeed = powerUp->GetSpeed();
	sf::Vector2f powerUpDir = powerUp->GetDirection();
	sf::Vector2f powerUpPos = powerUp->GetPosition();
	sf::Vector2f paddlePos = GetPosition();

	if (powerUpPos.x < dimensions.x + paddlePos.x && powerUpPos.x + powerUpDim.x > paddlePos.x && powerUpPos.y + powerUpDim.y > paddlePos.y && powerUpPos.y < paddlePos.y + dimensions.y) {
		return true;
	}
	else {
		return false;
	}
}

void Paddle::LargerPaddle() {
	if (!largerPaddle) {
		largerPaddle = true;
		clock.restart();
		dimensions.x += largerPaddleSize;
		shape.setSize(sf::Vector2f(dimensions));
		for (int i = 0; i < blurQuality; i++) {
			blur[i].setSize(dimensions);
		}
	}
	clock.restart();
}

void Paddle::Reset() {
	// Initialize all properties to defaults
	direction = sf::Vector2f(0.0f, 0.0f);
	shape.setFillColor(sf::Color(250, 0, 80));
	dimensions = sf::Vector2f(80.0f, 15.0f);
	speed = 0.0f;
	gravityVector = sf::Vector2f(0.0f, 0.0f);
	airFriction = 0.18f;
	density = 1.0f; // Initialize body properties to default
	SetPosition(sf::Vector2f(WIDTH / 2.0 - dimensions.x / 2.0, HEIGHT - dimensions.y - 5.0));
	//SetPosition(sf::Vector2f(WIDTH / 2.0, HEIGHT / 2.0));
	//SetPosition(sf::Vector2f(WIDTH / 2.0 - dimensions.x / 2.0, 5.0));
	shape.setSize(dimensions);
	for (int i = 0; i < blurQuality; i++) {
		blur[i].setSize(dimensions);
		blur[i].setPosition(sf::Vector2f(WIDTH / 2.0 - dimensions.x / 2.0, HEIGHT - dimensions.y - 5.0));
		blur[i].setFillColor(shape.getFillColor());
	}
	largerPaddle = false;
}

Paddle::~Paddle() {

}
