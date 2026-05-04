#include "stringConverter.hh"
namespace File
{
    // Primary template
    template <typename T>
    T ConvertTo(const std::string& data);

    template <>
    int ConvertTo<int>(const std::string& data) {
        try{
            if (data.empty()) return 0;
            return std::stoi(data);
        }catch(...){
            std::cout<<"can't convert "<<data<<" to int"<<std::endl;
            throw std::runtime_error("S2I convertion error");
        }
        
    }

    template <>
    double ConvertTo<double>(const std::string& data) {
        return std::stod(data);
    }

    template <>
    bool ConvertTo<bool>(const std::string& data) {
        int dataValue= std::stoi(data);
        return dataValue==1;
    }
    template<>
    Entities::EnemyType ConvertTo<Entities::EnemyType>(const std::string& data){
        Entities::EnemyType dataValue;
        switch (std::stoi(data))
        {
        case 0:
            dataValue = Entities::EnemyType::NORMAL;
            break;
        case 1:
            dataValue = Entities::EnemyType::MINIBOSS;
            break;
        case 2:
            dataValue = Entities::EnemyType::BOSS;
            break;
        
        default:
            dataValue = Entities::EnemyType::NORMAL; //default fallback
            break;
        }
        return dataValue;
    }

}
