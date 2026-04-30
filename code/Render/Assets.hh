#ifndef Assets_h
#define Assets_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>

namespace Assets {
// PATH

const std::string AssetFolder=".\\asset\\";
const std::string buttonTextureFolder = AssetFolder+"buttons\\";
const std::string enemyTextureFolder = AssetFolder+"enemy\\";
const std::string GUIFolder= AssetFolder+"GUI\\";

// Buttons assets
constexpr int buttonNumber = 6;

const std::string buttonNames[buttonNumber]{
    "ATTACK","ACT","ITEM","SPARE","BESTIARY","EXIT"
};

enum ButtonId {
    ATTACK,
    ACT,
    ITEM,
    SPARE,
    BESTIARY,
    EXIT
};

const int buttonPlacement[buttonNumber]{
    0,1,2,3,2,3
};

struct Button {
    sf::Sprite sprite;
    sf::Sprite hover_sprite;
    ButtonId id;
    int placement;

    Button(const sf::Sprite& s,const sf::Sprite &hs ,ButtonId i, int p)
        : sprite(s),hover_sprite(hs), id(i), placement(p){}
};
// Helper function declarations
std::vector<sf::Texture> LoadButtonTexture();
std::vector<sf::Sprite> LoadButtonSprites(const std::vector<sf::Texture>& textures);
std::vector<Button> LoadButtons(std::vector<sf::Texture>& textures);
std::vector<sf::Texture> LoadEnemyTexture(const std::string& EnemyName);
std::vector<sf::Sprite> LoadEnemySprites(const std::vector<sf::Texture>& textures);
std::vector<sf::Texture> LoadPlayerTexture();
std::vector<sf::Sprite> LoadPlayerSprites(const std::vector<sf::Texture> & textures);



std::vector<sf::Sprite> SimpleLoadTexture(const std::vector<sf::Texture> & textures);
bool FileExist(const std::string &path);

} // namespace Assets
#endif