#include <Combat.hh>
namespace GameLogic
{
    Combat::Combat(Player player, Enemy Enemy){
        this->player = player;
        this->Enemy = Enemy;
    }
}