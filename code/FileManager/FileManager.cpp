#include <FileManager.hh>
#include <filesystem>
#include <iostream>
namespace File{
    
    static std::string trim(const std::string& s) {
        const char* whitespace = " \t\r\n";
        size_t start = s.find_first_not_of(whitespace);
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(whitespace);
        return s.substr(start, end - start + 1);
    }

    
    FileManager::FileManager(){}
    std::vector<std::string> FileManager::readRow(const std::string &row){// passes original value as read only to avoid copying
        std::vector<std::string> fields = {""};
        int i =0;
        for(char c : row){
            switch(c){
                case ';':{
                    fields[i]= trim(fields[i]);
                    fields.push_back("");
                    i++;
                    break;
                }
                case '\r':{
                    break;
                }
                case '\0':{
                    break;
                }
                default :{
                    fields[i].push_back(c);
                }
            }
        }
        return fields;
    }
    std::vector<std::vector<std::string>> FileManager::ExtractDataFromStream(std::istream &in){
        std::vector<std::vector<std::string>> table;
        std::string row;
        while (std::getline(in, row)) {
            if (row.empty()) continue; // skip blank lines
            auto fields = readRow(row);
            table.push_back(fields);
        }
        return table;
        
    }
    std::optional<std::vector<std::vector<std::string>>> FileManager::ReadCSV(const std::string &filepath){
        std::ifstream stream(filepath);
        if(!stream){
            std::cout<< "Error opening "<<filepath<<std::endl;
            return std::nullopt;
        }
        
        return ExtractDataFromStream(stream);
    }

    
    std::vector<Entities::Enemy> FileManager::LoadEnemies(){
        std::vector<Entities::Enemy> entities= {};
        auto dataOpt=ReadCSV(this->entityCSV);
        if(!dataOpt.has_value()){
            return {};
        }
        auto data = dataOpt.value();
        for (int i =1;i<data.size();i++){
            auto dataRow= data[i];
            for(std::string field:dataRow){
                std::cout<<field<<";";
            }
            std::cout<<std::endl;
            std::string name = dataRow[0];
            int hpMax = ConvertTo<int>(dataRow[1]);
            Entities::EnemyType enemyType = ConvertTo<Entities::EnemyType>(dataRow[2]);
            std::string description = dataRow[3];
            int mercy = ConvertTo<int>(dataRow[4]);
            auto act = ActionVectorFromData(dataRow,5,4);

            Entities::Enemy currEnemy(name, hpMax,enemyType, description, mercy,act);
            entities.push_back(currEnemy);
        }
        return entities;
    }
    Entities::Player FileManager::LoadPlayer(const std::string &name){
        std::cout << "Current path is " << std::filesystem::current_path() << '\n'; 
        auto items = LoadItems(itemCSV);
        if(items.size()==0){
            throw std::runtime_error("Error loading items");
        }
        Entities::Player new_player(name,100,items);
        return new_player;
    }
    std::vector<Attributes::Item> FileManager::LoadItems(const std::string &filepath){
        std::vector<Attributes::Item> items;
        auto dataOpt=ReadCSV(filepath);
        if(!dataOpt.has_value()){
            return {};
        }
        auto data = dataOpt.value();
        for (int i =1;i<data.size();i++){
            auto dataRow= data[i];
            auto item=LoadItemFromData(dataRow);
            std::cout<<item.GetName()<<";";
            items.push_back(item);
        }
        std::cout<<std::endl;
        return items;
    }
    Attributes::Item FileManager::LoadItemFromData(const std::vector<std::string>& dataRow, int startOffset){
        std::string name= dataRow[startOffset];
        std::string description = dataRow[startOffset+1];
        int power= ConvertTo<int>(dataRow[startOffset+2]);
        int quantite = ConvertTo<int>(dataRow[startOffset+3]);
        return Item(name,description,power,quantite);
    }
    std::vector<Attributes::Action> FileManager::ActionVectorFromData(const std::vector<std::string>& dataRow, int offset, int numberOfActions)
    {
        vector<Attributes::Action> act;
        for (int i = 0; i < numberOfActions; i++) {
            int idx = offset + i * 3;
            if (idx + 2 >= (int)dataRow.size()) {
                std::cout << "Warning: not enough fields for action " << i << std::endl;
                break; // or continue, depending on your needs
            }
            Attributes::Action action(
                dataRow[idx],
                dataRow[idx + 1],
                ConvertTo<int>(dataRow[idx + 2])
            );
            act.push_back(action);
        }
        return act;
    }

}
