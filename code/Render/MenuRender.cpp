#include "MenuRender.hh"
#include <iostream>
#include <algorithm>
namespace Render{

    MenuRender::MenuRender(MenuType menuType)
    :menuType(menuType){
        LoadAssets();
        FilterButtons();
        AddButtons();
    }
    MenuRender::~MenuRender() {}
    void MenuRender::LoadAssets() {
        this->textures = Assets::LoadButtonTexture(); // textures stored in member var
        this->buttons = Assets::LoadButtons(this->textures); // sprites point into member var
    }

    void MenuRender::handleClick(sf::Vector2f mousePos) {
        for (auto &b : buttons) {
            if (b.sprite.getGlobalBounds().contains(mousePos)) {
                onButtonPressed(b.id);
            }
        }
    }
    void MenuRender::AddButtons() {
        std::vector<Assets::Button> copy = this->buttons;
        const int x =buttons[0].sprite.getTexture().getSize().x;
        const int y =buttons[0].sprite.getTexture().getSize().y;
        const float staticOffset = 10.f;
        this->buttons.clear();
        for (int i = 0; i < (int)copy.size(); i++) {
            Assets::Button b = copy[i];
            int Voffset = (i >= 2) ? 2 : 1;
            
            sf::Vector2f vect((x+staticOffset) * (i % 2),(y+staticOffset)* Voffset);
            b.sprite.setPosition(vect);
            this->buttons.push_back(b);
        }
    }
    void MenuRender::FilterButtons() {
        auto buttonsToHide = GetButtonsToHide(this->menuType);
        this->buttons.erase(
            std::remove_if(this->buttons.begin(), this->buttons.end(),
                [&buttonsToHide](const Assets::Button& b) {
                    for (Assets::ButtonId id : buttonsToHide)
                        if (b.id == id) return true;
                    return false;
                }),
            this->buttons.end()
        );
}
    std::vector<Assets::ButtonId> MenuRender::GetButtonsToHide(MenuType menuType){
        std::vector<Assets::ButtonId> buttonsToHide;
        switch (menuType)
        {
        case MAIN_MENU:
            buttonsToHide = {
                Assets::ButtonId::ACT, 
                Assets::ButtonId::SPARE
            };
            break;
        case COMBAT_MENU:
            buttonsToHide = {
                Assets::ButtonId::BESTIARY,
                Assets::ButtonId::EXIT
            };
            break;
        default:
            buttonsToHide = {
                Assets::ButtonId::ACT,
                Assets::ButtonId::ATTACK,
                Assets::ButtonId::BESTIARY,
                Assets::ButtonId::ITEM,
                Assets::ButtonId::SPARE,
            };
            break;
        }
        return buttonsToHide;
    }
    
    void MenuRender::onButtonPressed(Assets::ButtonId id) {
        using namespace Assets;
        switch (id)
        {
        case ButtonId::ATTACK:
            std::cout<<"Attack";
            break;
        case ButtonId::ACT:
            std::cout<<"ACT";
            break;
        case ButtonId::BESTIARY:
            std::cout<<"BESTIARY";
            break;
        case ButtonId::ITEM:
            std::cout<<"ITEM";
            break;
        case ButtonId::SPARE:
            std::cout<<"SPARE";
            break;
        case ButtonId::EXIT:
            std::cout<<"Exit";
            break;
        default:
            std::cout<<"gne";
            break;
        }
    }
    void MenuRender::draw(sf::RenderWindow& window) {
    for (auto& b : buttons)
        window.draw(b.sprite);
    }   
    
};