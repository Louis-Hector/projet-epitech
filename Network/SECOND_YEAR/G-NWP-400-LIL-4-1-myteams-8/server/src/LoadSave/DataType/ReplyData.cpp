/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** ReplyData
*/

#include "ReplyData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

ReplyData::ReplyData()
{
}

ReplyData::~ReplyData()
{
}

bool ReplyData::saveReplies(const std::vector<Reply> &replies, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/replies.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < replies.size(); ++i) {
        file << replies[i].thread_uuid << "|"
             << replies[i].user_uuid << "|"
             << replies[i].timestamp << "|"
             << replies[i].body << "\n";
    }
    return true;
}

bool ReplyData::loadReplies(std::vector<Reply> &replies, std::string dirname)
{
    std::ifstream file(dirname + "/replies.db");
    std::string line;

    if (!file.is_open())
        return false;

    replies.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string timestampStr;
        Reply reply;

        if (!std::getline(ss, reply.thread_uuid, '|'))
            continue;
        if (!std::getline(ss, reply.user_uuid, '|'))
            continue;
        if (!std::getline(ss, timestampStr, '|'))
            continue;
        if (!std::getline(ss, reply.body))
            continue;

        reply.timestamp = static_cast<std::time_t>(std::atoll(timestampStr.c_str()));

        replies.push_back(reply);
    }
    return true;
}
