#ifndef Particle_h
#define Particle_h
#include "Assets.hh"
#include <vector>
#include <cmath>
#include <algorithm>
enum class ShapeType { Circle, Rectangle,Sprite };
enum class MovementType { Constant, Homing,None};

struct PixelMask {
    std::vector<bool> mask;
    unsigned int width, height;
};
struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float angle;
    float steerStrength;
    float displayLag;
    float startupLag;
    std::optional<sf::Sprite> sprite;
    float spriteRotationSpeed;
    std::optional<PixelMask> pixelMask;
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
    bool pixelCollision(const Particle& particle, const sf::FloatRect& target);
    void UpdatePos(Particle &particle, const sf::Vector2f &playerpos, float dt);
    
    
    public:
    ParticleManager();
    PixelMask buildMask(const sf::Texture& tex);
    bool CheckAndUpdateLifetime(Particle &particle,const float &dt);
    bool checkCollision(const Particle& particle, const sf::FloatRect& target);
    void update(Particle &particle, const sf::Vector2f &PlayerPos, float dt);
    void drawParticle(sf::RenderWindow &window,Particle& particle);
    Particle makeCircle(sf::Vector2f pos, float speed, float angle,float radius,float startupLag=0,float displayLag=0,float steerStrength=0, MovementType mov=MovementType::Constant, float lifetime=3);
    Particle makeRectangle(sf::Vector2f pos, float speed, float angle,sf::Vector2f size,float startupLag=0,float displayLag=0,float steerStrength=0, MovementType mov=MovementType::Constant, float lifetime=3);
    Particle makeSprite(sf::Vector2f pos, float speed, float angle,sf::Sprite sprite,PixelMask pixelMask,float spriteRotationSpeed=0,float startupLag=0,float displayLag=0,float steerStrength=0, MovementType mov=MovementType::Constant, float lifetime=3);
    
};
#endif