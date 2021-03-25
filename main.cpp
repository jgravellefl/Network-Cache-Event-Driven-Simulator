//main loop
#include <iostream>
#include "Cache/Cache.h"

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

 
 return 1;
}