CC = g++
PREFIX = /usr/

compile:
	$(CC) -Wall -fexceptions -std=c++20 -fpermissive ./ponyfetch.cpp -o ponyfetch

install:
	chmod 755 ./ponyfetch
	cp ./ponyfetch $(PREFIX)bin
	rm ./ponyfetch
clean
	rm $(PREFIX)bin/ponyfetch
