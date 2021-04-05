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

    RemoteServer remoteServer(400); // Remote Server with propagation time = 400

    remoteServer.insertFile(1, 1);
    remoteServer.insertFile(1, 5);
    remoteServer.insertFile(2, 23);
    remoteServer.insertFile(5, 7);
    remoteServer.insertFile(8, 19);

    cout << "Testing Remote Server Implementation:" << endl;

    map<int, File*>::iterator iter;
    for (iter = remoteServer.fileMap.begin(); iter != remoteServer.fileMap.end(); iter++)  {
        cout << "\tAdded File " << iter->first << ": " << iter->second->value << endl;
    }

    cout << "\nTesting File Selector Implementation:\n";
    int range = 0;
    FileSelector fileSelector = FileSelector();
    for (int i = 1; i <= 10000; i++) {
        int random = rand() % 10 + 1;
        // This shows insertion
        // printf("\tFile ID: %d, Min: %d, Max: %d\n", i, fileSelector.nextMin, (fileSelector.nextMin + random));
        fileSelector.insertFile(i, fileSelector.nextMin, fileSelector.nextMin + random);
        range += random + 1;
    }
    printf("\tInsert ended\n");

    chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();

    for (int i = 0; i < 10000; i++) {
        int random = rand() % (range - 1) + 1;
        int fileID = fileSelector.getFile(random);
        // This shows file matched at given input
        // printf("\tFound File %d with input %d\n", fileID, random);
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