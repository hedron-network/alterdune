#include <iostream>
#include <string>
#include <Entity.hh>
#include <Attack.hh>
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

    double Entity::GetAttackModifier()
    {
        return attack.GetAttackModifier();
    }

    int Entity::Attack()
    {
        return (int)attack.GetAttackModifier();       
    }

    void Entity::TakeDamage(int damage, int hp)
    {
        hp=hp-damage;
    }

    void Heal(int amount, int hp, int hpMax)
    {
        if(hp+amount<=hpMax)
        {
            hp=hp+amount;
        }
        else hp=hpMax;
    }
}








