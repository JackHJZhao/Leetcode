#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, int> index_maps;
        for (auto s : strs) {
            string ss = s;
            std::sort(ss.begin(), ss.end());
            if (index_maps.find(ss) != index_maps.end()) {
                ans[index_maps[ss]].emplace_back(s);
            } else {
                ans.emplace_back(vector<string>{s});
                index_maps[ss] = ans.size() - 1;
            }
        }
        return ans;
    }
};