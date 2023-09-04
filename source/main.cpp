#include <iostream>
#include <climits>
#include "JsonObject.h"

int main()
{
    std::cout << "Create Json." << std::endl;
    JsonObject json{};
    json.PutValueString("text", "Hello, World!");
    json.PutValueLong("integer", 1145141919810);
    json.PutValueDouble("decimal", 3.141592);
    json.PutValueBoolean("bool", true);
    json.PutArrayString("arrayStr", std::vector<std::string>{"abc", "def", "gh"});
    json.PutArrayInt("arrayInt", std::vector<int>{1234, 56789, 114514});
    json.PutArrayDouble("arrayDouble", std::vector<double>{1234.56789, 29389.232434, 237287.33434});
    json.PutArrayBoolean("arrayBool", std::vector<bool>{true, false, false});
    json.PutValueRaw("arrayArrayArrayInt", "[[[1,2],[3,4]],[[5,6],[7,8]],[[9,10],[11,12],[114514]]]");
    std::cout << "Print:\n" << json.PrintToString(true) << std::endl;

    std::cout << "Read Json." << std::endl;
    std::cout << "text: " << json.GetValueString("text") << std::endl;
    std::cout << "integer: " << json.GetValueLong("integer") << std::endl;
    std::cout << "decimal: " << json.GetValueDouble("decimal") << std::endl;
    std::cout << "bool: " << (json.GetValueBoolean("bool") ? "true" : "false") << std::endl;
    std::cout << "arrayStr: ";
    for (const auto &item : json.GetArrayString("arrayStr")) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
    std::cout << "arrayInt: ";
    for (const auto &item : json.GetArrayInt("arrayInt")) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
    std::cout << "arrayDouble: ";
    for (const auto &item : json.GetArrayDouble("arrayDouble")) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
    std::cout << "arrayBool: ";
    for (const auto &item : json.GetArrayBoolean("arrayBool")) {
        std::cout << (item ? "true" : "false") << ' ';
    }
    std::cout << std::endl;
    std::cout << "arrayArrayArrayInt: " << std::endl;
    for (const auto &item : json.GetArrayItem("arrayArrayArrayInt")) {
        for (const auto &itemItem : item.valueArray) {
            for (const auto &itemItemItem : itemItem.valueArray) {
                std::cout << itemItemItem.valueInt << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << "Modify Json." << std::endl;
    json.PutValueString("integer", "happyhappyhappy");
    std::cout << "Print:\n" << json.PrintToString(true) << std::endl;
    std::cout << "integer: " << json.GetValueLong("integer") << std::endl;
    std::cout << "integer: " << json.GetValueString("integer") << std::endl;

    std::cout << "Parse Json." << std::endl;
    char jsonText[] = "{\"test\": 1145141919810, \"test2\": \"衬衫的价格是九镑十五便士.\"}";
    json += JsonObject(jsonText);
    std::cout << "Print:\n" << json.PrintToString(true) << std::endl;

    std::cout << "Other Function." << std::endl;
    json.Remove("test");
    json.Remove("test2");
    std::cout << "Print:\n" << json.PrintToString(true) << "\nSize:" << json.Size() << std::endl;
    auto pos = json.GetKeyPos("text");
    std::cout << "integer: " << json.GetItemAtPos(pos + 1).valueString << std::endl;
    auto backupJson = json;
    json.Clear();
    std::cout << (backupJson == json ? "true" : "false") << std::endl;
    json = backupJson;
    std::cout << (backupJson == json ? "true" : "false") << std::endl;

    std::cout << "Exception." << std::endl;
    try {
        JsonObject("{wudhfeui: wufhiwehfuiewhuih}");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        JsonObject("{\"array\": []]}");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        json.GetValueRaw("wdqwdwqadw");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
