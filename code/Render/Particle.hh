#ifndef Particle_h
#define Particle_h
#include "Assets.hh"
#include <vector>
#include <math.h>
enum class ShapeType { Circle, Rectangle,Sprite };
enum class MovementType { Constant, Homing,None};

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float angle;
    float steerStrength;
    std::optional<sf::Sprite> sprite;
    ShapeType shape;
    MovementType movement;

    float radius;              // for circle
    sf::Vector2f Rectsize;         // for rectangle

    float lifetime;
};



class ParticleManager{
    private:
    inline void DrawCircle(sf::RenderWindow &window, const Particle& particle);
    inline void DrawRectangle(sf::RenderWindow &window,const Particle& particle);
    inline void DrawSprite(sf::RenderWindow &window, Particle& particle);
    inline sf::Vector2f GetVelocity(const Particle &particle);
    inline void BaseUpdateStep(Particle &particle, float dt);
    inline void UpdateTowardsPlayer(Particle &particle, const sf::Vector2f &PlayerPos, float dt);
    
    public:
    ParticleManager();
    bool checkCollision(const Particle& particle, const sf::FloatRect& target);
    void UpdatePos(Particle &particle, const sf::Vector2f &playerpos, float dt);
    void drawParticle(sf::RenderWindow &window,Particle& particle);
    Particle makeCircle(sf::Vector2f pos, float speed, float angle,float radius,float steerStrength, MovementType mov, float lifetime);
    Particle makeRectangle(sf::Vector2f pos, float speed, float angle,sf::Vector2f size,float steerStrength, MovementType mov, float lifetime);
    Particle makeSprite(sf::Vector2f pos, float speed, float angle,sf::Sprite sprite,float steerStrength, MovementType mov, float lifetime);
    
};
#endif