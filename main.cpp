//main loop
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include "LRUCache/LRUCache.h"
#include "FIFOCache/FIFOCache.h"
#include "Events/Event.h"
#include "Constants/Constants.h"
#include "Events/FileRequestEvent.h"
#include "RemoteServer/RemoteServer.h"
#include "FileSelection/FileSelection.h"

using namespace std;

int main(){

    double paretoMean = 10;
    double paretoShape = 2.5;
    double paretoScale = (paretoShape-1.0)/paretoShape * paretoMean;
    int cacheCapacity = 20;
    int numFiles = 40;
    int numRequests = 100;
    int propagationTime = 4;
    int initRequests = numRequests;
    int cacheBandwidth = 5;
    int fifoBandwidth = 2;
    int poissonMean = 5;

    RemoteServer* remoteServer = new RemoteServer(propagationTime, numFiles, paretoShape, paretoScale); // Remote Server with propagation time = 400
    std::cout << "files" << endl;
    for (int i = 1; i < remoteServer->fileMap.size() + 1; i ++){
        std::cout << "file " << i << ": " << remoteServer->getFile(i) << endl;
    }

    FileSelector* fileSelector = new FileSelector(numFiles, paretoShape, paretoScale);

    LRUCache* LRU_Cache = new LRUCache(cacheCapacity);	// cache capacity 2

    // TESTING
    FIFOCache* FIFO_Cache = new FIFOCache(3);  // cache capacity 3

    // Add FIFO
    Constants* constants = new Constants(LRU_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests, poissonMean, 0.0);

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

    // TESTING
    FIFO_Cache->insertFile(1, 5);
    FIFO_Cache->insertFile(2, 6);
    FIFO_Cache->insertFile(5, 2);
    FIFO_Cache->insertFile(1, 3);
    cout << "File 1: " << FIFO_Cache->getFile(1) << endl;
    FIFO_Cache->insertFile(3, 7);
    cout << "File 1: " << FIFO_Cache->getFile(1) << endl;
    cout << "File 5: " << FIFO_Cache->getFile(5) << endl;
    return 0;
}