#ifndef BOT_H
#define BOT_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Bot {
public:
    int id;
    std::string location;
    std::vector<std::string> collectedData;

    // Constructor
    Bot(int id, const std::string &location);

    // Methods
    void sendDataToBot(std::shared_ptr<Bot> otherBot, const std::string &data);
    std::string collectData();
};

#endif // BOT_H
