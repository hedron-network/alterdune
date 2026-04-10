#ifndef stringConverter_h
#define stringConverter_h
#include <string>
#include "../Entities/Enemy.hh"
namespace File
{
    template <typename T>
    T ConvertTo(const std::string& data);
};  
#endif
