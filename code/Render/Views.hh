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
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual ~State() {}
    };

    class MenuTemplate: public State{
        MenuRender menu;
        public:
        MenuTemplate(MenuType type);

        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;
    };

    class MainMenu : public MenuTemplate {
        public:
            MainMenu();
    };
    class CombatMenu : public MenuTemplate{
        public:
            CombatMenu();
    };
    class ItemMenu : public MenuTemplate{
        public:
            ItemMenu();
    };
};
#endif