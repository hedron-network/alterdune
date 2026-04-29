#include "MenuRender.hh"
#include <iostream>
#include <algorithm>
namespace Render{

    MenuRender::MenuRender(MenuType menuType,sf::RenderWindow& window)
    :menuType(menuType){
        LoadAssets();
        FilterButtons();
        AddButtons(window);
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
    void MenuRender::AddButtons(sf::RenderWindow& window) {
        auto windowSize =window.getSize();
        std::vector<Assets::Button> copy = this->buttons;
        const int buttonWidth =buttons[0].sprite.getTexture().getSize().x;
        const int buttonHeight =buttons[0].sprite.getTexture().getSize().y;
        const float staticOffset = 10.f;
        const float bottomMargin = 40.f;

        const int cols = 4;
        const int rows =1;

        float totalWidth = cols * buttonWidth + (cols - 1) * staticOffset;
        float totalHeight = rows * buttonHeight + (rows - 1) * staticOffset;

        float startX = (windowSize.x - totalWidth) / 2.f;
        float startY = windowSize.y - totalHeight - bottomMargin;

        this->buttons.clear();
        for (int i = 0; i < (int)copy.size(); i++) {
            Assets::Button b = copy[i];
            int col = i % cols;
            int row = i / cols;

            float x = startX + col * (buttonWidth + staticOffset);
            float y = startY + row * (buttonHeight + staticOffset);

            b.sprite.setPosition({x, y});
            b.hover_sprite.setPosition({x, y});

            this->buttons.push_back(b);
        }
    }
    bool MenuRender::isHovered(sf::RenderWindow& window, Assets::Button b) {
        auto mousePixel = sf::Mouse::getPosition(window);
        auto mouseWorld = window.mapPixelToCoords(mousePixel);
        return b.sprite.getGlobalBounds().contains(
            sf::Vector2f((float)mouseWorld.x,(float)mouseWorld.y)
        );
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
    void MenuRender::update(float dt){
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
        if(isHovered(window,b)){
            window.draw(b.hover_sprite);
        }
        else{
            window.draw(b.sprite);
        }

    }   
    
};