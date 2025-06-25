#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int j = i + 1;
            while(j < n) {
                int target = nums[i] + nums[j];
                // 由于 nums 是单调递增的，所以target必然要小于等于0时，才可能使得三元组为0
                if (target <= 0) {
                    int k = std::lower_bound(nums.begin() + j + 1, nums.end(), -target) - nums.begin(); 
                    if (k < n && nums[k] == -target) {
                        ans.emplace_back(vector<int>{nums[i], nums[j], nums[k]});
                    }
                }
                ++j;
                while (j < n && nums[j] == nums[j-1]) {
                    ++j;
                }
            }
        }
        return ans;
    }

    vector<vector<int>> threeSum_pointer(vector<int>& nums) {
        vector<vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int k = 0; k < n; ++k) {
            if (k > 0 && nums[k] == nums[k-1]) {
                continue;
            }
            int i = k + 1, j = n - 1;
            int target = -nums[k];
            while (i < j)
            {
                int sum = nums[i] + nums[j];
                if (sum == target) {
                    ans.emplace_back(vector<int>{nums[k], nums[i], nums[j]});
                    ++i;
                    --j;
                    while(i < j && nums[i] == nums[i-1]) {
                        ++i;
                    }
                    while(i < j && nums[j] == nums[j+1]) {
                        --j;
                    }
                } else if (sum > target) {
                    --j;
                } else {
                    ++i;
                }
            } 
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {-1,0,1,2,-1,-4};
    Solution s;
    auto ans = s.threeSum_pointer(nums);
    for (auto &one : ans) {
        std::cout << one[0] << ' ' << one[1] << ' ' << one[2] << endl;
    }
    return 0;
}