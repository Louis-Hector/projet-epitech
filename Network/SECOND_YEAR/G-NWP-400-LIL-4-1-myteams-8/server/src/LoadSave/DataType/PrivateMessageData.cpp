/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** PrivateMessageData
*/

#include "PrivateMessageData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

PrivateMessageData::PrivateMessageData()
{
}

PrivateMessageData::~PrivateMessageData()
{
}

bool PrivateMessageData::savePrivateMessages(const std::vector<PrivateMessage> &messages, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/private_messages.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < messages.size(); ++i) {
        file << messages[i].sender_uuid << "|"
             << messages[i].receiver_uuid << "|"
             << messages[i].timestamp << "|"
             << messages[i].body << "\n";
    }
    return true;
}

bool PrivateMessageData::loadPrivateMessages(std::vector<PrivateMessage> &messages, std::string dirname)
{
    std::ifstream file(dirname + "/private_messages.db");
    std::string line;

    if (!file.is_open())
        return false;

    messages.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string timestampStr;
        PrivateMessage message;

        if (!std::getline(ss, message.sender_uuid, '|'))
            continue;
        if (!std::getline(ss, message.receiver_uuid, '|'))
            continue;
        if (!std::getline(ss, timestampStr, '|'))
            continue;
        if (!std::getline(ss, message.body))
            continue;

        message.timestamp = static_cast<std::time_t>(std::atoll(timestampStr.c_str()));

        messages.push_back(message);
    }
    return true;
}
