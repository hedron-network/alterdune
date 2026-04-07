#ifndef FileManager_h
#define FileManager_h
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <optional>
#include <Entity.hh>
#include <Player.hh>

namespace File
{
class FileManager
{
private:
    std::optional<std::vector<std::vector<std::string>>> ReadCSV(std::string filepath);
    std::vector<std::vector<std::string>> ExtractDataFromStream(std::istream &in);
    std::vector<std::string> readRow(const std::string &row);
public:
    const std::string entityCSV;
    const std::string playerCSV;
    FileManager();
     ~FileManager();
    std::vector<Entity> LoadEntities(std::string filepath);
    Player LoadPlayer(std::string filepath);
};  

}
#endif
