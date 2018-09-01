#include "standard_value.h"

namespace cpp_plugin {


bool StandardValue::asBool()const {
	return type_ == TYPE_TRUE;
}

int StandardValue::asInt()const {
	switch (type_)
	{
	case TYPE_NULL:
		return 0;
	case TYPE_TRUE:
		return 1;
	case TYPE_FALSE:
		return 0;
	case TYPE_INT:
		return data_.int_value;
	case TYPE_LONG:
		return (int)data_.int64_value;
	case TYPE_DOUBLE:
		return (int)data_.double_value;
	default:
		break;
	}
	return 0;
}

int64_t StandardValue::asInt64()const { 
	switch (type_)
	{
	case TYPE_NULL:
		return 0;
	case TYPE_TRUE:
		return 1;
	case TYPE_FALSE:
		return 0;
	case TYPE_INT:
		return (int64_t)data_.int_value;
	case TYPE_LONG:
		return (int64_t)data_.int64_value;
	case TYPE_DOUBLE:
		return (int64_t)data_.double_value;
	default:
		break;
	}
	return 0;
}


double StandardValue::asDouble()const { 
	switch (type_)
	{
	case TYPE_NULL:
		return 0.0;
	case TYPE_TRUE:
		return 1.0;
	case TYPE_FALSE:
		return 0.0;
	case TYPE_INT:
		return (double)data_.int_value;
	case TYPE_LONG:
		return (double)data_.int64_value;
	case TYPE_DOUBLE:
		return (double)data_.double_value;
	default:
		break;
	}
	return 0.0;
}

std::string* StandardValue::asString()const {
	if (type_ == TYPE_STRING)
		return data_.string_value;
	else
		return nullptr;
}


std::vector<uint8_t>* StandardValue::asUint8List()const {
	if (type_ == TYPE_BYTE_ARRAY)
		return data_.uint8list_value;
	else
		return nullptr;
}

std::vector<int32_t>* StandardValue::asInt32List()const {
	if (type_ == TYPE_INT_ARRAY)
		return data_.int32list_value; 
	else
		return nullptr;
}

std::vector<int64_t>* StandardValue::asInt64List()const {
	if (type_ == TYPE_LONG_ARRAY)
		return data_.int64list_value; 
	else
		return nullptr;
}


std::vector<double>* StandardValue::asDoubleList()const {
	if (type_ == TYPE_DOUBLE_ARRAY)
		return data_.doublelist_value; 
	else
		return nullptr;
}

std::vector<std::shared_ptr<StandardValue>>* StandardValue::asList()const {
	if (type_ == TYPE_LIST)
		return data_.list_value;
	else
		return nullptr;
}

std::map<std::string, std::shared_ptr<StandardValue>>* StandardValue::asMap()const {
	if (type_ == TYPE_MAP)
		return data_.map_value;
	else
		return nullptr;
}

void StandardValue::fromBool(bool value) {
	Release();
	if (value)
		type_ = TYPE_TRUE;
	else
		type_ = TYPE_FALSE;
}

void StandardValue::fromInt(int value) {
	Release();
	type_ = TYPE_INT;
	data_.int_value = value;
}

void StandardValue::fromInt64(int64_t value) {
	Release();
	type_ = TYPE_LONG;
	data_.int64_value = value;
}

void StandardValue::fromDouble(double value) {
	Release();
	type_ = TYPE_DOUBLE;
	data_.double_value = value;
}

void StandardValue::fromString(const std::string& value) {
	Release();
	type_ = TYPE_STRING;
	data_.string_value = new std::string(value);
}

void StandardValue::fromString(const char* value, size_t len) {
	Release();
	type_ = TYPE_STRING;
	data_.string_value = new std::string(value, len);
}

void StandardValue::fromUint8List(const uint8_t* data, size_t len) {
	Release();
	type_ = TYPE_BYTE_ARRAY;
	data_.uint8list_value = new std::vector<uint8_t>(len, 0);
	for (size_t i = 0; i < len; i++)
	{
		(*data_.uint8list_value)[i] = data[i];
	}
}

void StandardValue::fromInt32List(const int32_t* data, size_t len) {
	Release();
	type_ = TYPE_INT_ARRAY;
	data_.int32list_value = new std::vector<int32_t>(len, 0);
	for (size_t i = 0; i < len; i++)
	{
		(*data_.int32list_value)[i] = data[i];
	}
}

void StandardValue::fromInt64List(const int64_t* data, size_t len) {
	Release();
	type_ = TYPE_LONG_ARRAY;
	data_.int64list_value = new std::vector<int64_t>(len, 0);
	for (size_t i = 0; i < len; i++)
	{
		(*data_.int64list_value)[i] = data[i];
	}
}

void StandardValue::fromDoubleList(const double* data, size_t len) {
	Release();
	type_ = TYPE_LONG_ARRAY;
	data_.doublelist_value = new std::vector<double>(len, 0);
	for (size_t i = 0; i < len; i++)
	{
		(*data_.doublelist_value)[i] = data[i];
	}
}

int& StandardValue::toInt() {
	if (type_ != TYPE_INT)
	{
		Release();
		type_ = TYPE_INT;
	}
	return data_.int_value;
}

int64_t& StandardValue::toInt64() {
	if (type_ != TYPE_LONG)
	{
		Release();
		type_ = TYPE_LONG;
	}
	return data_.int64_value;
}

double& StandardValue::toDouble() {
	if (type_ != TYPE_DOUBLE)
	{
		Release();
		type_ = TYPE_DOUBLE;
	}
	return data_.double_value;
}

std::string& StandardValue::toString() {
	if (type_ != TYPE_STRING)
	{
		Release();
		type_ = TYPE_STRING;
		data_.string_value = new std::string();
	}
	return *data_.string_value;
}


std::vector<uint8_t>& StandardValue::toUint8List() {
	if (type_ != TYPE_BYTE_ARRAY)
	{
		Release();
		type_ = TYPE_BYTE_ARRAY;
		data_.uint8list_value = new std::vector<uint8_t>();
	}
	return *data_.uint8list_value;
}

std::vector<int32_t>& StandardValue::toInt32List() {
	if (type_ != TYPE_INT_ARRAY)
	{
		Release();
		type_ = TYPE_INT_ARRAY;
		data_.int32list_value = new std::vector<int32_t>();
	}
	return *data_.int32list_value;
}

std::vector<int64_t>& StandardValue::toInt64List() {
	if (type_ != TYPE_LONG_ARRAY)
	{
		Release();
		type_ = TYPE_LONG_ARRAY;
		data_.int64list_value = new std::vector<int64_t>();
	}
	return *data_.int64list_value;
}

std::vector<double>& StandardValue::toDoubleList() {
	if (type_ != TYPE_DOUBLE_ARRAY)
	{
		Release();
		type_ = TYPE_DOUBLE_ARRAY;
		data_.doublelist_value = new std::vector<double>();
	}

	return *data_.doublelist_value;
}

std::vector<std::shared_ptr<StandardValue>>& StandardValue::toList() {
	if (type_ != TYPE_LIST)
	{
		Release();
		type_ = TYPE_LIST;
		data_.list_value = new std::vector<std::shared_ptr<StandardValue>>();
	}
	return *data_.list_value;
}

std::map<std::string, std::shared_ptr<StandardValue>>& StandardValue::toMap(){
	if (type_ != TYPE_MAP)
	{
		Release();
		type_ = TYPE_MAP;
		data_.map_value = new std::map<std::string, std::shared_ptr<StandardValue>>();
	}
	return *data_.map_value;
}

void StandardValue::Release() {
	switch (type_)
	{
	case StandardValue::TYPE_STRING:
		delete data_.string_value;
		break;
	case StandardValue::TYPE_BYTE_ARRAY:
		delete data_.uint8list_value;
		break;
	case StandardValue::TYPE_INT_ARRAY:
		delete data_.int32list_value;
		break;
	case StandardValue::TYPE_LONG_ARRAY:
		delete data_.int64list_value;
		break;
	case StandardValue::TYPE_DOUBLE_ARRAY:
		delete data_.doublelist_value;
		break;
	case StandardValue::TYPE_LIST:
		delete data_.list_value;
		break;
	case StandardValue::TYPE_MAP:
		delete data_.map_value;
		break;
	default:
		break;
	}
	type_ = TYPE_NULL;
	memset(&data_, 0, sizeof(data_));
}


void writeChar(std::vector<uint8_t>& dest, int value) {
	dest.push_back(value);
	dest.push_back(value>>8);
}

void writeInt(std::vector<uint8_t>& dest, int value) {
	dest.push_back(value);
	dest.push_back(value >> 8);
	dest.push_back(value >> 16);
	dest.push_back(value >> 24);
}

void writeLong(std::vector<uint8_t>& dest, int64_t value) {
	dest.push_back(value);
	dest.push_back(value >> 8);
	dest.push_back(value >> 16);
	dest.push_back(value >> 24);
	dest.push_back(value >> 32);
	dest.push_back(value >> 40);
	dest.push_back(value >> 48);
	dest.push_back(value >> 56);
}

void writeDouble(std::vector<uint8_t>& dest, double value) {
	int64_t* temp = (int64_t*)&value;
	writeLong(dest, *temp);
}

void WriteSize(std::vector<uint8_t>& dest, size_t value) {

	if (value < 254) {
		dest.push_back(value);
	}
	else if (value <= 0xffff) {
		dest.push_back(254);
		writeChar(dest,value);
	}
	else {
		dest.push_back(255);
		writeInt(dest, value);
	}
}

void writeString(std::vector<uint8_t>& dest,const std::string& value) {
	WriteSize(dest, value.length());
	for (auto ch : value)
	{
		dest.push_back(ch);
	}
}

void writeAlignment(std::vector<uint8_t>& dest, int alignment) {
	int mod = dest.size() % alignment;
	if (mod != 0) {
		for (int i = 0; i < alignment - mod; i++) {
			dest.push_back(0);
		}
	}
}

void StandardValue::WriteValue(std::vector<uint8_t>& dest) {

	dest.push_back(type_);
	switch (type_)
	{
	case TYPE_INT:
		writeInt(dest, data_.int_value);
		break;

	case TYPE_LONG:
		writeLong(dest,data_.int64_value);
		break;

	case TYPE_DOUBLE:
		writeAlignment(dest, 8);
		writeDouble(dest,data_.double_value);
		break;

	case TYPE_STRING:
		writeString(dest,*data_.string_value);
		break;

	case TYPE_BYTE_ARRAY:
		WriteSize(dest, data_.uint8list_value->size());
		for (auto ch : *data_.uint8list_value)
		{
			dest.push_back(ch);
		}
		break;

	case TYPE_INT_ARRAY:
		WriteSize(dest, data_.int32list_value->size());
		writeAlignment(dest, 4);
		for (auto value : *data_.int32list_value)
		{
			writeInt(dest, value);
		}
		break;

	case TYPE_LONG_ARRAY:
		WriteSize(dest, data_.int64list_value->size());
		writeAlignment(dest, 8);
		for (auto value : *data_.int64list_value)
		{
			writeLong(dest, value);
		}
		break;

	case TYPE_DOUBLE_ARRAY:
		WriteSize(dest, data_.doublelist_value->size());
		writeAlignment(dest, 8);
		for (auto value : *data_.doublelist_value)
		{
			writeDouble(dest,value);
		}
		break;

	case TYPE_LIST:
		WriteSize(dest, data_.list_value->size());
		for (auto value : *data_.list_value)
		{
			value->WriteValue(dest);
		}
		break;

	case TYPE_MAP:
		WriteSize(dest, data_.map_value->size());
		for (auto value : *data_.map_value)
		{
			writeString(dest, value.first);
			value.second->WriteValue(dest);
		}
		break;
	default:
		break;
	}
}

class ReadBuffer
{
public:
	ReadBuffer(const uint8_t*d, size_t len)
		:data_(d),size_(len), current_(0)
	{
	}

	size_t readSize() {
		size_t value = data_[current_]; ++current_;
		if (value < 254) {
			return value;
		}
		else if (value == 254) {
			return (size_t)getChar();
		}
		else {
			return (size_t)getInt();
		}
	}

	const uint8_t* readBytes(size_t &len) {
		len = readSize();
		const uint8_t* data = data_ + current_;
		current_ += len;
		return data;
	}
	
	void readAlignment(int alignment) {
		int mod = current_ % alignment;
		if (mod != 0) {
			current_ = current_ + alignment - mod;
		}
	}

	int getByte() {
		int ch = data_[current_]; ++current_;
		return ch;
	}

	int getChar() {
		int ch = data_[current_]; ++current_;
		ch |= data_[current_] << 8; ++current_;
		return ch;
	}

	int getInt() {
		int ch = data_[current_]; ++current_;
		ch |= int(data_[current_]) << 8; ++current_;
		ch |= int(data_[current_]) << 16; ++current_;
		ch |= int(data_[current_]) << 24; ++current_;
		return ch;
	}

	int64_t getLong() {
		int64_t ch = data_[current_]; ++current_;
		ch |= int64_t(data_[current_]) << 8; ++current_;
		ch |= int64_t(data_[current_]) << 16; ++current_;
		ch |= int64_t(data_[current_]) << 24; ++current_;
		ch |= int64_t(data_[current_]) << 32; ++current_;
		ch |= int64_t(data_[current_]) << 40; ++current_;
		ch |= int64_t(data_[current_]) << 48; ++current_;
		ch |= int64_t(data_[current_]) << 56; ++current_;
		return ch;
	}

	double getDouble() {
		int64_t value = getLong();
		return *(double*)&value;
	}

	size_t current() { return current_; }

	void offset(size_t off) {
		current_ += off;
	}
private:
	const uint8_t *data_;
	size_t size_;
	size_t current_;
};



size_t StandardValue::ReadValue(const uint8_t *message, const size_t size) {
	
	ReadBuffer buffer(message,size);
	uint8_t type = buffer.getByte();

	switch (type)
	{
	case TYPE_NULL:
		Release();
		break;
	case TYPE_TRUE:
		fromBool(true);
		break;
	case TYPE_FALSE:
		fromBool(false);
		break;
	case TYPE_INT:
		fromInt(buffer.getInt());
		break;
	case TYPE_LONG:
		fromInt64(buffer.getLong());
		break;
	case TYPE_DOUBLE:
		buffer.readAlignment(8);
		fromDouble(buffer.getDouble());
		break;
	case TYPE_STRING:
		{
			size_t len = 0;
			const char* str=(char*)buffer.readBytes(len);
			fromString(str, len);
		}
		break;
	case TYPE_BYTE_ARRAY:
		{
			size_t len = 0;
			const uint8_t* data = buffer.readBytes(len);
			fromUint8List(data, len);
		}
		break;
	case TYPE_INT_ARRAY:
		{
			Release();
			size_t length = buffer.readSize();
			buffer.readAlignment(4);
			type_ = TYPE_INT_ARRAY;
			data_.int32list_value = new std::vector<int32_t>(length, 0);

			for (size_t i = 0; i < length; i++)
			{
				(*data_.int32list_value)[i]=buffer.getInt();
			}
		}
		break;
	case TYPE_LONG_ARRAY:
		{
			Release();
			size_t length = buffer.readSize();
			buffer.readAlignment(8);
			type_ = TYPE_LONG_ARRAY;
			data_.int64list_value = new std::vector<int64_t>(length, 0);

			for (size_t i = 0; i < length; i++)
			{
				(*data_.int64list_value)[i] = buffer.getLong();
			}
		}
		break;
	case TYPE_DOUBLE_ARRAY:
		{
			Release();
			size_t length = buffer.readSize();
			buffer.readAlignment(8);
			type_ = TYPE_DOUBLE_ARRAY;
			data_.doublelist_value = new std::vector<double>(length, 0);

			for (size_t i = 0; i < length; i++)
			{
				(*data_.doublelist_value)[i] = buffer.getDouble();
			}
		}
		break;
	case TYPE_LIST:
		{
			Release();
			size_t length = buffer.readSize();
			type_ = TYPE_LIST;
			data_.list_value = new std::vector<std::shared_ptr<StandardValue>>(length);

			for (size_t i = 0; i < length; i++)
			{
				std::shared_ptr<StandardValue> value = std::make_shared<StandardValue>();
				buffer.offset(value->ReadValue(message+buffer.current(),size - buffer.current()));
				(*data_.list_value)[i] = value;
			}
		}
		break;
	case TYPE_MAP:
		{
			Release();
			int length = buffer.readSize();
			type_ = TYPE_MAP;
			data_.map_value = new std::map<std::string, std::shared_ptr<StandardValue>>();

			for (int i = 0; i < length; i++)
			{
				StandardValue key;
				buffer.offset(key.ReadValue(message + buffer.current(), size - buffer.current()));

				std::shared_ptr<StandardValue> value = std::make_shared<StandardValue>();
				buffer.offset(value->ReadValue(message + buffer.current(), size - buffer.current()));
				(*data_.map_value)[*key.asString()] = value;
			}
		}
		break;
	default:
		break;
	}

	return buffer.current();
}




}//namespace


