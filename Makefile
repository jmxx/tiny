all:
	g++ main.cpp src/Mesero.cpp src/Socket.cpp src/SocketServer.cpp src/HttpRequest.cpp src/Utils.cpp -o main.o

test:
	g++ test.cpp src/Utils.cpp -o test.o
