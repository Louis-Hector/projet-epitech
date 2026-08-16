/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** LoadSave
*/

#ifndef LOADSAVE_HPP_
#define LOADSAVE_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "ChannelData.hpp"
#include "PrivateMessageData.hpp"
#include "ReplyData.hpp"
#include "SubscriptionData.hpp"
#include "TeamData.hpp"
#include "ThreadData.hpp"
#include "UserData.hpp"

struct SaveData {
    std::vector<User> users;
    std::vector<Team> teams;
    std::vector<Subscription> subscriptions;
    std::vector<Channel> channels;
    std::vector<Thread> threads;
    std::vector<Reply> replies;
    std::vector<PrivateMessage> private_messages;
};

class LoadSave : public ChannelData, PrivateMessageData, ReplyData, SubscriptionData, TeamData, ThreadData, UserData {
    public:
        LoadSave(const std::string &dirname);
        ~LoadSave();

        bool saveAll(const SaveData &data);
        bool loadAll(SaveData &data);

    private:
        std::string _dirname;
        std::string buildPath(const std::string &filename) const;
};

#endif /* !LOADSAVE_HPP_ */
