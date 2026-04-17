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
    void MenuRender::AddButtons(){
        const int MaxButton = 4;
        for(Assets::Button b:this->buttons){
            int Voffset= 1;
            if (b.placement >=2){
                Voffset=2;
            }
            sf::Vector2f vect(100.f * (b.placement%2), 250.f*Voffset);
            b.sprite.setPosition(vect);
            buttons.push_back(b);
        }
    }
    void MenuRender::FilterButtons(){
        auto buttonsToHide = GetButtonsToHide(this->menuType);
        int numberOfButtonsToPop=0;
        for(int i =buttons.size()-1;i>=0;i--){
            for(Assets::ButtonId id : buttonsToHide){
                if(buttons[i].id==id){
                    Assets::Button temp = buttons[buttons.size()-1];
                    buttons[buttons.size()-1] = buttons[i];
                    buttons[i]=temp;
                    numberOfButtonsToPop++;
                }
            }
        }
        for(int i=0;i<numberOfButtonsToPop;i++){
            buttons.pop_back();
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
       
    
};