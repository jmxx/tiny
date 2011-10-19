CXX := g++
program_NAME := tiny.o
program_SRCS := $(wildcard src/*.cpp)
program_OBJS := ${program_SRCS:.cpp=.o}

$(program_NAME) : $(program_OBJS)
	$(CXX) main.cpp $(program_OBJS) -o $(program_NAME) #$(CXXFLAGS) $(LDFLAGS)

all:
	g++ main.cpp src/Tiny.cpp src/Socket.cpp src/SocketServer.cpp src/HttpRequest.cpp src/Utils.cpp -o main.o

test:
	g++ test.cpp src/Utils.cpp -o test.o
