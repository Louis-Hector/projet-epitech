/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** SubscriptionData
*/

#ifndef SUBSCRIPTIONDATA_HPP_
#define SUBSCRIPTIONDATA_HPP_

#include <string>
#include <vector>

struct Subscription {
    std::string user_uuid;
    std::string team_uuid;
};

class SubscriptionData {
    public:
        SubscriptionData();
        ~SubscriptionData();

        bool saveSubscriptions(const std::vector<Subscription> &subscriptions, std::string _dirname);
        bool loadSubscriptions(std::vector<Subscription> &subscriptions, std::string _dirname);

    protected:
    private:
};

#endif /* !SUBSCRIPTIONDATA_HPP_ */
