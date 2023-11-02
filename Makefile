build:
	g++ main.cpp aes_decryption.cpp aes_encryption.cpp -o main -lssl -lcrypto
start:
	./main
clean:
	rm -rf *.o main