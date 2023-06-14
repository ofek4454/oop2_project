
#include "TimeCounting.h"

TimeCounting::TimeCounting() : m_window(WindowManager::instance().getWindow()) {
    m_countdownText.setFont(*ResourcesManager::instance().getFont());
    m_countdownText.setCharacterSize(64);
    m_countdownText.setFillColor(sf::Color::White);
    m_countdownText.setStyle(sf::Text::Bold);
    m_circle.setFillColor(sf::Color::Transparent);
    m_circle.setOutlineThickness(2.0f);
    m_circle.setOutlineColor(sf::Color::White);
    m_circle.setOrigin(CIRCLE_RADIUS, CIRCLE_RADIUS);
    m_circle.setPosition(CLOCK_CIRCLE_CENTER);
}

void TimeCounting::updateCount() {
    static int scaleFactor = 1.0f;
    m_countLength--;
    scaleFactor = 1.5f;
    if (m_countLength <= 0) {
        EventLoop::instance().addEvent(Event(TimeOver));
        return;
    }

    m_countdownText.setScale(scaleFactor, scaleFactor);
    scaleFactor -= 0.05f;
    if (scaleFactor <= 1.0f) {
        m_countdownText.setScale(1.0f, 1.0f);
    }
}

void TimeCounting::print() {
    if(m_countdownText.getFillColor() != sf::Color::Red) {
        m_window->draw(m_circle);
        float angleIncrement = 2 * M_PI / numLines;

        for (int i = 0; i < numLines; ++i) {
            float angle = i * angleIncrement;
            sf::CircleShape line(CIRCLE_RADIUS / 15.0f);
            line.setFillColor(sf::Color::White);
            line.setOrigin(line.getRadius(), line.getRadius());
            line.setPosition(std::cos(angle) * (CIRCLE_RADIUS - line.getRadius()) + m_circle.getPosition().x,
                             std::sin(angle) * (CIRCLE_RADIUS - line.getRadius()) + m_circle.getPosition().y);
            m_window->draw(line);
        }
    }
    m_window->draw(m_countdownText);
}

void TimeCounting::setText(float dt) {
    m_countdownText.setString(std::to_string(m_countLength));
    sf::FloatRect textBounds = m_countdownText.getGlobalBounds();
    m_countdownText.setOrigin(textBounds.width/2,textBounds.height/2);
    m_countdownText.setPosition(CLOCK_CIRCLE_CENTER);
    float completion = std::min(1.0f, dt);
    numLines = static_cast<int>(numSegments * completion);
}

void TimeCounting::setColor(sf::Color color) {
    m_countdownText.setFillColor(color);
}
