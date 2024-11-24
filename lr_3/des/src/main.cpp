#include "DES.h"
#include "InputHandler.h"
#include "FileManager.h"

#include <iostream>

int main(int argc, char* argv[])
{
    InputHandler ih;
    if (!ih.process(argc, argv))
    {
        ih.printErrorMessage();
        return 0;
    }
    
    DES des(DES::ECB);

    switch(ih.getCommand())
    {
        case InputHandler::Command::KEYGEN:
        {
            try {
                FileManager fm(ih.getDestination());
                des.genKey();
                fm.setData(des.getKeyString());
            }
            catch(std::ios_base::failure& exc)
            {
                std::cerr << "Exception occured (" << exc.what() << ")\n";
            }
            break;
        }
        case InputHandler::Command::ENCRYPT:
        {
            if (!ih.isKey())
            {
                try
                {
                    des.genKey();
                    FileManager fmK("key");
                    fmK.setData(des.getKeyString());

                    FileManager fmD(ih.getSource(), ih.getDestination());
                    auto data = des.encrypt(fmD.getData(), des.getKey());
                    fmD.setData(data);
                }
                catch(std::ios_base::failure& exc)
                {
                    std::cerr << "Exception occured (" << exc.what() << ")\n";
                }
                catch (std::exception& exc)
                {
                    std::cerr << "Exception occured (" << exc.what() << ")\n";
                }
            } else
            {
                try
                {
                    FileManager fmD(ih.getSource(), ih.getDestination());
                    auto data = des.encrypt(fmD.getData(), ih.getKey());
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
                FileManager fmD(ih.getSource(), ih.getDestination());
                auto data = des.decrypt(fmD.getData(), ih.getKey());
                fmD.removeZeros(data);
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