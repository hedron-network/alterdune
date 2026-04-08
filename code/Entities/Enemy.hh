#include <Entity.hh>
#include <string>
#include <Action.hh>
#include <vector>

using namespace std;

namespace Entities
{
    enum EnemyType{
        NORMAL,
        MINIBOSS,
        BOSS
    };
    class Enemy : public Entity {
    private:
    EnemyType categorie; 
    string description;
    int mercy;
    vector<Action> Act;

    public :
    Enemy (string name, int hpMax, EnemyType categorie, string description, int mercy, string act[]);

    void ACT(Action action);

    bool Spare();

    string GetName();

    Action GetAction();


};  
}

