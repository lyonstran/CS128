#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "constants.hpp"
#include "group.hpp"

std::vector<Volunteer> volunteers;
std::vector<Group> group_of_volunteers;

bool Valid(const std::vector<Group>& group) {
    for (const Group& g : group) {
        if (g.GetAvgBuildingExp() < kMinAvgBuildingExp ||
            g.GetAvgStamina() < kMinAvgStamina ||
            g.GetReturningMembers() < kMinReturning) {
            return false;
        }
    }
    return true;
}

void SwappingFinal(std::vector<Group>& groupin) {
    size_t group_size = groupin.size();
    int firstgroupindex = rand() % group_size;
    int secondgroupindex;
    do {
        secondgroupindex = rand() % group_size;
    } while (firstgroupindex == secondgroupindex);

    Group& f_random_group = groupin[firstgroupindex];
    Group& s_random_group = groupin[secondgroupindex];
    Volunteer& first_random = f_random_group.GetRandomVolunteer();
    Volunteer& second_random = s_random_group.GetRandomVolunteer();
    std::swap(first_random, second_random);
}

int main(int /*argc*/, char* argv[]) {
    srand(time(nullptr));

    std::string input_file = argv[1];
    int number_of_volunteers = std::stoi(argv[2]);
    std::string output_file = argv[3];

    std::ifstream ifs(input_file);
    std::ofstream ofs(output_file);
    
    if (!ifs) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    volunteers.reserve(number_of_volunteers);
    for (int i = 0; i < number_of_volunteers; ++i) {
        int build_experience, stamina_bar;
        bool return_status;
        std::string volunteer_name;
        ifs >> volunteer_name >> build_experience >> stamina_bar >> return_status;
        volunteers.emplace_back(volunteer_name, build_experience, stamina_bar, return_status);
    }

    size_t num_groups = volunteers.size() / kSizeGroups;
    for (size_t i = 0; i < num_groups; ++i) {
        Group cur_group;
        for (size_t j = 0; j < kSizeGroups; ++j) {
            cur_group.AddVolunteer(volunteers[i * kSizeGroups + j]);
        }
        group_of_volunteers.push_back(cur_group);
    }

    unsigned int iterations = 0;
    while (iterations < kMaxIterations && !Valid(group_of_volunteers)) {
        SwappingFinal(group_of_volunteers);
        iterations++;
    }

    if (iterations == kMaxIterations) {
        std::cout << "No Groups Found" << std::endl;
    } else {
        for (const Group& g : group_of_volunteers) {
            ofs << g << std::endl;
        }
    }

    return 0;
}
