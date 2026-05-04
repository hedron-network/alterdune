#include "Bestiary.hh"
#include <iostream>

namespace GameLogic {

    void Bestiary::AddEnemy(const Entities::Enemy& enemy, bool spared) {
        entries.push_back({enemy, spared});
    }

    void Bestiary::Display() const {
        if (entries.empty()) {
            std::cout << "\nBestiaire vide — aucun ennemi vaincu pour l'instant.\n" << std::endl;
            return;
        }

        std::cout << "\n========== BESTIAIRE ==========" << std::endl;
        std::cout << entries.size() << " ennemi(s) vaincu(s)\n" << std::endl;

        for (int i = 0; i < (int)entries.size(); i++) {
            const BestiaryEntry& e = entries[i];

            // Convertir la catégorie en texte lisible
            std::string categorie;
            switch (e.enemy.GetCategorie()) {
                case Entities::EnemyType::NORMAL:   categorie = "NORMAL";   break;
                case Entities::EnemyType::MINIBOSS: categorie = "MINIBOSS"; break;
                case Entities::EnemyType::BOSS:     categorie = "BOSS";     break;
            }

            // Résultat du combat
            std::string resultat = e.wasSpared ? "Épargné" : "Tué";

            std::cout << "[" << (i + 1) << "] " << e.enemy.GetName() << std::endl;
            std::cout << "    Catégorie : " << categorie << std::endl;
            std::cout << "    HP max    : " << e.enemy.GetHpMax() << std::endl;
            std::cout << "    Résultat  : " << resultat << std::endl;
            std::cout << std::endl;
        }

        std::cout << "================================\n" << std::endl;
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
