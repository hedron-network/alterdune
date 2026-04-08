#include <iostream>
#include <string>
using namespace std;

class Item {
    private:
    string name;
    string description;
    int quantite; //heal

    public:
    Item(string name, string description)
     {
        this->name=name;
        this->description=description;
        this->quantite=quantite;
     }
};