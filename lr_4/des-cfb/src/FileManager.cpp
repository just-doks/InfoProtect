#include "FileManager.h"

#include <array>
#include <iomanip>

FileManager::FileManager(std::string dest) try
{
    m_dest.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    m_dest.open(dest, std::ios_base::out | std::ios_base::binary);
}
catch(std::ios_base::failure& exc)
{
    throw(FileManagerException("Error opening destination file"));
}

FileManager::FileManager(std::string src, std::string dest) try
{
    m_src.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    m_dest.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    
    m_src.open(src, std::ios_base::in | std::ios_base::binary);
    m_dest.open(dest, std::ios_base::out | std::ios_base::binary);
}
catch(std::ios_base::failure& exc)
{
    throw(FileManagerException("Error opening source and dest files"));
}

std::vector<char> FileManager::getData(size_t byteSize)
{
    try
    {
        if (!m_src.is_open())
            throw std::ios_base::failure("Source is not set");

        size_t size;
        if (byteSize > 0) 
        {
            size = byteSize;
        }
        else 
        {
            m_src.seekg(0, m_src.end);
            size = m_src.tellg();
            m_src.seekg(0, m_src.beg);
        }
        char* rowData = new char[size];
        m_src.read(rowData, size);
        return std::vector<char>(rowData, rowData + size);
    }
    catch(const std::ios_base::failure& e)
    {
        throw(FileManagerException("Error getting data"));
    }
}

void FileManager::removeZeros(std::vector<char>& data)
{
    char ch = data.back();
    while (ch == 0 && data.size() != 0)
    {
        data.pop_back();
        ch = data.back();
    }
}

void FileManager::setData(std::vector<char> data)
{
    try
    {
        m_dest.write(data.data(), data.size());
    }
    catch(const std::ios_base::failure& e)
    {
        throw(FileManagerException("Error setting data"));
    }
}

void FileManager::setData(std::string data)
{
    try
    {
        m_dest.write(data.data(), data.size());
    }
    catch(const std::ios_base::failure& e)
    {
        throw(FileManagerException("Error setting data"));
    }
}

void FileManager::setData(char* data, size_t size)
{
    try
    {
        m_dest.write(data, size);
    }
    catch(const std::ios_base::failure& e)
    {
        throw(FileManagerException("Error setting data"));
    }
}

/*
bool FileManager::saveKey(std::array<char, 8> key, std::string fileName)
{
    std::ofstream keyFile;
    keyFile.exceptions (std::ostream::failbit | std::ofstream::badbit);
    keyFile.open(fileName, std::ios_base::out);

    if (!keyFile.is_open())
        return false;

    printKey(keyFile, key.data(), key.size());

    keyFile.close();

    return true;
}

std::ostream& FileManager::printKey(std::ostream& out, char* key, size_t size, char separator)
{
    std::ios init(NULL);
    init.copyfmt(out);

    out << std::hex << std::uppercase; 
    out << std::setfill('0');
    for (int i = 0; i < size; ++i)
    {
        out << std::setw(2) << static_cast<unsigned int>
            (static_cast<unsigned char>(key[i]));
        if (separator != 0)
            out << separator;
    }
    out.copyfmt(init);
    return out;
}
*/