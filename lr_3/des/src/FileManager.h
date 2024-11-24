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
        FileManager(std::string dest)
        {
            m_dest.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            m_dest.open(dest, std::ios_base::out | std::ios_base::binary);
        }

        FileManager(std::string src, std::string dest)
        {
            m_src.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            m_dest.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            
            m_src.open(src, std::ios_base::in | std::ios_base::binary);
            m_dest.open(dest, std::ios_base::out | std::ios_base::binary);
        }

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

#endif // FILEMANAGER_H