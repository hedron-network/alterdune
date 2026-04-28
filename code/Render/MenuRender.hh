#ifndef MenuRender_h
#define MenuRender_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Assets.hh"
namespace Render{
    enum MenuType{
    MAIN_MENU,COMBAT_MENU,ITEM_MENU
};
class MenuRender
{
private:
    const MenuType menuType;
    std::vector<sf::Texture> textures;
    std::vector<Assets::Button> buttons;
    void LoadAssets();
    void FilterButtons();
    std::vector<Assets::ButtonId> GetButtonsToHide(MenuType menuType);
public:
    MenuRender(MenuType menuType);
    ~MenuRender();
    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);
    void AddButtons();
    void onButtonPressed(Assets::ButtonId id);
    void SetComponentVisibility(MenuType menuType);
};

};
#endif