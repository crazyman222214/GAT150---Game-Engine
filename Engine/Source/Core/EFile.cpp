#include "EFile.h"
#include <iostream>
#include <fstream>

std::string File::GetFilePath()
{
    return std::filesystem::current_path().string();
}

bool File::SetFilePath(const std::string& filepath)
{
    std::error_code ec;
    std::filesystem::current_path(filepath, ec);

    return !ec;
}

bool File::FileExists(const std::string& filepath)
{
    return std::filesystem::exists(filepath);
}

bool File::GetFileSize(const std::string& filepath, int& size)
{
    //Really looking for a filepath, but they can take a string
    std::filesystem::path path(filepath);

    std::error_code ec;
    size = (int)std::filesystem::file_size(path, ec);
    return !ec;
}

bool File::ReadFile(const std::string filepath, std::string& buffer)
{
    if (!FileExists(filepath))
    {
        std::cerr << "File does not exist: " << filepath << std::endl;
        return false;
    }
    std::ifstream stream(filepath);

    if (!stream.is_open())
    {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return false;
    }

    std::ostringstream ostream;
    ostream << stream.rdbuf();
    buffer = ostream.str();

    return true;
}

bool File::SaveFile(const std::string filepath, std::string& buffer)
{
    if (!FileExists(filepath))
    {
        std::cerr << "File does not exist: " << filepath << std::endl;
        return false;
    }
    std::ofstream output(filepath);
    if (!output.is_open())
    {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return false;
    }
    std::istringstream istream;

    return true;
}
