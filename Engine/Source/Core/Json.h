#pragma once

#include "Math/Vector2.h"
#include "Math/Rect.h"
#include "Renderer/Color.h"

#include <vector>
#include <rapidjson/document.h>
#include <string>

#define READ_DATA(value, data) Json::Read(value, #data, data, false)
#define READ_DATA_REQUIRED(value, data) Json::Read(value, #data, data, true)
#define READ_DATA_NAME(value, name, data) Json::Read(value, name, data)
#define READ_DATA_STRUCT(value, data, _struct) Json::Read(value, #data, _struct.##data)

#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]

#define WRITE_DATA(value, data) Json::Write(value, #data, data)
#define WRITE_DATA_NAME(value, name, data) Json::Write(value, name, data)

namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Save(const std::string& filename, rapidjson::Document& document);

	bool Write(rapidjson::Value& value, const std::string& name, float& data);
	bool Write(rapidjson::Value& value, const std::string& name, Vector2& data);

	bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool isRequired = false);

}

using json_t = rapidjson::Value;
//Older c++
//typedef rapidjson::Value json_t;