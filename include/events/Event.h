#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.h"
// event types


/**
 * Event class for creating events in the game
 */
class Event{
public:
    Event(EventType_t type, Winner_t winner = NoneEvent);
    EventType_t getEventType() const;
    Winner_t getWinner() const;
private:
    EventType_t m_eventType;
    Winner_t m_winner;
};