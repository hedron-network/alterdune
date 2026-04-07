#ifndef Combat_h
#define Combat_h
#include <Enemy.hh>
#include <Player.hh>

namespace GameLogic
{
class Combat
{
private:
    Entities::Player player;
    Entities::Enemy Enemy;
    bool IsRunning;
public:
    Combat(Entities::Player player, Entities::Enemy Enemy);
     ~Combat();
    void ExecutePlayerTurn();
    void ExecuteEnemyTurn();
    Entities::Player GetPlayer();
    bool IsRunning();

};  
}
#endif
