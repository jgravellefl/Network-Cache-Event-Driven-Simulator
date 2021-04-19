//main loop
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
#include "Cache/Cache.h"
#include "LRUCache/LRUCache.h"
#include "FIFOCache/FIFOCache.h"
#include "SecondChanceCache/SecondChanceCache.h"
#include "Events/Event.h"
#include "Constants/Constants.h"
#include "Events/FileRequestEvent.h"
#include "RemoteServer/RemoteServer.h"
#include "FileSelection/FileSelection.h"

using namespace std;


float* runEvents(Constants* constants, string name, int initRequests){

    float returns[2];
    priority_queue<Event*, std::vector<Event*>, LessThanByTime > pq;
    
    Event* event1 = new FileRequestEvent(0, 0,  constants->fileSelector->getFile(), constants);

    pq.push(event1);
    Event* eventParams[2] = {NULL}; 
    int returnNum;

    while (!pq.empty()){
        Event* currEvent = pq.top();
        pq.pop();
        returnNum = currEvent->process(eventParams);
        delete currEvent;
        if (returnNum > 0){
            pq.push(eventParams[0]);
        }
        if (returnNum > 1){
            pq.push(eventParams[1]);
        }
    }
    cout << "Running: " << name << endl;
    cout << "final time: " << constants->totalTime << endl;
    float avgTime = constants->totalTime/initRequests;
    cout << "avg time: " << avgTime << endl;
    float cacheHitRate = (1-float(constants->cacheMisses)/float(initRequests));
    cout << "cache Hit Rate: " << cacheHitRate << "%" << endl;
    cout << "cache misses: " << constants->cacheMisses << endl;
    cout << endl;
    cout << endl;
    returns[0] = avgTime;
    returns[1] = cacheHitRate;
    return returns;
}

int main(){

    string line;
    string fileInput[11];
    std::ifstream myfile ("input.txt");
    string delimiter = "= ";
    int i = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            string parsedInput = line.substr(line.find(delimiter) +2, line.length());
            fileInput[i] = parsedInput;
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
    string cacheType = fileInput[10];


    RemoteServer* remoteServer = new RemoteServer(propagationTime, numFiles, paretoShape, paretoScale, cacheCapacity); // Remote Server with propagation time = 400
    
    FileSelector* fileSelector = new FileSelector(numFiles, paretoShape, paretoScale);


    Cache* _Cache = NULL;
    float avg = 0;
    float hitRate = 0.0;
    if (cacheType.compare("ALL") == 0){
        for (int i = 0; i < 5; i++) {
            _Cache = new LRUCache(cacheCapacity);
            Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests, poissonMean, 0.0, 0);
            float* temp = runEvents(ourConstants, "LRU", numRequests);
            avg += temp[0];
            hitRate += temp[1];
            delete ourConstants;
            // _Cache->~Cache();
            delete _Cache;
        }
        cout << "average of LRU time's: " << avg/5 << endl;
        cout << "LRU average hit rate: " << hitRate/5 << "%" << endl;
        cout << endl;
        cout << endl;
        avg = 0;
        hitRate = 0.0;
        for (int i = 0; i < 5; i++) {
            _Cache = new FIFOCache(cacheCapacity);
            Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests, poissonMean, 0.0, 0);
            float* temp = runEvents(ourConstants, "FIFO", numRequests);
            avg += temp[0];
            hitRate += temp[1];
            delete ourConstants;
            // _Cache->~Cache();
            delete _Cache;
        }
        cout << "average of FIFO time's: " << avg/5 << endl;
        cout << "FIFO average hit rate: " << hitRate/5 << "%" << endl;
        cout << endl;
        cout << endl;
        avg = 0;
        hitRate = 0.0;
        for (int i = 0; i < 5; i++) {
        _Cache = new SecondChanceCache(cacheCapacity);
            Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests, poissonMean, 0.0, 0);
            float* temp = runEvents(ourConstants, "Second-Chance", numRequests);
            avg += temp[0];
            hitRate += temp[1];
            delete ourConstants;
            // _Cache->~Cache();
            delete _Cache;
        }
        cout << "average of SecondChance time's: " << avg/5 << endl;
        cout << "Second-Chance average hit rate: " << hitRate/5 << "%" << endl;
        cout << endl;
        cout << endl;        
    }
    else {
        string name = "";
        if (cacheType.compare("LRU") == 0){
            _Cache = new LRUCache(cacheCapacity);
            name = "LRU";
        }
        else if (cacheType.compare("FIFO") == 0){
            _Cache = new FIFOCache(cacheCapacity);
            name = "FIFO";
        }
        else if (cacheType.compare("SECOND-CHANCE") == 0){
            _Cache = new SecondChanceCache(cacheCapacity);
            name = "Second chance";
        }
        else{
            cout << "incorrect cache-type parameter" << endl;
        }
        Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests, poissonMean, 0.0, 0);
        cout << name << endl;
        runEvents(ourConstants, name, numRequests);
        delete ourConstants;
    }
    return 0;
}