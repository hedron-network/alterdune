#include "Player.hh"

namespace Entities {
    Player::Player(string name, int hpMax, vector<Item> ListOfItem) : Entity(hpMax, name, Attributes::Attack("Player Attack", "Basic player attack", 1.0))
    {
        this->numberOfKill = 0;
        this->numberOfSpare = 0;
        this->numberOfVictory = 0;
        this->ListOfItem=ListOfItem;
    }
    std::vector<Item> Player::GetItems(){
        return ListOfItem;
    }
}