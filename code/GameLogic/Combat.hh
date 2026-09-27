#ifndef Combat_h
#define Combat_h
#include "../Entities/Enemy.hh"
#include "../Entities/Player.hh"
#include <random>
#include <ctime>

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
    Entities::Player& GetPlayer();
    bool IsRunning();
    void Attack();
    void Spare();

};  
}
#endif
