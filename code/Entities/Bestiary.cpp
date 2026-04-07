#include "Bestiary.hh"

Bestiary::Bestiary()
    : enemies(), result()
{
}

Bestiary::Bestiary(const std::string& result)
    : enemies(), result(result)
{
}

Bestiary::Bestiary(const std::vector<Enemy*>& enemies, const std::string& result)
    : enemies(enemies), result(result)
{
}

void Bestiary::AddEnemy(Enemy* enemy)
{
    if (enemy != nullptr) {
        enemies.push_back(enemy);
    }
}

const std::vector<Enemy*>& Bestiary::GetEnemies() const
{
    return enemies;
}

const std::string& Bestiary::GetResult() const
{
    return result;
}

void Bestiary::SetResult(const std::string& value)
{
    result = value;
}

size_t Bestiary::Size() const
{
    return enemies.size();
}

bool Bestiary::IsEmpty() const
{
    return enemies.empty();
}
