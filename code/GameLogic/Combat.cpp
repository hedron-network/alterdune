#include <Combat.hh>
namespace GameLogic
{
    Combat::Combat(Entities::Player player, Entities::Enemy Enemy){
        this->player = player;
        this->Enemy = Enemy;
        this->IsRunning = true;
    }
    bool Combat::IsRunning(){
        return IsRunning;
    }
    void ExecutePlayerTurn(){
        throw -1; //not implemented
    }
    void ExecuteEnemyTurn(){
        throw -1;
    }
    Entities::Player GetPlayer(){
        return this->player;
    }

}