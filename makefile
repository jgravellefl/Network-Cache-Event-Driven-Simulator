all: compile run
compile: main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp Events/FileRequestEvent.cpp FileMap/FileMap.cpp RemoteServer/RemoteServer.cpp
	g++ -Wall -I/usr/local/includemain main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp Events/FileRequestEvent.cpp FileMap/FileMap.cpp RemoteServer/RemoteServer.cpp FileSelection/FileSelection.cpp -c
	g++ -L/user/local/include -lgsl main.o RemoteServer.o Cache.o Event.o Constants.o FileRequestEvent.o FileMap.o FileSelection.o
run: a.out	
	-./a.out
clean: main
	rm main