#include "CombatRenderer.hh"
namespace Render{
    CombatRenderer::CombatRenderer(GameLogic::Combat combat,const sf::RenderWindow& window):combat(combat){
        CreateBounds(window);
    }
    void CombatRenderer::CreateBounds(const sf::RenderWindow& window){
        const auto windowSize = window.getSize();
        const float totalWidth=200;
        const float totalHeight=200;
        const float bottomMargin = 40;
        float startX = (windowSize.x - totalWidth) / 2.f;
        float startY = windowSize.y - totalHeight - bottomMargin;
        playerBounds = sf::RectangleShape(sf::Vector2f(totalWidth,totalHeight));
        playerBounds.setOutlineThickness(4);
        playerBounds.setOutlineColor(sf::Color::White);
        playerBounds.setFillColor(sf::Color::Transparent);
        playerBounds.setPosition(sf::Vector2f(startX,startY));
        this->startX=startX;
        this->startY=startY;
        this->endX=startX+totalWidth;
        this->endY=endY+totalHeight;
    }
    inline Vector2 CombatRenderer::Origin(){
        return Vector2((startX+endX)/2.f,(startY+endY)/2.f);
    }
}