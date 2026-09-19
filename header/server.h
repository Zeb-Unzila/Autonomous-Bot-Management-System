#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "avl.h"  // Include AVLTree header
#include "linkedlist.h"  // Include LinkedList header
#include "bot.h"  // Include Bot class header

class Server {
private:
    AVLTree botTree;  // AVL Tree of bots
    std::ofstream logFile;
    std::ofstream individualCommandFile;
    std::ofstream combinedCommandFile;
    LinkedList createdFiles;  // Linked list of created files

    void createBotFile(int botID);
    void writeCommandToBotFile(int botID, const std::string &command);

public:
    Server();
    ~Server();

    void addBot(std::shared_ptr<Bot> bot);
    void removeBot(int botID);
    void sendCommandToBot(std::shared_ptr<Bot> bot, const std::string &command);
    void sendCommandToAll(const std::string &command);
    void fetchDataFromAllBots();
    void displayAllBots();
};

#endif // SERVER_H
