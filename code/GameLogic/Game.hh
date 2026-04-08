#ifndef Game_h
#define Game_h
#include <vector>
#include <random>
#include <algorithm>
#include <optional>

#include <Menu.hh>
#include <FileManager.hh>
#include <Player.hh>
#include <Combat.hh>
#include <Enemy.hh>
namespace GameLogic
{
class Game
{
private:
    Entities::Player player;
    std::optional<Combat> combat;
    std::optional<Bestiary> bestiary;
    Menu menu;
    std::vector<Entities::Enemy> enemies;
    File::FileManager fileManager;

    void LoadExternalData();
    void CreateFirstEncounter();
    bool NextEncounter();
    void ShuffleEnemies();
    void GameLoop();
    void Fight();
    bool ShowBestiary();
    void Reset();
    bool ShowMenu();
    bool ShowMainMenu();


public:
    Game();
     ~Game();
    void StartGame();

};  
}
#endif
