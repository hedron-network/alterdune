#ifndef Player_h
#define Player_h
#include <string>
#include <vector>

#include "Entity.hh"
#include "../Attributes/Item.hh"
using namespace std;

namespace Entities
{
    class Player : public Entity {
    private:
    int numberOfKill;
    int numberOfSpare;
    int numberOfVictory;
    vector<Attributes::Item> ListOfItem;

    public :
    Player(string name, int hpMax,vector<Attributes::Item> ListOfItem);
    vector<Attributes::Item> GetItems();

};
}
#endif