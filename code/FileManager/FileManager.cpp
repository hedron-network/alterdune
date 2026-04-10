#include <FileManager.hh>
namespace File{
    const std::string entityCSV="";
    const std::string itemCSV="";
    std::vector<std::string> FileManager::readRow(const std::string &row){// passes original value as read only to avoid copying
        std::vector<std::string> fields = {""};
        int i =0;
        for(char c : row){
            switch(c){
                case ',':{
                    fields.push_back("");
                    i++;
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
        while (!in.eof())
        {
           std::getline(in,row);
           if(in.bad()||in.fail()){
                break;
           }
           auto fields = readRow(row);
           table.push_back(fields);
        }
        return table;
        
    }
    std::optional<std::vector<std::vector<std::string>>> FileManager::ReadCSV(const std::string &filepath){
        std::ifstream stream(filepath);
        if(!stream){
            return std::nullopt;
        }
        return ExtractDataFromStream(stream);
    }

    
    std::vector<Entities::Enemy> FileManager::LoadEnemies(const std::string &filepath){
        std::vector<Entities::Enemy> entities= {};
        auto dataOpt=ReadCSV(filepath);
        if(!dataOpt.has_value()){
            return {};
        }
        auto data = dataOpt.value();
        for (int i =1;i<data.size();i++){
            auto dataRow= data[i];
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
        auto items = LoadItems(itemCSV);
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
            items.push_back(LoadItemFromData(dataRow));
        }
        return items;
    }
    Attributes::Item FileManager::LoadItemFromData(const std::vector<std::string>& dataRow, int startOffset){
        std::string name= dataRow[startOffset];
        std::string description = dataRow[startOffset+1];
        int power= ConvertTo<int>(dataRow[startOffset+2]);
        int quantite = ConvertTo<int>(dataRow[startOffset+3]);
        return Item(name,description,power,quantite);
    }
    std::vector<Attributes::Action> FileManager::ActionVectorFromData(const std::vector<std::string>& dataRow,int offset,int numberOfActions){
        vector<Attributes::Action> act;
            for(int i = 0;i<numberOfActions;i++){
                Attributes::Action action(
                    dataRow[offset+i*3],
                    dataRow[1+offset+i*3],
                    ConvertTo<int>(dataRow[2+offset+i*3])
                    );
                act.push_back(action);
            }
        return act;
    }

}
