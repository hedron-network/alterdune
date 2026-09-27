#ifndef ItemMenuRender_h
#define ItemMenuRender_h
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../Attributes/Item.hh"
#include "../Entities/Player.hh"
#include "Assets.hh"
#include "renderTypes.hh"

namespace Render {

class ItemMenuRender {
private:
    Render::Signal signal = Signal::None;
    std::vector<Attributes::Item>& items;
    Entities::Player& player;

    int selectedIndex = 0;
    sf::RectangleShape panelRect;
    sf::RectangleShape selectionHighlight;

    // Layout constants
    float panelX, panelY, panelWidth, panelHeight;
    static constexpr float ROW_HEIGHT   = 40.f;
    static constexpr float PADDING      = 24.f;
    static constexpr float FONT_SIZE_LG = 22;
    static constexpr float FONT_SIZE_SM = 16;

    int validSelected() const; // clamps selectedIndex to non-empty items
    void drawLifeBar(sf::RenderWindow& window);
public:
    ItemMenuRender(std::vector<Attributes::Item>& items,Entities::Player& player,const sf::RenderWindow& window);

    void handleClick(sf::Vector2f mousePos);
    void handleKeyPress(sf::Keyboard::Key key);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    Render::Signal getSignal();
    void setSignal(Signal signal);
};

}
#endif