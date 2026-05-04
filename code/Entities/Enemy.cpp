#include "Enemy.hh"

namespace Entities{
    Enemy::Enemy (string name, int hpMax, EnemyType categorie, string description, int mercy, vector<Action> Act) : Entity(hpMax, name, Attributes::Attack("Enemy Attack", "Basic enemy attack", 1.0, {}))
    {
        this->categorie=categorie;
        this->description=description;
        this->mercy=mercy;
        this->Act=Act;  
        this->textures = Assets::LoadEnemyTexture(name);
        this->sprites = Assets::LoadEnemySprites(textures);

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
    vector<sf::Texture>& Enemy::GetTextures(){
        return textures;
    }
    vector<sf::Sprite>& Enemy::GetSprites(){
        return sprites;
    }


}   

