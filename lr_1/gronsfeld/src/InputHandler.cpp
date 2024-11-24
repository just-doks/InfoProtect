#include "InputHandler.h"

#include <cstring>
#include <iostream>

bool InputHandler::isKey(char* str)
{
    if (   (*(str) == '-')
        && (*(str + 1) == 'k')
        && (*(str + 2) == '='))
    {
        return true;
    } else
        return false;
}

InputHandler::Status InputHandler::checkArgs(int argc, char* argv[])
{
    if (argc < 3 || argc > 5)
        return Status::INVALID;
    
    if (strcmp(argv[1], "encrypt") == 0)
        m_command = Command::ENCRYPT; 
    else if (strcmp(argv[1], "decrypt") == 0)
        m_command = Command::DECRYPT;
    else
        return Status::INVALID;
    
    Status result {Status::NONE};

    for (int i = 2; i < argc - 1; ++i)
    {
        if (isKey(argv[i]))
        {
            result = Status::INVALID;
            break;
        }
    }
    if (result != INVALID && isKey(argv[argc - 1]))
    {
        if (argc == 4)
            result = Status::SK;
        if (argc == 5)
            result = Status::SDK;
    }
    return result;
}

std::string InputHandler::getKeyPath(char* arg)
{
    std::string path;
    for (int i = 3; i < strlen(arg); ++i)
    {
        path += *(arg + i);
    }
    return path;
}

std::vector<unsigned int> InputHandler::extractKey(const std::string keyPath)
{
    std::ifstream keyFile;
    std::vector<unsigned int> key;
    keyFile.open(keyPath, std::ios_base::in);
    if (!keyFile.is_open())
    {
        std::cout << "Invalid key path\n";
        return key;
    }
    char ch = keyFile.get();
    while (ch != EOF)
    {
        if (ch >= '0' && ch <= '9')
        {
            key.push_back(ch - '0');
            ch = keyFile.get();
        } else if (ch == '\n' || ch == ' ') 
        {
            ch = keyFile.get();
        } else 
        {
            key.clear();
            break;
        }
    }

    keyFile.close();

    return key;
}

std::vector<unsigned int> InputHandler::convertKey(const std::string keyString)
{
    std::vector<unsigned int> key;
    for (const auto ch : keyString)
    {
        if (!(ch >= '0') && !(ch <= '9'))
            return std::vector<unsigned int>();
        key.push_back(ch - '0');
    }
    return key;
}

bool InputHandler::process(int argc, char* argv[])
{
    using std::string, std::cout, std::cin;
    
    Status result = checkArgs(argc, argv);
    if (result == Status::INVALID)
    {
        //cout << "Invalid arguments.\n";
        //cout << syntax;
        return false;
    }


    if ((result == Status::SK) || (result == Status::SDK))
    {
        string keyFile = getKeyPath(argv[argc - 1]);
        m_key = extractKey(keyFile);
    }
    else
    {
        cout << "Enter key: ";
        std::string keyString;
        cin >> keyString;
        m_key = convertKey(keyString);
    }

    if (m_key.size() == 0)
    {
        return false;
    }

    m_sourceName = argv[2];

    if (result == Status::SD || result == Status::SDK)
        m_destinationName = argv[3];
    else
    {
        switch(m_command)
        {
            case Command::ENCRYPT: 
                m_destinationName = "encrypted_" + m_sourceName;
                break;
            case Command::DECRYPT:
                m_destinationName = "decrypted_" + m_sourceName;
                break;
        }
    }
    
    cout << "argc = " << argc << '\n';
    cout << "Source = " << m_sourceName << '\n';
    cout << "Destination = " << m_destinationName << '\n';
    cout << "Key: ";
    for (auto el : m_key)
        cout << el;
    cout << '\n';

    return true;
}

void InputHandler::printMessage()
{
    char syntax[] = "Syntax:\n" \
        "./gronsfeld encrypt|decrypt <source_file_path> [<destination_file_path>] [-k=\"<key_file_path>\"]\n";
    std::cout << syntax;
}


std::string InputHandler::getSource() const
{
    return m_sourceName;
}

std::string InputHandler::getDestination() const
{
    return m_destinationName;
}

std::vector<unsigned int> InputHandler::getKey() const
{
    return m_key;
}

InputHandler::Command InputHandler::getCommand() const
{
    return m_command;
}