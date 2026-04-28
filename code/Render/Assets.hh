#ifndef Assets_h
#define Assets_h
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Assets {
// PATH

const std::string AssetFolder=".\\asset\\";
const std::string TextureFolder = AssetFolder+"buttons\\";

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

} // namespace Assets
#endif