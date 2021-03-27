//main loop
#include <iostream>
#include "Cache/Cache.h"
#include <queue>
#include "Events/Event.h"
#include "Constants/Constants.h"
#include "Events/FileRequestEvent.h"

using namespace std;

int main(){
    Cache cache(2);	// cache capacity 2
    cache.insertFile(2, 2);
    cout << cache.getFile(2) << endl;
    cout << cache.getFile(1) << endl;
    cache.insertFile(1, 1);
    cache.insertFile(1, 5);
    cout << cache.getFile(1) << endl;
    cout << cache.getFile(2) << endl;
    cache.insertFile(8, 8);
    cout << cache.getFile(1) << endl;
    cout << cache.getFile(8) << endl;
    
    FileMap files = FileMap();

    Constants constants = Constants(&cache, 100, 1000, &files, 3, 5);
    Constants* constPtr = &constants;
    cout << "constants og num of files" << endl;
    cout << constants.numRequests << endl;
    cout << constPtr->numRequests << endl;

    priority_queue<Event*, std::vector<Event*>, LessThanByTime > pq;

    Event* myEvent[2];
    
    Event* event1 = new FileRequestEvent(10, 10, 1, constPtr);
    //cout << event1.constants->numRequests << endl;
    //Event* p1 = &event1;
    pq.push(event1);
    Event* eventParams[2]; 

    while (constants.numRequests > 0 && !pq.empty()){
        Event* currEvent = pq.top();
        pq.pop();
        cout << "hello" << endl;
        cout << "asdf" << endl;
        cout << "fileId " << currEvent->fileId << endl;
        currEvent->process(eventParams);
        delete currEvent;
        cout << "checking before its put in: " << eventParams[1]->fileId << endl;
        pq.push(eventParams[1]);
    }
    return 1;
}