#ifndef Menu_h
#define Menu_h
#include <iostream>
#include <optional>
#include <vector>
#include <limits>

#include "../Attributes/Item.hh"
#include "../Attributes/Action.hh"
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
    std::optional<MenuChoice> DisplayMainMenu();
    std::optional<MenuChoice> DisplayCombatMenu();
    std::optional<Attributes::Action> ActMenu(std::vector<Attributes::Action>& actions);
    void ShowBestiary();
    std::optional<Attributes::Item> ChooseItems(std::vector<Attributes::Item>& items);
    std::string NameSelection();
};  
}
#endif