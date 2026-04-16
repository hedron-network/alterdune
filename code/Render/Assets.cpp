#include "Assets.hh"
namespace Assets{
std::vector<sf::Texture> LoadButtonTexture(){
    std::vector<sf::Texture> textures;
    for(int i=0;i<buttonNumber;i++){
        sf::Texture tex;
        tex.loadFromFile(TextureFolder + buttonNames[i] + ".png");
        textures.push_back(tex);
    }
    return textures;
}
std::vector<sf::Sprite> LoadButtonSprites(const std::vector<sf::Texture> & textures){
    std::vector<sf::Sprite> sprites;
    for(int i =0;i<buttonNumber;i++){
        sf::Sprite sprite(textures[i]);
        sprite.setTextureRect({{10, 10}, {50, 30}});    
        sprites.push_back(sprite);
    }
    return sprites;
}
std::vector<Button> LoadButtons(const std::vector<sf::Texture> & textures){
    auto sprites = LoadButtonSprites(textures);
    std::vector<Button> buttons;
    for(int i=0; i<buttonNumber;i++){
        buttons.push_back(Button{sprites[i], static_cast<ButtonId>(i),buttonPlacement[i]});
    }
    return buttons;
}
}