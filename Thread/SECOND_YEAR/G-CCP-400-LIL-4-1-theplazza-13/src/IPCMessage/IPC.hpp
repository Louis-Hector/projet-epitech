/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include "IPCMessage.hpp"

class IPC
{
private:
    int _fd;
    std::string _path_file;
public:
    IPC(std::string &path_file);
    ~IPC();
    void open_mode_file(int mode);
    bool wait_for_data(int timeoutMs);
    void writeMessage(const PackedIPCMessage &packed);
    PackedIPCMessage readMessage();
    class ERROR_IPC : public std::exception {
        private:
            std::string msg;
        public:
            ERROR_IPC(const std::string &error);
            ~ERROR_IPC() = default;
            const char *what() const noexcept override;
    };
};

#endif /* !IPC_HPP_ */
