#ifndef Item_h
#define Item_h
#include <iostream>
#include <string>
using namespace std;
namespace Attributes
{

class Item {
    private:
    string name;
    string description;
    int quantite; //heal

    public:
    Item(string name, string description, int quantite);
};
}
#endif