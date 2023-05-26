#include "Event.h"

/**
 * create new event
 * @param type event type (enum)
 * @param pointsToAdd how much points the event worth
 */
Event::Event(EventType_t type, Winner_t winner)
        : m_eventType(type), m_winner(winner){}

EventType_t Event::getEventType() const {return m_eventType;}

Winner_t Event::getWinner() const {
    return m_winner;
}
