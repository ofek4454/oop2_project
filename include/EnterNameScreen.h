#include "string"
#include "SFML/Graphics.hpp"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "UserService.h"

enum Mode_t{
    Create,
    Join,
};

class EnterNameScreen{
public:
    EnterNameScreen(Mode_t mode);

private:
    Mode_t m_mode;
    std::string m_name;
    sf::RectangleShape m_background;
    sf::Text m_title;
    sf::Text m_nameText;
    sf::RenderWindow *m_window;

    void init();
    void handleEvents();
    void print();
};