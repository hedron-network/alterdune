#ifndef ActMenuRenderer_h
#define ActMenuRenderer_h
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../Attributes/Action.hh"
#include "../Entities/Player.hh"
#include "../Entities/Enemy.hh"
#include "Assets.hh"
#include "renderTypes.hh"

namespace Render {

class ActMenuRender {
private:
    Render::Signal signal = Signal::None;
    std::vector<Action>  actions;
    Entities::Enemy&      enemy;
    Entities::Player&     player;

    int   selectedIndex  = 0;
    bool  showingDesc    = false;
    float descTimer      = 0.f;
    static constexpr float DESC_DURATION = 2.f;

    sf::RectangleShape panelRect;
    sf::RectangleShape selectionHighlight;
    sf::RectangleShape descBox;

    float panelX, panelY, panelWidth, panelHeight;
    static constexpr float ROW_HEIGHT   = 40.f;
    static constexpr float PADDING      = 24.f;
    static constexpr float FONT_SIZE_LG = 22;
    static constexpr float FONT_SIZE_SM = 16;

    int  validSelected() const;
    void drawLifeBar(sf::RenderWindow& window);

public:
    ActMenuRender(std::vector<Action> actions,
                  Entities::Enemy&    enemy,
                  Entities::Player&   player,
                  const sf::RenderWindow& window);

    void handleClick(sf::Vector2f mousePos);
    void handleKeyPress(sf::Keyboard::Key key);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    Render::Signal getSignal();
    void           setSignal(Signal s);
};

} 
#endif