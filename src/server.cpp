#include "server.h"
#include "utils.h"
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <ctime>

// std::string getCurrentTimestamp() {
//     time_t now = time(nullptr);
//     char buf[20];
//     strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
//     return std::string(buf);
// }

// Constructor
Server::Server() {
    std::ofstream("server_log.txt", std::ios::trunc).close();
    std::ofstream("IndividualCommand.txt", std::ios::trunc).close();
    std::ofstream("CombinedCommand.txt", std::ios::trunc).close();

    logFile.open("server_log.txt", std::ios::app);
    individualCommandFile.open("IndividualCommand.txt", std::ios::app);
    combinedCommandFile.open("CombinedCommand.txt", std::ios::app);

    createdFiles.add("server_log.txt");
    createdFiles.add("IndividualCommand.txt");
    createdFiles.add("CombinedCommand.txt");

    if (!logFile.is_open() || !individualCommandFile.is_open() || !combinedCommandFile.is_open()) {
        throw std::runtime_error("Failed to open log or command files.");
    }
}

// Destructor
Server::~Server() {
    if (logFile.is_open()) logFile.close();
    if (individualCommandFile.is_open()) individualCommandFile.close();
    if (combinedCommandFile.is_open()) combinedCommandFile.close();

    // Delete all created files upon server shutdown
    createdFiles.traverseAndDeleteFiles();
}

// Add bot to the server
void Server::addBot(std::shared_ptr<Bot> bot) {
    try {
        botTree.addBot(bot);
        createBotFile(bot->id);
        std::cout << "Bot with ID " << bot->id << " added to the server." << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << " Cannot add Bot with ID " << bot->id << "." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

// Remove bot from the server
void Server::removeBot(int botID) {
    botTree.removeBot(botID);
    std::string fileName = std::to_string(botID) + ".txt";
    createdFiles.remove(fileName);  // Remove from linked list
    if (remove(fileName.c_str()) == 0) {
        std::cout << "File " << fileName << " deleted successfully." << std::endl;
    } else {
        std::cerr << "Failed to delete file " << fileName << "." << std::endl;
    }
    std::cout << "Bot with ID " << botID << " removed from the server." << std::endl;
}

// Send command to a specific bot
void Server::sendCommandToBot(std::shared_ptr<Bot> bot, const std::string &command) {
    std::string timestamp = getCurrentTimestamp();
    individualCommandFile << timestamp << "," << bot->id << "," << bot->location << "," << command << std::endl;
    writeCommandToBotFile(bot->id, command);
    std::cout << "Server sent command to Bot " << bot->id << ": " << command << std::endl;
}

// Send command to all bots
void Server::sendCommandToAll(const std::string &command) {
    std::vector<int> allBotIDs = botTree.getAllBotIDs();
    std::string timestamp = getCurrentTimestamp();
    std::string botIDs;

    for (size_t i = 0; i < allBotIDs.size(); ++i) {
        botIDs += std::to_string(allBotIDs[i]);
        if (i < allBotIDs.size() - 1) botIDs += ",";
        writeCommandToBotFile(allBotIDs[i], command);
    }

    combinedCommandFile << timestamp << "," << botIDs << "," << command << std::endl;
    std::cout << "Server sent command to all bots: " << command << std::endl;
}

// Fetch data from all bots and log to file
void Server::fetchDataFromAllBots() {
    botTree.fetchData(logFile);
    std::cout << "Data fetched from bots and logged in 'server_log.txt'." << std::endl;
}

// Display all bots in the server
void Server::displayAllBots() {
    std::cout << "Displaying all bots:" << std::endl;
    botTree.displayBots();
}

// Create a file for a bot
void Server::createBotFile(int botID) {
    std::string fileName = std::to_string(botID) + ".txt";
    std::ofstream botFile(fileName, std::ios::app);
    if (!botFile.is_open()) {
        throw std::runtime_error("Failed to create or open bot file.");
    }
    createdFiles.add(fileName);  // Track file creation
}

// Write command to a bot file
void Server::writeCommandToBotFile(int botID, const std::string &command) {
    std::string fileName = std::to_string(botID) + ".txt";
    std::ofstream botFile(fileName, std::ios::app);
    if (!botFile.is_open()) {
        throw std::runtime_error("Failed to write to bot file.");
    }
    std::string timestamp = getCurrentTimestamp();
    botFile << timestamp << "," << command << std::endl;
}
