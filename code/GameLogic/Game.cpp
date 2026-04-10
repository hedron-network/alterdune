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
        this->enemies= fileManager.LoadEnemies();
        if(enemies.size()==0){
            throw std::runtime_error("Error loading enemies");
        }
    }
    void Game::ShuffleEnemies(){
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
        
        std::cout<<"pass;";
        enemies.pop_back();
        
        std::cout<<"pass;";
    }
    void Game::Reset(){
        LoadExternalData();
        
        ShuffleEnemies();
        
        CreateFirstEncounter();
        
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
            throw std::runtime_error("Invalid state");
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
            throw std::runtime_error("Invalid state");
        }
        bool running=ShowMainMenu();
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
    void Game::StartGame(){
        GameLoop();
    }
}