all: compile run
compile: main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp Events/FileRequestEvent.cpp FileMap/FileMap.cpp RemoteServer/RemoteServer.cpp
	g++ -Wall -I/usr/local/includemain main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp Events/FileRequestEvent.cpp FileMap/FileMap.cpp RemoteServer/RemoteServer.cpp FileSelection/FileSelection.cpp Events/FileArriveEvent.cpp Events/FileEnterQueueEvent.cpp Events/FileLeaveQueueEvent.cpp -c
	g++ -L/user/local/include -lgsl main.o RemoteServer.o Cache.o Event.o Constants.o FileRequestEvent.o FileMap.o FileSelection.o FileArriveEvent.o FileLeaveQueueEvent.o FileEnterQueueEvent.o
run: a.out	
	-./a.out > output1.txt

clean: 
	rm main *.o *.out