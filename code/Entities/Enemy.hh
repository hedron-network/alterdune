#include <Entity.hh>
#include <string>
#include <Action.hh>

using namespace std;

namespace Entities
{
    class Enemy : public Entity {
    private:
    string categorie; 
    string statistique;
    int mercy;
    string act[4];

    public :
    Enemy (string name, int hpMax, string categorie, string statistique, int mercy, string act[]);

    void ACT(Action action);

};  
}

