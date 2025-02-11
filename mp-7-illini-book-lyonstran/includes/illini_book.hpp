#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <utilities.hpp>
#include <queue>
#include <set>


class IlliniBook {  
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);

  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;

  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;

  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

private: 
  std::map<int, std::map<int, std::string>> adj_list_;
  //void BfsCountGroups(int i, std::map<int, bool>& visited) const;
  //void BfsCountGroupsRel(int i, std::map<int, bool> visited, const std::string& relationship) const;
  //void BfsCountGroupsLast(int i, std::map<int, bool> visited, const std::vector<std::string>& relationships) const;
  //bool checker(const std::string& relationship, const std::vector<std::string>& relationships) const;
  std::map<int, int> BreadthFirstSearch(int i, const std::string& relationship, bool checker) const;
  size_t GenCounter(const std::set<std::string>& check_relations) const;
};
#endif
