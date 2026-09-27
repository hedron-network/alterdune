#ifndef Entity_h
#define Entity_h
#include <iostream>
#include <string>
#include "../Attributes/Attack.hh"
using namespace std;
using namespace Attributes;


namespace Entities
{


class Entity {
    protected:
    int hpMax;
    int hp;
    string name;
    Attributes::Attack attack;

    public:
    Entity(int hpMax, string name, Attributes::Attack atk);
    virtual ~Entity();
    int GetHp();
    std::string GetName() const;
    double GetAttackModifier();
    int Attack();
    void TakeDamage(int damage);
    void Heal(int amount);
    int GetHpMax() const;
};


}
#endif


