#include "GameLogic/Game.hh"
#include <memory.h>
#include <SFML/Graphics.hpp>

#include "Render/StateManager.hh"
#include "Render/Views.hh"
#include "Render/Assets.hh"

void HandleStateChange(GameLogic::Game& game,sf::RenderWindow& window,Render::StateManager& manager, Render::Signal signal){
    using namespace Render;
    
    switch (signal)
    {
    case Signal::ACTMENU:
        break;
    case Signal::BESTIARYMENU:
        break;
    case Signal::COMBATMENU:
        if(game.combat.value().IsRunning()){
            manager.pushState(std::make_unique<Render::CombatMenu>(window,game.combat.value()));
        }else{
            manager.popState();
        }
        break;
    case Signal::COMBATSTEP:
        game.combat.value().enemy.TakeDamage(game.combat.value().player.Attack());
        manager.pushState(std::make_unique<Render::CombatState>(game.combat.value(),window));
        break;
    case Signal::ITEMMENU:
        manager.pushState(std::make_unique<Render::ItemMenu>(game.combat.value().player.GetItems(),game.combat.value().player,window));
        break;
    case Signal::MAINMENU:
        break;
    case Signal::None:
        break;
    case Signal::POP:
        manager.getCurrentState()->setSignal(Signal::None);
        manager.popState();
        if(auto* state = manager.getCurrentState()){

            state->setSignal(Render::Signal::None);
        }
        if(!game.combat.value().IsRunning()){
            game.NextEncounter();
        }
        break;
    case Signal::POPANDFIGHT:
        manager.getCurrentState()->setSignal(Signal::None);
        manager.popState();
        if(auto* state = manager.getCurrentState()){

            state->setSignal(Render::Signal::None);
        }
        manager.pushState(std::make_unique<Render::CombatState>(game.combat.value(),window));
    default:
        break;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({940, 720}), "Game");
    Assets::LoadFont();
    Render::StateManager manager;
    GameLogic::Game game;
    sf::Clock clock;

    if(!game.combat.has_value()){
        throw -1;
    }
    //manager.pushState(std::make_unique<Render::CombatState>(game.combat.value(),window));
    manager.pushState(std::make_unique<Render::CombatMenu>(window,game.combat.value()));
    while (window.isOpen()) {
         if (auto* state = manager.getCurrentState()){
        HandleStateChange(game,window,manager,state->getSignal());
    }
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
