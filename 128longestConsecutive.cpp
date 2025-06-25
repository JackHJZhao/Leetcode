#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> nums_set;
        for (auto num : nums) {
            nums_set.insert(num);
        }
        int ans = 0;

        for (int num : nums_set) {
            if (!nums_set.count(num - 1)) {
                int cur_num = num;
                int count = 1;
                while(nums_set.count(cur_num + 1)) {
                    cur_num++;
                    count++;
                }
                ans = max(ans, count);
            }
        }
        return ans;
    }
};