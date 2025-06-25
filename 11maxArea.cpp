#include <vector>
#include <iostream>
using namespace std;

class Solution {
    // 找到第一个大于等于target的标，如果没有返回nums的长度
    int lower_bound(int target, vector<int> &index, vector<int> &nums) {
        int ans = nums.size();
        int i = 0, j = index.size();
        while(i < j) {
            int mid = i + (j - i) / 2;
            if (nums[index[mid]] >= target) {
                ans = index[mid];
                j = mid;
            } else {
                i = mid + 1;
            }
        }
        return ans;
    }

public:
    int maxArea(vector<int>& height) {
        if (height.size() == 2) {
            return std::min(height[0], height[1]);
        }
        vector<int> left;           // 递增的序列
        left.emplace_back(0);
        for (int i = 1; i < height.size(); ++i) {
            if (height[i] > height[left.back()]) {
                left.emplace_back(i);
            }
        }
        int ans = 0;
        vector<int> right;
        right.emplace_back(height.size() - 1);
        for (int i = height.size() - 1; i >= 0; --i) {
            // 在left中找到第一个大于等于height[i]的
            int left_index = lower_bound(height[i], left, height);
            int right_index = lower_bound(height[i], right, height);
            left_index = std::min(left_index, i);
            if (right_index == height.size()) {
                right_index = i;
            }
            ans = std::max(ans, (right_index - left_index) * height[i]);
            if (height[i] > height[right.back()]) {
                right.emplace_back(i);
            }
        }
        return ans;
    }

    int maxArea(vector<int> &nums) {
        int i = 0, j = nums.size() - 1;
        int ans = 0;
        while (i < j)
        {
            ans = std::max(ans, std::min(nums[i], nums[j]) * (j - i));
            if (nums[i] < nums[j]) {
                ++i;
            } else {
                --j;
            }
        }
        return ans; 
    }
};

int main() {
    vector<int> nums = {8,7,2,1};
    Solution s;
    std::cout << s.maxArea(nums) << std::endl;
}