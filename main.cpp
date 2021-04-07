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

    RemoteServer remoteServer(400, 100, paretoShape, paretoScale); // Remote Server with propagation time = 400


    cout << "Testing Remote Server Implementation:" << endl;
    

     map<int, File*>::iterator iter;
     for (iter = remoteServer.fileMap.begin(); iter != remoteServer.fileMap.end(); iter++)  {
         cout << "\tAdded File " << iter->first << ": " << iter->second->value << endl;
     }

    cout << "\nTesting File Selector Implementation:\n";
    FileSelector fileSelector = FileSelector(100, paretoShape, paretoScale);

    printf("\tInsert ended\n");

    chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();
    srand (time(NULL));
    for (int i = 0; i < 50; i++) {
        int random = rand() % (fileSelector.currSize - 1) + 1;
        int fileID = fileSelector.getFile(random);
        // This shows file matched at given input
        printf("\tFound File %d with input %d\n", fileID, random);
    }
    chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
    double time = chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    printf("\tTesting get ended\n\tTime elapsed in seconds: %f\n", time/1000);

    cout << "\nTesting LRU Cache Implementation:" << endl;
    Cache cache(2);	// cache capacity 2
    cache.insertFile(2, 23);
    cout << "\tInserting File 2 (Value = 23)\n\t - Geting File 2: " << cache.getFile(2) << endl;
    //Returns -1 because it wasn't added
    cout << "\t - Geting File 1: " << cache.getFile(1) << endl;
    cache.insertFile(1, 1);
    cache.insertFile(1, 5);
    cout << "\tInserting File 1 (Value = 5)\n\t - Geting File 1: " << cache.getFile(1) << endl;
    cout << "\t - Geting File 2: " << cache.getFile(2) << endl;
    cache.insertFile(8, 19);
    cout << "\tInserting File 8 (Value = 19)\n\t - Geting File 1: " << cache.getFile(1) << endl;
    cout << "\t - Geting File 1: " <<cache.getFile(8) << endl << endl;

    FileMap files = FileMap();

    Constants constants = Constants(&cache, 100, 1000, &files, 3, 5, 0);
    Constants* constPtr = &constants;

    priority_queue<Event*, std::vector<Event*>, LessThanByTime > pq;

    Event* myEvent[2];
    
    Event* event1 = new FileRequestEvent(10, 10, 1, constPtr);

    pq.push(event1);
    Event* eventParams[2]; 

    cout << "Testing processing events framework:" << endl;
    while (constants.numRequests > 0 && !pq.empty()){
        Event* currEvent = pq.top();
        cout << "\tcurrentEvent: " << currEvent->fileId << endl;
        pq.pop();
        currEvent->process(eventParams);
        delete currEvent;
        pq.push(eventParams[1]);
    }
    return 0;
}