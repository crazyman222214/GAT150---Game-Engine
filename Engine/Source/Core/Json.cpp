#include "Json.h"
#include "EFile.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <iostream>
#include <fstream>

namespace Json
{
    bool Load(const std::string& filename, rapidjson::Document& document)
    {
        std::string buffer;
        if (!File::ReadFile(filename, buffer))
        {
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        document.ParseStream(istream);

        if (!document.IsObject())
        {
            std::cerr << "Could not parse document: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Save(const std::string& filename, rapidjson::Document& document)
    {
        std::ofstream ofs(filename);
        rapidjson::OStreamWrapper osw(ofs);

        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        bool writen = document.Accept(writer);
        if (!writen)
        {
            std::cerr << "oh no cant save";
        }

        return true;
    }

    bool Write(rapidjson::Value& value, const std::string& name, float& data)
    {
        if (!value.HasMember(name.c_str()))
        {
           
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        value[name.c_str()].SetFloat(data);
        
    }

    bool Write(rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];

        for (rapidjson::SizeType i = 0; i < 2; i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            array[i].SetFloat(data[i]);
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;

        }
        data = value[name.c_str()].GetInt();
        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
        {
                if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
        }
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }
        data = value[name.c_str()].GetBool();
        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }
        data = value[name.c_str()].GetString();
        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array with 4 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }


        // get json array object
        auto& array = value[name.c_str()];

        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        //data[i] = value[name.c_str()].GetString();
        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array with 4 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }


        // get json array object
        auto& array = value[name.c_str()];

        // get array values
        data.x = array[0].GetInt();
        data.y = array[1].GetInt();
        data.height = array[2].GetInt();
        data.width = array[3].GetInt();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }


        // get json array object
        auto& array = value[name.c_str()];

        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data.push_back(array[i].GetInt());
        }

        //data[i] = value[name.c_str()].GetString();
        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }


        // get json array object
        auto& array = value[name.c_str()];

        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsString())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data.push_back(array[i].GetString());
        }

        //data[i] = value[name.c_str()].GetString();
        return true;
    }
}
