#ifndef CombatRenderer_h
#define CombatRenderer_h
#include <vector>
#include <SFML/Graphics.hpp>

#include "../GameLogic/Combat.hh"
#include "Assets.hh"
namespace Render{
    enum CombatMode{
        MAIN,
        GRAVITY
    };
    class CombatRenderer{
        private:
            sf::Vector2f playerPos;
            sf::Vector2f playerVelocity;
            CombatMode combatMode;
            GameLogic::Combat combat;
            const float PlayerSpeed=150.f;
            
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
        public:
            CombatRenderer(GameLogic::Combat& combat,const sf::RenderWindow& window);
            void handleEvent(sf::Event& event,sf::RenderWindow& window);
            void update(float dt);
            void draw(sf::RenderWindow& window);
    };
    class Particle{
        sf::Vector2f origin;
        sf::Vector2f velocity;
        public:
            virtual sf::Vector2f GetNextPos(float dt)=0;
            virtual bool IsHit(sf::Vector2f pos)=0;
    };
    class Bone :public Particle{
        sf::CircleShape hitbox;
    };
    class Bullet : public Particle{
        sf::RectangleShape hitbox;
    };
}

#endif