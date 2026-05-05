#include "Player.hh"

namespace Entities {
    Player::Player(string name, int hpMax, vector<Item> ListOfItem) : Entity(hpMax, name, Attributes::Attack("Player Attack", "Basic player attack", 100000.0))
    {
        this->numberOfKill = 0;
        this->numberOfSpare = 0;
        this->numberOfVictory = 0;
        this->ListOfItem = std::move(ListOfItem);
    }

    std::vector<Item>& Player::GetItems(){
        return ListOfItem;
    }

    const std::vector<Item>& Player::GetItems() const {
        return ListOfItem;
    }

    int Player::GetVictories() const {
        return numberOfVictory;
    }
    int Player::Attack(){
        auto rng = std::default_random_engine {static_cast<unsigned>(std::time(nullptr))};
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(rng)*Entity::Attack();
    }
    void Player::AddVictory() {
        ++numberOfVictory;
    }

    int Player::GetKills() const {
        return numberOfKill;
    }

    void Player::AddKill() {
        ++numberOfKill;
    }

    int Player::GetSpares() const {
        return numberOfSpare;
    }

    void Player::AddSpare() {
        ++numberOfSpare;
    }
}