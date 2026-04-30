#include "GameLogic/Game.hh"
#include <memory.h>
#include <SFML/Graphics.hpp>

#include "Render/StateManager.hh"
#include "Render/Views.hh"

int main() {
    sf::RenderWindow window(sf::VideoMode({940, 720}), "Game");

    Render::StateManager manager;
    manager.pushState(std::make_unique<Render::CombatMenu>(window));

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto* state = manager.getCurrentState())
                state->handleEvent(*event, window);
        }

        auto mPos = sf::Vector2f(sf::Mouse::getPosition(window));
        if (auto* state = manager.getCurrentState())
            state->update(dt);

        window.clear(sf::Color::Black);

        if (auto* state = manager.getCurrentState())
            state->draw(window);

        window.display();
    }
}
/*
int main(){
    GameLogic::Game game;
    game.StartGame(); 
    return 0;
};*/