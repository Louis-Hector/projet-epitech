/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** ThreadData
*/

#include "ThreadData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

ThreadData::ThreadData()
{
}

ThreadData::~ThreadData()
{
}

bool ThreadData::saveThreads(const std::vector<Thread> &threads, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/threads.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < threads.size(); i++) {
        file << threads[i].uuid << "|"
             << threads[i].channel_uuid << "|"
             << threads[i].user_uuid << "|"
             << threads[i].timestamp << "|"
             << threads[i].title << "|"
             << threads[i].body << "\n";
    }
    return true;
}

bool ThreadData::loadThreads(std::vector<Thread> &threads, std::string dirname)
{
    std::ifstream file(dirname + "/threads.db");
    std::string line;

    if (!file.is_open())
        return false;

    threads.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string timestampStr;
        Thread thread;

        if (!std::getline(ss, thread.uuid, '|'))
            continue;
        if (!std::getline(ss, thread.channel_uuid, '|'))
            continue;
        if (!std::getline(ss, thread.user_uuid, '|'))
            continue;
        if (!std::getline(ss, timestampStr, '|'))
            continue;
        if (!std::getline(ss, thread.title, '|'))
            continue;
        if (!std::getline(ss, thread.body))
            continue;

        thread.timestamp = static_cast<std::time_t>(std::atoll(timestampStr.c_str()));

        threads.push_back(thread);
    }
    return true;
}
