#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>

class FileManager
{
    private:
        std::ifstream m_src;
        std::ofstream m_dest;
    
    public:
        FileManager(std::string dest);
        FileManager(std::string src, std::string dest);

        std::vector<char> getData(size_t byteSize = 0);

        void setData(std::vector<char> data);
        void setData(std::string data);
        void setData(char* data, size_t size);

        ~FileManager();
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