
#include "WindowManager.h"
#include "Weapon.h"
#include "Warrior.h"

Weapon::Weapon(const std::string symbol, bool visible) : m_is_visible(visible), m_symbol(symbol) {

    m_timeCounting.setCount(5);
    m_timerBox.setSize(sf::Vector2f(CIRCLE_RADIUS*2,CIRCLE_RADIUS*2));
    m_timerBox.setOrigin(CIRCLE_RADIUS,CIRCLE_RADIUS);
    m_timerBox.setFillColor(BLUE_COLOR);
    m_timerBox.setPosition(CLOCK_CIRCLE_CENTER);
}

void Weapon::draw() {
    auto window = WindowManager::instance().getWindow();
    window->draw(m_weapon_sprite);
}

void Weapon::moveWeapon(sf::Vector2f offset) {
    m_weapon_sprite.move(offset);
}

void Weapon::setOwner(Warrior *warrior) {
    m_warrior = warrior;
}

void Weapon::lose() {
    m_warrior->lose();
}

void Weapon::chooseWeapon() {
    auto window = WindowManager::instance().getWindow();

    sf::Texture bg;
    bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    bg.update(*window);
    sf::Sprite background(bg);
    initChooseBox();
    m_timeCounting.setCount(5);

    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                for (auto &texture: m_weapons_textures)
                    if (texture.getGlobalBounds().contains(move.x, move.y))
                        texture.setScale(1.1, 1.1);
                    else
                        texture.setScale(1, 1);
                return false;
            },
            [this, window, background](auto click, auto &exit) {
                for (int i = 0; i < 3; i++)
                    if (m_weapons_textures[i].getGlobalBounds().contains(click.x, click.y)) {
                        m_warrior->setWeapon(Weapons_t(i));
                        window->clear();
                        window->draw(background);
                        window->display();
                        exit = true;
                    }
                return false;
            },
            [](auto key, auto exit) {
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this, window, background](auto &exit) {
                if (EventLoop::instance().hasEvent() &&
                    EventLoop::instance().popEvent().getEventType() == TimeOver) {
                    int random = std::rand() % 3;
                    m_warrior->setWeapon(Weapons_t(random));
                    window->clear();
                    window->draw(background);
                    window->display();
                    exit = true;
                    return;
                }
                window->draw(background);
                window->draw(m_ChooseBoxRect);
                window->draw(m_timerBox);
                m_timeCounting.updateCount();
                m_timeCounting.print();
                for (const auto &texture: m_weapons_textures)
                    window->draw(texture);
                window->draw(m_ChooseWeaponText);
                window->display();
            }
    );
}

void Weapon::initChooseBox() {
    m_ChooseBoxRect.setSize(sf::Vector2f(RECT_SIZE * (BOARD_SIZE - 2), RECT_SIZE * (ROWS - 2)));
    sf::Vector2f boxPos(BOARD_TOP_LEFT.left + RECT_SIZE, BOARD_TOP_LEFT.top + RECT_SIZE);
    m_ChooseBoxRect.setPosition(boxPos);
    m_ChooseBoxRect.setFillColor(sf::Color(sf::Color(181, 193, 105, 100)));
    m_ChooseBoxRect.setOutlineColor(sf::Color::White);
    m_ChooseBoxRect.setOutlineThickness(2);

    auto weapons_texture = ResourcesManager::instance().getTexture(Rps);

    m_weapons_textures[Rock_t].setTexture(*weapons_texture);
    m_weapons_textures[Rock_t].setTextureRect(sf::IntRect(WEP_WIDTH * 2, WEP_HEIGHT * 3, WEP_WIDTH, WEP_HEIGHT));
    m_weapons_textures[Rock_t].setPosition(boxPos.x + RECT_SIZE, boxPos.y + RECT_SIZE);
    m_weapons_textures[Rock_t].setOrigin(m_weapons_textures[Rock_t].getGlobalBounds().width / 2,
                                         m_weapons_textures[Rock_t].getGlobalBounds().height / 2);

    m_weapons_textures[Paper_t].setTexture(*weapons_texture);
    m_weapons_textures[Paper_t].setTextureRect(sf::IntRect(WEP_WIDTH * 2, WEP_HEIGHT * 5, WEP_WIDTH, WEP_HEIGHT));
    m_weapons_textures[Paper_t].setPosition(boxPos.x + RECT_SIZE * 3, boxPos.y + RECT_SIZE);
    m_weapons_textures[Paper_t].setOrigin(m_weapons_textures[Paper_t].getGlobalBounds().width / 2,
                                          m_weapons_textures[Paper_t].getGlobalBounds().height / 2);

    m_weapons_textures[Scissors_t].setTexture(*weapons_texture);
    m_weapons_textures[Scissors_t].setTextureRect(sf::IntRect(WEP_WIDTH * 2, WEP_HEIGHT, WEP_WIDTH, WEP_HEIGHT));
    m_weapons_textures[Scissors_t].setPosition(boxPos.x + RECT_SIZE * 5, boxPos.y + RECT_SIZE);
    m_weapons_textures[Scissors_t].setOrigin(m_weapons_textures[Scissors_t].getGlobalBounds().width / 2,
                                             m_weapons_textures[Scissors_t].getGlobalBounds().height / 2);

    m_ChooseWeaponText.setFont(*ResourcesManager::instance().getFont());
    m_ChooseWeaponText.setString("Choose Your\n   Weapon  ");
    m_ChooseWeaponText.setFillColor(sf::Color::White);
    m_ChooseWeaponText.setCharacterSize(H1);
    m_ChooseWeaponText.setPosition(boxPos.x + RECT_SIZE * 3, boxPos.y + RECT_SIZE * 2);
    m_ChooseWeaponText.setOrigin(m_ChooseWeaponText.getGlobalBounds().width / 2, 0);
    m_ChooseWeaponText.setOutlineColor(GRAY_COLOR);
    m_ChooseWeaponText.setOutlineThickness(3);
}

bool Weapon::animateWeapon() {
    static bool middle = false;
    static int offset = 22;
    if(!middle)
        m_weaponIntRect.top -= WEP_HEIGHT;
    else
        m_weaponIntRect.top += WEP_HEIGHT;

    if (m_weaponIntRect.top < 0 && !middle) {
        middle = true;
        m_weaponIntRect.top = 0;
        m_weapon_sprite.setTextureRect(m_weaponIntRect);
        m_weapon_sprite.move(sf::Vector2f(0,-offset));
        return false;
    }
    if(m_weaponIntRect.top >= WEP_HEIGHT * 3 && middle){
        middle = false;
        m_weaponIntRect.top = WEP_HEIGHT * 3;
        m_weapon_sprite.setTextureRect(m_weaponIntRect);
        m_weapon_sprite.move(sf::Vector2f(0,offset));
        return true;
    }
    if(!middle)
        m_weapon_sprite.move(sf::Vector2f(0,-offset));
    else
        m_weapon_sprite.move(sf::Vector2f(0,offset));

    m_weapon_sprite.setTextureRect(m_weaponIntRect);
    return false;
}
