#ifndef Views_h
#define Views_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MenuRender.hh"
namespace Render{
    class State {
    public:
        virtual void handleEvent(sf::Event& event,sf::RenderWindow& window) = 0;
        virtual void update(float dt, sf::Vector2f mousePos) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual ~State() {}
    };

    class MenuTemplate: public State{
        MenuRender menu;
        public:
        MenuTemplate(MenuType type,const sf::RenderWindow& window);

        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt, sf::Vector2f mousePos) override;
        void draw(sf::RenderWindow& window) override;
    };

    class MainMenu : public MenuTemplate {
        public:
            MainMenu(const sf::RenderWindow& window);
    };
    class CombatMenu : public MenuTemplate{
        public:
            CombatMenu(const sf::RenderWindow& window);
    };
    class ItemMenu : public MenuTemplate{
        public:
            ItemMenu(const sf::RenderWindow& window);
    };
};
#endif