#ifndef CombatRenderer_h
#define CombatRenderer_h
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../GameLogic/Combat.hh"
#include "Particle.hh"
#include "Assets.hh"
namespace Render{
    enum CombatMode{
        MAIN,
        GRAVITY
    };
    class CombatRenderer{
        private:
            ParticleManager particleManager;
            std::vector<Particle> particles;
            sf::Vector2f playerPos;
            sf::Vector2f playerVelocity;
            CombatMode combatMode;
            GameLogic::Combat combat;
            const float PlayerSpeed=150.f;
            sf::Texture tex = Assets::LoadSingleTexture(Assets::GUIFolder+"trottinette.png");
            PixelMask trottinetteeMask;
            Attack circleAttack;
            
            float startX;
            float startY;
            float endX;
            float endY;
            
            sf::RectangleShape playerBounds;
            const vector<sf::Texture> playerTextures= Assets::LoadPlayerTexture();
            vector<sf::Sprite> playerSprites = Assets::LoadPlayerSprites(playerTextures);
            
            int playerSpriteIdex;

            void CreateBounds(const sf::RenderWindow &window);
            sf::Vector2f Origin();
            void ChangeTo(CombatMode combatMode);
            void UpdatePos(float dt);
            void HandleInput();
            std::vector<Particle> MakeBulletCircleAttack(sf::Vector2f origin,int bulletCount,float radius,float bulletRadius,float speed,float delayStep,float lifetime);
        public:
            CombatRenderer(GameLogic::Combat& combat,const sf::RenderWindow& window);
            void handleEvent(sf::Event& event,sf::RenderWindow& window);
            void update(float dt);
            void draw(sf::RenderWindow& window);
    };

}

#endif