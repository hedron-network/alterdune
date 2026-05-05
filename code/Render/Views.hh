#ifndef Views_h
#define Views_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../GameLogic/Combat.hh"
#include "renderTypes.hh"
#include "MenuRender.hh"
#include "CombatRenderer.hh"
#include "ItemMenuRenderer.hh"
namespace Render{
    class State {
    public:
        virtual void handleEvent(sf::Event& event,sf::RenderWindow& window) = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual Signal getSignal()=0;
        virtual void setSignal(Signal signal)=0;
        virtual ~State() {}
    };

    class MenuTemplate: public State{
        MenuRender menu;
        public:
        MenuTemplate(MenuType type,const sf::RenderWindow& window);

        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
        Signal getSignal() override;
        void setSignal(Signal signal) override;
    };

    class MainMenu : public MenuTemplate {
        public:
            MainMenu(const sf::RenderWindow& window);
    };
    class CombatMenu : public MenuTemplate{
        private:
            std::unique_ptr<sf::Text> enemyNameText;
            GameLogic::Combat& combat;
        public:
            CombatMenu(const sf::RenderWindow& window, GameLogic::Combat& combat);
            void draw(sf::RenderWindow& window);
            void drawEnemyName(sf::RenderWindow& window);
    };
    class ItemMenu : public State {
        ItemMenuRender itemMenuRender;
    public:
        ItemMenu(std::vector<Attributes::Item>& items,Entities::Player& player,const sf::RenderWindow& window);

        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
        Signal getSignal() override;
        void setSignal(Signal signal) override;
    };
    class CombatState: public State{
        public:
        CombatRenderer combatRenderer;
        CombatState(GameLogic::Combat &combat,const sf::RenderWindow& window);
        void handleEvent(sf::Event& event,sf::RenderWindow& window);
        void update(float dt);
        void draw(sf::RenderWindow& window);
        Signal getSignal() override;
        void setSignal(Signal signal) override;
    };
}
#endif