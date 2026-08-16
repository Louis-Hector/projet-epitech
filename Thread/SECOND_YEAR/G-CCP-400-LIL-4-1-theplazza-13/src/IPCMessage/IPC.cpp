/*
** EPITECH PROJECT, 2026
** G-CCP-400-LIL-4-1-theplazza-13
** File description:
** IPC
*/

#include "IPC.hpp"

IPC::IPC(std::string &path_file) : _fd(-1), _path_file(path_file)
{
    if (mkfifo(_path_file.c_str(), 0666) == -1) {
        if (errno != EEXIST)
            throw ERROR_IPC("Not possible to create the file for the kitchen (FIFO)");
    }
}

IPC::~IPC()
{
    if (_fd != -1)
        close(_fd);
}

IPC::ERROR_IPC::ERROR_IPC(const std::string &error) : msg(error)
{
}

const char* IPC::ERROR_IPC::what() const noexcept
{
    return msg.c_str();
}

void IPC::open_mode_file(int mode)
{
    _fd = open(_path_file.c_str(), mode);
    if (_fd == -1)
        throw ERROR_IPC("Impossible to open the file " + _path_file  + "\n");
}

bool IPC::wait_for_data(int timeoutMs)
{
    struct pollfd pollFd;
    if (_fd == -1)
        throw ERROR_IPC("no valid_fd");
    pollFd.fd = _fd;
    pollFd.events = POLLIN;
    pollFd.revents = 0;
    int result = poll(&pollFd, 1, timeoutMs);
    if (result == -1)
        throw ERROR_IPC("poll failed");
    if (result == 0)
        return false;
    return (pollFd.revents & POLLIN);
}

void IPC::writeMessage(const PackedIPCMessage &packed)
{
    ssize_t bytes = write(_fd, &packed, sizeof(PackedIPCMessage));
    if (bytes != static_cast<ssize_t>(sizeof(PackedIPCMessage)))
        throw ERROR_IPC("write fail");
}

PackedIPCMessage IPC::readMessage()
{
    PackedIPCMessage message;
    ssize_t bytes = read(_fd, &message, sizeof(PackedIPCMessage));
    if (bytes <= 0)
        throw ERROR_IPC("fifo empty");
    if (bytes != static_cast<ssize_t>(sizeof(PackedIPCMessage)))
        throw ERROR_IPC("read fail");
    return message;
}