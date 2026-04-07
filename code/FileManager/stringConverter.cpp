#include <stringConverter.hh>
namespace File
{
    // Primary template
    template <typename T>
    T ConvertTo(const std::string& data);

    template <>
    int ConvertTo<int>(const std::string& data) {
        return std::stoi(data);
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
}
