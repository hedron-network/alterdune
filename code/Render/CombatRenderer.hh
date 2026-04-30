#ifndef CombatRenderer_h
#define CombatRenderer_h
#include <vector>
#include <SFML/Graphics.hpp>

#include "../GameLogic/Combat.hh"
#include "Assets.hh"
namespace Render{
    struct Vector2{
        float x;
        float y;
        Vector2(float X, float Y){
            this->x=X;this->y=Y;
        };
        Vector2(){
            this->x=0;this->y=0;
        }
    };
    enum CombatMode{
        MAIN,
        GRAVITY
    };
    class CombatRenderer{
        private:
            Vector2 playerPos;
            Vector2 playerVelocity;
            CombatMode combatMode;
            GameLogic::Combat combat;
            
            float startX;
            float startY;
            float endX;
            float endY;

            sf::RectangleShape playerBounds;


            void CreateBounds(const sf::RenderWindow &window);
            Vector2 Origin();
        public:
            CombatRenderer(GameLogic::Combat combat,const sf::RenderWindow& window);
            void handleEvent(sf::Event& event,sf::RenderWindow& window);
            void update(float dt);
            void draw(sf::RenderWindow& window);
    };
}
#endif