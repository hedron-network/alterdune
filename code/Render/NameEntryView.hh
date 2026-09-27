#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Views.hh"
#include "Assets.hh"
#include "renderTypes.hh"

namespace Render {

    class NameEntryView : public State {
        std::string name;
        Signal      signal = Signal::None;
        bool        done   = false;

    public:
        NameEntryView() = default;

        const std::string& getName() const { return name; }

        void handleEvent(sf::Event& event, sf::RenderWindow&) override {
            if (done) return;

            if (const auto* te = event.getIf<sf::Event::TextEntered>()) {
                uint32_t c = te->unicode;
                if (c == '\b') {                          // backspace
                    if (!name.empty()) name.pop_back();
                } else if (c == '\r' || c == '\n') {      // enter — confirm
                    if (!name.empty()) { done = true; signal = Signal::POP; }
                } else if (c >= 32 && c < 127 && name.size() < 16) {
                    name += static_cast<char>(c);
                }
            }
        }

        void update(float) override {}

        void draw(sf::RenderWindow& window) override {
            // Prompt
            sf::Text prompt(Assets::GetFont(), "Enter your name:", 28);
            prompt.setFillColor(sf::Color::White);
            sf::FloatRect pb = prompt.getLocalBounds();
            prompt.setPosition({(window.getSize().x - pb.size.x) / 2.f, 240.f});
            window.draw(prompt);

            // Input box background
            sf::RectangleShape box({300.f, 44.f});
            box.setFillColor({30, 30, 30, 255});
            box.setOutlineColor(sf::Color::White);
            box.setOutlineThickness(2.f);
            box.setPosition({(window.getSize().x - 300.f) / 2.f, 300.f});
            window.draw(box);

            // Typed text + blinking cursor
            std::string displayed = name + "_";
            sf::Text input(Assets::GetFont(), displayed, 24);
            input.setFillColor(sf::Color::White);
            sf::FloatRect ib = input.getLocalBounds();
            input.setPosition({(window.getSize().x - ib.size.x) / 2.f, 308.f});
            window.draw(input);

            // Hint
            sf::Text hint(Assets::GetFont(), "Press Enter to confirm  (max 16 chars)", 14);
            hint.setFillColor({150, 150, 150, 255});
            sf::FloatRect hb = hint.getLocalBounds();
            hint.setPosition({(window.getSize().x - hb.size.x) / 2.f, 360.f});
            window.draw(hint);
        }

        Signal getSignal() override         { return signal; }
        void   setSignal(Signal s) override { signal = s; }
    };
}