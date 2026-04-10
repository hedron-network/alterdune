#ifndef Bestiary_h
#define Bestiary_h
#include <string>
#include <vector>
#include "../Entities/Enemy.hh"
using namespace std;

namespace GameLogic{

class Bestiary {
    private:
        vector<Entities::Enemy*> enemies;
        string result;

    public:
        Bestiary();
        explicit Bestiary(const std::string& result);
        Bestiary(const std::vector<Entities::Enemy*>& enemies, const std::string& result);

        void AddEnemy(Entities::Enemy* enemy);
        const vector<Entities::Enemy*>& GetEnemies() const;
        const string& GetResult() const;
        void SetResult(const std::string& value);

        size_t Size() const;
        bool IsEmpty() const;
    };
};

#endif