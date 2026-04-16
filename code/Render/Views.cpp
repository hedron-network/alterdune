#include "Views.hh"
namespace Render{
    void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
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
}