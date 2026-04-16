#ifndef Views_h
#define Views_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MenuRender.hh"
namespace Render{
    class State {
    public:
        virtual void handleEvent(sf::Event& event,sf::Window& window) = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual ~State() {}
    };
    class MainMenu : public State {
    MenuRender menu;
    public:
        void handleEvent(sf::Event& event, sf::RenderWindow& window) {
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
    };
};
#endif