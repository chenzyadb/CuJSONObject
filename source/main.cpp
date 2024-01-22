#include <iostream>
#include "CuJSONObject.h"

int main()
{
    using namespace CU;
    // item test.
    {
        JSONItem item{};
        std::cout << item.toString() << std::endl;
        item = true;
        std::cout << item.toBoolean() << std::endl;
        item = INT_MAX;
        std::cout << item.toInt() << std::endl;
        item = INT64_MAX;
        std::cout << item.toLong() << std::endl;
        item = 3.14159;
        std::cout << item.toDouble() << std::endl;
        item = "Hello, World!";
        std::cout << item.toString() << std::endl;
    }

    // array test.
    {
        JSONArray array{};
        array = std::vector<bool>{true, false, false};
        std::cout << array.toString() << std::endl;
        array = std::vector<int>{1, 2, 3};
        std::cout << array.toString() << std::endl;
        array = std::vector<int64_t>{12345678987654321, 98765432123456789};
        std::cout << array.toString() << std::endl;
        array = std::vector<double>{3.14, 7.62, 5.56};
        std::cout << array.toString() << std::endl;
        array = std::vector<std::string>{"This", "is", "List"};
        std::cout << array.toString() << std::endl;
        array = JSONArray("[[[]], [[[], []], [[], []]], [[[], [], []], [[], [], []], [[], [], []]]]");
        std::cout << array.toString() << std::endl;

        array = JSONArray("[1, 2, 3, \"text\", null]");
        std::cout << array.toString() << std::endl;
        array.remove("text");
        array.remove(2);
        std::cout << array.toString() << std::endl;
    }

    // object test.
    {
        JSONObject object(
            "{\"boolean\": true, \"int\": 12345678, \"long\": 12345678987654321, \"double\": 3.141592, \n"
            "\"string\": \"Hello, World!\", \"array\": [true, 123, 123321123321123321, 5.56, \"test\", [], {}], \n"
            "\"object\": {\"val\": {}}, \"null\": null}"
        );
        std::cout << object.toFormatedString() << std::endl;
        std::cout << object["boolean"].toBoolean() << std::endl;
        std::cout << object["int"].toInt() << std::endl;
        std::cout << object["long"].toLong() << std::endl;
        std::cout << object["double"].toDouble() << std::endl;
        std::cout << object["string"].toString() << std::endl;
        std::cout << object["array"].toArray().toString() << std::endl;
        std::cout << object["object"].toObject().toString() << std::endl;

        object["newVal"] = JSONObject("{\"newObj\": \"test\"}");
        std::cout << object.toFormatedString() << std::endl;
    }

    return 0;
}
