#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "bot.h"  // Include the Bot class header

class AVLNode {
public:
    std::shared_ptr<Bot> bot;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(std::shared_ptr<Bot> bot);
};

class AVLTree {
private:
    AVLNode *root;

    int getHeight(AVLNode *node);
    int getBalanceFactor(AVLNode *node);
    AVLNode *rotateRight(AVLNode *y);
    AVLNode *rotateLeft(AVLNode *x);
    AVLNode *insert(AVLNode *node, std::shared_ptr<Bot> bot);
    AVLNode *remove(AVLNode *node, int botID);
    AVLNode *minValueNode(AVLNode *node);
    void inOrder(AVLNode *node, std::vector<std::shared_ptr<Bot>> &bots);
    void fetchData(AVLNode *node, std::ofstream &logFile);
    void getAllBotIDs(AVLNode *node, std::vector<int> &ids);

public:
    AVLTree();

    void addBot(std::shared_ptr<Bot> bot);
    void removeBot(int botID);
    void displayBots();
    void fetchData(std::ofstream &logFile);
    std::vector<int> getAllBotIDs();
};

#endif // AVL_TREE_H
