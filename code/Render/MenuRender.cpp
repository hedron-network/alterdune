#include "MenuRender.hh"
namespace Render{
    MenuRender::MenuRender(MenuType menuType)
    :menuType(menuType){
        LoadAssets();
        FilterButtons();
        AddButtons();
    }
    void MenuRender::LoadAssets(){
        this->textures = Assets::LoadButtonTexture();
        this->buttons = Assets::LoadButtons(textures);
    }


    void MenuRender::handleClick(sf::Vector2f mousePos) {
        for (auto &b : buttons) {
            if (b.sprite.getGlobalBounds().contains(mousePos)) {
                onButtonPressed(b.id);
            }
        }
    }
    void MenuRender::AddButtons() {
    std::vector<Assets::Button> copy = this->buttons; // iterate the copy
        this->buttons.clear();
        for (Assets::Button b : copy) {
            int Voffset = (b.placement >= 2) ? 2 : 1;
            sf::Vector2f vect(100.f * (b.placement % 2), 250.f * Voffset);
            b.sprite.setPosition(vect);
            this->buttons.push_back(b);
        }
    }
    void MenuRender::FilterButtons(){
        auto buttonsToHide = GetButtonsToHide(this->menuType);
        for(int i =buttons.size()-1;i>=0;i--){
            for(Assets::ButtonId id : buttonsToHide){
                if(buttons[i].id==id){
                    Assets::Button temp = buttons[buttons.size()-1];
                    buttons[buttons.size()-1] = buttons[i];
                    buttons[i]=temp;
                    buttons.pop_back();
                }
            }
        }
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
        
    }
    void MenuRender::draw(sf::RenderWindow& window) {
    for (auto& b : buttons)
        window.draw(b.sprite);
    }   
    
};