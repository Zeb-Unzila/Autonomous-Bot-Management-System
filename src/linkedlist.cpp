#include "linkedlist.h"
#include "utils.h"
#include <cstdio>

// Constructor for LinkedListNode
LinkedListNode::LinkedListNode(const std::string &fileName) : fileName(fileName), next(nullptr) {}

// Constructor for LinkedList
LinkedList::LinkedList() : head(nullptr) {}

// Destructor for LinkedList
LinkedList::~LinkedList() {
    while (head) {
        LinkedListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Add a file to the linked list
void LinkedList::add(const std::string &fileName) {
    LinkedListNode *newNode = new LinkedListNode(fileName);
    newNode->next = head;
    head = newNode;
}

// Remove a file from the linked list
void LinkedList::remove(const std::string &fileName) {
    LinkedListNode *current = head;
    LinkedListNode *prev = nullptr;

    while (current) {
        if (current->fileName == fileName) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Helper function to remove a file from the filesystem
bool LinkedList::removeFile(const std::string &fileName) {
    return std::remove(fileName.c_str()) == 0;
}

// Traverse the linked list and delete all files
void LinkedList::traverseAndDeleteFiles() {
    while (head) {
        LinkedListNode *current = head;
        if (removeFile(current->fileName)) {
            std::cout << "File " << current->fileName << " deleted successfully." << std::endl;
        } else {
            std::cerr << "Failed to delete file " << current->fileName << "." << std::endl;
        }
        head = head->next;
        delete current;
    }
}
