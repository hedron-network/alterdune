#ifndef CombatRenderer_h
#define CombatRenderer_h
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../GameLogic/Combat.hh"
#include "Particle.hh"
#include "Assets.hh"
#include "Views.hh"
namespace Render{
    enum CombatMode{
        MAIN,
        GRAVITY
    };
    class CombatRenderer{
        private:
            std::unique_ptr<sf::Text> enemyNameText;
            bool enemyNameInitialized = false;
            bool IsFinished = false;
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
            float grace;
            float startX;
            float startY;
            float endX;
            float endY;
            
            int enemyDamage=0;
            bool hasCombatStarted= false;

            sf::RectangleShape playerBounds;
            const vector<sf::Texture> playerTextures= Assets::LoadPlayerTexture();
            vector<sf::Sprite> playerSprites = Assets::LoadPlayerSprites(playerTextures);
            
            int playerSpriteIdex;

            void CreateBounds(const sf::RenderWindow &window);
            sf::Vector2f Origin();
            void ChangeTo(CombatMode combatMode);
            void UpdatePos(float dt);
            void HandleInput();
            void drawLifeBar(sf::RenderWindow& window);
            void drawEnemyName(sf::RenderWindow& window);
        public:
            CombatRenderer(GameLogic::Combat& combat,const sf::RenderWindow& window);
            void handleEvent(sf::Event& event,sf::RenderWindow& window);
            void update(float dt);
            void draw(sf::RenderWindow& window);
            Signal getSignal();
    };

}

#endif