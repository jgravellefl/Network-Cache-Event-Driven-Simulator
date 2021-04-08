//main loop
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include "Cache/Cache.h"
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