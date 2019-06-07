# c compiler
CC = gcc
# c++ compiler
CXX = g++
PROG = main.exe 
CXXFLAGS = -O3 -g 

#LIBS = -L/usr/local/Cellar/boost/1.67.0_1/lib -lboost_filesystem
LIBS = -L/opt/ohpc/pub/libs/gnu/openmpi/boost/1.66.0/lib -lboost_filesystem

#INCLUDES = -I/usr/local/Cellar/boost/1.67.0_1/include
INCLUDES = -I/opt/ohpc/pub/libs/gnu/openmpi/boost/1.66.0/include

OBJ =  main.o

all: build_all 

build_all: $(PROG)

clobber:
	rm -f *.o

clean:clobber
	rm -f ${PROG}

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJ) $(LIBS)
	echo "Build completed"

%.o : %.c
	$(CC) $(CXXFLAGS) ${INCLUDES} -c -o $@ $<

%.o : %.cpp 
	$(CXX) $(CXXFLAGS) ${INCLUDES} -c -o $@ $<

