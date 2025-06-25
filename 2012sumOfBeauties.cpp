#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        vector<int> right(n, 0);    // right[i] 表示从 [i, n-1] 的最小值
        right[n-1] = nums[n-1];
        for (int i = n - 2; i >= 0; --i) {
            right[i] = std::min(nums[i], right[i+1]);
        }

        --n;
        int pre_max = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > pre_max && nums[i] < right[i+1]) {
                ans += 2;
            } else if (nums[i] > nums[i-1] && nums[i] < nums[i+1]) {
                ++ans;
            }
            pre_max = std::max(pre_max, nums[i]);
        }
        return ans;
    }

    // 单调栈法
    int sumOfBeautiesStack(vector<int>& nums) {
        stack<int> stk;
        int n = nums.size();
        int ans = 0;
        int pre_max = nums[0];
        for (int i = 1; i < n; ++i) {
            while(!stk.empty() && nums[stk.top()] >= nums[i]) {
                int j = stk.top();
                if (nums[j - 1] < nums[j] && nums[j] < nums[j+1]) {
                    ans++;
                }
                stk.pop();
            }
            if (nums[i] > pre_max) {
                pre_max = nums[i];
                stk.push(i);
            } else {
                if (nums[i-1] < nums[i] && nums[i] < nums[i+1]) {
                    ans++;
                }
            }
        }
        ans += stk.size() * 2;
        if (!stk.empty() && stk.top() == n - 1) {
            ans -= 2;
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {6,8,3,7,8,9,4,8};
    Solution s;
    cout << s.sumOfBeautiesStack(nums) << endl;
}