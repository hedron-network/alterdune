#ifndef Bestiary_h
#define Bestiary_h
#include <string>
#include <vector>
#include "../Entities/Enemy.hh"
using namespace std;
#pragma once

namespace GameLogic {

    // Une entrée du bestiaire : un ennemi vaincu + comment il a été vaincu
    struct BestiaryEntry {
        Entities::Enemy enemy;
        bool wasSpared; // true = épargné, false = tué
    };

    class Bestiary {
    private:
        std::vector<BestiaryEntry> entries;

    public:
        Bestiary() = default;

        // Ajoute un ennemi vaincu au bestiaire
        void AddEnemy(const Entities::Enemy& enemy, bool spared);

        // Affiche tous les ennemis vaincus (pour le menu Bestiaire)
        void Display() const;

        // Retourne toutes les entrées (utile pour les stats de fin)
        const std::vector<BestiaryEntry>& GetEntries() const;

        bool IsEmpty() const;
        size_t Size() const;
    };

} // namespace GameLogic
#endif