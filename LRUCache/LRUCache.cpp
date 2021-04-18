#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include "LRUCache.h"

File::File(int fileId, int fileSize){
	this->fileId = fileId;
	this->fileSize = fileSize;
	this->prev = nullptr;
    this->next = nullptr;
}

//To check if there are any files
bool DoublyLinkedList::isEmpty() {
    return end == nullptr;
}

DoublyLinkedList::DoublyLinkedList() {
    this->start = nullptr;
    this->end = nullptr;
}

File *DoublyLinkedList::add_file_to_start(int fileId, int fileSize) {
    File *file = new File(fileId, fileSize);

    //If linked list is empty
    //Try using isEmpty()
    if (isEmpty()) {
        this->start = file;
        this->end = file;
    } else {
        file->next = this->start;
        this->start->prev = file;
        this->start = file;
    }
    return file;
}

void DoublyLinkedList::move_file_to_start(File *file) {
    if (file == start) {
        return;
    }

    if (file == end) {
        //Set end to the file infront of end
        this->end = this->end->prev;
        this->end->next = nullptr;
    } else {
        //Have the files before and after the current file to be connected
        file->prev->next = file->next;
        file->next->prev = file->prev;
    }

    //Move the file to the front of the linked list
    file->next = this->start;
    file->prev = nullptr;
    this->start->prev = file;
    this->start = file;
}

int DoublyLinkedList::remove_last_file() {
    //Returns -1 if the linked list is emptu
    if (isEmpty()) {
        return -1;
    }

    int lastFileId = this->end->fileId;
    //If only one element in linked list
    if (this->start == this->end) {
        delete end;
        this->start = nullptr;
        this->end = nullptr;
    } else {
        File *tempFile = this->end;
        this->end = this->end->prev;
        this->end->next = nullptr;
        delete tempFile;
        return lastFileId;
    }

    return lastFileId;
}

LRUCache::LRUCache(int capacity) {
    this->capacity = capacity;
    this->currSize = 0;
    this->fileLinkedList = new DoublyLinkedList();
    this->fileMap = map<int, File*>();
}

int LRUCache::getFile(int fileId) {
    if (this->fileMap.find(fileId) == this->fileMap.end()) {
        return -1;
    }
    int currfileSize = fileMap[fileId]->fileSize;
    fileLinkedList->move_file_to_start(fileMap[fileId]);

    return currfileSize;
}

void LRUCache::insertFile(int fileId, int fileSize) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->fileSize = fileSize;
        this->fileLinkedList->move_file_to_start(this->fileMap[fileId]);
        return;
    }

    //If the current size reached capacity, remove the LRU file
    while (this->currSize + fileSize > this->capacity) {
        int tempFileSize = this->fileLinkedList->end->fileSize;
        this->fileMap.erase(this->fileLinkedList->remove_last_file());
        this->currSize  = this->currSize - tempFileSize;
    }

    File *file = this->fileLinkedList->add_file_to_start(fileId, fileSize);
    this->fileMap[fileId] = file;
    this->currSize += file->fileSize;
}

LRUCache::~LRUCache() {
    // cout << " child " << endl;
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
    delete this->fileLinkedList;
}