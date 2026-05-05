#pragma once
#include <SFML/Graphics.hpp>
#include "../GameLogic/Game.hh"
#include "renderTypes.hh"
#include "Assets.hh"
#include "Views.hh"

namespace Render {

    enum class EndingType { PACIFIST, GENOCIDE, NEUTRAL, GAMEOVER };

    class EndingView : public State {
        EndingType  type;
        Signal      signal = Signal::None;

    public:
        explicit EndingView(const GameLogic::PlayerStats& stats) {
            if      (stats.numberOfSpares >= 10) type = EndingType::PACIFIST;
            else if (stats.numberOfKills  >= 10) type = EndingType::GENOCIDE;
            else if (stats.numberOfVictories>=10) type = EndingType::NEUTRAL;
            else type =EndingType::GAMEOVER;
        }

        void handleEvent(sf::Event& event, sf::RenderWindow&) override {
            if (const auto* kp = event.getIf<sf::Event::KeyPressed>())
                if (kp->code == sf::Keyboard::Key::Enter)
                    signal = Signal::POP;
        }

        void update(float) override {}

        void draw(sf::RenderWindow& window) override {
            // Background tint
            sf::RectangleShape bg(sf::Vector2f(window.getSize()));
            switch (type) {
                case EndingType::PACIFIST: bg.setFillColor({10,  60,  10,  220}); break;
                case EndingType::GENOCIDE: bg.setFillColor({60,  10,  10,  220}); break;
                case EndingType::NEUTRAL:  bg.setFillColor({30,  30,  60,  220}); break;
            }
            window.draw(bg);

            // Title
            const char* title = (type == EndingType::PACIFIST) ? "PACIFIST ENDING"
                              : (type == EndingType::GENOCIDE)  ? "GENOCIDE ENDING"
                              : (type==EndingType::NEUTRAL) ? "NEUTRAL ENDING"
                              :"GAME OVER";
                                
            sf::Text titleText(Assets::GetFont(), title, 36);
            titleText.setFillColor(sf::Color::White);
            sf::FloatRect tb = titleText.getLocalBounds();
            titleText.setPosition({(window.getSize().x - tb.size.x) / 2.f, 200.f});
            window.draw(titleText);

            // Flavour line
            const char* flavour =
                (type == EndingType::PACIFIST) ? "You spared everyone. True peace." :
                (type == EndingType::GENOCIDE) ? "You showed no mercy." :
                (type == EndingType::NEUTRAL) ? "The world remembers you... somewhere in between.":
                                                "You died";
            sf::Text sub(Assets::GetFont(), flavour, 20);
            sub.setFillColor({200, 200, 200, 255});
            sf::FloatRect sb = sub.getLocalBounds();
            sub.setPosition({(window.getSize().x - sb.size.x) / 2.f, 270.f});
            window.draw(sub);

            // Prompt
            sf::Text prompt(Assets::GetFont(), "Press Enter to continue", 16);
            prompt.setFillColor({150, 150, 150, 255});
            sf::FloatRect pb = prompt.getLocalBounds();
            prompt.setPosition({(window.getSize().x - pb.size.x) / 2.f, 380.f});
            window.draw(prompt);
        }

        Signal getSignal() override          { return signal; }
        void   setSignal(Signal s) override  { signal = s; }
    };
}