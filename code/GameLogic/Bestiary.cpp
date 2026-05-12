#include "Bestiary.hh"
#include <iostream>

namespace GameLogic {

    void Bestiary::AddEnemy(const Entities::Enemy enemy, bool spared) {
        entries.push_back({enemy, spared});
    }

    const std::vector<BestiaryEntry>& Bestiary::GetEntries() const {
        return entries;
    }

    bool Bestiary::IsEmpty() const {
        return entries.empty();
    }

    size_t Bestiary::Size() const {
        return entries.size();
    }

} // namespace GameLogic
