#include "Enemy.hh"

namespace Entities{
    Enemy::Enemy (string name, int hpMax, EnemyType categorie, string description, int mercy, vector<Action> Act, vector<Attributes::Attack> attacks) : Entity(hpMax, name, Attributes::Attack("Enemy Attack", "Basic enemy attack", 1.0))
    {
        this->categorie=categorie;
        this->description=description;
        this->mercy=mercy;
        this->Act=Act;  
        this->textures = Assets::LoadEnemyTexture(name);
        this->sprites = Assets::LoadEnemySprites(textures);
        this->attacks=attacks;

    }

    void Enemy::ACT(Action action)
    {
        std::cout<<action.GetDescription()<<std::endl;
        mercy-=action.GetMercyModifier();
    }

    bool Enemy::Spare()
    {
        if (mercy<0){

        return true;
        }
        return false;
    }

    vector<Action> Enemy::GetAction()
    {
        return Act;
    }
    vector<Particle> Enemy::Attack(){
        ShuffleAttacks();
        return attacks.back().GetAttackParticles();
    }
    int Enemy::GetAttackDamage(){
        return attacks.back().GetAttackModifier();
    }
    vector<sf::Texture>& Enemy::GetTextures(){
        return textures;
    }
    vector<sf::Sprite>& Enemy::GetSprites(){
        return sprites;
    }
    void Enemy::ShuffleAttacks(){
        auto rng = std::default_random_engine {static_cast<unsigned>(std::time(nullptr))};
        std::shuffle(this->attacks.begin(), this->attacks.end(), rng);
    }


    EnemyType Enemy::GetCategorie() const
    {
        return categorie;
    }
    int Enemy::GetHpMax() const{
        return this->hpMax;
    }
}   

