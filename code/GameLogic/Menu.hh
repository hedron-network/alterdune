#ifndef Menu_h
#define Menu_h
#include <iostream>
#include <optional>
#include <vector>

#include <Item.hh>
#include <Action.hh>


namespace GameLogic
{
enum MenuChoice {
        FIGHT,
        ITEMS,
        BESTIARY,
        ACT,
        SPARE,
        EXIT
};
class Menu
{
private:
public:
    Menu();
     ~Menu();
    std::optional<MenuChoice> DisplayMainMenu();
    std::optional<MenuChoice> DisplayCombatMenu();
    std::optional<Attributes::Action> ActMenu(std::vector<Attributes::Action>& actions);
    void ShowBestiary();
    std::optional<Attributes::Item> ChooseItems(std::vector<Item>& items);
    std::string NameSelection();
};  
}
#endif