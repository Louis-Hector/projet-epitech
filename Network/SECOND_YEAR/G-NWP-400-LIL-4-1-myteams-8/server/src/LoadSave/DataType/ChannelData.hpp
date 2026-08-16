/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** ChannelData
*/

#ifndef CHANNELDATA_HPP_
#define CHANNELDATA_HPP_

#include <string>
#include <vector>

struct Channel {
    std::string uuid;
    std::string team_uuid;
    std::string name;
    std::string description;
};

class ChannelData {
    public:
        ChannelData();
        ~ChannelData();

        bool saveChannels(const std::vector<Channel> &channels, std::string _dirname);
        bool loadChannels(std::vector<Channel> &channels, std::string _dirname);

    protected:
    private:
};

#endif /* !CHANNELDATA_HPP_ */
