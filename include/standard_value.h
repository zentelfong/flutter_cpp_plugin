#ifndef CPP_PLUGIN_STANDARD_VALUE_CALL_H_
#define CPP_PLUGIN_STANDARD_VALUE_CALL_H_

#include <string>
#include <vector>
#include <map>
#include <list>
#include <stdint.h>
#include <string.h>

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
	bool asBool()const{
		return type_==TYPE_TRUE; 
	}
	int asInt()const { return data_.int_value; }
	int64_t asInt64()const { return data_.int64_value; }
	double asDouble()const { return data_.double_value; }
	std::string* asString()const { return data_.string_value; }
	std::vector<uint8_t>* asUint8List()const { return data_.uint8list_value; }
	std::vector<int32_t>* asInt32List()const { return data_.int32list_value; }
	std::vector<int64_t>* asInt64List()const { return data_.int64list_value; }
	std::vector<double>* asDoubleList()const { return data_.doublelist_value; }
	std::vector<StandardValue*>* asList()const { return data_.list_value; }
	std::map<std::string, StandardValue*>* asMap()const { return data_.map_value; }

	void fromBool(bool value) {
		Release();
		if (value)
			type_ = TYPE_TRUE;
		else
			type_ = TYPE_FALSE;
	}

	void fromInt(int value) {
		Release();
		type_ = TYPE_INT;
		data_.int_value = value;
	}

	void fromInt64(int64_t value) {
		Release();
		type_ = TYPE_LONG;
		data_.int64_value = value;
	}

	void fromDouble(double value) {
		Release();
		type_ = TYPE_DOUBLE;
		data_.double_value = value;
	}

	void fromString(const std::string& value) {
		Release();
		type_ = TYPE_STRING;
		data_.string_value = new std::string(value);
	}

	void fromString(const char* value,size_t len) {
		Release();
		type_ = TYPE_STRING;
		data_.string_value = new std::string(value,len);
	}

	void fromUint8List(const uint8_t* data,size_t len) {
		Release();
		type_ = TYPE_BYTE_ARRAY;
		data_.uint8list_value = new std::vector<uint8_t>(len,0);
		for (size_t i = 0; i < len; i++)
		{
			(*data_.uint8list_value)[i] = data[i];
		}
	}

	void fromInt32List(const int32_t* data, size_t len) {
		Release();
		type_ = TYPE_INT_ARRAY;
		data_.int32list_value = new std::vector<int32_t>(len, 0);
		for (size_t i = 0; i < len; i++)
		{
			(*data_.int32list_value)[i] = data[i];
		}
	}

	void fromInt64List(const int64_t* data, size_t len) {
		Release();
		type_ = TYPE_LONG_ARRAY;
		data_.int64list_value = new std::vector<int64_t>(len, 0);
		for (size_t i = 0; i < len; i++)
		{
			(*data_.int64list_value)[i] = data[i];
		}
	}

	void fromDoubleList(const double* data, size_t len) {
		Release();
		type_ = TYPE_LONG_ARRAY;
		data_.doublelist_value = new std::vector<double>(len, 0);
		for (size_t i = 0; i < len; i++)
		{
			(*data_.doublelist_value)[i] = data[i];
		}
	}

	//¶ÁÐ´
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
		std::vector<StandardValue*>*  list_value;
		std::map<std::string,StandardValue*>*  map_value;
	};
	DataT data_;
};

}//namespace

#endif //CPP_PLUGIN_STANDARD_VALUE_CALL_H_
