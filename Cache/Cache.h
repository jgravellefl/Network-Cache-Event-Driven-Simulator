#pragma once
#include <stdio.h>
#include <time.h>
using namespace std;

class File {
    private:
        int fileId, value;
        File *prev, *next;
        
    public:
    //Create file with id and value
        File(int fileId, int value);
};

class DoublyLinkedList {
    private:
        File *start, *end;
        bool isEmpty();

    public:
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

class Cache
{
	private:
		int capacity, currSize;
		DoublyLinkedList *fileLinkedList;
		map<int, File*> fileMap;

	public:
		Cache(int capacity);
		int getFile(int fileId);
		void insertFile(int fileId, int value);
		~Cache();
};