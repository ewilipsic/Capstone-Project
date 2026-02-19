#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cstdint>

void yens(int n,
    std::vector<std::vector<int>>& adj,int source,int sink,int K,
    std::vector<int>& A,
    int& prev_cost,
    int& prev_spuridx,
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>>& B_queue,
    std::map<int,int>& B_spuridx,
    int& key,
    std::map<int,std::vector<int>>& B_paths);