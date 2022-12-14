OBJS	= source/main.o source/othellobord.o
SOURCE	= source/main.cc source/othellobord.cc
HEADER	= include/main.h include/othellobord.h
OUT	= build/othello.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 
	
all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

source/main.o: source/main.cc
	$(CC) $(FLAGS) source/main.cc -std=c++11

source/othellobord.o: source/othellobord.cc
	$(CC) $(FLAGS) source/othellobord.cc -std=c++11


clean:
	rm -f $(OBJS) $(OUT)