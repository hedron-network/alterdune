#include <string>
#include <vector>
#include <Enemy.hh>
using namespace std;
using namespace Entities;

namespace GameLogic{

class Bestiary {
    private:
        vector<Enemy*> enemies;
        string result;

    public:
        Bestiary();
        explicit Bestiary(const std::string& result);
        Bestiary(const std::vector<Enemy*>& enemies, const std::string& result);

        void AddEnemy(Enemy* enemy);
        const vector<Enemy*>& GetEnemies() const;
        const string& GetResult() const;
        void SetResult(const std::string& value);

        size_t Size() const;
        bool IsEmpty() const;
    };
};

