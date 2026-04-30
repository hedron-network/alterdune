#ifndef Game_h
#define Game_h
#include <vector>
#include <random>
#include <algorithm>
#include <optional>
#include <ctime>

#include "Menu.hh"
#include "Combat.hh"
#include "Bestiary.hh"
#include "../FileManager/FileManager.hh"
#include "../Entities/Player.hh"
#include "../Entities/Enemy.hh"
namespace GameLogic
{
class Game
{
private:
    std::optional<Entities::Player> player;
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
    void ShowAndUseItem();


public:
    Game();
    std::optional<Combat> combat;
    void StartGame();

}; 

}
#endif
