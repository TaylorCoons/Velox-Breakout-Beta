#pragma once
#include "Includes.h"
#include "Constants.h"
#include "Helpers.h"

// Class to draw faded text
class FadeText {
private:
    // Time until the text is completely faded
    sf::Time timeTillFade;
    // timer
    sf::Clock timer;
    // Text 
    sf::Text text;
    // Alpha
    unsigned int alpha;

public:
    // Default ctor
    FadeText();
    // Overloaded ctor
    FadeText(sf::Text text, sf::Font font, sf::Time timeTillFade);
    // Draw text
    void DrawText(sf::RenderWindow* pRenderWindow);
    // Set fade
    void Fade(std::string textString, sf::Time newTimeTillFade);

    // Getters
    sf::Text GetText() { return text; }
    const sf::Font* GetFont() { return text.getFont(); }
    unsigned int GetAlpha() { return alpha; }

    // Setters
    void SetFont(sf::Font &newFont) { text.setFont(newFont); }
    void SetAlpha(unsigned int newAlpha) { alpha = newAlpha; }

    // Dtor
    ~FadeText();
};