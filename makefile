CC = gcc
CCPP = g++
CFLAGS = -lpthread

default: serv

serv: serv.cpp
	$(CCPP) $(CFLAGS) -o serv serv.cpp

clean:
	rm serv
	rm logs.txt
	touch logs.txt

