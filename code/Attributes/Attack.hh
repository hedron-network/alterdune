#ifndef Attack_h
#define Attack_h
#include <string>
#include "../Render/Particle.hh"
#include "../Render/Assets.hh"
namespace Attributes
{
class Attack
{
private:
    std::string name;
    std::string description;
    double attackModifier;
    std::vector<sf::Texture> tex;
    std::vector<Particle> attack;
public:
    Attack(std::string name,std::string description,double attackModifier,std::vector<Particle> attack);
     ~Attack();
    double GetAttackModifier();
    std::string GetInfoString();
    std::vector<Particle>& GetAttackParticles();
    void BuildAttack(std::string& attackData);
};  

}
#endif
