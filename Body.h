#pragma once
#include "Constants.h"
#include "Includes.h"

// Templated Shape Wrapper To Allow Shapes to Have Speed Direction and Rigidness // 
template<typename T>
class Body {
protected:
    // Vector to hold current direction of shape
    sf::Vector2f direction;
    // Float to hold current speed of shape
    float speed;
    // Shape to hold the instantiation of the shape
    T shape;
    // Width and height of shape (assumes origin is at local 0,0)
    sf::Vector2f dimensions;
    // Gravity Vector
    sf::Vector2f gravityVector;
    // Air friction
    float airFriction;
    // Density
    float density;

public:
    // Ctor
    // Default Ctor
    Body();
    // Intitialized Ctor
    Body(sf::Vector2f paramPosition, sf::Vector2f paramDimensions = sf::Vector2f(0.0f, 0.0f), sf::Vector2f paramDirection = sf::Vector2f(0.0f, 0.0f), float paramSpeed = 0.0f);

    // Getters (inline)
    // Get direction
    sf::Vector2f GetDirection() { return direction; }
    // Get position
    sf::Vector2f GetPosition() { return shape.getPosition(); }
    // Get dimensions
    sf::Vector2f GetDimensions() { return dimensions; }
    // Get speed
    float GetSpeed() { return speed; }
    // Get shape pointer (allows type related operations to be performed)
    T* GetShapePointer() { return &shape; }
    // Get gravity vector
    sf::Vector2f GetGravity() { return gravityVector; }
    // Get air friction
    float GetAirFriction() { return airFriction; }
    // Get density 
    float GetDensity() { return density; }

    // Setters (inline) 
    // Set position
    void SetPosition(sf::Vector2f newPosition) { shape.setPosition(newPosition); }
    // Set direction
    void SetDirection(sf::Vector2f newDirection) { direction = newDirection; }
    // Set dimensions
    void SetDimensions(sf::Vector2f newDimensions) { dimensions = newDimensions; }
    // Set speed
    void SetSpeed(float newSpeed) { speed = newSpeed; }
    // Set gravity
    void SetGravity(sf::Vector2f newGravityVector) { gravityVector = newGravityVector; }
    // Set air friction
    void SetAirFriction(float newAirFriction) { airFriction = newAirFriction; }
    // Set density
    void SetDensity(float newDensity) { density = newDensity; }

    // Body Functions
    // On Frame (perfroms time dependent actions and updates and draws body for that frame)
    void OnFrame(sf::RenderWindow* const pWindow);
    // Handles collision against walls
    void WallCollision();
    // Handles collision against other bodies
    template<typename R>
    void BodyCollisions(Body<R>* body2);
    // Rotates the direction vector by an angle theta
    void Rotate(float theta);
    // Apply gravity
    void ApplyGravity();
    // Apply air friction
    void ApplyAirFriction();
    // Apply impulse
    void ApplyImpulse(sf::Vector2f impDir, float impStrength);




    // Dtor
    ~Body();

};


// Ctor
template<typename T>
Body<T>::Body() {
    // Initialize all properties to defaults
    SetPosition(sf::Vector2f(0.0f, 0.0f));
    direction = sf::Vector2f(0.0f, 0.0f);
    dimensions = sf::Vector2f(0.0f, 0.0f);
    speed = 0.0f;
    gravityVector = sf::Vector2f(0.0f, 0.0f);
    airFriction = 0.0f;
    density = 1.0f; // Initialize body properties to default
}

// Intitialized Ctor
template<typename T>
Body<T>::Body(sf::Vector2f paramPosition, sf::Vector2f paramDimensions = sf::Vector2f(0.0f, 0.0f), sf::Vector2f paramDirection = sf::Vector2f(0.0f, 0.0f), float paramSpeed = 0.0f) {
    // Initialize all properties
    SetPosition(paramPosition);
    direction = paramDirection;
    dimensions = paramDimensions;
    speed = paramSpeed;
    gravityVector = sf::Vector2f(0.0f, 0.0f);
    airFriction = 0.0;
    density = 1.0f; // Set body properties to specified values
}

template<typename T>
void Body<T>::OnFrame(sf::RenderWindow* const pWindow) {
    // Handle wall collisions
    WallCollision();
    // Apply gravity
    ApplyGravity();
    // Apply air friction
    ApplyAirFriction();
    // Update position accordingly
    sf::Vector2f newPos = GetPosition();
    newPos.x += direction.x * speed;
    newPos.y += direction.y * speed;
    // Set position
    SetPosition(newPos);
    // Draw the shape
    pWindow->draw(shape);
}

// Handle wall collision
template<typename T>
void Body<T>::WallCollision() {
    sf::Vector2f pos = GetPosition();
    if (pos.x + dimensions.x >= WIDTH || pos.x <= 0.0f) {
        direction.x *= -1.0f;
        if (pos.x <= 0.0f) {
            pos.x = 1.0f;
        }
        else {
            pos.x = WIDTH - dimensions.x - 1.0f;
        }
    }
    if (pos.y + dimensions.y >= HEIGHT || pos.y <= 0.0f) {
        direction.y *= -1.0f;
        if (pos.y <= 0.0f) {
            pos.y = 1.0f;
        }
        else {
            pos.y = HEIGHT - dimensions.y - 1.0f;
        }
    }
    SetPosition(pos); // Check if hits all, if did change its direction
}

template<typename T>
void Body<T>::Rotate(float theta) {
    sf::Vector2f oldDir = direction;
    direction.x = oldDir.x * cos(theta) - oldDir.y * sin(theta);
    direction.y = oldDir.x * sin(theta) + oldDir.y * cos(theta); // Rotate a vector
}

template<typename T>
void Body<T>::ApplyGravity() {
    sf::Vector2f vel = direction * speed;
    vel += gravityVector;
    speed = sqrt(pow(vel.x, 2.0) + pow(vel.y, 2.0));
    if (speed != 0)
        direction = vel / speed; // Apply some gravity using physics cause god said so

}

template<typename T>
void Body<T>::ApplyAirFriction() {
    speed -= pow(speed * airFriction, 2.0) / 4.0; // Apply air friction using more physics
}

template<typename T>
void Body<T>::ApplyImpulse(sf::Vector2f impDir, float impStrength) {
    direction += impDir * impStrength / (dimensions.x * dimensions.y * density);
    //std::cout << "Impulse direction: " << impDir.x << ", " << impDir.y <<  std::endl;
    speed = hf::Mag(direction);
    direction = hf::Normalize(direction); // Apply a simulated impulse
}

// Dtor
template <typename T>
Body<T>::~Body() {
    // Fortunatly I don't have to take care of dynamic memory
}

//Handle body collision
template<typename T>
template<typename R>
void Body<T>::BodyCollisions(Body<R>* body2) {
    sf::Vector2f dir2 = body2->GetDirection();
    sf::Vector2f position = GetPosition();
    sf::Vector2f pos2 = body2->GetPosition();
    sf::Vector2f dim2 = body2->GetDimensions();

    float speed2 = body2->GetSpeed();

    if ((position.x >= pos2.x && position.x <= pos2.x + dim2.x || pos2.x >= position.x && pos2.x <= position.x + dimensions.x) &&
        ((position.y >= pos2.y && position.y <= pos2.y + dim2.y || pos2.y >= position.y && pos2.y <= position.y + dimensions.y))) {
        sf::Vector2f vel1 = sf::Vector2f(direction.x * speed, direction.y * speed);
        sf::Vector2f vel2 = sf::Vector2f(dir2.x * speed2, dir2.y * speed2);
        sf::Vector2f posCOM1 = sf::Vector2f((position.x + dimensions.x) / 2.0f, (position.y + dimensions.y) / 2.0f);
        sf::Vector2f posCOM2 = sf::Vector2f((pos2.x + dim2.x) / 2.0f, (pos2.y + dim2.y) / 2.0f);
        float mass1 = dimensions.x * dimensions.y;
        float mass2 = dim2.x * dim2.y * density;
        sf::Vector2f vel1Prime = vel1 - (2.0f * mass2 / (mass1 + mass2)) * hf::Dot(vel1 - vel2, posCOM1 - posCOM2) / pow(hf::Mag(posCOM1 - posCOM2), 2.0f) * (posCOM1 - posCOM2);
        sf::Vector2f vel2Prime = vel2 - (2.0f * mass1 / (mass1 + mass2)) * hf::Dot(vel2 - vel1, posCOM2 - posCOM1) / pow(hf::Mag(posCOM2 - posCOM1), 2.0f) * (posCOM2 - posCOM1);
        sf::Vector2f newDir1 = hf::Normalize(vel1Prime);
        sf::Vector2f newDir2 = hf::Normalize(vel2Prime);
        float newSpeed1 = hf::Mag(vel1Prime);
        float newSpeed2 = hf::Mag(vel2Prime);
        body2->SetDirection(newDir2);
        body2->SetSpeed(newSpeed2);
        SetDirection(newDir1);
        SetSpeed(newSpeed1);

        if (std::abs(std::abs(position.x + dimensions.x) / 2.0 - std::abs(pos2.x + dim2.x) / 2.0) < std::abs(std::abs(position.y + dimensions.y) / 2.0 - std::abs(pos2.y + dim2.y) / 2.0)) {
            if (position.y > pos2.y) {
                position.y = pos2.y + dim2.y + 2.0f;
            }
            else {
                position.y = pos2.y - dimensions.y - 2.0f;
            }
        }
        else if (std::abs(std::abs(position.x + dimensions.x) / 2.0 - std::abs(pos2.x + dim2.x) / 2.0) > std::abs(std::abs(position.y + dimensions.y) / 2.0 - std::abs(pos2.y + dim2.y) / 2.0)) {
            if (position.x > pos2.x) {
                position.x = pos2.x + dim2.x + 2.0f;
            }
            else {
                position.x = pos2.x - dimensions.x - 2.0f;
            }
        }
        SetPosition(position);
    }
    // LOTS of good phsyics, figure it out
}