#include "Game.hh"
namespace GameLogic{
    Game::Game(std::string playerName)
    :playerName(playerName)
    {
        Reset();
    }
    void Game::recordWin(bool hasSpared){
        if(hasSpared){
            stats.numberOfSpares++;
        }else{
            stats.numberOfKills++;
        }stats.numberOfVictories++;
    }
    
    #pragma region dataHandling

    void Game::LoadExternalData(){
        std::string name;
        if(!this->player.has_value()){
           name = playerName;//menu.NameSelection();
        }
        else{
            name = this->player.value().GetName();      
        }
        this->player = fileManager.LoadPlayer(name);
        this->enemies= fileManager.LoadEnemies();
        if(enemies.size()==0){
            throw std::runtime_error("Error loading enemies");
        }
    }
    void Game::ShuffleEnemies(){
        std::cout<<"enemies remaining"<<enemies.size()<<std::endl;
        auto rng = std::default_random_engine {static_cast<unsigned>(std::time(nullptr))};
        std::shuffle(this->enemies.begin(), this->enemies.end(), rng);
    }
    void Game::CreateFirstEncounter(){
        if(!this->player.has_value()){
            throw std::runtime_error("Error loading player");
        }
        std::cout<<this->player.value().GetName();
        std::cout<<enemies.size();
        std::cout<<this->enemies.back().GetName();
        this->combat = Combat(this->player.value(),this->enemies.back());
        enemies.pop_back();
    }
    void Game::Reset(){
        LoadExternalData();
        std::cout<<"External Data loaded ;";
        ShuffleEnemies();
        std::cout<<"Enemies Shuffled ;";
        CreateFirstEncounter();
        std::cout<<"Encouter Created ;";

    }
    bool Game::NextEncounter(){
        if(!combat.has_value()){
            throw std::runtime_error("Invalid state");
        }
        if(enemies.size()<=0){
            return false;
        }
        this->player =this->combat.value().GetPlayer();
        this->combat = Combat(player.value(),enemies.back());
        enemies.pop_back();
        return true;
    }

    #pragma endregion

}