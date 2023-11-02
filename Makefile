build: main

main: main.o aes_decryption.o aes_encryption.o file_working.o random_key.o
	g++ main.o aes_decryption.o aes_encryption.o file_working.o random_key.o -o main -lssl -lcrypto

main.o: main.cpp
	g++ -c main.cpp

aes_decryption.o: aes_decryption.cpp aes_decryption.h
	g++ -c aes_decryption.cpp

aes_encryption.o: aes_encryption.cpp aes_encryption.h
	g++ -c aes_encryption.cpp

file_working.o: file_working.cpp file_working.h
	g++ -c file_working.cpp

random_key.o: random_key.cpp random_key.h
	g++ -c random_key.cpp	

clean:
	rm -rf *.o main

start: main
	./main