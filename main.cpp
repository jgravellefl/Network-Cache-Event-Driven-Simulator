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
    //cout << "Running: " << name << endl;
    //cout << "final time: " << constants->totalTime << endl;
    float avgTime = constants->totalTime/initRequests;
    //cout << "avg time: " << avgTime << endl;
    float cacheHitRate = (1-float(constants->cacheMisses)/float(initRequests));
    //cout << "cache Hit Rate: " << cacheHitRate << "%" << endl;
    //cout << "cache misses: " << constants->cacheMisses << endl;
    //cout << endl;
    //cout << endl;
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

    double paretoMean = stod(fileInput[0]) * 8;
    double paretoShape[3] = {1.25, 2, 8};
    int cacheCapacity[3] = {800000, 8000000, 320000000};
    int numFiles = stoi(fileInput[3]);
    int numRequests[2] = {10000, 100000};
    int propagationTime = stoi(fileInput[5]);
    int cacheBandwidth = stoi(fileInput[6]) * 1000;
    int fifoBandwidth = stoi(fileInput[7]) * 1000;
    int poissonMean[3] = {30, 150, 500};
    string cacheType = fileInput[10];


     for (int p = 0; p < 3; p++){
        for (int c = 0; c < 3; c++){
            for (int n = 0; n < 2 ; n++){
                for (int pm = 0; pm < 3; pm++){



                    cout << "--------------------------------------" << endl;
                    cout << endl;
                    cout << "iter #: " << (p + c + n + pm + 1) << endl;
                    cout << "paretoMean (B): " << paretoMean/8 << endl;
                    cout << "paretoShape value: " << paretoShape[p] << endl;
                    cout << "cacheCapacity value (B): " << cacheCapacity[c]/8 << endl;
                    cout << "numFiles: " << numFiles << endl;
                    cout << "numRequests value: " << numRequests[n] << endl;
                    cout << "propagationTime(ms): " << propagationTime << endl;
                    cout << "cacheBandwidth(Mb/s): " << cacheBandwidth/1000 << endl;
                    cout << "fifoBandwidth(Mb/s): " << fifoBandwidth/1000 << endl;
                    cout << "poissonMean value (ms): " << poissonMean[pm] << endl;
                    cout << endl;
                    cout << endl;


                    int initRequests = numRequests[n];
                    double paretoScale = (paretoShape[p]-1.0)/paretoShape[p] * paretoMean;
                    Cache* _Cache = NULL;
                    float avg = 0;
                    float hitRate = 0.0;

                    RemoteServer* remoteServer = new RemoteServer(propagationTime, numFiles, paretoShape[p], paretoScale, cacheCapacity[c]); // Remote Server with propagation time = 400
    
                    FileSelector* fileSelector = new FileSelector(numFiles, paretoShape[p], paretoScale);

                    if (cacheType.compare("ALL") == 0){
                        for (int i = 0; i < 3; i++) {
                            _Cache = new LRUCache(cacheCapacity[c]);
                            Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests[n], poissonMean[pm], 0.0, 0);
                            float* temp = runEvents(ourConstants, "LRU", numRequests[n]);
                            avg += temp[0];
                            hitRate += temp[1];
                            delete ourConstants;
                            delete _Cache;
                        }
                        cout << "average of LRU time's: " << avg/3 << endl;
                        cout << "LRU average hit rate: " << hitRate/3 << "%" << endl;
                        cout << endl;
                        cout << endl;
                        avg = 0;
                        hitRate = 0.0;
                        for (int i = 0; i < 3; i++) {
                            _Cache = new FIFOCache(cacheCapacity[c]);
                            Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests[n], poissonMean[pm], 0.0, 0);
                            float* temp = runEvents(ourConstants, "FIFO", numRequests[n]);
                            avg += temp[0];
                            hitRate += temp[1];
                            delete ourConstants;
                            delete _Cache;
                        }
                        cout << "average of FIFO time's: " << avg/3 << endl;
                        cout << "FIFO average hit rate: " << hitRate/3 << "%" << endl;
                        cout << endl;
                        cout << endl;
                        avg = 0;
                        hitRate = 0.0;
                        for (int i = 0; i < 3; i++) {
                            _Cache = new SecondChanceCache(cacheCapacity[c]);
                            Constants* ourConstants = new Constants(_Cache, fifoBandwidth, cacheBandwidth, remoteServer, fileSelector , numRequests[n], poissonMean[pm], 0.0, 0);
                            float* temp = runEvents(ourConstants, "Second-Chance", numRequests[n]);
                            avg += temp[0];
                            hitRate += temp[1];
                            delete ourConstants;
                            delete _Cache;
                        }
                        cout << "average of SecondChance time's: " << avg/3 << endl;
                        cout << "Second-Chance average hit rate: " << hitRate/3 << "%" << endl;
                        cout << endl;
                        cout << endl;        
                    }
    /*else {
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
    }*/
    delete remoteServer;
    delete fileSelector;
                }}}}
    return 0;
}