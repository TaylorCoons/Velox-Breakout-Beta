#pragma once
#include "Includes.h"
#include "Constants.h"

// Helper functions
namespace hf {
    inline static double Map(double oldMin, double oldMax, double newMin, double newMax, double value)
    {
        if (oldMax - oldMin == 0) {
            return 0.0;
        }
        return (value - oldMin) / (oldMax - oldMin) * (newMax - newMin) + newMin;
    }

    inline static float Dot(sf::Vector2f v1, sf::Vector2f v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline static float Mag(sf::Vector2f v)
    {
        return sqrt(pow(v.x, 2.0f) + pow(v.y, 2.0f));
    }

    inline static sf::Vector2f Normalize(sf::Vector2f v)
    {
        float mag = Mag(v);
        return sf::Vector2f(v.x / mag, v.y / mag);
    }
}