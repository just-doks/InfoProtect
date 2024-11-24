#include "FileManager.h"

#include <array>
#include <iostream>
#include <iomanip>

FileManager::FileManager(std::string dest) try
{
    m_dest.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    m_dest.open(dest, std::ios_base::out | std::ios_base::binary);
}
catch(const std::ios_base::failure& e)
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
catch(const std::ios_base::failure& e)
{
    throw(FileManagerException("Error opening source and dest files"));
}

FileManager::~FileManager()
{
    if (m_src.is_open())
        m_src.close();
    if (m_dest.is_open())
        m_dest.close();
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