#include <iostream>
#include "group.hpp"
#include "volunteer.hpp"
#include <cstdlib>


void Group::AddVolunteer(const Volunteer& vol) {
    group_of_volunteers_.push_back(vol);
}



double Group::GetAvgBuildingExp() const {
    double avg_build_exp = 0.0;
    if (group_of_volunteers_.empty()) {
        return avg_build_exp;
     }
    for (const Volunteer& cur_person : group_of_volunteers_) {
      avg_build_exp += cur_person.GetBuildingExperience();
        
    }
    avg_build_exp = avg_build_exp / static_cast<double>(group_of_volunteers_.size());
    return avg_build_exp;
}


int Group::GetReturningMembers() const {
    int returning_mem = 0;
    for (const Volunteer& cur_person : group_of_volunteers_) {
        if (cur_person.IsReturning()) {
            returning_mem++;
        }
    }
    return returning_mem;
}


double Group::GetAvgStamina() const {
    double avg_stam = 0.0;
    if (group_of_volunteers_.empty()) {
        return avg_stam;
    }
    for (const Volunteer& cur_person : group_of_volunteers_) {
        avg_stam += cur_person.GetPhysicalStamina();
    }
    avg_stam = avg_stam / static_cast<double>(group_of_volunteers_.size());
    return avg_stam;
}


Volunteer& Group::GetRandomVolunteer() {
    return group_of_volunteers_[rand() % group_of_volunteers_.size()];
}

std::ostream& operator<<(std::ostream& os, const Group& g_in) {
    os << "Avg. EXP -> Build: " << g_in.GetAvgBuildingExp() << ", ";
    os << "Stamina: " << g_in.GetAvgStamina() << ". ";
    os << "Number of returning members: " << g_in.GetReturningMembers() << std::endl;
    for (const Volunteer& volunteer_name : g_in.group_of_volunteers_) {
        os << volunteer_name.GetName() << std::endl;
    }
    return os;
}

