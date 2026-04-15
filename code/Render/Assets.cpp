#include "Assets.hh"
using namespace std;
namespace Assets{
vector<sf::Texture> LoadButtonTexture(){
    vector<sf::Texture> textures;
    for(int i=0;i<buttonNumber;i++){
        sf::Texture tex;
        tex.loadFromFile(TextureFolder + buttonNames[i] + ".png");
        textures.push_back(tex);
    }
    return textures;
}
vector<sf::Sprite> LoadButtonSprites(const vector<sf::Texture> & textures){
    vector<sf::Sprite> sprites;
    for(int i =0;i<buttonNumber;i++){
        sf::Sprite sprite(textures[i]);
        sprite.setTextureRect({{10, 10}, {50, 30}});    
        sprites.push_back(sprite);
    }
    return sprites;
}
vector<Button> LoadButtons(const vector<sf::Texture> & textures){
    auto sprites = LoadButtonSprites(textures);
    vector<Button> buttons;
    for(int i=0; i<buttonNumber;i++){
        buttons.push_back(Button{sprites[i], static_cast<ButtonId>(i),buttonPlacement[i]});
    }
    return buttons;
}
}