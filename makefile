CC = gcc
CCPP = g++
CFLAGS = -Wwrite-strings

default:

prueba: serv

serv: read_config.o test_config.o
	$(CCPP) $(CFLAGS) -o serv test_config.o read_config.o

test_config.o: test_config.cpp
	$(CCPP) $(CFLAGS) -c test_config.cpp
	
read_config.o: read_config.c
	$(CCPP) $(CFLAGS) -c read_config.c

clean:
	rm *.o serv
	
