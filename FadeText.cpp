#include "FadeText.h"

// Initialize fade text class
FadeText::FadeText() {
    text.setScale(sf::Vector2f(0.6f, 0.6f));
    text.setPosition(sf::Vector2f(static_cast<float>(WIDTH) / 2.0f - 100.0f, static_cast<float>(HEIGHT) / 2.0f + 6.0f));
    text.setFillColor(sf::Color::White);
    alpha = text.getFillColor().a;
    //Set some properties
}

FadeText::FadeText(sf::Text text, sf::Font font, sf::Time timeTillFade) {
    this->text = text;
    this->timeTillFade = timeTillFade;
    alpha = text.getFillColor().Transparent.toInteger();
    timer.restart();
    // Fade some text in a cool manor
}

void FadeText::DrawText(sf::RenderWindow * pRenderWindow) {
    sf::Time elapsedTime = timer.getElapsedTime();
    if (elapsedTime <= timeTillFade) {
        unsigned int newAlpha = hf::Map(0, timeTillFade.asSeconds(), alpha, 0, elapsedTime.asSeconds());
        sf::Color color = text.getFillColor();
        text.setFillColor(sf::Color(color.r, color.g, color.b, newAlpha));
        pRenderWindow->draw(text);
    }
    // Draw the text being faded
}

void FadeText::Fade(std::string textString, sf::Time newTimeTillFade) {
    text.setString(textString);
    timeTillFade = newTimeTillFade;
    timer.restart();
    // I'm wayy to tired to comment right now
}

FadeText::~FadeText() {
    //~~~~~~~Squiggles~are~fun~~~~~~~Dtor
}