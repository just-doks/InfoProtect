#ifndef DES_EXCEPTION_H
#define DES_EXCEPTION_H

#include <exception>
#include <string>

class DESException : std::exception
{
    private:
        std::string m_error;
    public:
        DESException(std::string error): 
            m_error(error) {}
        const char* what() const noexcept 
        {
            return m_error.c_str();
        }
}; 

#endif // DES_EXCEPTION_H