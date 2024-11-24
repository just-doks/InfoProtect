g++ -std=c++23 -I../lib/gmp-6.3.0 -o rsa main.cpp MPZ.cpp RSA.cpp RSA_Key.cpp KeyHandling.cpp \
 FileManager.cpp InputHandler.cpp \
 -L ../lib/gmp-6.3.0/.libs -lgmpxx -lgmp