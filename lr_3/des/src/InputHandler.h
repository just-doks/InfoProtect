#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include <fstream>
#include <array>

class InputHandler
{
    public:
        enum class Status
        {
            NONE, // None
            S, // Only a Source provided 
            SD, // Source and Destination provided
            KG, // Keygen requested
            KGD, // Keygen requested with Destination file
            INVALID // Invalid input
        };
        enum class Command
        {
            HELP,
            KEYGEN,
            ENCRYPT,
            DECRYPT,
            NONE
        };
    private:
        // Members
        std::string         m_sourceName;
        std::string         m_destinationName;
        std::array<char, 8> m_key;
        Command             m_command;
        bool                m_keyFlag;

        // Private methods
        auto isArgKey(char* str) -> bool;
        auto checkArgs(int argc, char* argv[]) -> Status;
        auto getKeyPath(char* arg) -> std::string;
        auto extractKey(const std::string keyPath) -> std::string;
        auto convertKey(const std::string keyString) -> std::array<char, 8>;


    public:
        InputHandler(): 
            m_command(Command::NONE),
            m_keyFlag(false) {}

        bool process(int argc, char* argv[]);
        void printErrorMessage();

        // Getters
        auto getSource() const -> std::string;
        auto getDestination() const -> std::string;
        auto getCommand() const -> Command;
        auto getKey() -> std::array<char, 8>;

        // Key Managment
        bool isKey();

        ~InputHandler() {}
};

#endif // INPUTHANDLER_H