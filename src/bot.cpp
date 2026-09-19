#include "bot.h"
#include "utils.h"
#include <cstdlib>  // For rand()

// Constructor for Bot
Bot::Bot(int id, const std::string &location) : id(id), location(location) {}

// Method to send data to another Bot
void Bot::sendDataToBot(std::shared_ptr<Bot> otherBot, const std::string &data) {
    std::cout << "Bot " << id << " sent data to Bot " << otherBot->id << ": " << data << std::endl;
    otherBot->collectedData.push_back(data);
}

// Method to collect data
std::string Bot::collectData() {
    std::vector<std::string> possibleData = {"grass found", "water found", "rock found", "no data"};
    std::string data = possibleData[rand() % possibleData.size()];
    collectedData.push_back(data);
    return data;
}
