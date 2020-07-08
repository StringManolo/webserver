CC = gcc
CCPP = g++
CFLAGS =

default:

prueba: serv

serv: read_config.o test_config.o
	$(CCPP) $(CFLAGS) -o serv test_config.o read_config.o

test_config.o: test_config.cpp
	$(CCPP) $(CFLAGS) -c test_config.cpp
	
read_config.o: read_config.cpp
	$(CCPP) $(CFLAGS) -c read_config.cpp

clean:
	rm *.o serv
	
