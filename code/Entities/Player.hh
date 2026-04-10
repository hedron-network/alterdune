#include <Entity.hh>
#include <string>
#include <vector>
#include <Item.hh>
using namespace std;

namespace Entities
{
    class Player : public Entity {
    private:
    int numberOfKill;
    int numberOfSpare;
    int numberOfVictory;
    vector<Item> ListOfItem;

    public :
    Player(string name, int hpMax,vector<Item> ListOfItem);
    vector<Item> GetItems();

};
}
