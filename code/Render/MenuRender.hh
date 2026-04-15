#ifndef MenuRender_h
#define MenuRender_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Assets.hh"
namespace Render{
class MenuRender
{
private:
    std::vector<sf::Texture> textures;
    std::vector<Assets::Button> buttons;
    void LoadAssets();
public:
    MenuRender();
    ~MenuRender();
    void handleClick(sf::Vector2f mousePos);
    void AddButtons();
    void onButtonPressed(Assets::ButtonId id);
};

};
#endif