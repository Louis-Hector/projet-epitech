/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** PrivateMessageData
*/

#ifndef PRIVATEMESSAGEDATA_HPP_
#define PRIVATEMESSAGEDATA_HPP_

#include <string>
#include <ctime>
#include <vector>

struct PrivateMessage {
    std::string sender_uuid;
    std::string receiver_uuid;
    std::time_t timestamp;
    std::string body;
};

class PrivateMessageData {
    public:
        PrivateMessageData();
        ~PrivateMessageData();

        bool savePrivateMessages(const std::vector<PrivateMessage> &messages, std::string _dirname);
        bool loadPrivateMessages(std::vector<PrivateMessage> &messages, std::string _dirname);

    protected:
    private:
};

#endif /* !PRIVATEMESSAGEDATA_HPP_ */
