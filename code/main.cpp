#include "GameLogic/Game.hh"
#include <memory.h>
#include <SFML/Graphics.hpp>

#include "Render/StateManager.hh"
#include "Render/Views.hh"
#include "Render/Assets.hh"
#include "Render/BestiaryView.hh"
#include "Render/StatsView.hh"
#include "Render/EndingView.hh"
#include "Render/NameEntryView.hh"

void HandleStateChange(GameLogic::Game& game,sf::RenderWindow& window,Render::StateManager& manager, Render::Signal signal){
    using namespace Render;
    
    switch (signal)
    {
    case Signal::STATSMENU:
        manager.pushState(std::make_unique<Render::StatsView>(
        game.combat.value().player,game.stats, window));
    break;
    case Signal::ACTMENU:
        manager.pushState(std::make_unique<Render::ActMenu>(
        game.combat.value().enemy.GetAction(),
        game.combat.value().enemy,
        game.combat.value().player,
        window));
        break;
    case Signal::BESTIARYMENU:
        manager.pushState(std::make_unique<Render::BestiaryView>(game.bestiary));
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
        manager.pushState(std::make_unique<Render::ItemMenu>(game.combat.value().player.GetItems(),game.combat.value().player,window,false));
        break;
    case Signal::ITEMMENUFROMMAIN:
        manager.pushState(std::make_unique<Render::ItemMenu>(game.combat.value().player.GetItems(),game.combat.value().player,window,true));
        break;
    case Signal::ENDING:
        manager.pushState(std::make_unique<Render::EndingView>(game.stats));
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
            game.bestiary.AddEnemy(game.combat.value().enemy,false);
            game.recordWin(false);
            manager.popState();
            if(auto* state = manager.getCurrentState()){

                state->setSignal(Render::Signal::None);
            }
            game.NextEncounter();
            if (game.stats.numberOfVictories >= 10|| game.combat.value().player.GetHp()<=0)
            {
                manager.pushState(std::make_unique<Render::EndingView>(game.stats));
            }
        }
        break;
    case Signal::POPANDFIGHT:
        manager.getCurrentState()->setSignal(Signal::None);
        manager.popState();
        if(auto* state = manager.getCurrentState()){

            state->setSignal(Render::Signal::None);
        }
        manager.pushState(std::make_unique<Render::CombatState>(game.combat.value(),window));
        break;
    case Signal::SPARE:
        game.bestiary.AddEnemy(game.combat.value().enemy,true);
        game.recordWin(true);
        manager.getCurrentState()->setSignal(Signal::None);
        manager.popState();
        if(auto* state = manager.getCurrentState()){

            state->setSignal(Render::Signal::None);
        }
        game.NextEncounter();
    default:
        break;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({940, 720}), "Game");
    Assets::LoadFont();
    
    Render::StateManager manager;
    std::string playerName;
{
    auto* nameView = new Render::NameEntryView();
    manager.pushState(std::unique_ptr<Render::State>(nameView));

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (auto* s = manager.getCurrentState())
                s->handleEvent(*event, window);
        }

        if (auto* s = manager.getCurrentState())
            if (s->getSignal() == Render::Signal::POP) {
                playerName = nameView->getName();   // grab name before pop
                manager.popState();
                break;
            }

        window.clear(sf::Color::Black);
        if (auto* s = manager.getCurrentState()) s->draw(window);
        window.display();
    }
}
    GameLogic::Game game(playerName);
    sf::Clock clock;

    if(!game.combat.has_value()){
        throw -1;
    }
    //manager.pushState(std::make_unique<Render::CombatState>(game.combat.value(),window));
    manager.pushState(std::make_unique<Render::MainMenu>(window));
    manager.pushState(std::make_unique<Render::StatsView>(game.combat.value().player,game.stats,window));
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
