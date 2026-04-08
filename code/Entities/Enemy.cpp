#include <Enemy.hh>

namespace Entities{
    Enemy::Enemy (string name, int hpMax, EnemyType categorie, string description, int mercy, vector<Action> Act) : Entity(hpMax, name, Attributes::Attack("Enemy Attack", "Basic enemy attack", 1.0))
    {
        this->categorie=categorie;
        this->description=description;
        this->mercy=mercy;
        this->Act=Act;

        
    }

    void Enemy::ACT(Action action)
    {
        mercy-=action.GetMercyModifier();
    }

    bool Enemy::Spare()
    {
        if (mercy<0)

        return true;
    }

    string Enemy::GetName()
    {
        return name;
    }

    vector<Action> Enemy::GetAction()
    {
        return Act;
    }



}   

