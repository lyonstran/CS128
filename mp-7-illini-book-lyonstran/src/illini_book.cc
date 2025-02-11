#include "illini_book.hpp"

// Your code here!
IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream f_people(people_fpath);
    std::ifstream relationships_file(relations_fpath);
    int uin = 0;
    while (f_people >> uin) {
        adj_list_[uin] = std::map<int, std::string>();
    }
    int f_uin = 0;
    int s_uin = 0;
    char comma = ',';
    std::string relationship;
    while (relationships_file >> f_uin >> comma >> s_uin >> comma >> relationship) {
        adj_list_[f_uin][s_uin] = relationship;
        adj_list_[s_uin][f_uin] = relationship;
    }
}   

std::map<int, int> IlliniBook::BreadthFirstSearch(int i, const std::string& relationship, bool checker) const {
    std::queue<int> q;
    std::map<int, int> dist;
    std::map<int, bool> visited;
    q.push(i);
    visited[i] = true;
    dist[i] = 0;
    while (!(q.empty())) {
        int c = q.front();
        q.pop();
        for (const auto& neighbor : adj_list_.at(c)) {
            if ((!visited[neighbor.first]) && (!checker || neighbor.second == relationship)) {
                visited[neighbor.first] = true;
                q.push(neighbor.first);
                dist[neighbor.first] = dist[c] + 1;
            }
        }
    }
    return dist;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    // std::queue<int> q;
    // std::map<int, bool> visited;
    // q.push(uin_1);
    // visited[uin_1] = true;
    // while (!(q.empty())) {
    //     int cur = q.front();
    //     if (cur == uin_2) {
    //         return true;
    //     }
    //     for (const auto& neighbor : adj_list_.at(cur)) {
    //         if (!(visited[neighbor.first])) {
    //             q.push(neighbor.first);
    //             visited[neighbor.first] = true;
    //         }
    //     }
    // }
    // return false;
    std::map<int, int> d = BreadthFirstSearch(uin_1, "", false);
    return d.find(uin_2) != d.end();
}
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    // std::queue<int> q;
    // std::map<int, bool> visited;
    // q.push(uin_1);
    // visited[uin_1] = true;
    // while (!(q.empty())) {
    //     int cur = q.front();
    //     q.pop();
    //     if (cur == uin_2) {
    //         return true;
    //     }
    //     for (const auto& neighbor : adj_list_.at(cur)) {
    //         if (!(visited[neighbor.first] && neighbor.second == relationship)) {
    //             q.push(neighbor.first);
    //             visited[uin_1] = true;
    //         }
    //     }
    // }
    // return false;
    std::map<int, int> d = BreadthFirstSearch(uin_1, relationship, true);
    return d.find(uin_2) != d.end();
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    // std::queue<int> q;
    // std::map<int, int> dist;
    // q.push(uin_1);
    // dist[uin_1] = 0;
    // std::map<int, bool> visited;
    // visited[uin_1] = true;

    // while (!(q.empty())) {
    //     int cur = q.front();
    //     q.pop();
    //     if (cur == uin_2) {
    //         return dist[cur];
    //     }
    //     for (const auto& neighbor : adj_list_.at(cur)) {
    //         if (!(visited[neighbor.first])) {
    //             visited[neighbor.first] = true;
    //             q.push(neighbor.first);
    //             dist[neighbor.first] = dist[cur] + 1;
    //         }
    //     }
    // }
    // return -1;
    std::map<int, int> d = BreadthFirstSearch(uin_1, "", false);
    auto m = d.find(uin_2);
    if (m != d.end()) {
        return m->second;
    }
    return -1;
   
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    // std::queue<int> q;
    // std::map<int, int> dist;
    // q.push(uin_1);
    // dist[uin_1] = 0;
    // std::map<int, bool> visited;
    // visited[uin_1] = true;

    // while (!(q.empty())) {
    //     int cur = q.front();
    //     q.pop();
    //     if (cur == uin_2) {
    //         return dist[uin_2];
    //     }
    //     for (const auto& neighbor : adj_list_.at(cur)) {
    //         if (!(visited[neighbor.first] && neighbor.second == relationship)) {
    //             visited[neighbor.first] = true;
    //             q.push(neighbor.first);
    //             dist[neighbor.first] = dist[cur] + 1;
    //         }
    //     }
    // }
    // return -1;
    std::map<int, int> d = BreadthFirstSearch(uin_1, relationship, true);
    auto m = d.find(uin_2);
    if (m != d.end()) {
        return m->second;
    }
    return -1;
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    // std::queue<int> q;
    // std::map<int, int> dist;
    // std::vector<int> result;

    // if (adj_list_.find(uin) == adj_list_.end()) {
    //     return result;
    // }
    // q.push(uin);
    // dist[uin] = 0;
    // while (!(q.empty())) {
    //     int cur = q.front();
    //     q.pop();
    //     for (const auto& neighbor : adj_list_.at(cur)) {
    //         if (dist.find(neighbor.first) == dist.end()) {
    //             dist[neighbor.first] = dist[cur] + 1;
    //             q.push(neighbor.first);
    //             if (dist[neighbor.first] == n) {
    //                 result.push_back(neighbor.first);
    //             }
    //         }
    //     }
    // }
    // return result;
    std::map<int, int> d = BreadthFirstSearch(uin, "", false);
    std::vector<int> returning; 
    for (const auto& p : d) {
        if (p.second == n) {
            returning.push_back(p.first);
        }
    }
    return returning;
}
// void IlliniBook::BfsCountGroups(int i, std::map<int, bool>& visited) const {
//     std::queue<int> q;
//     q.push(i);
//     visited[i] = true;
//     while (!(q.empty())) {
//         int c = q.front();
//         q.pop();
//         for (const auto& neighbor : adj_list_.at(c)) {
//             if (!(visited[neighbor.first])) {
//                 visited[neighbor.first] = true;
//                 q.push(neighbor.first);
//             }
//         }
//     }
// }
// void IlliniBook::BfsCountGroupsRel(int i, std::map<int, bool> visited, const std::string& relationship) const {
//     std::queue<int> q;
//     q.push(i);
//     visited[i] = true;
//     while (!(q.empty())) {
//         int c = q.front();
//         q.pop();
//         for (const auto& neighbor : adj_list_.at(c)) {
//             if (!(visited[neighbor.first] && neighbor.second == relationship)) {
//                 visited[neighbor.first] = true;
//                 q.push(neighbor.first);
//             }
//         }
//     }
// }

// void IlliniBook::BfsCountGroupsLast(int i, std::map<int, bool> visited, const std::vector<std::string>& relationships) const {
//     std::queue<int> q;
//     q.push(i);
//     visited[i] = true;
//     while(!(q.empty())) {
//         int c = q.front();
//         q.pop();
//         for (const auto& neighbor : adj_list_.at(c)) {
//             if (!(visited[neighbor.first] && checker(neighbor.second, relationships))) {
//                 visited[neighbor.first] = true;
//                 q.push(neighbor.first);
//             }
//         }
//     }
// }

// bool IlliniBook::checker(const std::string& relationship, const std::vector<std::string>& relationships) const {
//     for (const auto& r : relationships) {
//         if (relationship == r) {
//             return true;
//         }
//     }
//     return false;
// }
size_t IlliniBook::GenCounter(const std::set<std::string>& check_relations) const {
    std::map<int, bool> visited;
    size_t count = 0;
    for (const auto& n : adj_list_) {
        if (!visited[n.first]) {
            std::queue<int> q;
            q.push(n.first);
            visited[n.first] = true;
            while (!(q.empty())) {
                int c = q.front();
                q.pop();
                for (const auto& neighbor : adj_list_.at(c)) {
                    if (!visited[neighbor.first] && (check_relations.empty() || check_relations.find(neighbor.second) != check_relations.end())) {
                        visited[neighbor.first] = true;
                        q.push(neighbor.first);
                    }
                }
            }
            count++;
        }
    }
    return count;
}
size_t IlliniBook::CountGroups() const {
    // std::map<int, bool> visited;
    // size_t count = 0;
    // for (const auto& p : adj_list_) {
    //     if (!(visited[p.first])) {
    //         BfsCountGroups(p.first, visited);
    //         count++;
    //     }
    // }
    // return count;
    return GenCounter(std::set<std::string>());
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    // std::map<int, bool> visited;
    // size_t count = 0;
    // for (const auto& pair : adj_list_) {
    //     if (!(visited[pair.first])) {
    //         BfsCountGroupsRel(pair.first, visited, relationship);
    //     }
    // }
    // return count;
    return GenCounter(std::set<std::string>{relationship});
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    // std::map<int, bool> visited;
    // size_t count = 0;
    // for (const auto& p : adj_list_) {
    //     if (!(visited[p.first])) {
    //         BfsCountGroupsLast(p.first, visited, relationships);
    //         count++;
    //     }
    // }
    // return count;
    std::set<std::string> check_relation(relationships.begin(), relationships.end());
    return GenCounter(check_relation);
}