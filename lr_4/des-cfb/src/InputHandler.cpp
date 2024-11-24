#include "InputHandler.h"

#include <cstring>
#include <iostream>
#include <limits> // std::numeric_limits<>::max()
#include <iomanip> // std::setfill, std::setw(2), std::uppercase

bool InputHandler::isArgKey(char* str)
{
    char key[] = "key=";
    if (strncmp(str, key, sizeof(key) - 1) == 0)
        return true;
    else
        return false;
}

InputHandler::Status InputHandler::checkArgs(int argc, char* argv[])
{
    if (argc == 1)
        return Status::NONE;
    if (argc > 5)
        return Status::INVALID;

    if (strcmp(argv[1], "help") == 0)
        m_command = Command::HELP;
    if (strcmp(argv[1], "keygen") == 0)
        m_command = Command::KEYGEN;
    else if (strcmp(argv[1], "encrypt") == 0)
        m_command = Command::ENCRYPT; 
    else if (strcmp(argv[1], "decrypt") == 0)
        m_command = Command::DECRYPT;
    else
        return Status::INVALID;
    
    Status result {Status::NONE};

    switch(m_command)
    {
        case Command::KEYGEN:
        {
            if (argc == 2)
                result = Status::KG;
            else if (argc == 3)
                result = Status::KGD;
            else
                result = Status::INVALID;
            break;
        }
        case Command::ENCRYPT:
        {
            switch(argc)
            {
                case 3:
                    result = Status::S;
                    break;
                case 4:
                    if (isArgKey(argv[argc - 1]))
                    {
                        result = Status::S;
                        m_keyFlag = true;
                    } else
                        result = Status::SD;
                    break;
                case 5:
                    if (isArgKey(argv[argc - 1]))
                    {
                        result = Status::SD;
                        m_keyFlag = true;
                    } else
                        result = Status::INVALID;
                    break;
                default:
                    result = Status::INVALID;
                    break;
            }
            break;
        }
        case Command::DECRYPT:
        {
            if (argc < 4 || !isArgKey(argv[argc - 1]))
            {
                result = Status::INVALID;
                break;
            }
            m_keyFlag = true;
            switch(argc)
            {
                case 4:
                    result = Status::S;
                    break;
                case 5:
                    result = Status::SD;
                    break;
                default:
                    result = Status::INVALID;
                    break;
            }
            break;
        }
        default:
            break;
    }
    
    return result;
}

std::string InputHandler::getKeyPath(char* arg)
{
    std::string path;
    for (int i = 4; i < strlen(arg); ++i)
    {
        path += *(arg + i);
    }
    return path;
}

/*
std::string InputHandler::extractKey(const std::string keyPath)
{
    std::ifstream keyFile;
    std::string keyString;
    keyFile.open(keyPath, std::ios_base::in);
    if (!keyFile.is_open())
    {
        return keyString;
    }
    char ch = keyFile.get();
    while (ch != EOF)
    {
        if (    (ch >= 'A' && ch <= 'F') 
             || (ch >= '0' && ch <= '9')
             || (ch >= 'a' && ch <= 'f'))
        {
            keyString.push_back(ch);
            ch = keyFile.get();
        } else if (ch == '\n') 
        {
            ch = keyFile.get();
        } else 
        {
            keyString.clear();
            break;
        }
    }

    keyFile.close();

    return keyString;
}


std::array<char, 8> InputHandler::convertKey(const std::string keyString)
{
    if (keyString.size() != 16)
        return std::array<char, 8>();

    std::array<char, 8> key{};
    unsigned char a;
    int ind = 0;
    int shift = 4;
    for (const auto ch : keyString)
    {
        a = 0;

        if (ch >= 'A' && ch <= 'F')
        {
            a = (ch - 'A') + 10;
        } else 
        if (ch >= 'a' && ch <= 'f')
        {
            a = (ch - 'a') + 10;
        } else
        if (ch >= '0' && ch <= '9')
        {
            a = ch - '0';
        }
        key[ind] |= (a << shift);
        if (shift == 0)
        {
            ++ind;
            shift = 4;            
        } else
            shift = 0;
    }
    return key;
}
*/

bool InputHandler::process(int argc, char* argv[])
{
    using std::string, std::cout, std::cin;
    
    Status result = checkArgs(argc, argv);
    if (result == Status::INVALID || result == Status::NONE)
    {
        return false;
    }

    switch(m_command)
    {
        case Command::KEYGEN:
        {
            switch(result)
            {
                case Status::KG:
                    m_keyPathName = "key";
                    break;
                case Status::KGD:
                    m_destinationName = argv[2];
                    break;
                default:
                    break;
            }
            return true;
        }
        case Command::ENCRYPT:
        {
            m_sourceName = argv[2];
            switch(result)
            {
                case Status::SD:
                    m_destinationName = argv[3];
                    break;
                case Status::S:
                    m_destinationName = "encrypted";
                    break;
                default:
                    break;
            }
            break;
        }
        case Command::DECRYPT:
        {
            m_sourceName = argv[2];
            switch(result)
            {
                case Status::S:
                    m_destinationName = "decrypted";
                    break;
                case Status::SD:
                    m_destinationName = argv[3];
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    if (m_keyFlag)
    {
        m_keyPathName = getKeyPath(argv[argc - 1]);
        /*
        string keyFile = getKeyPath(argv[argc - 1]);
        string keyString = extractKey(keyFile);
        m_key = convertKey(keyString);
        if (m_key.size() == 0)
            return false;
        */
    }
    //cout << "argc = " << argc << '\n';
    //cout << "Source = " << m_sourceName << '\n';
    //cout << "Destination = " << m_destinationName << '\n';
    //cout << "Key: " << m_key << '\n';

    return true;
}

void InputHandler::printErrorMessage()
{
    std::cout << "Syntax:\n";
    char keygen[] = "./des-cfb keygen [<key_file_path>]\n" \
            "\tIf key file path is not set,\n" \
            "\tfile named \"key\" will be created at the same directory.\n";
    
    char encrypt[] = "./des-cfb encrypt <source_file_path> [<destination_file_path>] \
        [key=\"<key_file_path>\"]\n" \
            "\tIf key option is not set, a key file will be generated automatically.\n" \
            "\tIf destination file name is not set,\n" \
            "\tfile named \"encrypted\" will be created at the same directory.\n";

    char decrypt[] = "./des-cfb decrypt <encrypted_file_path> [<decrypted_file_path>] \
        key=<key_file_path>\n" \
            "\tIf decrypted file name is not set,\n" \
            "\tfile named \"decrypted\" will be created at the same directory.\n";

    char help[] = "./des-cfb help\n";

    switch(m_command)
    {
        case Command::KEYGEN:
            std::cout << keygen << '\n';
            break;
        case Command::ENCRYPT:
            std::cout << encrypt << '\n';
            break;
        case Command::DECRYPT:
            std::cout << decrypt << '\n';
            break;
        default:
            std::cout << keygen << '\n' << encrypt << '\n' << decrypt << '\n'
                  << help << '\n';
            break;
    }
}


std::string InputHandler::getSource() const
{
    return m_sourceName;
}

std::string InputHandler::getDestination() const
{
    return m_destinationName;
}

std::string InputHandler::getKeyPath() const
{
    return m_keyPathName;
}

InputHandler::Command InputHandler::getCommand() const
{
    return m_command;
}

bool InputHandler::isKeySet()
{
    return m_keyFlag;
}