#include <iostream>
#include <fstream>
#include <string>

#include "InputHandler.h"
#include "FileManager.h"
#include "RSA.h"
#include "MPZ.h"
#include "KeyHandling.h"

int main (int argc, char* argv[])
{
    namespace KH = KeyHandling;

    InputHandler ih;
    if (!ih.process(argc, argv))
    {
        ih.printErrorMessage();
        return 0;
    }

    RSA rsa;

    switch(ih.getCommand())
    {
        case InputHandler::Command::KEYGEN:
        {
            try {
                if (!rsa.genKeys(1024, 65537))
                {
                    std::cerr << "Error generating keys\n";
                    break;
                }
                KH::exportKey(ih.getDestination(), rsa.priv());
                KH::exportKey(ih.getDestination() + ".pub", rsa.pub());
            }
            catch (std::exception& exc)
            {
                std::cerr << "Exception occured (" << exc.what() << ")\n";
            }
            break;
        }
        case InputHandler::Command::ENCRYPT:
        {
            if (!ih.isKeySet())
            {
                try
                {
                    rsa.genKeys(1024, 65537);
                    KH::exportKey(ih.getKeyPath(), rsa.priv());
                    KH::exportKey(ih.getKeyPath() + ".pub", rsa.pub());

                    FileManager fmD(ih.getSource(), ih.getDestination());
                    auto data = rsa.encrypt(fmD.getData(), rsa.pub());
                    fmD.setData(data);
                }
                catch (std::exception& exc)
                {
                    std::cerr << "Exception occured (" << exc.what() << ")\n";
                }
            } else
            {
                try
                {
                    const auto pubKey = KH::importKey(ih.getKeyPath());

                    FileManager fmD(ih.getSource(), ih.getDestination());
                    auto data = rsa.encrypt(fmD.getData(), pubKey);
                    fmD.setData(data);
                }
                catch (std::exception& exc)
                {
                    std::cerr << "Exception occured (" << exc.what() << ")\n";
                }
            }
            break;
        }
        case InputHandler::Command::DECRYPT:
        {    
            try
            {
                auto privKey = KH::importKey(ih.getKeyPath());

                FileManager fmD(ih.getSource(), ih.getDestination());
                auto data = rsa.decrypt(fmD.getData(), privKey);
                fmD.setData(data);
            }
            catch (std::exception& exc)
            {
                std::cerr << "Exception occured (" << exc.what() << ")\n";
            }
            break;
        }
        default:
            break;
    }
    
    return 0;
}