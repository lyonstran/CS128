#ifndef GROUP_HPP
#define GROUP_HPP

#include <ostream>
#include <vector>
#include "volunteer.hpp"

class Group {
public:
  void AddVolunteer(const Volunteer& vol);

  // void SetAvgBuildingExp();
  double GetAvgBuildingExp() const;

  // void SetReturningMembers();
  int GetReturningMembers() const;

  // void SetAvgStamina();
  double GetAvgStamina() const;

  friend std::ostream& operator<<(std::ostream& os, const Group& g_in);

  Volunteer& GetRandomVolunteer();

private:
  //TODO create private member variable(s)
  std::vector<Volunteer> group_of_volunteers_;
  // double AvgStam_;
  // double AvgBuildExp_;
  // int total_returning_members_;

};

std::ostream& operator<<(std::ostream& os, const Group& g_in);

#endif
