#include <iostream>
#include <string>
using namespace std;

class Entity {
    private:
    int hpMax;

    protected:
    int hp;
    string name;

    public:
    Entity(int hpMax, string name)
    {
        this->hpMax=hpMax;
        this->name=name;
        this->hp=hpMax;
    }
};

class Player : public Entity {
    private:
    int numberOfKill;
    int numberOfSpare;
    int numberOfVictory;

    public :
    Player(string name, int hpMax) : Entity(hpMax, name)
    {
        this->numberOfKill = 0;
        this->numberOfSpare = 0;
        this->numberOfVictory = 0;
    }

};

class Enemy : public Entity {
    private:
    string categorie; 
    string statistique;
    int mercy;
    int act[4];

    public :
    Enemy (string name, int hpMax, string categorie, string statistique, int mercy, int act[]) : Entity(hpMax, name)
    {
        this->categorie=categorie;
        this->statistique=statistique;
        this->mercy=mercy;
        for (int i=0; i<4; i++)
        {
            this->act[i]=act[i];
        }
    }

};