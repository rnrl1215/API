cryptotest.out: cryptoAPITest.o cryptoapi.o
        g++ -o cryptotest.out cryptoAPITest.o cryptoapi.o  -lcryptopp -lpthread

cryptoAPITest.o: CryptoAPIExample.h CryptoAPITest.cpp
        g++ -c -o cryptoAPITest.o CryptoAPITest.cpp -lcryptopp -lpthread

cryptoapi.o: CryptoAPIExample.h CryptoAPIExample.cpp
        g++ -c -o cryptoapi.o CryptoAPIExample.cpp -lcryptopp -lpthread

clean:
        rm -f *.o
