#ifndef Enemy_h
#define Enemy_h

#include <string>
#include <vector>
#include "../Attributes/Action.hh"
#include "Entity.hh"

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
    Enemy (string name, int hpMax, EnemyType categorie, string description, int mercy, vector<Action> Act);

    void ACT(Action action);

    bool Spare();

    vector<Action> GetAction();


};  
}

#endif