/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** ThreadData
*/

#ifndef THREADDATA_HPP_
#define THREADDATA_HPP_

#include <string>
#include <ctime>
#include <vector>

struct Thread {
    std::string uuid;
    std::string channel_uuid;
    std::string user_uuid;
    std::time_t timestamp;
    std::string title;
    std::string body;
};

class ThreadData {
    public:
        ThreadData();
        ~ThreadData();

        bool saveThreads(const std::vector<Thread> &threads, std::string _dirname);
        bool loadThreads(std::vector<Thread> &threads, std::string _dirname);

    protected:
    private:
};

#endif /* !THREADDATA_HPP_ */
