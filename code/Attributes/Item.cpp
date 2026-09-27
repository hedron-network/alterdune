#include "Item.hh"
#include "../Entities/Player.hh"
using namespace std;

namespace Attributes{
    Item::Item(string name, string description,int itemPower, int quantite)
    {
        this->name = name;
        this->description = description;
        this->itemPower = itemPower;
        this->quantite = quantite;
    }

    bool Item::UseItem(Entities::Player &player){
        if (quantite <= 0) {
            return false;
        }
        player.Heal(itemPower);
        quantite -= 1;
        return true;
    }

    string Item::GetName() const {
        return name;
    }

    int Item::GetQuantity() const {
        return quantite;
    }

    bool Item::IsEmpty() const {
        return quantite <= 0;
    }
};

