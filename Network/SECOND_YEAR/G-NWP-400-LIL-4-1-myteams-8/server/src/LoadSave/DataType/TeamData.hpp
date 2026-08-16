/*
** EPITECH PROJECT, 2026
** G-NWP-400-LIL-4-1-myteams-8
** File description:
** TeamData
*/

#ifndef TEAMDATA_HPP_
#define TEAMDATA_HPP_

#include <string>
#include <vector>

struct Team {
    std::string uuid;
    std::string name;
    std::string description;
    std::string creator_uuid;
};

class TeamData {
    public:
        TeamData();
        ~TeamData();

        bool saveTeams(const std::vector<Team> &teams, std::string _dirname);
        bool loadTeams(std::vector<Team> &teams, std::string _dirname);

    protected:
    private:
};

#endif /* !TEAMDATA_HPP_ */
