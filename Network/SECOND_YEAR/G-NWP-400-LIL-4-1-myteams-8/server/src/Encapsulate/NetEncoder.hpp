/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** NetEncoder
*/

#ifndef NETENCODER_HPP_
#define NETENCODER_HPP_

#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <vector>
#include <string>

class NetEncoder
{
private:
    int _socket;
public:
    NetEncoder();
    ~NetEncoder();
    void InitSocket();
    int getsocket();
    uint16_t htons(int port);
    void bind(struct sockaddr_in _addr);
    void listen();
    int poll(std::vector<struct pollfd> &tab_clients, int nb_sockets);
    void close_socket(int socket);
    ssize_t read_socket(int socket, char *buffer, int size);
    class C_ERROR : public std::exception {
        private:
            std::string _msg;
        public:
            C_ERROR(std::string error);
            const char *what() const noexcept override;
    };
};

#endif /* !NETENCODER_HPP_ */
