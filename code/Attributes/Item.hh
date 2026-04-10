#ifndef Item_h
#define Item_h
#include <iostream>
#include <string>
#include<Player.hh>
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
    void UseItem(Entities::Player& player);
};
}
#endif