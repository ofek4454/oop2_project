#pragma once
#include <SFML/Graphics.hpp>
// event types
enum EventType_t{
    Won,
    Lose,
    TimeOver,
    FightRockPaper,
    FightRockScissors,
    FightRockRock,
    FightPaperRock,
    FightPaperScissors,
    FightPaperPaper,
    FightScissorsRock,
    FightScissorsPaper,
    FightScissorsScissors,
};

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