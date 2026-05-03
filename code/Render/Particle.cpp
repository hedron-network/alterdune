#include "Particle.hh"

    ParticleManager::ParticleManager(){}
    bool ParticleManager::CheckAndUpdateLifetime(Particle &particle,const float &dt){
        particle.lifetime -=dt;
        if(particle.lifetime<=0){
            return true;
        }
        return false;
    }
    
    void ParticleManager::update(Particle &particle, const sf::Vector2f &PlayerPos, float dt){
        UpdatePos(particle,PlayerPos,dt);
        if (particle.shape == ShapeType::Sprite){
            const auto rotation =particle.sprite.value().getRotation().asDegrees();
            particle.sprite.value().setRotation(
                sf::degrees(rotation + particle.spriteRotationSpeed * dt)
            );
        }
    }
    
    void ParticleManager::UpdatePos(Particle &particle, const sf::Vector2f &PlayerPos, float dt){
        switch (particle.movement)
        {
        case MovementType::Constant:
            BaseUpdateStep(particle,dt);
            break;
        case MovementType::Homing:
            UpdateTowardsPlayer(particle,PlayerPos,dt);
            break;
        default:
            BaseUpdateStep(particle,dt);
            break;
        }
    }
    
    inline void ParticleManager::BaseUpdateStep(Particle &particle, float dt){
        const float speedX = particle.speed*sin(particle.angle);
        const float speedY = particle.speed*cos(particle.angle);
        particle.position.x+= speedX* dt;
        particle.position.y+= speedY*dt;
    }
    inline void ParticleManager::UpdateTowardsPlayer(Particle &particle, const sf::Vector2f &PlayerPos, float dt){
        const auto desiredPos= (PlayerPos-particle.position).normalized()*particle.speed;
            auto steer = desiredPos - particle.velocity;
            if (steer.length() > particle.steerStrength){
                steer = steer.normalized() * particle.steerStrength;
            }
            particle.velocity += steer * dt;
            if ( particle.velocity.length()> particle.speed){
               particle.velocity = particle.velocity.normalized()* particle.speed;
            }
            particle.position += particle.velocity * dt;
    }
    inline sf::Vector2f ParticleManager::GetVelocity(const Particle &particle){
        const float speedX = particle.speed*sin(particle.angle);
        const float speedY = particle.speed*cos(particle.angle);
        return sf::Vector2f(speedX,speedY);
    }


   bool ParticleManager::checkCollision(const Particle& particle, const sf::FloatRect& target){
        switch (particle.shape)
        {
        case ShapeType::Circle:
        {
            // Find the closest point on the rect to the circle center
            float closestX = std::clamp(particle.position.x, target.position.x, target.position.x + target.size.x);
            float closestY = std::clamp(particle.position.y, target.position.y, target.position.y + target.size.y);

            float dx = particle.position.x - closestX;
            float dy = particle.position.y - closestY;
            return (dx * dx + dy * dy) <= (particle.radius * particle.radius);
        }
        case ShapeType::Rectangle:
        {
            // Build the particle's rect and check intersection
            sf::FloatRect particleRect(
                sf::Vector2f(particle.position.x - particle.Rectsize.x / 2.f,
                            particle.position.y - particle.Rectsize.y / 2.f),
                particle.Rectsize
            );
            return particleRect.findIntersection(target).has_value();
        }
        case ShapeType::Sprite:
        {
            pixelCollision(particle,target);
        }
        default:
            return false;
        }
    }
    PixelMask ParticleManager::buildMask(const sf::Texture& tex){
        PixelMask pm;
        auto img = tex.copyToImage();
        pm.width  = img.getSize().x;
        pm.height = img.getSize().y;
        for(unsigned y = 0; y < pm.height; y++)
            for(unsigned x = 0; x < pm.width; x++)
                pm.mask.push_back(img.getPixel({x,y}).a > 128);
        return pm;
    }
    bool ParticleManager::pixelCollision(const Particle& particle, const sf::FloatRect& target){
        const auto mask = particle.pixelMask.value();
        auto bounds = particle.sprite.value().getGlobalBounds();
        auto intersection = bounds.findIntersection(target);
        if(!intersection.has_value()) return false;

        // map intersection back into texture space
        float scaleX = mask.width  / bounds.size.x;
        float scaleY = mask.height / bounds.size.y;

        int x0 = (int)((intersection->position.x - bounds.position.x) * scaleX);
        int y0 = (int)((intersection->position.y - bounds.position.y) * scaleY);
        int x1 = (int)((intersection->position.x + intersection->size.x - bounds.position.x) * scaleX);
        int y1 = (int)((intersection->position.y + intersection->size.y - bounds.position.y) * scaleY);

        for(int y = y0; y < y1; y++)
            for(int x = x0; x < x1; x++)
                if(mask.mask[y * mask.width + x]) return true;

        return false;
    }
    void ParticleManager::drawParticle(sf::RenderWindow &window, Particle& particle){
        switch (particle.shape)
        {
        case ShapeType::Circle:
            DrawCircle(window,particle);
            break;
        case ShapeType::Rectangle:
            DrawRectangle(window,particle);
            break;
        case ShapeType::Sprite:
            DrawSprite(window,particle);
            break;
        default:
            break;
        }
    }
    inline void ParticleManager::DrawCircle(sf::RenderWindow &window,const Particle& particle){
        const float radius =particle.radius;
        auto particleShape = sf::CircleShape(radius);
        particleShape.setPosition(sf::Vector2f(particle.position.x-radius,particle.position.y-radius));
        window.draw(particleShape);
    }
    inline void ParticleManager::DrawRectangle(sf::RenderWindow &window,const Particle& particle){
        auto particleShape = sf::RectangleShape(particle.Rectsize);
        particleShape.setPosition(sf::Vector2f(particle.position.x-particle.Rectsize.x/2.f,particle.position.y-particle.Rectsize.y/2.f));
        window.draw(particleShape);
    }
    inline void ParticleManager::DrawSprite(sf::RenderWindow &window, Particle& particle){
        particle.sprite.value().setPosition(particle.position);
        window.draw(particle.sprite.value());
    }

    /// @brief 
     /// @param pos World Pos
    /// @param speed World Speed
    /// @param angle Initial Angle
    /// @param radius Radius of the circle in px
    /// @param steerStrength Steering strength
    /// @param mov Movement type
    /// @param lifetime Lifetime in seconds
    /// @return Particle
    Particle ParticleManager::makeCircle(sf::Vector2f pos, float speed, float angle,float radius,float steerStrength, MovementType mov, float lifetime) {
    Particle p;
    p.position = pos;
    p.speed = speed;
    p.angle=angle;
    p.steerStrength = steerStrength;
    p.shape = ShapeType::Circle;
    p.radius = radius;
    p.movement = mov;
    p.lifetime = lifetime;
    return p;
    }
    /// @brief 
    /// @param pos World Pos
    /// @param speed World Speed
    /// @param angle Initial Angle
    /// @param size Vector of the rectangles sizes in px
    /// @param steerStrength Steering strength
    /// @param mov Movement type
    /// @param lifetime Lifetime in seconds
    /// @return Particle
    Particle ParticleManager::makeRectangle(sf::Vector2f pos, float speed, float angle,sf::Vector2f size,float steerStrength, MovementType mov, float lifetime) {
    Particle p;
    p.position = pos;
    p.speed = speed;
    p.angle = angle;
    p.steerStrength = steerStrength;
    p.shape = ShapeType::Rectangle;
    p.Rectsize = size;
    p.movement = mov;
    p.lifetime = lifetime;
    return p;
    }
    /// @brief 
    /// @param pos World Pos
    /// @param speed World Speed
    /// @param angle Initial Angle
    /// @param sprite Sprite
    /// @param pixelMask Pixel Mask
    /// @param spriteRotationSpeed Sprite rotation speed as Degree/second
    /// @param steerStrength Steering strength
    /// @param mov Movement type
    /// @param lifetime Lifetime in seconds
    /// @return Particle
    Particle ParticleManager::makeSprite(sf::Vector2f pos,  float speed, float angle,sf::Sprite sprite,PixelMask pixelMask,float spriteRotationSpeed,float steerStrength, MovementType mov, float lifetime) {
    Particle p;
    p.position = pos;
    p.speed = speed;
    p.angle = angle;
    p.spriteRotationSpeed = spriteRotationSpeed;
    p.steerStrength = steerStrength;
    p.shape = ShapeType::Sprite;
    p.sprite = sprite;
    p.pixelMask = pixelMask;
    p.movement = mov;
    p.lifetime = lifetime;
    return p;
    }
