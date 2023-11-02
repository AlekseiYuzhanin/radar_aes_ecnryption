build: main

main: main.o aes_decryption.o aes_encryption.o
	g++ main.o aes_decryption.o aes_encryption.o -o main -lssl -lcrypto

main.o: main.cpp
	g++ -c main.cpp

aes_decryption.o: aes_decryption.cpp aes_decryption.h
	g++ -c aes_decryption.cpp

aes_encryption.o: aes_encryption.cpp aes_encryption.h
	g++ -c aes_encryption.cpp

start: main
	./main

clean:
	rm -rf *.o main