#ifndef Combat_h
#define Combat_h
#include "../Entities/Enemy.hh"
#include "../Entities/Player.hh"
#include "Menu.hh"

namespace GameLogic
{
class Combat
{
private:
    bool isRunning;
public:
    Entities::Player player;
    Entities::Enemy enemy;
    Combat(Entities::Player player, Entities::Enemy enemy);
    void ExecutePlayerTurn(Menu& menu);
    void ExecuteEnemyTurn();
    Entities::Player& GetPlayer();
    bool IsRunning();
    void Attack();
    bool ACT(Menu& menu);
    bool UseItem(Menu& menu);
    void Spare();

};  
}
#endif
