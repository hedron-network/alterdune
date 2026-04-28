#include "Assets.hh"
namespace Assets{
std::vector<sf::Texture> LoadButtonTexture(){
    std::vector<sf::Texture> textures;
    for(int i=0;i<buttonNumber;i++){
        sf::Texture tex;
        sf::Texture htex;
        tex.loadFromFile(TextureFolder + +"ut_button_"+buttonNames[i] + "_normal.png");
        htex.loadFromFile(TextureFolder + +"ut_button_"+buttonNames[i] + "_hover.png");
        textures.push_back(tex);
        textures.push_back(htex);
    }
    return textures;
}
std::vector<sf::Sprite> LoadButtonSprites(const std::vector<sf::Texture> & textures){
    std::vector<sf::Sprite> sprites;
    for(int i =0;i<textures.size();i+=2){
        sf::Sprite sprite(textures[i]);
        sf::Sprite hover_sprite(textures[i+1]);  
        sprites.push_back(sprite);
        sprites.push_back(hover_sprite);
    }
    return sprites;
}
std::vector<Button> LoadButtons(std::vector<sf::Texture>& textures) {
    std::vector<Button> buttons;
    for (int i = 0; i < buttonNumber; i++) {
        // textures[i*2] and textures[i*2+1] are stable in the stored vector
        sf::Sprite sprite(textures[i * 2]);
        sf::Sprite hover_sprite(textures[i * 2 + 1]);
        buttons.push_back(Button{sprite, hover_sprite,
            static_cast<ButtonId>(i), buttonPlacement[i]});
    }
    
    return buttons;
}
}