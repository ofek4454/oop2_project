
#include "Undefined.h"
#include "Warrior.h"

Undefined::Undefined(bool isMine){
    if(isMine){
        int rand = std::rand() % 3;
        auto wep = Weapons_t(rand);
        auto weapon = ResourcesManager::instance().getTexture(Rps);
        m_weapon_sprite.setTexture(*weapon);
        if(wep == Rock_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55,58));
        else if(wep == Paper_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
        else if(wep == Scissors_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 0, 55, 58));
    }
}

void Undefined::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}

void Undefined::chooseWeapon(Weapon &other) {
    auto window = WindowManager::instance().getWindow();
    sf::Texture bg;
    bg.loadFromImage(window->capture());
    sf::Sprite background(bg);
    initChooseBox();
    while (window->isOpen()) {
        window->clear();
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::MouseButtonReleased) {
                for(int i=0 ; i<3 ; i++)
                    if(m_weapons_textures[i].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                        m_warrior->setWeapon(Weapons_t(i), other);
                        return;
                    }
            }
            if (event.type == sf::Event::MouseMoved) {
                for(auto &texture : m_weapons_textures)
                    if(texture.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        texture.setScale(3.5,3.5);
                    else
                        texture.setScale(3,3);
            }
        }
        window->draw(background);
        window->draw(m_ChooseBoxRect);
        for(const auto &texture : m_weapons_textures)
            window->draw(texture);
        window->draw(m_ChooseWeaponText);
        window->display();
    }
}

void Undefined::initChooseBox() {
    m_ChooseBoxRect.setSize(sf::Vector2f(RECT_SIZE*(BOARD_SIZE-2), RECT_SIZE*(BOARD_SIZE-2)));
    sf::Vector2f boxPos((WINDOW_WIDTH * 0.775 - BOARD_SIZE * RECT_SIZE) / 2 + RECT_SIZE, WINDOW_HEIGHT / 2 - RECT_SIZE * (BOARD_SIZE / 2) + RECT_SIZE);
    m_ChooseBoxRect.setPosition(boxPos);
    m_ChooseBoxRect.setFillColor(sf::Color(sf::Color(181, 193, 105, 100)));
    m_ChooseBoxRect.setOutlineColor(sf::Color::White);
    m_ChooseBoxRect.setOutlineThickness(2);

    auto weapons_texture = ResourcesManager::instance().getTexture(Rps);

    m_weapons_textures[Rock_t].setTexture(*weapons_texture);
    m_weapons_textures[Rock_t].setTextureRect(sf::IntRect(110, 174, 55,58));
    m_weapons_textures[Rock_t].setPosition(boxPos.x+RECT_SIZE, boxPos.y + RECT_SIZE*2);
    m_weapons_textures[Rock_t].setOrigin(m_weapons_textures[Rock_t].getGlobalBounds().width/2,m_weapons_textures[Rock_t].getGlobalBounds().height/2);
    m_weapons_textures[Rock_t].setScale(3,3);

    m_weapons_textures[Paper_t].setTexture(*weapons_texture);
    m_weapons_textures[Paper_t].setTextureRect(sf::IntRect(110, 290, 55, 58));
    m_weapons_textures[Paper_t].setPosition(boxPos.x+RECT_SIZE*3, boxPos.y + RECT_SIZE*2);
    m_weapons_textures[Paper_t].setOrigin(m_weapons_textures[Paper_t].getGlobalBounds().width/2,m_weapons_textures[Paper_t].getGlobalBounds().height/2);
    m_weapons_textures[Paper_t].setScale(3,3);

    m_weapons_textures[Scissors_t].setTexture(*weapons_texture);
    m_weapons_textures[Scissors_t].setTextureRect(sf::IntRect(110, 58, 55, 58));
    m_weapons_textures[Scissors_t].setPosition(boxPos.x+RECT_SIZE*5, boxPos.y + RECT_SIZE*2);
    m_weapons_textures[Scissors_t].setOrigin(m_weapons_textures[Scissors_t].getGlobalBounds().width/2,m_weapons_textures[Scissors_t].getGlobalBounds().height/2);
    m_weapons_textures[Scissors_t].setScale(3,3);

    m_ChooseWeaponText.setFont(*ResourcesManager::instance().getFont());
    m_ChooseWeaponText.setString("Choose Your\n  Weapon  ");
    m_ChooseWeaponText.setFillColor(sf::Color::White);
    m_ChooseWeaponText.setCharacterSize(80);
    m_ChooseWeaponText.setPosition(boxPos.x +RECT_SIZE*3,boxPos.y + RECT_SIZE*3);
    m_ChooseWeaponText.setOrigin(m_ChooseWeaponText.getGlobalBounds().width/2,0);
    m_ChooseWeaponText.setOutlineColor(DARK_GREEN_COLOR);
    m_ChooseWeaponText.setOutlineThickness(3);
}
