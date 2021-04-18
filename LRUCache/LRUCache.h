#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include "../Cache/Cache.h"

using namespace std;

class File {
    public:
        int fileId, value;
        File *prev, *next;

    //Create file with id and value
        File(int fileId, int value);
        File();
};

class DoublyLinkedList {
    public:
        File *start, *end;
        bool isEmpty();
    /*
     * Set up functions to add and move files to head
     * Since it's based off of an LRU Cache System
    */
        DoublyLinkedList();
        File* add_file_to_start(int fileId, int value);
        void move_file_to_start(File *file);
        //Combine remove and get rear
        int remove_last_file();
};

class LRUCache : public Cache {
    public:
		int capacity, currSize;
		DoublyLinkedList *fileLinkedList;
		map<int, File*> fileMap;

		LRUCache(int capacity);
		int getFile(int fileId);
		void insertFile(int fileId, int value);
		~LRUCache();
        LRUCache();
};