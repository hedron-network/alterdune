#ifndef Attack_h
#define Attack_h
#include <string>
namespace Attributes
{
class Attack
{
private:
    std::string name;
    std::string description;
    double attackModifier;
public:
    Attack(std::string name,std::string description,double attackModifier);
     ~Attack();
    double GetAttackModifier();
    std::string GetInfoString();
};  

}
#endif
