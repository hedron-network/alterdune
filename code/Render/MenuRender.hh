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
    Assets::ButtonId selected;
    sf::RectangleShape buttonRect;
    const MenuType menuType;
    std::vector<sf::Texture> textures;
    std::vector<Assets::Button> buttons;
    int getPrevButtonIndex();
    int getNextButtonIndex();
    void LoadAssets();
    void FilterButtons();
    std::vector<Assets::ButtonId> GetButtonsToHide(MenuType menuType);
    bool isHovered(sf::RenderWindow& window, Assets::Button b);
public:
    void update(float dt);
    MenuRender(MenuType menuType,const sf::RenderWindow& window);
    ~MenuRender();
    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);
    void handleKeyPress(sf::Keyboard::Key key);
    void AddButtons(sf::RenderWindow& window);
    void onButtonPressed(Assets::ButtonId id);
    void SetComponentVisibility(MenuType menuType);
};

};
#endif