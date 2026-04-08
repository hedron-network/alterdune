#include <Attack.hh>
namespace Attributes
{
    Attack::Attack(std::string name,std::string description,double attackModifier){
        this->name = name;
        this->description = description;
        this->attackModifier = attackModifier;
    }
    double Attack::GetAttackModifier(){
        return attackModifier;
    }
    std::string Attack::GetInfoString(){
        return this->name+"\n"+this->description;
    }
}