#ifndef Game_h
#define Game_h
#include <optional>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

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
    void ShuffleEnemies();
    void GameLoop();
    void Fight();
    void Reset();
    bool ShowMenu();
    bool ShowMainMenu();
    void ShowAndUseItem();
    void DisplayStartSummary();
    void DisplayEnding();


public:
    Game();
    std::optional<Combat> combat;
    void StartGame();
    bool NextEncounter();

}; 

}
#endif
