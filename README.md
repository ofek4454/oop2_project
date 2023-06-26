# OOP2 Project - Rock Paper Scissors

## Submitted by:
Ofek Gorgi & Bar Kobi

## Overview:
This project is a "Rock Paper Scissors" game created with SFML.
Rock Paper Scissors is an online game that you can play with your friends.
Create/Join a room, and start play!
The game starts by choosing a flag and hole, the goal of the game is to get the opponent's flag.
you can move the players using the mouse or the keyboard.
if you get to the same block with an opponent's warrior there is a fight!
choose your weapon (Rock/Paper/Scissors), this weapon will stay for the whole game,
you can choose weapon once in a game for each warrior.
if you meet the opponent's hole your warrior will fall in the hole and the turn will be of the opponent.
the game finish when you get to the opponents flag (or the opponent get yours) than you can choose
if you want to rematch.

## File list:

#### Path: ./include/events

### Event.h / Event.cpp
- Class that builds and manage events in the game.

### eventLoop.h / eventLoop.cpp
- Singleton class of event queue that saves the events.

#### Path: ./include/exceptions

### GameException.h
- An exception thrown if a game error occur like the opponent logout.

### HttpException.h
- An exception thrown if a network error occur.

#### Path: ./include/weapons

### Flag.h / Flag.cpp
- The weapon of the warrior is flag.

### Hole.h / Hole.cpp
- The weapon of the warrior is hole.

### Rock/Paper/Scissors.h / Rock/Paper/Scissors.cpp
- The weapon of the warrior after choosing one.

### Undefined.h / Undefined.cpp
- If you haven't chosen a weapon yet.

### Weapon.h / Weapon.cpp
- A base class for all the weapons.

#### Path: ./include
### Board.h / Board.cpp
- Responsible for handling the Board creation, layout and management.

### Controller.h / Controller.cpp
- The main class that managing the game.

### GameBar.h / GameBar.cpp
- Responsible for showing and updating stats about the game.

### Menu.h / Menu.cpp
- The main menu of the game (First screen to show).

### Referee.h / Referee.cpp
- Load and animate the referee.

### Warrior.h / Warrior.cpp
- Represent a single warrior on the board.

#### Path: ./models
### PlayerModel.h
- A model of the player with name and uid.

### RoomModel.h
- A model of the room in the server.

#### Path: ./screens
### AfterGameScreen.h / AfterGameScreen.cpp
- Screen the shown after the game is done with the option to rematch.

### AvailableRooms.h / AvailableRooms.cpp
- Screen to show all the available rooms to join in the server.

### EnterNameScreen.h / EnterNameScreen.cpp
- Screen to enter your name before create a user in the server.

### ErrorScreen.h / ErrorScreen.cpp
- Screen that pop out in a case of error and show the user what happened.

### SettingsScreen.h / SettingsScreen.cpp
- Screen to control the settings such as volume of the music and sounds.

### WaitingRoom.h / WaitingRoom.cpp
- A screen to show while you wait for an opponent to join your room.

#### Path: ./services
### env.h
- Server environment consts like url.

### RoomService.h / RoomService.cpp
- All the API calls for managing the room in the server.

### UserService.h / UserService.cpp
- All the API calls for managing the user in the server.

#### Path: ./stateManagement
### EnemyState.h / EnemyState.cpp
- A state of the opponent, parse the move from the server to show on the screen.

### PlayerState.h / PlayerState.cpp
- A base class for the enemy and user state.

### RoomState.h / RoomState.cpp
- Manage the room state and connect between the local and server.

### UserState.h / UserState.cpp
- A state of the user.

#### Path: ./utils
### Consts.h
- All the consts of the game, sizes, enums, font sizes and more.

### HttpRequestsManager.h / HttpRequestsManager.cpp
- Make all the http requests to the server.

### Location.h / Location.cpp
- A location in the board (row,col).

### ResourcesManager.h / ResourcesManager.cpp
- Load and hold all the assets for the game.

### SettingsManager.h / SettingsManager.cpp
- Manage the settings of the game and update the settings file.

### SoundFlip.h / SoundFlip.cpp
- Singleton class for the sound switches.

### TimeCounting.h / TimeCounting.cpp
- A component of timer with animation.

### WindowManager.h / WindowManager.cpp
- Create and manage the window and the eventsLoop.

## Data structures:
### 2D vector of Rectangles 
- Holds matrix rectangles

### Vector of UniquePtr
- Holds the user/opponents warriors.

## Algorithms:
### Calculating Counting Clock Circle's 
- Using trigonometric functions to calculate circles around the number using
  2 * Pi / Num of Circles for each half of the circle.
  Each little circle calculated relative to the previous one until reached the base.

### Mirroring The Board Among The Users
- Using a mirroring algorithm to parse the board according to player's real id based
  on whether he opened the room or not.

### Screen Capture During Fight's Animations
- To keep the fight real until the result the data is transferred between the users
  and to keep the indication for the user that fight is being handled, we used
  window->update function to keep the last frame while the other user is fighting.

## Known bugs:
With poor internet connection the game may not work properly.

## Other notes:
This game is a multiplayer network game,
run the game twice, in the first window create a room than join with the another one.
make sure you have an internet connection that is stable.