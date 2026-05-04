#include <iostream>
#include <string>
#include "Entity.hh"
using namespace std;
using namespace Attributes;
namespace Entities{

    Entity::Entity(int hpMax, string name, Attributes::Attack atk)
        : attack(atk)
    {
        this->hpMax=hpMax;
        this->name=name;
        this->hp=hpMax;
    }

    Entity::~Entity() {}

    int Entity::GetHp()
    {
        return hp;
    }
    string Entity::GetName()
    {
        return name;
    }

    double Entity::GetAttackModifier()
    {
        return attack.GetAttackModifier();
    }

    int Entity::Attack()
    {
        return (int)attack.GetAttackModifier();       
    }

    void Entity::TakeDamage(int damage)
    {
        if(hp-damage>=0){
            hp=hp-damage;
        }
        else{
            hp=0;
        }
    }

    void Entity::Heal(int amount)
    {
        if(hp+amount<=hpMax)
        {
            hp=hp+amount;
        }
        else hp=hpMax;
    }


    EnemyType GetCategorie()
    {
        return this->categorie
    }

    int GetHpMax()
    {
        return this->hpMax;
    }
}








