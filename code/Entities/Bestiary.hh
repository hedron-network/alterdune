#ifndef BESTIARY_HH
#define BESTIARY_HH

#include <string>
#include <vector>

class Enemy;

class Bestiary {
private:
    std::vector<Enemy*> enemies;
    std::string result;

public:
    Bestiary();
    explicit Bestiary(const std::string& result);
    Bestiary(const std::vector<Enemy*>& enemies, const std::string& result);

    void AddEnemy(Enemy* enemy);
    const std::vector<Enemy*>& GetEnemies() const;
    const std::string& GetResult() const;
    void SetResult(const std::string& value);

    size_t Size() const;
    bool IsEmpty() const;
};

#endif // BESTIARY_HH
