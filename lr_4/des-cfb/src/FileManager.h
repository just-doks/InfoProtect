#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <exception>

class FileManager
{
    private:
        std::ifstream m_src;
        std::ofstream m_dest;
    
    public:
        FileManager(std::string dest);

        FileManager(std::string src, std::string dest);

        std::vector<char> getData(size_t byteSize = 0);

        void removeZeros(std::vector<char>& data);

        void setData(std::vector<char> data);
        void setData(std::string data);
        void setData(char* data, size_t size);


        ~FileManager()
        {
            if (m_src.is_open())
                m_src.close();
            if (m_dest.is_open())
                m_dest.close();
        }
};

class FileManagerException : public std::exception
{
    private:
        std::string m_error;
    public:
        FileManagerException(std::string msg) : m_error(msg) {}
        const char* what() const noexcept { return m_error.c_str(); }
};

#endif // FILEMANAGER_H