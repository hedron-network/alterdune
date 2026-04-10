#include <Game.hh>
namespace GameLogic{
    Game::Game(){
        Reset();
    }
    #pragma region dataHandling

    void Game::LoadExternalData(){
        std::string name;
        if(!this->player.has_value()){
           name = menu.NameSelection();
        }
        else{
            name = this->player.value().GetName();      
        }
        this->player = fileManager.LoadPlayer(name);
        this->enemies= fileManager.LoadEnemies(fileManager.entityCSV);
    }
    void Game::ShuffleEnemies(){
        auto rng = std::default_random_engine {};
        std::shuffle(this->enemies.begin(), this->enemies.end(), rng);
    }
    void Game::CreateFirstEncounter(){
        this->combat = Combat(this->player.value(),this->enemies.back());
        enemies.pop_back();
    }
    void Game::Reset(){
        LoadExternalData();
        ShuffleEnemies();
        CreateFirstEncounter();
    }
    bool Game::NextEncounter(){
        if(!combat.has_value()){
            throw "Invalid state";
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

    #pragma region GameLoop
    bool Game::ShowMainMenu(){
        auto choiceOPT=menu.DisplayMainMenu();
        if(!choiceOPT.has_value()){
            while (!choiceOPT.has_value())
            {
                choiceOPT=menu.DisplayMainMenu();
            }   
        }
        MenuChoice choice= choiceOPT.value();
        bool continueGame= true;
        switch (choice)
        {
        case MenuChoice::FIGHT:
            break;
        case MenuChoice::BESTIARY:
            menu.ShowBestiary();
            ShowMainMenu();
            break;
        case MenuChoice::ITEMS:
            ShowAndUseItem();
            ShowMainMenu();
            break;
        case MenuChoice::EXIT:
            continueGame=false;
            break;
        default:
            throw "Invalid state";
        }
        return continueGame;
    }
    void Game::ShowAndUseItem(){
        auto itemlist = this->player.value().GetItems();
        auto item=menu.ChooseItems(itemlist);
        if (item.has_value()){
            item->UseItem(player.value());
        }
    }
    
    void Game::GameLoop(){
        if(!combat.has_value()){
            throw "Invalid state";
        }
        bool running=true;
        while (running)
        {
            if(!combat.has_value()){
                break;
            }
            Fight();
            if(!NextEncounter()){
                Reset();
            }
            running=ShowMainMenu();
        }
    }
    void Game::Fight(){
        while(combat->IsRunning()){
            combat->ExecutePlayerTurn(menu);
            if(combat->IsRunning()){
                combat.value().ExecuteEnemyTurn();
            }
        }
    
    }
    #pragma endregion
    
}