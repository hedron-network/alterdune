#include "Combat.hh"
namespace GameLogic
{
    Combat::Combat(Entities::Player player, Entities::Enemy enemy)
    :player(player),enemy(enemy)
    {
        this->isRunning = true;
    }
    bool Combat::IsRunning(){
        return player.GetHp()>0 && enemy.GetHp()>0;
    }
    void Combat::Attack()
    {
        std::cout<<"Attacked"<<std::endl;
        const int dmg = player.Attack();
        enemy.TakeDamage(dmg);
    }
    void Combat::Spare()
    {
        if(enemy.Spare()){
            std::cout<<enemy.GetName()<<" has been spared"<<std::endl;
        }
        else{
            std::cout<<"Failed"<<std::endl;
        }
    }

    Entities::Player& Combat::GetPlayer(){
        return this->player;
    }

}