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
    Render::Signal MenuTemplate::getSignal(){
        return menu.getSignal();
    }
    void MenuTemplate::setSignal(Render::Signal signal){
        menu.setSignal(signal);
    }


    MainMenu::MainMenu(const sf::RenderWindow& window):MenuTemplate(MAIN_MENU,window){}
    CombatMenu::CombatMenu(const sf::RenderWindow& window, GameLogic::Combat& combat):MenuTemplate(COMBAT_MENU,window),combat(combat){}
    void CombatMenu::draw(sf::RenderWindow& window){
        drawEnemyName(window);
        MenuTemplate::draw(window);
    }

    void CombatMenu::drawEnemyName(sf::RenderWindow& window){
            enemyNameText = std::make_unique<sf::Text>(Assets::GetFont(), combat.enemy.GetName(), 24);
            enemyNameText->setFillColor(sf::Color::White);
        

        sf::FloatRect bounds = enemyNameText->getLocalBounds();
        float x = (window.getSize().x - bounds.size.x) / 2.f;
        enemyNameText->setPosition(sf::Vector2f(x, 20.f));

        window.draw(*enemyNameText);
    }


    ItemMenu::ItemMenu(std::vector<Attributes::Item>& items,Entities::Player& player,const sf::RenderWindow& window)
    : itemMenuRender(items, player, window) {}

void ItemMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (const auto* mp = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mp->button == sf::Mouse::Button::Left)
            itemMenuRender.handleClick(window.mapPixelToCoords(mp->position));
    }
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>())
        itemMenuRender.handleKeyPress(kp->code);
    }

    void ItemMenu::update(float dt){
        itemMenuRender.update(dt); 
    }
    void ItemMenu::draw(sf::RenderWindow& window){ itemMenuRender.draw(window); }
    Signal ItemMenu::getSignal(){
        return itemMenuRender.getSignal();
    }
    void ItemMenu::setSignal(Signal signal){
        itemMenuRender.setSignal(signal);
    }


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
        Render::Signal CombatState::getSignal(){
        return  combatRenderer.getSignal();
    }
    void CombatState::setSignal(Signal signal){

    }

}