all: compile run
compile: main.cpp Events/Event.cpp Constants/Constants.cpp LRUCache/LRUCache.cpp FIFOCache/FIFOCache.cpp Events/FileRequestEvent.cpp RemoteServer/RemoteServer.cpp
	g++ -Wall -I/usr/local/includemain main.cpp Events/Event.cpp Constants/Constants.cpp LRUCache/LRUCache.cpp FIFOCache/FIFOCache.cpp Events/FileRequestEvent.cpp RemoteServer/RemoteServer.cpp FileSelection/FileSelection.cpp Events/FileArriveEvent.cpp Events/FileEnterQueueEvent.cpp Events/FileLeaveQueueEvent.cpp -c
	g++ -L/user/local/include -lgsl main.o RemoteServer.o LRUCache.o FIFOCache.o Event.o Constants.o FileRequestEvent.o FileSelection.o FileArriveEvent.o FileLeaveQueueEvent.o FileEnterQueueEvent.o
run: a.out	
	-./a.out > output.txt

clean: 
	rm main *.o *.out