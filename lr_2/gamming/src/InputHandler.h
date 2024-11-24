#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include <fstream>
#include <vector>

class InputHandler
{
    public:
        enum Status
        {
            NONE, // None
            S, // Only the Source was entered 
            SD, // Source and Destination were entered
            SK, // Source and Key were entered
            SDK, // Source, Destination and key were entered
            INVALID // Invalid input
        };
        enum Command
        {
            ENCRYPT,
            DECRYPT
        };
    private:

        std::string m_sourceName;
        std::string m_destinationName;
        std::string m_key;

        Status m_status;
        Command m_command;

        bool isKey(char* str);
        Status checkArgs(int argc, char* argv[]);
        bool isKeyCorrect(const std::string key);

        std::string getKeyPath(char* arg);
        std::string extractKey(const std::string keyPath);
        //std::vector<char> convertKey(const std::string keyString);

    public:
        InputHandler(): m_status(Status::NONE) {}

        bool process(int argc, char* argv[]);
        void printMessage();

        std::string getSource() const;
        std::string getDestination() const;
        std::string getKey() const;
        Command getCommand() const;

        ~InputHandler() {}
};

#endif // INPUTHANDLER_H