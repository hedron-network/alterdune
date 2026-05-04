#include "Assets.hh"
#include <iostream>
namespace Assets{
std::vector<sf::Texture> LoadButtonTexture(){
    std::vector<sf::Texture> textures;
    textures.reserve(buttonNumber * 2); // prevent reallocation
    for(int i = 0; i < buttonNumber; i++){
        sf::Texture tex, htex;
        tex.loadFromFile(buttonTextureFolder +"ut_button_"+buttonNames[i] + "_normal.png");
        htex.loadFromFile(buttonTextureFolder +"ut_button_"+buttonNames[i] + "_hover.png");
        textures.push_back(std::move(tex));
        textures.push_back(std::move(htex));
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

std::vector<sf::Texture> LoadPlayerTexture(){
    std::vector<sf::Texture> textures;
    int i=0;
    while (FileExist(GUIFolder+"heart_"+std::to_string(i)+".png"))
    {
        std::cout<<"on "<<GUIFolder+"heart_"+std::to_string(i)+".png"<<std::endl;
        sf::Texture tex;
        tex.loadFromFile(GUIFolder+"heart_"+std::to_string(i)+".png");
        tex.setSmooth(true);
        textures.push_back(tex);
        i++;
    }
    std::cout<<"loaded "<<textures.size()<<" textures";
    return textures;
}

std::vector<sf::Texture> LoadEnemyTexture(const std::string& EnemyName){
    std::vector<sf::Texture> textures;
    int i =0;
    while (FileExist(enemyTextureFolder+"enemy_"+EnemyName+std::to_string(i)+".png"))
    {
        sf::Texture tex;
        tex.loadFromFile(enemyTextureFolder+"enemy_"+EnemyName+std::to_string(i)+".png");
        textures.push_back(tex);
        i++;
    }
    return textures;
        
}
sf::Texture LoadSingleTexture(const std::string &path){
    sf::Texture tex;
    tex.loadFromFile(path);
    return tex;
}
std::vector<sf::Sprite> LoadEnemySprites(const std::vector<sf::Texture>& textures){
    return SimpleLoadTexture(textures);
}
std::vector<sf::Sprite> LoadPlayerSprites(const std::vector<sf::Texture>& textures){
    return SimpleLoadTexture(textures);
}


//inline Helpers
inline std::vector<sf::Sprite> SimpleLoadTexture(const std::vector<sf::Texture>& textures){
    std::vector<sf::Sprite> sprites;
    for(int i =0;i<textures.size();i++){
        sf::Sprite sprite(textures[i]);
        sprites.push_back(sprite);
    }
    return sprites;
}
inline bool FileExist (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}
}