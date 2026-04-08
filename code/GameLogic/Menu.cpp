#include <Menu.hh>
namespace GameLogic
{
    std::optional<MenuChoice> Menu::DisplayMainMenu(){
        std::cout<<"1 Fight 2 Bestiary \n3 Item 4 EXIT\n-1 Back"<<std::endl;
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
        std::cout<<"1 Fight 2 ACT \n3 Item 4 Spare\n-1 Back"<<std::endl;
        int choice;
        std::cin>>choice;
        std::optional<MenuChoice> formattedChoice;
        switch (choice)
        {
        case 1:
            formattedChoice= MenuChoice::FIGHT;
            break;
        case 2:
            formattedChoice = MenuChoice::ACT;
            break;
        case 3:
            formattedChoice = MenuChoice::ITEMS;
            break;
        case 4:
            formattedChoice = MenuChoice::SPARE;
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
        std::cout<<"\n-1 Back"<<std::endl;
        int choice;
        std::cin>>choice;
        if(choice>=actions.size()||choice<0){
            return std::nullopt;
        }
        return actions[choice];
    }
}

