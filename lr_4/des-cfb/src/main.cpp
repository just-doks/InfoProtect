#include "DES.h"
#include "InputHandler.h"
#include "FileManager.h"
#include "KeyHandling.h"

#include <iostream>

int main(int argc, char* argv[])
{
    namespace KH = KeyHandling;

    InputHandler ih;
    if (!ih.process(argc, argv))
    {
        ih.printErrorMessage();
        return 0;
    }
    
    DES des(DES::CFB);

    switch(ih.getCommand())
    {
        case InputHandler::Command::KEYGEN:
        {
            try {
                KeyPair pair = des.getKeyPair();
                std::cout << ih.getKeyPath() << '\n';
                KH::exportKey(ih.getKeyPath(), pair);
                /*
                FileManager fm(ih.getDestination());
                des.genKey();
                fm.setData(des.getKeyString());
                */
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
                    KeyPair pair = des.getKeyPair();
                    KH::exportKey(ih.getKeyPath(), pair);
                    //FileManager fmK("key");
                    //fmK.setData(des.getKeyString());

                    FileManager fmD(ih.getSource(), ih.getDestination());
                    auto data = des.encrypt_cfb(fmD.getData());
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
                    KeyPair pair = KH::importKey(ih.getKeyPath());
                    des.setKeyPair(pair);
                    //std::cout << "key: " << KH::__private__::getKeyString(pair.get_key()) << '\n';
                    //std::cout << "iv: " << KH::__private__::getKeyString(pair.get_iv()) << '\n';

                    FileManager fmD(ih.getSource(), ih.getDestination());
                    auto data = des.encrypt_cfb(fmD.getData());
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
                KeyPair pair = KH::importKey(ih.getKeyPath());
                des.setKeyPair(pair);

                FileManager fmD(ih.getSource(), ih.getDestination());
                auto data = des.decrypt_cfb(fmD.getData());
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