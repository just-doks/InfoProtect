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
        std::string         m_keyPathName;
        Command             m_command;
        bool                m_keyFlag;

        // Private methods
        auto isArgKey(char* str) -> bool;
        auto checkArgs(int argc, char* argv[]) -> Status;
        auto getKeyPath(char* arg) -> std::string;


    public:
        InputHandler(): 
            m_command(Command::NONE),
            m_keyFlag(false) {}

        bool process(int argc, char* argv[]);
        void printErrorMessage();

        // Getters
        auto getSource() const -> std::string;
        auto getDestination() const -> std::string;
        auto getKeyPath() const -> std::string;
        auto getCommand() const -> Command;

        // Key Managment
        bool isKeySet();

        ~InputHandler() {}
};

#endif // INPUTHANDLER_H