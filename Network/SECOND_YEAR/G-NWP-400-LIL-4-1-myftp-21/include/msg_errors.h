/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** msg_error
*/

#ifndef MSG_ERROR_H_
    #define MSG_ERROR_H_

typedef struct {
    const char *msg;
} error_t;

static const error_t error_messages[] = {
    {"150 File status okay; about to open data connection.\r\n"},
    {"200 Command okay.\r\n"},
    {"220 Service ready for new user.\r\n"},
    {"221 Service closing control connection.\r\n"},
    {"226 Closing data connection. Requested file action successful.\r\n"},
    {"230 User logged in, proceed.\r\n"},
    {"250 Requested file action okay, completed.\r\n"},
    {"331 User name okay, need password.\r\n"},
    {"332 Need account for login.\r\n"},
    {"425 Can't open data connection\r\n"},
    {"500 Syntax error, command unrecognized.\r\n"},
    {"501 Syntax error in parameters or arguments.\r\n"},
    {"530 Not logged in.\r\n"},
    {"550 Requested action not taken.\r\n"}
};

#endif /* !MSG_ERROR_H_ */
