#include "Views.hh"
namespace Render{
    
    MenuTemplate::MenuTemplate(MenuType type,const sf::RenderWindow& window):menu(MenuRender(type,window)){}
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
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            menu.handleKeyPress(
                keyPressed->code
            );
        }
    }
    void MenuTemplate::update(float dt) {
        menu.update(dt);
    }

    void MenuTemplate::draw(sf::RenderWindow& window) {
        menu.draw(window);
    }


    MainMenu::MainMenu(const sf::RenderWindow& window):MenuTemplate(MAIN_MENU,window){}
    CombatMenu::CombatMenu(const sf::RenderWindow& window):MenuTemplate(COMBAT_MENU,window){}
    ItemMenu::ItemMenu(const sf::RenderWindow& window):MenuTemplate(ITEM_MENU,window){}

    CombatState::CombatState(GameLogic::Combat &combat,const sf::RenderWindow& window):combatRenderer(CombatRenderer(combat,window)){}
    void CombatState::draw(sf::RenderWindow& window){
        combatRenderer.draw(window);
    }
    void CombatState::update(float dt){
        combatRenderer.update(dt);
    }
    void CombatState::handleEvent(sf::Event& event,sf::RenderWindow& window){
        combatRenderer.handleEvent(event,window);
    }

}