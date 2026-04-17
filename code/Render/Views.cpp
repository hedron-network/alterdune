#include "Views.hh"
namespace Render{

    MenuTemplate::MenuTemplate(MenuType type):menu(MenuRender(type)){}
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


    MainMenu::MainMenu():MenuTemplate(MAIN_MENU){}
    CombatMenu::CombatMenu():MenuTemplate(COMBAT_MENU){}
    ItemMenu::ItemMenu():MenuTemplate(ITEM_MENU){}

}