#include "CombatRenderer.hh"
namespace Render{
    CombatRenderer::CombatRenderer(GameLogic::Combat& combat,const sf::RenderWindow& window):combat(combat){
        trottinetteeMask=particleManager.buildMask(tex);
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
        std::string attkstr = "470|570|0|0|200|0|0|0|0.25|-1.07374e+08|Circle|Constant|2|0|0|4|NONE\n478.658|574.995|0|0|200|1.04667|0|0.05|0.25|-1.07374e+08|Circle|Constant|2|0|0|4|NONE\n478.666|584.991|0|0|200|2.09333|0|0.1|0.25|-1.07374e+08|Circle|Constant|2|0|0|4|NONE\n470.016|590|0|0|200|3.14|0|0.15|0.25|-1.07374e+08|Circle|Constant|2|0|0|4|NONE\n461.35|585.018|0|0|200|4.18667|0|0.2|0.25|-1.07374e+08|Circle|Constant|2|0|0|4|NONE\n461.327|575.023|0|0|200|5.23333|0|0.25|0.25|-1.07374e+08|Circle|Constant|2|0|0|4|NONE";
        circleAttack.BuildAttack(attkstr);
        return;
        circleAttack = Attack("Bullet Circle", "Fires a ring of bullets", 1.0, MakeBulletCircleAttack(
            Origin(),
            /*bulletCount=*/  6,
            /*radius=*/       10.f,
            /*bulletRadius=*/ 2.f,
            /*speed=*/        200.f,
            /*delayStep=*/    0.1f,
            /*lifetime=*/     4.f
        ));
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
        

        if(const auto keyPress = event.getIf<sf::Event::KeyPressed>()){
            const auto keyCode= keyPress->code;
            if(keyCode == Key::B){
                auto sprite = sf::Sprite(tex);
                sprite.setScale(sf::Vector2f(
                40.f / sprite.getLocalBounds().size.x,
                40.f / sprite.getLocalBounds().size.y)
            );
                //particles.push_back(particleManager.makeSprite(Origin()+sf::Vector2f(0,-150),150.f,0,sprite,trottinetteeMask,30));
                particles= circleAttack.GetAttackParticles();
                std::cout<<circleAttack.SerializeParticles()<<endl;
            }
        }
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
                if(hit){std::cout<<"hit;";}
            } else {
                ++it;
            }
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


    
    std::vector<Particle> CombatRenderer::MakeBulletCircleAttack(
    sf::Vector2f origin,
    int bulletCount,
    float radius,
    float bulletRadius,
    float speed,
    float delayStep,   // 0.1s between each bullet appearing
    float lifetime
    ) {
    ParticleManager pm;
    std::vector<Particle> particles;
    particles.reserve(bulletCount);

    // All bullets start moving only after the last one has appeared
    const float moveDelay = (bulletCount - 1) * delayStep;

    for (int i = 0; i < bulletCount; i++) {
        // Angle in radians, starting from top, going clockwise
        float angle = (2.f * 3.14 * i) / bulletCount;

        // Spawn position on the ring
        sf::Vector2f spawnPos = {
            origin.x + radius * std::sin(angle),
            origin.y - radius * std::cos(angle)
        };

        // displayLag staggers visibility: bullet i appears at i * delayStep
        // startupLag delays movement: all bullets wait until the ring is full
        Particle p = pm.makeCircle(
            spawnPos,
            speed,
            angle,
            bulletRadius,
            /*startupLag=*/ moveDelay,
            /*displayLag=*/ i * delayStep,
            /*steerStrength=*/ 0.f,
            MovementType::Constant,
            lifetime
        );

        particles.push_back(p);
    }

    return particles;
}
}