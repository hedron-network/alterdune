#include "Item.hh"
#include "../Entities/Player.hh"
using namespace std;

namespace Attributes{
    Item::Item(string name, string description,int itemPower, int quantite)
    {
        this->name=name;
        this->description=description;
        this->itemPower=itemPower;
        this->quantite=quantite;
    }
    void Item::UseItem(Entities::Player &player){
        player.Heal(itemPower);
        quantite=quantite-1;
    }
    string Item::GetName(){
        return name;
    }
    int Item::GetQuantity(){
        return quantite;
    }
};

