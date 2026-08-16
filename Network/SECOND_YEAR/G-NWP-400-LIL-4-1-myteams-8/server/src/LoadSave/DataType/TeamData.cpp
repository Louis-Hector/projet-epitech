/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** TeamData
*/

#include "TeamData.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

TeamData::TeamData()
{
}

TeamData::~TeamData()
{
}

bool TeamData::saveTeams(const std::vector<Team> &teams, std::string dirname)
{
    std::filesystem::create_directories(dirname);
    std::ofstream file(dirname + "/teams.db");

    if (!file.is_open())
        return false;

    for (std::size_t i = 0; i < teams.size(); ++i) {
        file << teams[i].uuid << "|"
             << teams[i].name << "|"
             << teams[i].description << "|"
             << teams[i].creator_uuid << "\n";
    }
    return true;
}

bool TeamData::loadTeams(std::vector<Team> &teams, std::string dirname)
{
    std::ifstream file(dirname + "/teams.db");
    std::string line;

    if (!file.is_open())
        return false;

    teams.clear();

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        Team team;

        if (!std::getline(ss, team.uuid, '|'))
            continue;
        if (!std::getline(ss, team.name, '|'))
            continue;
        if (!std::getline(ss, team.description, '|'))
            continue;
        if (!std::getline(ss, team.creator_uuid))
            continue;

        teams.push_back(team);
    }
    return true;
}
