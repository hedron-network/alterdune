#include "CombatRenderer.hh"
namespace Render{
    CombatRenderer::CombatRenderer(GameLogic::Combat& combat,const sf::RenderWindow& window):combat(combat){
        IsFinished = false;
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
        grace = 3;
    }
    Render::Signal CombatRenderer::getSignal(){
        if(!IsFinished){
            return Render::Signal::None;
        }
        return Render::Signal::POP;
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
        using namespace sf::Keyboard;
        if(const auto keyPress = event.getIf<sf::Event::KeyReleased>()){
            const auto keyCode= keyPress->code;
            using namespace sf::Keyboard;
            if((keyCode== Key::Up|| keyCode==Key::Z)&&playerVelocity.y<0){
                playerVelocity.y= 0;
            }
            if((keyCode== Key::Down|| keyCode==Key::S)&&playerVelocity.y>0&& combatMode!= CombatMode::GRAVITY){
                playerVelocity.y= 0;
            }
            if((keyCode== Key::Left|| keyCode==Key::Q)&&playerVelocity.x<0){
                playerVelocity.x= 0;
            }
            if((keyCode== Key::Right|| keyCode==Key::D)&&playerVelocity.x>0){
                playerVelocity.x= 0;
            }
        }
        auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        if(playerBounds.getGlobalBounds().contains(mousePosition)){
            window.setMouseCursorVisible(false);
            playerPos=mousePosition;
            playerVelocity=sf::Vector2f(0,0);
        }
        else{
            window.setMouseCursorVisible(true);
        }
    }
    void CombatRenderer::HandleInput(){
        using namespace sf::Keyboard;
        if(isKeyPressed(Key::Up)||isKeyPressed(Key::Z)){
            playerVelocity.y= -PlayerSpeed;
        }
        if(isKeyPressed(Key::Down)||isKeyPressed(Key::S)){
            playerVelocity.y+= PlayerSpeed;
        }
        if(isKeyPressed(Key::Left)||isKeyPressed(Key::Q)){
            playerVelocity.x= -PlayerSpeed;
        }
        if(isKeyPressed(Key::Right)||isKeyPressed(Key::D)){
            playerVelocity.x+= PlayerSpeed;
        }
        if (playerVelocity != sf::Vector2f(0,0)){
            playerVelocity= playerVelocity.normalized()*PlayerSpeed;
        }
    }
    void CombatRenderer::update(float dt){
        if(grace<=0 && hasCombatStarted ==false){
            particles= combat.enemy.Attack();
            enemyDamage= combat.enemy.GetAttackDamage();
            hasCombatStarted=true;
            std::cout<<enemyDamage;
            std::cout<<particles.size();
        }
        grace-=dt;
        HandleInput();
        UpdatePos(dt);
        for(int i=0;i<playerSprites.size();i++){
            playerSprites[i].setPosition(playerPos);
        }
        sf::FloatRect playerRect = playerSprites[playerSpriteIdex].getGlobalBounds();

        for(auto it = particles.begin(); it != particles.end();){
            particleManager.update(*it, playerRect.getCenter(), dt);

            bool hit      = particleManager.checkCollision(*it, playerRect);
            bool expired  = particleManager.CheckAndUpdateLifetime(*it, dt);

            if(hit || expired){
                it = particles.erase(it);
                if(hit){std::cout<<"hit;";
                combat.GetPlayer().TakeDamage(enemyDamage);
                if(combat.GetPlayer().GetHp()<=0){
                    IsFinished=true;
                };
                }
            } else {
                ++it;
            }
        }
       if(particles.size()==0 && grace<=-2){
            IsFinished=true;
       }
    }
    void CombatRenderer::UpdatePos(float dt){
        playerPos.x = playerPos.x + playerVelocity.x *dt;
        if(playerPos.x<startX){playerPos.x=startX;}
        if(playerPos.x>endX-playerSprites[playerSpriteIdex].getGlobalBounds().size.x){playerPos.x=endX-playerSprites[playerSpriteIdex].getGlobalBounds().size.x;}
        playerPos.y = playerPos.y + playerVelocity.y *dt;
        if(playerPos.y<startY){playerPos.y=startY;}
        if(playerPos.y>endY-playerSprites[playerSpriteIdex].getGlobalBounds().size.y){playerPos.y=endY-playerSprites[playerSpriteIdex].getGlobalBounds().size.y;}
    }
    void CombatRenderer::draw(sf::RenderWindow& window){
        drawLifeBar(window);
        drawEnemyLifeBar(window);
        drawEnemyName(window);
        window.draw(playerBounds);
        window.draw(playerSprites[playerSpriteIdex]);
        for(Particle& p:particles){
            if(p.displayLag>0){continue;}
            particleManager.drawParticle(window,p);
        }
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
    void CombatRenderer::drawLifeBar(sf::RenderWindow& window) {
        const float barWidth  = endX - startX;   // same width as the combat box
        const float barHeight = 10.f;
        const float barY      = endY + 18.f;
        const float barX      = startX;

        auto& player   = combat.GetPlayer();
        float maxHp    = static_cast<float>(100);
        float currentHp = static_cast<float>(player.GetHp());
        float ratio    = std::clamp(currentHp / maxHp, 0.f, 1.f);

        // Background (empty bar)
        sf::RectangleShape bgBar(sf::Vector2f(barWidth, barHeight));
        bgBar.setPosition(sf::Vector2f(barX, barY));
        bgBar.setFillColor(sf::Color::Red);

        // Foreground (filled portion)
        sf::RectangleShape fgBar(sf::Vector2f(barWidth * ratio, barHeight));
        fgBar.setPosition(sf::Vector2f(barX, barY));
        fgBar.setFillColor(sf::Color::Yellow);

        window.draw(bgBar);
        window.draw(fgBar);
    }
    void CombatRenderer::drawEnemyName(sf::RenderWindow& window) {
        if (!enemyNameText) {
            enemyNameText = std::make_unique<sf::Text>(Assets::GetFont(), combat.enemy.GetName(), 24);
            enemyNameText->setFillColor(sf::Color::White);
        }

        sf::FloatRect bounds = enemyNameText->getLocalBounds();
        float x = (window.getSize().x - bounds.size.x) / 2.f;
        enemyNameText->setPosition(sf::Vector2f(x, 20.f));

        window.draw(*enemyNameText);
    }
    void CombatRenderer::drawEnemyLifeBar(sf::RenderWindow& window){
        const float barWidth  = endX - startX;   // same width as the combat box
        const float barHeight = 10.f;
        const float barY      = 20.f + 60.f;
        const float barX      = startX;

        auto& enemy   = combat.enemy;
        float maxHp    = static_cast<float>(enemy.GetHpMax());
        float currentHp = static_cast<float>(enemy.GetHp());
        float ratio    = std::clamp(currentHp / maxHp, 0.f, 1.f);

        // Background (empty bar)
        sf::RectangleShape bgBar(sf::Vector2f(barWidth, barHeight));
        bgBar.setPosition(sf::Vector2f(barX, barY));
        bgBar.setFillColor(sf::Color::Red);

        // Foreground (filled portion)
        sf::RectangleShape fgBar(sf::Vector2f(barWidth * ratio, barHeight));
        fgBar.setPosition(sf::Vector2f(barX, barY));
        fgBar.setFillColor(sf::Color::Yellow);

        window.draw(bgBar);
        window.draw(fgBar);
    }

}