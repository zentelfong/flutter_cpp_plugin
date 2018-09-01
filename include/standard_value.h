#ifndef CPP_PLUGIN_STANDARD_VALUE_CALL_H_
#define CPP_PLUGIN_STANDARD_VALUE_CALL_H_

#include <string>
#include <vector>
#include <map>
#include <list>
#include <stdint.h>
#include <string.h>
#include <memory>

/*
null: NULL
bool: bool
int:  int
double: double

String: std::string
Uint8List: std::vector<uint8_t>
Int32List: std::vector<int32_t>
Int64List: std::vector<int64_t>
Float64List: std::vector<double>
List: std::vector<StandardValue>
Map:  std::map<StandardValue>
*/

namespace cpp_plugin
{

class StandardValue
{
public:
	enum Type {
		TYPE_NULL = 0,
		TYPE_TRUE = 1,
		TYPE_FALSE = 2,
		TYPE_INT = 3,
		TYPE_LONG = 4,
		//TYPE_BIGINT = 5,
		TYPE_DOUBLE = 6,
		TYPE_STRING = 7,
		TYPE_BYTE_ARRAY = 8,
		TYPE_INT_ARRAY = 9,
		TYPE_LONG_ARRAY = 10,
		TYPE_DOUBLE_ARRAY = 11,
		TYPE_LIST = 12,
		TYPE_MAP = 13,
	};

	StandardValue() 
		:type_(TYPE_NULL)
	{
		memset(&data_, 0, sizeof(data_));
	}

	void Release();

	~StandardValue() {
		Release();
	}

	StandardValue(StandardValue const &) = delete;
	StandardValue &operator=(StandardValue const &) = delete;


	Type type() const { return type_; }

	bool asBool()const;

	int asInt()const;

	int64_t asInt64()const;
	double asDouble()const;
	std::string* asString()const;
	std::vector<uint8_t>* asUint8List()const;
	std::vector<int32_t>* asInt32List()const;
	std::vector<int64_t>* asInt64List()const;
	std::vector<double>* asDoubleList()const;
	std::vector<std::shared_ptr<StandardValue>>* asList()const;
	std::map<std::string, std::shared_ptr<StandardValue>>* asMap()const;

	void fromBool(bool value);

	void fromInt(int value);

	void fromInt64(int64_t value);

	void fromDouble(double value);

	void fromString(const std::string& value);

	void fromString(const char* value, size_t len);

	void fromUint8List(const uint8_t* data, size_t len);

	void fromInt32List(const int32_t* data, size_t len);

	void fromInt64List(const int64_t* data, size_t len);

	void fromDoubleList(const double* data, size_t len);

	//如果类型不正确强制转换为指定类型，如果仅获取使用as..
	int& toInt();
	int64_t& toInt64();
	double& toDouble();
	std::string& toString();
	std::vector<uint8_t>& toUint8List();
	std::vector<int32_t>& toInt32List();
	std::vector<int64_t>& toInt64List();
	std::vector<double>& toDoubleList();
	std::vector<std::shared_ptr<StandardValue>>& toList();
	std::map<std::string, std::shared_ptr<StandardValue>>& toMap();

	//读写
	void WriteValue(std::vector<uint8_t>& dest);
	size_t ReadValue(const uint8_t *message, const size_t size);

private:
	Type type_;
	union DataT {
		int  int_value;
		int64_t  int64_value;
		double double_value;
		std::string* string_value;
		std::vector<uint8_t>* uint8list_value;
		std::vector<int32_t>* int32list_value;
		std::vector<int64_t>* int64list_value;
		std::vector<double>*  doublelist_value;
		std::vector<std::shared_ptr<StandardValue>>*  list_value;
		std::map<std::string,std::shared_ptr<StandardValue>>*  map_value;
	};
	DataT data_;
};

}//namespace

#endif //CPP_PLUGIN_STANDARD_VALUE_CALL_H_
