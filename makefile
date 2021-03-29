all: compile run
compile: main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp Events/FileRequestEvent.cpp FileMap/FileMap.cpp RemoteServer/RemoteServer.cpp
	g++ -o main main.cpp Events/Event.cpp Constants/Constants.cpp Cache/Cache.cpp Events/FileRequestEvent.cpp FileMap/FileMap.cpp RemoteServer/RemoteServer.cpp
run: main	
	-./main
clean: main
	rm main