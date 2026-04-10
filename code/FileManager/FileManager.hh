#ifndef FileManager_h
#define FileManager_h
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <optional>

#include "../Entities/Enemy.hh"
#include "../Entities/Player.hh"
#include "stringConverter.hh"
#include "../Attributes/Item.hh"

namespace File
{
class FileManager
{
private:
    std::optional<std::vector<std::vector<std::string>>> ReadCSV(const std::string &filepath);
    std::vector<std::vector<std::string>> ExtractDataFromStream(std::istream &in);
    std::vector<std::string> readRow(const std::string &row);
    std::vector<Attributes::Item> LoadItems(const std::string &filepath);
    Attributes::Item LoadItemFromData(const std::vector<std::string>& dataRow, int startOffset=0);
    std::vector<Attributes::Action> ActionVectorFromData(const std::vector<std::string>& dataRow,int offset,int numberOfActions);
public:
    const std::string entityCSV="./asset/Enemies.csv";
    const std::string itemCSV="./asset/Items.csv";
    FileManager();
    std::vector<Entities::Enemy> LoadEnemies();
    Entities::Player LoadPlayer(const std::string& name);
    
};  

}
#endif
