#include <Action.hh>
namespace Attributes
{
    Action::Action(std::string name,std::string description,int mercyModifier){
        this->name = name;
        this->description = description;
        this-> mercyModifier;
    }
    Action::~Action(){}
    int Action::GetMercyModifier(){
        return mercyModifier;
    }
    std::string Action::GetInfoString(){
        return this->name+"\n"+this->description;
    }
}