CC = g++
CFLAGS = -pthread -g -std=c++11
INCLUDE = ./src
OBJECT = pa1.o system.o thread.o cpu.o
LIBS = libs/check.o

part1.out: clean configToP1 $(OBJECT) 
	$(CC) $(CFLAGS) -o part1.out $(OBJECT) $(LIBS)

part2.out: clean configToP2 $(OBJECT)
	$(CC) $(CFLAGS) -o part2.out $(OBJECT) $(LIBS)

part3_rr.out: clean configToRR $(OBJECT)
	$(CC) $(CFLAGS) -o part3_rr.out $(OBJECT) $(LIBS)

part3_fifo.out: clean configToFIFO $(OBJECT)
	$(CC) $(CFLAGS) -o part3_fifo.out $(OBJECT) $(LIBS)

pa1.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c pa1.cpp

system.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ./src/system.cpp

thread.o:
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ./src/thread.cpp

cpu.o: 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ./src/cpu.cpp


configToP1:
	sed -i "/#define PART/c\#define PART 1" ./src/config.h

configToP2:
	sed -i "/#define PART/c\#define PART 2" ./src/config.h

configToFIFO:
	sed -i "/#define PART/c\#define PART 3" ./src/config.h
	sed -i "/#define SCHEDULING/c\#define SCHEDULING SCHED_FIFO" ./src/config.h

configToRR:
	sed -i "/#define PART/c\#define PART 3" ./src/config.h
	sed -i "/#define SCHEDULING/c\#define SCHEDULING SCHED_RR" ./src/config.h
	

clean:
	rm -f *.o
