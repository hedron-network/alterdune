#include <Menu.hh>
namespace GameLogic
{
    std::optional<MenuChoice> Menu::DisplayMainMenu(){
        std::cout<<"1 Fight 2 Bestiary 3 Item 4 EXIT"<<std::endl;
        int choice;
        std::cin>>choice;
        std::optional<MenuChoice> formattedChoice;
        switch (choice)
        {
        case 1:
            formattedChoice= MenuChoice::FIGHT;
            break;
        case 2:
            formattedChoice = MenuChoice::BESTIARY;
            break;
        case 3:
            formattedChoice = MenuChoice::ITEMS;
            break;
        case 4:
            formattedChoice = MenuChoice::EXIT;
            break;
        default:
            formattedChoice = std::nullopt;
            break;
        }
        return formattedChoice;
    }

    std::optional<MenuChoice> Menu::DisplayCombatMenu(){
        std::cout<<"1 Fight 2 ACT 3 Item 4 Spare"<<std::endl;
        int choice;
        std::cin>>choice;
        std::optional<MenuChoice> formattedChoice;
        switch (choice)
        {
        case 1:
            formattedChoice= MenuChoice::FIGHT;
            break;
        case 2:
            formattedChoice = MenuChoice::BESTIARY;
            break;
        case 3:
            formattedChoice = MenuChoice::ITEMS;
            break;
        case 4:
            formattedChoice = MenuChoice::EXIT;
            break;
        default:
            formattedChoice = std::nullopt;
            break;
        }
        return formattedChoice;
    }
    std::optional<Attributes::Action> Menu::ActMenu(std::vector<Attributes::Action> actions){
        for(int i =0;i<actions.size();i++){
            std::cout<<i<<" "<<actions[i].GetInfoString()<<std::endl;
        }
        int choice;
        std::cin>>choice;
        if(choice>=actions.size()||choice<0){
            return std::nullopt;
        }
        return actions[choice];
    }
}

