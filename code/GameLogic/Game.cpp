#include <Game.hh>
namespace GameLogic{
    Game::Game(){
        LoadExternalData();
        ShuffleEnemies();
        CreateFirstEncounter();
    }


    void Game::LoadExternalData(){
        this->player = fileManager.LoadPlayer(fileManager.playerCSV);
        this->enemies= fileManager.LoadEntities(fileManager.entityCSV);
    }
    void Game::CreateFirstEncounter(){
        this->combat = Combat(this->player,this->enemies.back());
        enemies.pop_back();
    }
    bool Game::NextEncounter(){
        if(!combat.has_value()){
            throw "Invalid state";
        }
        if(enemies.size()<=0){
            return false;
        }
        this->player =this->combat.value().GetPlayer();
        this->player.fullHeal();
        this->combat = Combat(player,enemies.back());
        enemies.pop_back();
        return true;
    }
    void Game::ShuffleEnemies(){
        auto rng = std::default_random_engine {};
        std::shuffle(this->enemies.begin(), this->enemies.end(), rng);
    }
    void Game::Reset(){
        
        ShuffleEnemies();
        CreateFirstEncounter();
    }
    void Game::ShowMenu(){
        throw "Not Implemented";
    }
    
    void Game::GameLoop(){
        if(!combat.has_value()){
            throw "Invalid state";
        }
        while (true)
        {
            if(!combat.has_value()){
                break;
            }
            Fight();
            if(!NextEncounter){
                Reset();
            }
            ShowMenu();
        }
    }
    void Game::Fight(){
        while(combat->IsRunning()){
            combat->ExecutePlayerTurn();
            if(combat->IsRunning()){
                combat.value().ExecuteEnemyTurn();
            }
        }
    
    }
}