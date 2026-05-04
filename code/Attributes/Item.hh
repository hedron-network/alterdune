#ifndef Item_h
#define Item_h
#include <iostream>
#include <string>

namespace Entities{
    class Player;
}
using namespace std;
namespace Attributes
{

class Item {
    private:
    string name;
    string description;
    int itemPower;//heal
    int quantite; 

    public:
    Item(string name, string description,int itemPower, int quantite);
    bool UseItem(Entities::Player& player);
    string GetName() const;
    int GetQuantity() const;
    bool IsEmpty() const;
};
}
#endif