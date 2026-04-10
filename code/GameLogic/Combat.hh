#ifndef Combat_h
#define Combat_h
#include <Enemy.hh>
#include <Player.hh>
#include <Menu.hh>

namespace GameLogic
{
class Combat
{
private:
    Entities::Player player;
    Entities::Enemy enemy;
    bool isRunning;
public:
    Combat(Entities::Player player, Entities::Enemy enemy);
     ~Combat();
    void ExecutePlayerTurn(Menu& menu);
    void ExecuteEnemyTurn();
    Entities::Player GetPlayer();
    bool IsRunning();
    void Attack();
    bool ACT(Menu& menu);
    bool UseItem(Menu& menu);
    void Spare();

};  
}
#endif
