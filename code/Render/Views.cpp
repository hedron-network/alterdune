#include "Views.hh"
namespace Render{

    MenuTemplate::MenuTemplate(MenuType type,sf::RenderWindow& window):menu(MenuRender(type,window)){}
    void MenuTemplate::handleEvent(sf::Event& event, sf::RenderWindow& window){
        if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                menu.handleClick(
                    window.mapPixelToCoords(mousePressed->position)
                );
            }
        }
    }
    void MenuTemplate::update(float dt, sf::Vector2f mPos) {
        menu.update(dt);
    }

    void MenuTemplate::draw(sf::RenderWindow& window) {
        menu.draw(window);
    }


    MainMenu::MainMenu(sf::RenderWindow& window):MenuTemplate(MAIN_MENU,window){}
    CombatMenu::CombatMenu(sf::RenderWindow& window):MenuTemplate(COMBAT_MENU,window){}
    ItemMenu::ItemMenu(sf::RenderWindow& window):MenuTemplate(ITEM_MENU,window){}

}