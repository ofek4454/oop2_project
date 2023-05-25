#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.h"
// event types


/**
 * Event class for creating events in the game
 */
class Event{
public:
    Event(EventType_t type);
    EventType_t getEventType() const;
private:
    EventType_t m_eventType;
};