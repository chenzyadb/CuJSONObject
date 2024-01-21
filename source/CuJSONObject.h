// CuJSONObject V1 by chenzyadb@github.com
// Based on C++17 STL (MSVC).

#ifndef _CU_JSONOBJECT_
#define _CU_JSONOBJECT_

#include <map>
#include <vector>
#include <string>
#include <variant>
#include <memory>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <climits>

namespace CU
{
	inline char _GetEscapeChar(char ch) noexcept
	{
		char ret = ch;
		switch (ch) {
			case '\\':
				ret = '\\';
				break;
			case '\"':
				ret = '\"';
				break;
			case '\'':
				ret = '\'';
				break;
			case 'n':
				ret = '\n';
				break;
			case 'r':
				ret = '\r';
				break;
			case 't':
				ret = '\t';
				break;
			case 'b':
				ret = '\b';
				break;
			case 'f':
				ret = '\f';
				break;
			case 'a':
				ret = '\a';
				break;
			case 'v':
				ret = '\v';
				break;
			case '/':
				ret = '/';
				break;
			default:
				break;
		}
		return ret;
	}

	inline std::string _StringToJSONRaw(const std::string &str)
	{
		std::string JSONRaw("\"");
		for (const auto &ch : str) {
			switch (ch) {
				case '\\':
					JSONRaw += "\\\\";
					break;
				case '\"':
					JSONRaw += "\\\"";
					break;
				case '\'':
					JSONRaw += "\\\'";
					break;
				case '\n':
					JSONRaw += "\\n";
					break;
				case '\t':
					JSONRaw += "\\t";
					break;
				case '\r':
					JSONRaw += "\\r";
					break;
				case '\f':
					JSONRaw += "\\f";
					break;
				case '\a':
					JSONRaw += "\\a";
					break;
				case '\b':
					JSONRaw += "\\b";
					break;
				case '\v':
					JSONRaw += "\\v";
					break;
				case '/':
					JSONRaw += "\\/";
					break;
				default:
					JSONRaw += ch;
					break;
			}
		}
		JSONRaw += '\"';
		return JSONRaw;
	}

	class JSONExcept : public std::exception
	{
		public:
			JSONExcept(const std::string &message) : message_(message) { }

			const char* what() const noexcept override
			{
				return message_.c_str();
			}

		private:
			const std::string message_;
	};

	class JSONObject;
	class JSONArray;

	enum class ItemType : uint8_t {ITEM_NULL, BOOLEAN, INTEGER, LONG, DOUBLE, STRING, ARRAY, OBJECT};

	inline ItemType _GetItemType(const std::string &itemText)
	{
		ItemType type{};
		switch (itemText.front()) {
			case '{':
				if (itemText.back() == '}') {
					type = ItemType::OBJECT;
				} else {
					throw JSONExcept("Invalid JSONItem");
				}
				break;
			case '[':
				if (itemText.back() == ']') {
					type = ItemType::ARRAY;
				} else {
					throw JSONExcept("Invalid JSONItem");
				}
				break;
			case '\"':
				if (itemText.back() == '\"') {
					type = ItemType::STRING;
				} else {
					throw JSONExcept("Invalid JSONItem");
				}
				break;
			case '-':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				{
					auto num = atof(itemText.c_str());
					if (num == 0 && itemText != "0" && itemText != "0.0") {
						throw JSONExcept("Invalid JSONItem");
					}
					if (num == static_cast<int64_t>(num)) {
						if (num > static_cast<double>(INT_MAX) || num < static_cast<double>(INT_MIN)) {
							type = ItemType::LONG;
						} else {
							type = ItemType::INTEGER;
						}
					} else {
						type = ItemType::DOUBLE;
					}
				}
				break;
			case 't':
			case 'f':
				if (itemText == "true" || itemText == "false") {
					type = ItemType::BOOLEAN;
				} else {
					throw JSONExcept("Invalid JSONItem");
				}
				break;
			case 'n':
				if (itemText == "null") {
					type = ItemType::ITEM_NULL;
				} else {
					throw JSONExcept("Invalid JSONItem");
				}
				break;
			default:
				{
					throw JSONExcept("Invalid JSONItem");
				}
		}
		return type;
	}

	typedef uint8_t ItemNull;

	typedef std::variant<ItemNull, bool, int, int64_t, double, std::string, JSONArray*, JSONObject*> ItemValue;

	class JSONItem
	{
		public:
			JSONItem();
			JSONItem(const bool &value);
			JSONItem(const int &value);
			JSONItem(const int64_t &value);
			JSONItem(const double &value);
			JSONItem(const char* value);
			JSONItem(const std::string &value);
			JSONItem(const JSONArray &value);
			JSONItem(const JSONObject &value);
			JSONItem(const JSONItem &other);
			JSONItem(JSONItem &&other) noexcept;
			~JSONItem();
			
			JSONItem &operator()(const JSONItem &other);
			JSONItem &operator=(const JSONItem &other);
			bool operator==(const JSONItem &other) const;
			bool operator!=(const JSONItem &other) const;
			bool operator>(const JSONItem &other) const;
			bool operator<(const JSONItem &other) const;

			ItemType type() const;
			ItemValue value() const;

			bool toBoolean() const;
			int toInt() const;
			int64_t toLong() const;
			double toDouble() const;
			std::string toString() const;
			JSONArray toArray() const;
			JSONObject toObject() const;

			std::string _To_JSONRaw() const;
			void clear();
			
		private:
			ItemType type_;
			ItemValue value_;
	};

	class JSONArray
	{
		public:
			typedef std::vector<JSONItem>::iterator Iterator;
			typedef std::vector<JSONItem>::const_iterator ConstIterator;

			JSONArray();
			JSONArray(const size_t &init_size);
			JSONArray(const size_t &init_size, const JSONItem &init_value);
			JSONArray(Iterator begin_iter, Iterator end_iter);
			JSONArray(const std::string &JSONString);
			JSONArray(const std::vector<JSONItem> &data);
			JSONArray(const std::vector<bool> &list);
			JSONArray(const std::vector<int> &list);
			JSONArray(const std::vector<int64_t> &list);
			JSONArray(const std::vector<double> &list);
			JSONArray(const std::vector<std::string> &list);
			JSONArray(const std::vector<JSONArray> &list);
			JSONArray(const std::vector<JSONObject> &list);
			JSONArray(const JSONArray &other);
			JSONArray(JSONArray &&other) noexcept;
			~JSONArray();
			
			JSONArray &operator()(const JSONArray &other);
			JSONArray &operator=(const JSONArray &other);
			JSONArray &operator+=(const JSONArray &other);
			JSONItem &operator[](const size_t &pos);
			JSONArray operator+(const JSONArray &other) const;
			bool operator==(const JSONArray &other) const;
			bool operator!=(const JSONArray &other) const;
			bool operator>(const JSONArray &other) const;
			bool operator<(const JSONArray &other) const;

			std::vector<bool> toListBoolean() const;
			std::vector<int> toListInt() const;
			std::vector<int64_t> toListLong() const;
			std::vector<double> toListDouble() const;
			std::vector<std::string> toListString() const;
			std::vector<JSONArray> toListArray() const;
			std::vector<JSONObject> toListObject() const;

			JSONItem at(const size_t &pos) const;
			Iterator find(const JSONItem &item);
			void add(const JSONItem &item);
			void remove(const JSONItem &item);
			void resize(const size_t &new_size);
			void clear();
			size_t size() const;
			bool empty() const;
			std::vector<JSONItem> data() const;
			std::string toString() const;

			JSONItem &front();
			JSONItem &back();
			Iterator begin();
			Iterator end();
			ConstIterator begin() const;
			ConstIterator end() const;
			
		private:
			std::vector<JSONItem> data_;
	};

	class JSONObject
	{
		public:
			JSONObject();
			JSONObject(const std::string &JSONString);
			JSONObject(const std::map<std::string, JSONItem> &data);
			JSONObject(const JSONObject &other);
			JSONObject(JSONObject &&other) noexcept;
			~JSONObject();

			JSONObject &operator()(const JSONObject &other);
			JSONObject &operator=(const JSONObject &other);
			JSONObject &operator+=(const JSONObject &other);
			JSONItem &operator[](const std::string &key);
			JSONObject operator+(const JSONObject &other) const;
			bool operator==(const JSONObject &other) const;
			bool operator!=(const JSONObject &other) const;
			bool operator>(const JSONObject &other) const;
			bool operator<(const JSONObject &other) const;
			
			bool contains(const std::string &key) const;
			JSONItem at(const std::string &key) const;
			void add(const std::string &key, const JSONItem &value);
			void remove(const std::string &key);
			void clear();
			size_t size() const;
			bool empty() const;
			std::map<std::string, JSONItem> data() const;
			std::vector<std::string> order() const;
			std::string toString() const;
			std::string toFormatedString() const;

		private:
			std::map<std::string, JSONItem> data_;
			std::vector<std::string> order_;
	};
}

#endif
