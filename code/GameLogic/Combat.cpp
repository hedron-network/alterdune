#include <Combat.hh>
namespace GameLogic
{
    Combat::Combat(Entities::Player player, Entities::Enemy enemy)
    :player(player),enemy(enemy)
    {
        this->isRunning = true;
    }
    bool Combat::IsRunning(){
        return IsRunning;
    }
    void Combat::ExecutePlayerTurn(Menu& menu){
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
    void Combat::Attack()
    {
        const int dmg = player.Attack();
        enemy.TakeDamage(dmg);
    }
    bool Combat::ACT(Menu& menu)
    {
        auto actions = enemy.GetAction();
        auto select = menu.ActMenu(actions);
        if (!select.has_value()){
            return false;
        }    
        enemy.ACT(select.value());
        return true;
    }
    bool Combat::UseItem(Menu& menu)
    {
        auto items = player.GetItems();
        auto select = menu.ChooseItems(items);
        if (!select.has_value()){
            return false;
        }
        select.value().UseItem(player);
        return true;
    }
    void Combat::Spare()
    {
        if(enemy.Spare()){
            std::cout<<enemy.GetName()<<" has been spared"<<std::endl;
        }
        else{
            std::cout<<"Failed"<<std::endl;
        }
    }

    void Combat::ExecuteEnemyTurn(){
        throw -1;
    }
    Entities::Player Combat::GetPlayer(){
        return this->player;
    }

}