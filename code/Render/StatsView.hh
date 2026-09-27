#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.hh"
#include "Views.hh"
#include "../Entities/Player.hh"
#include "../GameLogic/Game.hh"

namespace Render {

class StatsView : public State {
public:
    StatsView(Entities::Player& player,GameLogic::PlayerStats& stats, const sf::RenderWindow& window);
    ~StatsView() override = default;

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal getSignal() override;
    void setSignal(Signal signal) override;

private:
    Entities::Player& player;
    GameLogic::PlayerStats& stats;
    Signal signal = Signal::None;
    void drawItems(sf::RenderWindow& window,float px, float iy, float pw);


    // Layout helpers
    void drawPanel(sf::RenderWindow& window);
    void drawStatRow(sf::RenderWindow& window, const std::string& label,
                     const std::string& value, float x, float y);

    // Panel dimensions (computed in constructor)
    float panelX, panelY, panelW, panelH;
};

} // namespace Render
