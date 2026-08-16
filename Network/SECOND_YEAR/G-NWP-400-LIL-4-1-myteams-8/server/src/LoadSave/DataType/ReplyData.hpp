/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** ReplyData
*/

#ifndef REPLYDATA_HPP_
#define REPLYDATA_HPP_

#include <string>
#include <ctime>
#include <vector>

struct Reply {
    std::string thread_uuid;
    std::string user_uuid;
    std::time_t timestamp;
    std::string body;
};

class ReplyData {
    public:
        ReplyData();
        ~ReplyData();

        bool saveReplies(const std::vector<Reply> &replies, std::string _dirname);
        bool loadReplies(std::vector<Reply> &replies, std::string _dirname);

    protected:
    private:
};

#endif /* !REPLYDATA_HPP_ */
