#include <Enemy.hh>

namespace Entities{
    Enemy::Enemy (string name, int hpMax, string categorie, string statistique, int mercy, string act[]) : Entity(hpMax, name, Attributes::Attack("Enemy Attack", "Basic enemy attack", 1.0))
    {
        this->categorie=categorie;
        this->statistique=statistique;
        this->mercy=mercy;
        for (int i=0; i<4; i++)
        {
            this->act[i]=act[i];
        }

        
    }

    void Enemy::ACT(Action action)
        {
            mercy+=action.GetMercyModifier();
        }
}
