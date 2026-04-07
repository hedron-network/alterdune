#include <FileManager.hh>
#include <stringConverter.hh>
namespace File{
    const std::string entityCSV="";
    const std::string playerCSV="";
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
    std::optional<std::vector<std::vector<std::string>>> FileManager::ReadCSV(std::string filepath){
        std::ifstream stream(filepath);
        if(!stream){
            return std::nullopt;
        }
        return ExtractDataFromStream(stream);
    }

    
    std::vector<Entity> FileManager::LoadEntities(std::string filepath){
        std::vector<Entity> entities= {};
        auto dataOpt=ReadCSV(filepath);
        if(!dataOpt.has_value()){
            return {};
        }
        auto data = dataOpt.value();
        for (const std::vector<std::string>& dataRow : data){
            int hp= File::ConvertTo<int>(dataRow[0]);
            entities.push_back(new Entity(hp));
        }
        return entities;
    }
    Player FileManager::LoadPlayer(std::string filepath){

    }


}
