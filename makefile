CC = gcc
CCPP = g++
CFLAGS =

default:

prueba: serv

serv: read_config.o test_config.o
	$(CCPP) -o serv test_config.o read_config.o

test_config.o: test_config.cpp
	$(CCPP) -c test_config.cpp
	
read_config.o: read_config.c
	$(CCPP) -c read_config.c

clean:
	rm *.o serv
	
