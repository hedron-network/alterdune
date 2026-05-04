#include "Attack.hh"
namespace Attributes
{
    Attack::Attack(std::string name,std::string description,double attackModifier)
    {
        this->name = name;
        this->description = description;
        this->attackModifier = attackModifier;
    }
    Attack::Attack(std::string name,std::string description,double attackModifier,std::vector<Particle>attack)
    :attack(attack)
    {
        Attack(name,description,attackModifier);
    }
    Attack::Attack(){}

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
        // --- Serialize ---
        // Format per particle (one line):
        // posX|posY|velX|velY|speed|angle|steerStrength|displayLag|startupLag
        // |spriteRotationSpeed|shape|movement|radius|rectW|rectH|lifetime
        // |textureName (or NONE)
        std::string Attack::SerializeParticles() const {
            std::ostringstream oss;
            for (size_t i = 0; i < attack.size(); ++i) {
                const Particle& p = attack[i];
                oss << p.position.x        << "|"
                    << p.position.y        << "|"
                    << p.velocity.x        << "|"
                    << p.velocity.y        << "|"
                    << p.speed             << "|"
                    << p.angle             << "|"
                    << p.steerStrength     << "|"
                    << p.displayLag        << "|"
                    << p.startupLag        << "|"
                    << p.spriteRotationSpeed << "|"
                    << shapeToStr(p.shape) << "|"
                    << movToStr(p.movement)<< "|"
                    << p.radius            << "|"
                    << p.Rectsize.x        << "|"
                    << p.Rectsize.y        << "|"
                    << p.lifetime          << "|"
                    << (p.shape == ShapeType::Sprite && i < texNames.size()
                        ? texNames[i] : "NONE");
                if (i + 1 < attack.size())
                    oss << "\n";
            }
            return oss.str();
        }

        // --- Deserialize ---
        // attackData is the multi-line string produced by SerializeParticles()
        // textureLoader is a callable: sf::Texture(const std::string& path)
        // Pass a ParticleManager to rebuild PixelMasks.
        void Attack::BuildAttack(std::string& attackData) {
            attack.clear();
            texNames.clear();

            std::istringstream stream(attackData);
            std::string line;

            while (std::getline(stream, line)) {
                if (line.empty()) continue;

                // Split on '|'
                std::vector<std::string> tok;
                std::istringstream ls(line);
                std::string field;
                while (std::getline(ls, field, '|'))
                    tok.push_back(field);

                // Expect exactly 17 fields
                if (tok.size() != 17)
                    throw std::runtime_error("Malformed particle line: " + line);

                Particle p;
                p.position          = { std::stof(tok[0]),  std::stof(tok[1]) };
                p.velocity          = { std::stof(tok[2]),  std::stof(tok[3]) };
                p.speed             = std::stof(tok[4]);
                p.angle             = std::stof(tok[5]);
                p.steerStrength     = std::stof(tok[6]);
                p.displayLag        = std::stof(tok[7]);
                p.startupLag        = std::stof(tok[8]);
                p.spriteRotationSpeed = std::stof(tok[9]);
                p.shape             = Attributes::strToShape(tok[10]);
                p.movement          =Attributes::strToMov(tok[11]);
                p.radius            = std::stof(tok[12]);
                p.Rectsize          = { std::stof(tok[13]), std::stof(tok[14]) };
                p.lifetime          = std::stof(tok[15]);

                std::string texName = tok[16];
                texNames.push_back(texName);

                // Rebuild sprite + pixel mask if needed
                if (p.shape == ShapeType::Sprite && texName != "NONE") {
                    sf::Texture t;
                    t.loadFromFile(texName);
                    tex.push_back(std::move(t));

                    sf::Sprite spr(tex.back());
                    p.sprite = spr;

                    ParticleManager pm;
                    p.pixelMask = pm.buildMask(tex.back());
                }

                attack.push_back(std::move(p));
            }
        }
    }

namespace Attributes
{
    // --- helpers ---
    static std::string serializeVec2(sf::Vector2f v) {
        return std::to_string(v.x) + "|" + std::to_string(v.y);
    }
    static sf::Vector2f parseVec2(const std::string& x, const std::string& y) {
        return { std::stof(x), std::stof(y) };
    }
    static std::string shapeToStr(ShapeType s) {
        switch(s) {
            case ShapeType::Circle:    return "Circle";
            case ShapeType::Rectangle: return "Rectangle";
            case ShapeType::Sprite:    return "Sprite";
        }
        return "Circle";
    }
    static ShapeType strToShape(const std::string& s) {
        if(s == "Rectangle") return ShapeType::Rectangle;
        if(s == "Sprite")    return ShapeType::Sprite;
        return ShapeType::Circle;
    }
    static std::string movToStr(MovementType m) {
        switch(m) {
            case MovementType::Constant: return "Constant";
            case MovementType::Homing:   return "Homing";
            case MovementType::None:     return "None";
        }
        return "Constant";
    }
    static MovementType strToMov(const std::string& s) {
        if(s == "Homing") return MovementType::Homing;
        if(s == "None")   return MovementType::None;
        return MovementType::Constant;
    }
}