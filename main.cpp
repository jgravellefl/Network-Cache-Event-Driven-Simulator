//main loop
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
#include "Cache/Cache.h"
#include "Events/Event.h"
#include "Constants/Constants.h"
#include "Events/FileRequestEvent.h"
#include "RemoteServer/RemoteServer.h"
#include "FileSelection/FileSelection.h"

using namespace std;

int main(){


    string line;
    string fileInput[9];
    std::ifstream myfile ("input.txt");
    string delimiter = "= ";
    int i = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            string parsedInput = line.substr(line.find(delimiter) +2, line.length());
            fileInput[i] = parsedInput;
            cout << parsedInput << endl;
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    double paretoMean = stod(fileInput[0]);
    double paretoShape = stod(fileInput[1]);
    double paretoScale = (paretoShape-1.0)/paretoShape * paretoMean;
    int cacheCapacity = stoi(fileInput[2]);
    int numFiles = stoi(fileInput[3]);
    int numRequests = stoi(fileInput[4]);
    int propagationTime = stoi(fileInput[5]);
    int initRequests = numRequests;
    int cacheBandwidth = stoi(fileInput[6]);
    int fifoBandwidth = stoi(fileInput[7]);
    int poissonMean = stoi(fileInput[8]);

    RemoteServer* remoteServer = new RemoteServer(propagationTime, numFiles, paretoShape, paretoScale); // Remote Server with propagation time = 400
    std::cout << "files" << endl;
    for (int i = 1; i < remoteServer->fileMap.size() + 1; i ++){
        std::cout << "file " << i << ": " << remoteServer->getFile(i) << endl;
    }

    FileSelector* fileSelector = new FileSelector(numFiles, paretoShape, paretoScale);

    Cache* cache = new Cache(cacheCapacity);	// cache capacity 2

    Constants* constants = new Constants(cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests, poissonMean, 0.0);

    priority_queue<Event*, std::vector<Event*>, LessThanByTime > pq;
    
    Event* event1 = new FileRequestEvent(0, 2, constants);

    pq.push(event1);
    Event* eventParams[2] = {NULL}; 
    int returnNum;

    std::cout << "Testing processing events framework:" << endl;
    while (!pq.empty()){
        Event* currEvent = pq.top();
        cout <<"in main" << endl;
        pq.pop();
        returnNum = currEvent->process(eventParams);
        cout << "return value:  " << returnNum << endl;
        delete currEvent;
        if (returnNum > 0){
            cout <<  "pushing: " << eventParams[0] << endl;
            pq.push(eventParams[0]);
        }
        if (returnNum > 1){
            cout <<  "pushing: " << eventParams[1] << endl;
            pq.push(eventParams[1]);
        }
    }
    cout << "final time: " << constants->totalTime << endl;
    float avgTime = constants->totalTime/initRequests;
    cout << "avg time: " << avgTime << endl;
    return 0;
}