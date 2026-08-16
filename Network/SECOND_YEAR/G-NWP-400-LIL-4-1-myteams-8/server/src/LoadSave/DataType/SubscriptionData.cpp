/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** SubscriptionData
*/

#include "SubscriptionData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

SubscriptionData::SubscriptionData()
{
}

SubscriptionData::~SubscriptionData()
{
}

bool SubscriptionData::saveSubscriptions(const std::vector<Subscription> &subscriptions, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/subscriptions.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < subscriptions.size(); ++i) {
        file << subscriptions[i].user_uuid << "|"
             << subscriptions[i].team_uuid << "\n";
    }
    return true;
}

bool SubscriptionData::loadSubscriptions(std::vector<Subscription> &subscriptions, std::string dirname)
{
    std::ifstream file(dirname + "/subscriptions.db");
    std::string line;

    if (!file.is_open())
        return false;

    subscriptions.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        Subscription subscription;

        if (!std::getline(ss, subscription.user_uuid, '|'))
            continue;
        if (!std::getline(ss, subscription.team_uuid))
            continue;

        subscriptions.push_back(subscription);
    }
    return true;
}
