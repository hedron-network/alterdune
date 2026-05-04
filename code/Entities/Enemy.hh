#ifndef Enemy_h
#define Enemy_h

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
#include "../Render/Assets.hh"
#include "../Attributes/Action.hh"
#include "../Attributes/Attack.hh"
#include "../Render/Particle.hh"
#include "Entity.hh"

using namespace std;

namespace Entities
{
    enum EnemyType{
        NORMAL,
        MINIBOSS,
        BOSS
    };
    class Enemy : public Entity {
    private:
    
    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> sprites;
    EnemyType categorie; 
    string description;
    int mercy;
    vector<Action> Act;
    std::vector<Attributes::Attack> attacks;
    void ShuffleAttacks();
    public :
    Enemy (string name, int hpMax, EnemyType categorie, string description, int mercy, vector<Action> Act, std::vector<Attributes::Attack> attacks);

    void ACT(Action action);
    vector <Particle> Attack();
    int GetAttackDamage();
    bool Spare();

    vector<Action> GetAction();

    vector<sf::Texture>& GetTextures();
    vector<sf::Sprite>& GetSprites();

    EnemyType GetCategorie() const;  // retourne this->categorie
    int GetHpMax() const;  // retourne this->hpMax (déjà dans Entity)

        
};  
}

#endif