#include "Event.h"

/**
 * create new event
 * @param type event type (enum)
 * @param pointsToAdd how much points the event worth
 */
Event::Event(EventType_t type)
        : m_eventType(type){}

EventType_t Event::getEventType() const {return m_eventType;}