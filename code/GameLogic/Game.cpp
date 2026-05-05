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

        DisplayStartSummary();
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
            //menu.ShowBestiary();
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
        auto& itemlist = this->player.value().GetItems();
        auto itemIndex = menu.ChooseItems(itemlist);
        if (itemIndex.has_value()){
            if(itemlist[itemIndex.value()].UseItem(player.value())){
                std::cout << "Objet utilisé : " << itemlist[itemIndex.value()].GetName() << std::endl;
            } else {
                std::cout << "Impossible d'utiliser cet objet." << std::endl;
            }
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

            if(player.value().GetVictories() >= 10)
            {
                DisplayEnding(); // affiche fin génocidaire/pacifiste/neutre
                return;
            }


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
            this->player = combat->GetPlayer(); 
/*
        if(combat->PlayerLost()){
            std::cout << "\n=== GAME OVER ===" << std::endl;
            Reset(); // repart du début
            return;
        }
        if(combat->PlayerWon()){
            player.value().AddVictory();
            bool spared = combat->WasSpared();
            if(spared) player.value().AddSpare();
            else       player.value().AddKill();
            bestiary.AddEnemy(combat->GetEnemy(), spared);
        }
    */
    }
    #pragma endregion
    void Game::StartGame(){
        GameLoop();
    }

        void Game::DisplayStartSummary()
        {
            auto& p = player.value();
            std::cout << "\n--- Bienvenue, " << p.GetName() << " ---" << std::endl;
            std::cout << "HP : " << p.GetHp() << " / " << p.GetHpMax() << std::endl;
            std::cout << "Inventaire :" << std::endl;
            for(auto& item : p.GetItems()){
                std::cout << "  - " << item.GetName() << " x" << item.GetQuantity() << std::endl;
            }
            std::cout << std::endl;
        }

    void Game::DisplayEnding(){
        int kills  = player.value().GetKills();
        int spares = player.value().GetSpares();

        std::cout << "\n========================================" << std::endl;
        std::cout << "     FIN — 10 victoires !" << std::endl;
        std::cout << "========================================" << std::endl;

        if(kills == 0)
            std::cout << "  FIN PACIFISTE — Vous avez tout épargné." << std::endl;
        else if(spares == 0)
            std::cout << "  FIN GÉNOCIDAIRE — Vous avez tout tué." << std::endl;
        else
            std::cout << "  FIN NEUTRE — Tués : " << kills << " | Épargnés : " << spares << std::endl;

        std::cout << "========================================\n" << std::endl;
}

}