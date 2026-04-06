#ifndef Combat_h
#define Combat_h
#include <Enemy.hh>
#include <Player.hh>

namespace GameLogic
{
class Combat
{
private:
    Player player;
    Enemy Enemy;
public:
    Combat(Player player, Enemy Enemy);
     ~Combat();
    void ExecutePlayerTurn();
    void ExecuteEnemyTurn();
};  
}
#endif
