#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::pair<std::vector<std::string>, std::vector<int>> loadData(const std::string& filename) {
    std::vector<std::string> messages;
    std::vector<int> categories;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {messages, categories};
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string category, message;

        if (std::getline(ss, category, ',') && std::getline(ss, message)) {
            if (!message.empty() && message[0] == '"') {
                message = message.substr(1, message.length() - 2);
            }
            messages.push_back(message);
            categories.push_back(category == "spam" ? 1 : 0);
        }
    }

    file.close();
    return {messages, categories};
}
