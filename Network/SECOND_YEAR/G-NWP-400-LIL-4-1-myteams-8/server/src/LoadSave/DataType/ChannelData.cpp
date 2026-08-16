/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** ChannelData
*/

#include "ChannelData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

ChannelData::ChannelData()
{
}

ChannelData::~ChannelData()
{
}

bool ChannelData::saveChannels(const std::vector<Channel> &channels, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/channels.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < channels.size(); ++i) {
        file << channels[i].uuid << "|"
             << channels[i].team_uuid << "|"
             << channels[i].name << "|"
             << channels[i].description << "\n";
    }
    return true;
}

bool ChannelData::loadChannels(std::vector<Channel> &channels, std::string dirname)
{
    std::ifstream file(dirname + "/channels.db");
    std::string line;

    if (!file.is_open())
        return false;

    channels.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        Channel channel;

        if (!std::getline(ss, channel.uuid, '|'))
            continue;
        if (!std::getline(ss, channel.team_uuid, '|'))
            continue;
        if (!std::getline(ss, channel.name, '|'))
            continue;
        if (!std::getline(ss, channel.description))
            continue;

        channels.push_back(channel);
    }
    return true;
}
