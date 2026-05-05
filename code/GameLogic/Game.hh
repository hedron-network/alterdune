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
    struct PlayerStats
    {
        int numberOfSpares=0;
        int numberOfKills=0;
        int numberOfVictories=0;
    };
class Game
{
private:
    std::optional<Entities::Player> player;
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
    PlayerStats stats;
    void recordWin(bool hasSpared);
    Bestiary bestiary;
    Game();
    std::optional<Combat> combat;
    void StartGame();
    bool NextEncounter();

}; 

}
#endif
