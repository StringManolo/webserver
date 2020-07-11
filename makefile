CC = gcc
CCPP = g++
CFLAGS =

default: serv

serv: serv.cpp
	$(CCPP) $(CFLAGS) -o serv serv.cpp

clean:
	rm serv
	
