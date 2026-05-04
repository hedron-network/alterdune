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
    private:
    int hpMax;

    protected:
    int hp;
    string name;
    Attributes::Attack attack;

    public:
    Entity(int hpMax, string name, Attributes::Attack atk);
    virtual ~Entity();
    int GetHp();
    std::string GetName();
    double GetAttackModifier();
    int Attack();
    void TakeDamage(int damage);
    void Heal(int amount);
    int GetHpMax() const;
};


}
#endif


