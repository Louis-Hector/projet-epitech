# G-NWP-400 — MyTeams Protocol

**Project:** MyTeams  
**Module:** Network Programming  
**Date:** March 2026  
**Status:** Draft Specification  

---

## 1. Message Format

All server responses MUST follow this format:


- `status`:
  - `0` → Success
  - `1` → Error
  - `2` → Informational

- `code`: Sub-status identifier  
- `message`: Human-readable description  

---

## 2. Success Codes (0)

| Code | Identifier        | Description |
|------|------------------|-------------|
| 0:0  | COMMAND_VALID    | Command successfully completed |
| 0:1  | LOGIN            | Logged in successfully |
| 0:2  | LOGOUT           | User logging out |
| 0:3  | USER             | Details about requested user |
| 0:4  | USERS            | List of all users |
| 0:5  | SEND             | Message sent |
| 0:6  | MESSAGES         | Messages exchanged |
| 0:7  | USE              | Context successfully changed |
| 0:8  | CREATE_*         | Resource created (team/channel/thread/reply) |
| 0:9  | INFO_*           | Information retrieved |
| 0:10 | LIST_*           | Resource list |
| 0:11 | SUBSCRIBE        | Subscribed to team |
| 0:12 | UNSUBSCRIBE      | Unsubscribed from team |

---

## 3. Error Codes (1)

| Code | Identifier          | Description |
|------|--------------------|-------------|
| 1:0  | INVALID_ARGS       | Invalid command |
| 1:1  | TOO_MANY_ARGS      | Too many arguments |
| 1:2  | NOT_ENOUGH_ARGS    | Not enough arguments |
| 1:3  | NAME_LENGTH        | Username too long |
| 1:4  | BODY_LENGTH        | Message body too long |
| 1:5  | DESCRIPTION_LENGTH | Description too long |
| 1:6  | *_ERROR            | Resource-related error (user/team/channel/thread) |
| 1:7  | UNKNOWN_USER       | Unknown user |
| 1:8  | ALREADY_SUB        | Resource already exists or already subscribed |

---

## 4. Informational Codes (2)

| Code | Identifier      | Description |
|------|----------------|-------------|
| 2:0  | NEW_CONNECTION | New incoming connection |
| 2:1  | ALREADY_LOG    | User already logged in |
| 2:2  | NOT_LOG        | User not logged in |
| 2:3  | NOT_LOCATION   | Invalid location |
| 2:4  | NOTIFY_OTHER   | New subscription event |
| 2:5  | LIST_SUB       | Subscription list |
| 2:6  | NEED_QUOTE     | Arguments must be quoted |

---

## 5. Command Reference

### **COMMAND**:
```text
    /help : show help

    /login ["user_name"] : set the user_name used by client

    /logout : disconnect the client from the server

    /users : get the list of all users that exist on the domain

    /user ["user_uuid"] : get details about the requested user

    /send ["user_uuid"] ["message_body"] : send a message to specific user

    /messages ["user_uuid"] : list all messages exchanged with the specified user

    /subscribe ["team_uuid"] : subscribe to the events of a team and its sub directories (enable reception of all events from a team)

    /subscribed ?["team_uuid"] : list all subscribed teams or list all users subscribed to a team

    /unsubscribe ["team_uuid"] : unsubscribe from a team

    /use ?["team_uuid"] ?["channel_uuid"] ?["thread_uuid"] : Sets the command context to a team/channel/thread
```

### CREATE:

When the context is not defined (/use):
```bash
    /create ["team_name"] ["team_description"] : create a new team
```

When team_uuid is defined (/use "team_uuid"):
```bash
    /create ["channel_name"] ["channel_description"] : create a new channel
```

When team_uuid and channel_uuid are defined (/use "team_uuid" "channel_uuid"):
```bash
    /create ["thread_title"] ["thread_message"] : create a new thread
```

When team_uuid, channel_uuid and thread_uuid are defined (/use "team_uuid" "channel_uuid" "thread_uuid"):
```bash
    /create ["comment_body"] : create a new reply
```

### LIST:

- When the context is not defined (/use):
```bash
    /list : list all existing teams
```

- When team_uuid is defined (/use "team_uuid"):
```bash
    /list : list all existing channels
```

- When team_uuid and channel_uuid are defined (/use "team_uuid" "channel_uuid"):
```bash
    /list : list all existing threads
```

- When team_uuid, channel_uuid and thread_uuid are defined (/use "team_uuid" "channel_uuid" "thread_uuid"):
```bash
    /list : list all existing replies
```

### INFO:

- When the context is not defined (/use):
```bash
    /info : display currently logged-in user details
```

- When team_uuid is defined (/use "team_uuid"):
```bash
    /info : display currently selected team details
```

- When team_uuid and channel_uuid are defined (/use "team_uuid" "channel_uuid"):
```bash
    /info : display currently selected channel details
```

- When team_uuid, channel_uuid and thread_uuid are defined (/use "team_uuid" "channel_uuid" "thread_uuid"):
```bash
    /info : display currently selected thread details
```

--- 

## 6. Authors

- P. Ammeloot, Editor
- L. Hector, Editor
- L. Capoen, Editor