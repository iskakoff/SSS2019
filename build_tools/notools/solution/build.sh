c++ -I/opt/ohpc/pub/libs/gnu/openmpi/boost/1.66.0/include -c main.cpp -o main.o
c++ -L/opt/ohpc/pub/libs/gnu/openmpi/boost/1.66.0/lib -lboost_filesystem main.o -o main.exe
