#include <Item.hh>
using namespace std;

namespace Items{
    Item::Item(string name, string description, int quantite)
    {
        this->name=name;
        this->description=description;
        this->quantite=quantite;
    }
};

