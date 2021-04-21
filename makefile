all: compile run
compile: main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp LRUCache/LRUCache.cpp FIFOCache/FIFOCache.cpp SecondChanceCache/SecondChanceCache.cpp Events/FileRequestEvent.cpp RemoteServer/RemoteServer.cpp
	g++ -Wall -I/usr/local/include main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp LRUCache/LRUCache.cpp FIFOCache/FIFOCache.cpp SecondChanceCache/SecondChanceCache.cpp Events/FileRequestEvent.cpp RemoteServer/RemoteServer.cpp FileSelection/FileSelection.cpp Events/FileArriveEvent.cpp Events/FileEnterQueueEvent.cpp Events/FileLeaveQueueEvent.cpp -c
	g++ -lgsl main.o RemoteServer.o Cache.o LRUCache.o FIFOCache.o SecondChanceCache.o Event.o Constants.o FileRequestEvent.o FileSelection.o FileArriveEvent.o FileLeaveQueueEvent.o FileEnterQueueEvent.o
run: a.out	
	-./a.out > output.txt

clean: 
	rm *.o *.out
