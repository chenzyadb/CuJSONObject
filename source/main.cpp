#include <iostream>
#include <climits>
#include "JsonObject.h"

constexpr char demo_json[] =
"{                                \r\n"
"\"jsonName\": \"demoJson\",      \r\n"
"\"jsonVersion\": 100,            \r\n"
"\"longValue\": 1234567890,       \r\n"
"\"json\": {                      \r\n"
"   \"boolean\": true,            \r\n"
"   \"number\": 1234567,          \r\n"
"   \"double_num\": 3.141592,     \r\n"
"   \"json\": {                   \r\n"
"       \"text\": \"Hello,World\",\r\n"
"       \"num\": 11451419         \r\n"
"      }                          \r\n"
"   },                            \r\n"
"\"num\": 1919810,                \r\n"
"\"stringList\": [                \r\n"
"    \"hello\",                   \r\n"
"    \"world\",                   \r\n"
"    \"chenzyadb\"],              \r\n"
"\"intList\": [                   \r\n"
"    187, 26, 3],                 \r\n"
"\"longList\": [                  \r\n"
"    123456789,987654321],        \r\n"
"\"doubleList\": [                \r\n"
"    1.23, 3.141592, 114.5],      \r\n"
"\"booleanList\": [               \r\n"
"    true, false, true],          \r\n"
"\"jsonList\": [                  \r\n"
"    {\"name\": \"abcabc\"},      \r\n"
"    {\"id\": 12345678},          \r\n"
"    {\"male\": false}]           \r\n"
"}                                \r\n";

int main()
{
    JsonObject json(demo_json);

    std::cout << "contains jsonName: " << json.Contains("jsonName") << std::endl;
    std::cout << "contains undefined: " << json.Contains("undefined") << std::endl;

    std::cout << "print jsonName: " << json.GetValueString("jsonName") << std::endl;
    std::cout << "print jsonVersion: " << json.GetValueInt("jsonVersion") << std::endl;
    std::cout << "print longValue: " << json.GetValueLong("longValue") << std::endl;
    std::cout << "print num: " << json.GetValueInt("num") << std::endl;
    std::cout << "print stringList: " << std::endl;
    for (const auto &s : json.GetArrayString("stringList")) {
        std::cout << s << std::endl;
    }
    std::cout << "print intList: " << std::endl;
    for (const auto &i : json.GetArrayInt("intList")) {
        std::cout << i << std::endl;
    }
    std::cout << "print longList: " << std::endl;
    for (const auto &l : json.GetArrayInt("longList")) {
        std::cout << l << std::endl;
    }
    std::cout << "print doubleList: " << std::endl;
    for (const auto &d : json.GetArrayDouble("doubleList")) {
        std::cout << d << std::endl;
    }
    std::cout << "print booleanList: " << std::endl;
    for (const auto &b : json.GetArrayBoolean("booleanList")) {
        std::cout << b << std::endl;
    }
    std::cout << "print jsonList: " << std::endl;
    for (const auto &j : json.GetArrayJson("jsonList")) {
        std::cout << j.PrintToString(false) << std::endl;
    }

    JsonObject itemJson = json.GetValueJson("json");
    std::cout << "print json(formatted):" << std::endl;
    std::cout << itemJson.PrintToString(true) << std::endl;
    std::cout << "print json(unformatted):"  << std::endl;
    std::cout << itemJson.PrintToString(false) << std::endl;
    std::cout << "print boolean: " << itemJson.GetValueBoolean("boolean") << std::endl;
    std::cout << "print number: " << itemJson.GetValueInt("number") << std::endl;
    std::cout << "print double_num: " << itemJson.GetValueDouble("double_num") << std::endl;

    JsonObject secItemJson = itemJson.GetValueJson("json");
    std::cout << "print json(formatted):" << std::endl;
    std::cout << secItemJson.PrintToString(true) << std::endl;
    std::cout << "print json(unformatted):" << std::endl;
    std::cout << secItemJson.PrintToString(false) << std::endl;
    std::cout << "print text: " << secItemJson.GetValueString("text") << std::endl;
    std::cout << "print num: " << secItemJson.GetValueInt("num") << std::endl;

    JsonObject newJson{};
    newJson.PutValueString("text", "Hello, this is a new JSON.");
    newJson.PutValueInt("int", INT_MAX);
    newJson.PutValueLong("long", LONG_MAX);
    newJson.PutValueDouble("double", 12.3456);
    newJson.PutValueBoolean("isTrue", false);
    newJson.PutValueJson("json", secItemJson);
    std::vector<std::string> arrayString = {"hello", "json"};
    newJson.PutArrayString("arrayString", arrayString);
    std::vector<int> arrayInt = {114, 514, 1919, 810};
    newJson.PutArrayInt("arrayInt", arrayInt);
    std::vector<long> arrayLong = {1919810, 114514, 1234567890};
    newJson.PutArrayLong("arrayLong", arrayLong);
    std::vector<double> arrayDouble = {1.23, 2.34, 3.45};
    newJson.PutArrayDouble("arrayDouble", arrayDouble);
    std::vector<bool> arrayBoolean = {true, true, false};
    newJson.PutArrayBoolean("arrayBoolean", arrayBoolean);
    std::vector<JsonObject> arrayJson{};
    for (int i = 0; i < 5; i++) {
        JsonObject j{};
        j.PutValueInt("value", i);
        arrayJson.emplace_back(j);
    }
    newJson.PutArrayJson("arrayJson", arrayJson);
    std::cout << "Print newJson: " << std::endl;
    std::cout << newJson.PrintToString(true) << std::endl;

    json += newJson;
    json.Remove("jsonName");
    std::cout << "Print Json: " << std::endl;
    std::cout << json.PrintToString(true) << std::endl;

    json.Clear();
    std::cout << "Print Json: " << std::endl;
    std::cout << json.PrintToString(true) << std::endl;

    std::cout << "Is json equals: " << (json == itemJson) << std::endl;

    json = itemJson;
    std::cout << "Is json equals: " << (json == itemJson) << std::endl;

    std::cout << "Exception Test: " << std::endl;
    try {
        JsonObject testJson = JsonObject("{,}");
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    try {
        JsonObject testJson{};
        testJson.GetValueString("123");
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
