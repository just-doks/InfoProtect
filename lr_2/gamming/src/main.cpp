#include <iostream>

#include "InputHandler.h"
#include "Gamming.h"

int main (int argc, char* argv[])
{
    InputHandler ih;
    if (!ih.process(argc, argv))
    {
        ih.printMessage();
        return 0;
    }

    std::ifstream source;
    std::ofstream destination;
    
    if (ih.getCommand() == InputHandler::Command::ENCRYPT)
    {
        source.open(ih.getSource(), std::ios_base::in);
        destination.open(ih.getDestination(), std::ios_base::out | std::ios_base::binary);
    }
    else if (ih.getCommand() == InputHandler::Command::DECRYPT)
    {
        source.open(ih.getSource(), std::ios_base::in | std::ios_base::binary);
        destination.open(ih.getDestination(), std::ios_base::out);
    }
    
    if (!source.is_open())
    {
        std::cout << "Error opening source\n";
        return 0;
    }

    if (!destination.is_open())
    {
        std::cout << "Error creating dest\n";
        return 0;
    }
    

    source.seekg(0, source.end);
    size_t sSize = source.tellg();
    source.seekg(0, source.beg);

    char* buff = new char[sSize + 1];
    
    source.read(buff, sSize);
    source.close();
    buff[sSize] = '\0';
    //std::cout << buff << '\n';

    Gamming gm(ih.getKey());
    if (ih.getCommand() == InputHandler::Command::ENCRYPT)
        gm.encrypt(buff, sSize);
    else if (ih.getCommand() == InputHandler::Command::DECRYPT)
        gm.decrypt(buff, sSize);

    
    //std::cout << buff << '\n';
    destination.write(buff, sSize);
    destination.close();
    
    delete[] buff;

    return 0;
}