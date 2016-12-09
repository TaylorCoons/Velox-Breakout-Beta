#include "Ball.h"



Ball::Ball() {
	Reset();
}

void Ball::Reset() {
	// Initialize all properties to defaults
	double radius = 5.0;
	//direction = sf::Vector2f(std::cos(0), std::sin(0));
	direction = sf::Vector2f(std::cos(PI / 2.0), std::sin(PI / 2.0));
	//direction = sf::Vector2f(std::cos(PI / 6.0), std::sin(PI / 6.0));
	shape.setFillColor(sf::Color(100, 240, 4));
	dimensions = sf::Vector2f(radius * 2.0, radius * 2.0);
	speed = 6.0f;
	gravityVector = sf::Vector2f(0.0f, 0.025f);
	airFriction = 0.0f;
	density = 1.0f; // Initialize body properties to default
	//SetPosition(sf::Vector2f(WIDTH * 2.0 / 4.0 - dimensions.x / 2.0 + 4.0, HEIGHT * 1.0 / 4.0 - dimensions.y));
	//SetPosition(sf::Vector2f(WIDTH * 3.0 / 4.0 - dimensions.x / 2.0, HEIGHT - dimensions.y - 5.0));
	SetPosition(sf::Vector2f(WIDTH / 2.0 - radius, HEIGHT / 2.0 - radius - 10.0));
	shape.setRadius(radius);
	frozen = false;
	acceleration = 0.0007;
	jerk = 0.00007;
	for (int i = 0; i < blurQuality; i++) {
		blur[i].setRadius(radius);
		blur[i].setPosition(sf::Vector2f(WIDTH / 2.0 - radius, HEIGHT / 2.0 - radius - 10.0));
		blur[i].setFillColor(shape.getFillColor());
	}
}

void Ball::SetInitialPosition(sf::Vector2f pos) {
	for (int i = 0; i < blurQuality; i++) {
		blur[i].setPosition(pos);
	}
	SetPosition(pos);
}

void Ball::Freeze() {
	frozen = true;
	prevSpeed = speed;
	speed = 0;
}

void Ball::UnFreeze() {
	frozen = false;
	speed = prevSpeed;
}

bool Ball::Loss() {
	if (GetPosition().y + dimensions.y > HEIGHT) {
		return true;
	}
	else {
		return false;
	}
}

void Ball::OnFrame(sf::RenderWindow* pWindow) {
	if (!frozen) {
		Body::OnFrame(pWindow);
		if (speed < maxSpeed) {
			speed += acceleration;
			acceleration += jerk;
			if (acceleration > maxAcceleration) {
				acceleration = maxAcceleration;
			}
		}
		for (int i = 0; i < blurQuality; i++) {
			if (i != blurQuality - 1) {
				blur[i] = blur[i + 1];
			}
			else {
				blur[i].setRadius(dimensions.x / 2.0);
				blur[i].setPosition(shape.getPosition());
				sf::Color color = shape.getFillColor();
				color.a = hf::Map(0, blurQuality, 90, 10, i);
				blur[i].setFillColor(color);
			}
			pWindow->draw(blur[i]);
		}
	}
	else {
		pWindow->draw(shape);
	}
}

Ball::~Ball() {

}
