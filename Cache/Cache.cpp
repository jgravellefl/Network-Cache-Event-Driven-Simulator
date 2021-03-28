#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include "Cache.h"

File::File(int fileId, int value){
	this->fileId = fileId;
	this->value = value;
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

File *DoublyLinkedList::add_file_to_start(int fileId, int value) {
    File *file = new File(fileId, value);

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

Cache::Cache(int capacity) {
    this->capacity = capacity;
    this->currSize = 0;
    this->fileLinkedList = new DoublyLinkedList();
    this->fileMap = map<int, File*>();
}

int Cache::getFile(int fileId) {
    if (this->fileMap.find(fileId) == this->fileMap.end()) {
        return -1;
    }
    int currValue = fileMap[fileId]->value;
    fileLinkedList->move_file_to_start(fileMap[fileId]);

    return currValue;
}

void Cache::insertFile(int fileId, int value) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->value = value;
        this->fileLinkedList->move_file_to_start(this->fileMap[fileId]);
        return;
    }

    //If the current size reached capacity, remove the LRU file
    if (this->currSize == this->capacity) {
        this->fileMap.erase(this->fileLinkedList->remove_last_file());
        this->currSize--;
    }

    File *file = this->fileLinkedList->add_file_to_start(fileId, value);
    this->fileMap[fileId] = file;
    this->currSize++;
}

Cache::~Cache() {
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
    delete this->fileLinkedList;
}