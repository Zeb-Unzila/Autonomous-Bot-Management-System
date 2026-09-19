#include "avl.h"
#include "utils.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <ctime>

// std::string getCurrentTimestamp() {
//     time_t now = time(nullptr);
//     char buf[20];
//     strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
//     return std::string(buf);
// }

// AVLNode constructor
AVLNode::AVLNode(std::shared_ptr<Bot> bot) : bot(bot), left(nullptr), right(nullptr), height(1) {}

// AVLTree constructor
AVLTree::AVLTree() : root(nullptr) {}

// Get height of a node
int AVLTree::getHeight(AVLNode *node) {
    return node ? node->height : 0;
}

// Get balance factor of a node
int AVLTree::getBalanceFactor(AVLNode *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right rotation
AVLNode* AVLTree::rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotation
AVLNode* AVLTree::rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert a bot into the AVL Tree
AVLNode* AVLTree::insert(AVLNode *node, std::shared_ptr<Bot> bot) {
    if (!node)
        return new AVLNode(bot);

    if (bot->id < node->bot->id)
        node->left = insert(node->left, bot);
    else if (bot->id > node->bot->id)
        node->right = insert(node->right, bot);
    else
        throw std::runtime_error("Duplicate bot ID detected.");

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalanceFactor(node);

    if (balance > 1 && bot->id < node->left->bot->id)
        return rotateRight(node);

    if (balance < -1 && bot->id > node->right->bot->id)
        return rotateLeft(node);

    if (balance > 1 && bot->id > node->left->bot->id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && bot->id < node->right->bot->id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Remove a bot from the AVL Tree
AVLNode* AVLTree::remove(AVLNode *node, int botID) {
    if (!node)
        return nullptr;

    if (botID < node->bot->id)
        node->left = remove(node->left, botID);
    else if (botID > node->bot->id)
        node->right = remove(node->right, botID);
    else {
        if (!node->left || !node->right) {
            AVLNode *temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            AVLNode *temp = minValueNode(node->right);
            node->bot = temp->bot;
            node->right = remove(node->right, temp->bot->id);
        }
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalanceFactor(node);

    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Get minimum value node (used for node replacement during deletion)
AVLNode* AVLTree::minValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// In-order traversal of the AVL Tree
void AVLTree::inOrder(AVLNode *node, std::vector<std::shared_ptr<Bot>> &bots) {
    if (node) {
        inOrder(node->left, bots);
        bots.push_back(node->bot);
        inOrder(node->right, bots);
    }
}

// Fetch data for each bot and log it to the provided file
void AVLTree::fetchData(AVLNode *node, std::ofstream &logFile) {
    if (node) {
        fetchData(node->left, logFile);
        std::string data = node->bot->collectData();
        std::string timestamp = getCurrentTimestamp();
        logFile << timestamp << "," << node->bot->id << "," << data << "," << node->bot->location << std::endl;
        fetchData(node->right, logFile);
    }
}

// Get all bot IDs in the AVL Tree
void AVLTree::getAllBotIDs(AVLNode *node, std::vector<int> &ids) {
    if (node) {
        getAllBotIDs(node->left, ids);
        ids.push_back(node->bot->id);
        getAllBotIDs(node->right, ids);
    }
}

// Public method to add a bot
void AVLTree::addBot(std::shared_ptr<Bot> bot) {
    root = insert(root, bot);
}

// Public method to remove a bot
void AVLTree::removeBot(int botID) {
    root = remove(root, botID);
}

// Display all bots in the AVL Tree
void AVLTree::displayBots() {
    std::vector<std::shared_ptr<Bot>> bots;
    inOrder(root, bots);
    std::cout << "Displaying bots:" << std::endl;
    for (auto &bot : bots) {
        std::cout << "Bot ID: " << bot->id << " Location: " << bot->location << std::endl;
    }
}

// Public method to fetch data and log it to a file
void AVLTree::fetchData(std::ofstream &logFile) {
    fetchData(root, logFile);
}

// Public method to get all bot IDs
std::vector<int> AVLTree::getAllBotIDs() {
    std::vector<int> ids;
    getAllBotIDs(root, ids);
    return ids;
}
