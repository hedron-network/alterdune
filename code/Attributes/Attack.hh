#ifndef Attack_h
#define Attack_h
#include <string>
#include <sstream>
#include <stdexcept>
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
    std::vector<std::string> texNames;
    std::vector<Particle> attack;
public:
    Attack(std::string name,std::string description,double attackModifier);
    Attack(std::string name,std::string description,double attackModifier,std::vector<Particle> attack);
    Attack();
     ~Attack();
    double GetAttackModifier();
    std::string GetInfoString();
    std::vector<Particle>& GetAttackParticles();
    void BuildAttack(std::string& attackData);
    std::string SerializeParticles() const;
};  
static std::string serializeVec2(sf::Vector2f v) ;

static sf::Vector2f parseVec2(const std::string& x, const std::string& y);
static std::string shapeToStr(ShapeType s);
static ShapeType strToShape(const std::string& s);
static std::string movToStr(MovementType m) ;
static MovementType strToMov(const std::string& s);
}
#endif
