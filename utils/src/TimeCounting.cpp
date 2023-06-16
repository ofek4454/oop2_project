
#include "TimeCounting.h"

TimeCounting::TimeCounting() : m_window(WindowManager::instance().getWindow()) {
    m_countdownText = TextClass("",H2,CLOCK_CIRCLE_CENTER).getText();
}

void TimeCounting::updateCount() {
    static sf::Clock clock;
    static float scaleFactor = 1.0f;
    static bool animating = false;
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 1.0f) {
        m_countLength--;
        clock.restart();
        if(m_countdownText.getFillColor() != sf::Color::Red){
            animating = true;
            scaleFactor = 1.5f;
        }
    }

    if (m_countLength <= 0) {
        EventLoop::instance().addEvent(Event(TimeOver));
        return;
    }

    if (animating) {
        m_countdownText.setScale(scaleFactor, scaleFactor);
        scaleFactor -= 0.05f;
        if (scaleFactor <= 1.0f) {
            animating = false;
            m_countdownText.setScale(1.0f, 1.0f);
        }
    }

    m_countdownText.setString(std::to_string(m_countLength));
    sf::FloatRect textBounds = m_countdownText.getLocalBounds();
    m_countdownText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                          textBounds.top + textBounds.height / 2.0f);
    float completion = std::min(1.0f, elapsed.asSeconds());
    numLines = static_cast<int>(numSegments * completion);
}

void TimeCounting::print() {
    if(m_countLength == -1) return;
    if(m_countdownText.getFillColor() != sf::Color::Red) {
        float angleIncrement = 2 * M_PI / numLines;

        for (int i = 0; i < numLines; ++i) {
            float angle = i * angleIncrement;
            sf::CircleShape line(CIRCLE_RADIUS / 15.0f);
            line.setFillColor(sf::Color::White);
            line.setOrigin(line.getRadius(), line.getRadius());
            line.setPosition(std::cos(angle) * (CIRCLE_RADIUS - line.getRadius()) + CLOCK_CIRCLE_CENTER.x,
                             std::sin(angle) * (CIRCLE_RADIUS - line.getRadius()) + CLOCK_CIRCLE_CENTER.y);
            line.setOutlineThickness(1);
            line.setOutlineColor(sf::Color::Black);
            m_window->draw(line);
        }
    }
    m_window->draw(m_countdownText);
}

void TimeCounting::setColor(sf::Color color) {
    m_countdownText.setFillColor(color);
}
