#include "Attack.hh"
namespace Attributes
{
    Attack::Attack(std::string name,std::string description,double attackModifier,std::vector<Particle> attack)
    :attack(attack)
    {
        this->name = name;
        this->description = description;
        this->attackModifier = attackModifier;
    }
    Attack::~Attack(){}
    double Attack::GetAttackModifier(){
        return attackModifier;
    }
    std::string Attack::GetInfoString(){
        return this->name+"\n"+this->description;
    }
    std::vector<Particle>& Attack::GetAttackParticles(){
        return attack;
    }
    void Attack::BuildAttack(std::string& attackData){
        
    }

}