#include "Menu.hh"
namespace GameLogic
{
    Menu::Menu(){}
    std::optional<MenuChoice> Menu::DisplayMainMenu(){
        std::cout<<std::endl;
        std::cout<<"1 Fight 2 Bestiary \n3 Item 4 EXIT\n-1 Back"<<std::endl;
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            return std::nullopt;
        }
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
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            return std::nullopt;
        }
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
    
    std::optional<Attributes::Action> Menu::ActMenu(std::vector<Attributes::Action>& actions){
        for(int i =0;i<actions.size();i++){
            std::cout<<i<<" "<<actions[i].GetName()<<std::endl;
        }
        std::cout<<"\n-1 Back"<<std::endl;
        int choice;
        std::cin>>choice;
        if(choice>=actions.size()||choice<0){
            return std::nullopt;
        }
        return actions[choice];
    }
    
    std::optional<Attributes::Item> Menu::ChooseItems(std::vector<Attributes::Item>& items){
        for(int i =0;i<items.size();i++){
            std::cout<<"("<<i<<") : "<<items[i].GetName()<<" | "<<items[i].GetQuantity()<<std::endl;
        }
        int choice;
        std::cin>>choice;
        if(choice<0||choice>=items.size()){
            return std::nullopt;
        }
        if(items[choice].GetQuantity()==0){
            return std::nullopt;
        }
        return items[choice];
    }
    
    std::string Menu::NameSelection(){
        std::cout<<"Enter your Name"<<std::endl;
        std::string name;
        std::cin>>name;
        return name;
    }
    void Menu::ShowBestiary(){
        throw std::runtime_error("Not Implemented");
    }
}

