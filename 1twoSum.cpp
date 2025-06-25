#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            int t = target - nums[i];
            if (m.find(t) != m.end()) {
                return {i, m[t]};
            }
            m[nums[i]] = i;
        }
        return {0, 0};
    }
};