#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>

class LinkedListNode {
public:
    std::string fileName;
    LinkedListNode *next;

    LinkedListNode(const std::string &fileName);
};

class LinkedList {
private:
    LinkedListNode *head;
    bool removeFile(const std::string &fileName);

public:
    LinkedList();
    ~LinkedList();
    void add(const std::string &fileName);
    void remove(const std::string &fileName);
    void traverseAndDeleteFiles();
};

#endif
