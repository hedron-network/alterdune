#include "Particle.hh"

    ParticleManager::ParticleManager(){}
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


    bool ParticleManager::checkCollision(const Particle& particle, const sf::FloatRect& target){return true;}
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
    Particle ParticleManager::makeSprite(sf::Vector2f pos,  float speed, float angle,sf::Sprite sprite,float steerStrength, MovementType mov, float lifetime) {
    Particle p;
    p.position = pos;
    p.speed = speed;
    p.angle = angle;
    p.steerStrength = steerStrength;
    p.shape = ShapeType::Sprite;
    p.sprite = sprite;
    p.movement = mov;
    p.lifetime = lifetime;
    return p;
    }
