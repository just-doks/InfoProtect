g++ -std=c++23 -I../lib/BigInt-master -I../lib/gmp-6.3.0 -o app main.cpp functions.cpp -L ../lib/gmp-6.3.0/.libs -lgmpxx -lgmp
#g++ -std=c++20 -o test main.cpp functions.cpp