#include "CombatRenderer.hh"
namespace Render{
    CombatRenderer::CombatRenderer(GameLogic::Combat& combat,const sf::RenderWindow& window):combat(combat){
        CreateBounds(window);
        ChangeTo(CombatMode::MAIN);
        playerPos = Origin();
        for(int i =0;i<playerSprites.size();i++){
            playerSprites[i].setScale(sf::Vector2f(
                20.f / playerSprites[i].getLocalBounds().size.x,
                20.f / playerSprites[i].getLocalBounds().size.y)
            );
            playerSprites[i].setPosition(Origin());
        }
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
        this->endY=startY+totalHeight;
    }
    inline sf::Vector2f CombatRenderer::Origin(){
        return sf::Vector2f((startX+endX)/2.f,(startY+endY)/2.f);
    }
    void CombatRenderer::handleEvent(sf::Event& event,sf::RenderWindow& window){
        if(const auto keyPress = event.getIf<sf::Event::KeyPressed>()){
            const auto keyCode= keyPress->code;
            using namespace sf::Keyboard;
            if(keyCode== Key::Up|| keyCode==Key::Z){
                playerVelocity.y= -PlayerSpeed;
            }
            if(keyCode== Key::Down|| keyCode==Key::S){
                playerVelocity.y= PlayerSpeed;
            }
            if(keyCode== Key::Left|| keyCode==Key::Q){
                playerVelocity.x= -PlayerSpeed;
            }
            if(keyCode== Key::Right|| keyCode==Key::D){
                playerVelocity.x= PlayerSpeed;
            }
        }
        if(const auto keyPress = event.getIf<sf::Event::KeyReleased>()){
            const auto keyCode= keyPress->code;
            using namespace sf::Keyboard;
            if((keyCode== Key::Up|| keyCode==Key::Z)&&playerVelocity.y==-PlayerSpeed){
                playerVelocity.y= 0;
            }
            if((keyCode== Key::Down|| keyCode==Key::S)&&playerVelocity.y==PlayerSpeed){
                playerVelocity.y= 0;
            }
            if((keyCode== Key::Left|| keyCode==Key::Q)&&playerVelocity.x==-PlayerSpeed){
                playerVelocity.x= 0;
            }
            if((keyCode== Key::Right|| keyCode==Key::D)&&playerVelocity.x==PlayerSpeed){
                playerVelocity.x= 0;
            }
        }
        auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        if(playerBounds.getGlobalBounds().contains(mousePosition)){
            playerPos=mousePosition;
            playerVelocity=sf::Vector2f(0,0);
        }
    }
    void CombatRenderer::update(float dt){
        playerPos.x = playerPos.x + playerVelocity.x *dt;
        if(playerPos.x<startX){playerPos.x=startX;}
        if(playerPos.x>endX-playerSprites[playerSpriteIdex].getGlobalBounds().size.x){playerPos.x=endX-playerSprites[playerSpriteIdex].getGlobalBounds().size.x;}
        playerPos.y = playerPos.y + playerVelocity.y *dt;
        if(playerPos.y<startY){playerPos.y=startY;}
        if(playerPos.y>endY-playerSprites[playerSpriteIdex].getGlobalBounds().size.y){playerPos.y=endY-playerSprites[playerSpriteIdex].getGlobalBounds().size.y;}
        for(int i=0;i<playerSprites.size();i++){
            playerSprites[i].setPosition(playerPos);
        }
    }
    void CombatRenderer::draw(sf::RenderWindow& window){
        window.draw(playerBounds);
        window.draw(playerSprites[playerSpriteIdex]);
    }
    void CombatRenderer::ChangeTo(CombatMode combatMode){
        switch (combatMode)
        {
        case CombatMode::MAIN:
            playerSpriteIdex=0;
            break;
        case CombatMode::GRAVITY:
            playerSpriteIdex=2;
            break;
        default:
            playerSpriteIdex=0;
            break;
        }
    }

}