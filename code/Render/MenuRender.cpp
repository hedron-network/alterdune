#include "MenuRender.hh"
namespace Render{
    MenuRender::MenuRender(){
        LoadAssets();
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
    void MenuRender::onButtonPressed(Assets::ButtonId id) {
        
    }
       
    
};