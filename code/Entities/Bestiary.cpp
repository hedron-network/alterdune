#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Enemy;

class Bestiary {
    private:
    vector<Enemy*> enemies;
    string result;

    public:

    Bestiary(vector<Enemy*> enemies, string result)
    {
        this->enemies = enemies;
        this->result = result;
    }

    void AddEnemy(Enemy* enemy)
    {
        this->enemies.push_back(enemy);
    }

    vector<Enemy*> GetEnemies()
    {
        return this->enemies;
    }

    string GetResult()
    {
        return this->result;
    }

    void SetResult(string value)
    {
        this->result = value;
    }

    size_t Size()
    {
        return this->enemies.size();
    }

    bool IsEmpty()
    {
        return this->enemies.empty();
    }
};