#include <Combat.hh>
namespace GameLogic
{
    Combat::Combat(Entities::Player player, Entities::Enemy enemy){
        this->player = player;
        this->enemy = enemy;
        this->IsRunning = true;
    }
    bool Combat::IsRunning(){
        return IsRunning;
    }
    void ExecutePlayerTurn(Menu& menu){
        auto choiceOPT =menu.DisplayCombatMenu();
        if (!choiceOPT.has_value()){
            while (!choiceOPT.has_value()){choiceOPT = menu.DisplayCombatMenu();}
        }
        auto choice = choiceOPT.value();
        switch (choice)
        {
        case MenuChoice::FIGHT:
            Attack();
            break;
        case MenuChoice::ACT:
            if(!ACT(menu)){
                ExecutePlayerTurn(menu);
            }
            break;
        case MenuChoice::ITEMS:
            if(!UseItem(menu)){
                ExecutePlayerTurn(menu);
            }
            break;
        case MenuChoice::SPARE:
            Spare();
            break;
        default:
            break;
        }
        
    }
    void Attack()
    {
        int dmg = player.Attack();
        enemy.TakeDamage(dmg);
    }
    bool ACT(Menu& menu)
    {
        auto actions = enemy.GetACT();
        auto select = menu.ActMenu(actions);
        if (!select.has_value()){
            return false;
        }    
        enemy.ACT(select.value());
        return true;
    }
    bool UseItem(Menu& menu)
    {
        auto select = menu.ChooseItems();
        if (!select.has_value()){
            return false;
        }
        select.value().UseItem();
        return true;
    }
    void Spare()
    {
        if(enemy.Spare()){
            std::cout<<enemy.GetName()<<" has been spared"<<std::endl;
        }
        else{
            std::cout<<"Failed"<<std::endl;
        }
    }

    void ExecuteEnemyTurn(){
        throw -1;
    }
    Entities::Player GetPlayer(){
        return this->player;
    }

}