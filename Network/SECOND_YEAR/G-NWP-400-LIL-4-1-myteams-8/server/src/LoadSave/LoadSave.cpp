/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** LoadSave
*/

#include "LoadSave.hpp"

LoadSave::LoadSave(const std::string &dirname) : _dirname(dirname)
{
}

LoadSave::~LoadSave()
{
}

std::string LoadSave::buildPath(const std::string &filename) const
{
    return _dirname + filename;
}

bool LoadSave::saveAll(const SaveData &data)
{
        if (!saveUsers(data.users, _dirname))
            return false;
        if (!saveTeams(data.teams, _dirname))
            return false;
        if (!saveSubscriptions(data.subscriptions, _dirname))
            return false;
        if (!saveChannels(data.channels, _dirname))
            return false;
        if (!saveThreads(data.threads, _dirname))
            return false;
        if (!saveReplies(data.replies, _dirname))
            return false;
        if (!savePrivateMessages(data.private_messages, _dirname))
            return false;
        return true;
}

bool LoadSave::loadAll(SaveData &data)
{
    if (!loadUsers(data.users, _dirname))
        return false;
    if (!loadTeams(data.teams, _dirname))
        return false;
    if (!loadSubscriptions(data.subscriptions, _dirname))
        return false;
    if (!loadChannels(data.channels, _dirname))
        return false;
    if (!loadThreads(data.threads, _dirname))
        return false;
    if (!loadReplies(data.replies, _dirname))
        return false;
    if (!loadPrivateMessages(data.private_messages, _dirname))
        return false;
    return true;
}