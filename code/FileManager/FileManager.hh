#ifndef FileManager_h
#define FileManager_h
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <Entity.hh>
#include <Player.hh>
namespace File
{
class FileManager
{
private:
    std::vector<std::vector<std::string>> ReadCSV(std::string filepath);
public:
    const std::string entityCSV;
    const std::string playerCSV;
    FileManager();
     ~FileManager();
    Entity* LoadEntities(std::string filepath);
    Player LoadPlayer(std::string filepath);
};  

}
#endif
