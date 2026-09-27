#ifndef Player_h
#define Player_h
#include <string>
#include <vector>

#include <random>
#include <ctime>
#include<SFML/Graphics.hpp>

#include "Entity.hh"
#include "../Attributes/Item.hh"
#include "../Render/Assets.hh"
using namespace std;

namespace Entities
{
    class Player : public Entity {
    vector<Attributes::Item> ListOfItem;
    public :
    Player(string name, int hpMax,vector<Attributes::Item> ListOfItem);
    std::vector<Attributes::Item>& GetItems();
    const std::vector<Attributes::Item>& GetItems() const;
    int Attack();
};
}
#endif