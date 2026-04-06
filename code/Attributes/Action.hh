#ifndef Action_h
#define Action_h
#include <string>
namespace Attributes
{
class Action
{
private:
    std::string name;
    std::string description;
    int mercyModifier;
public:
    Action(std::string name,std::string description,int mercyModifier);
     ~Action();
    int GetMercyModifier();
    std::string GetInfoString();
};  

}
#endif
