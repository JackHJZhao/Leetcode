#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Solution {
public:
    int trap(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        vector<int> right(n);
        stack<int> stk;
        right[n-1] = n;           // n - 1右边第一个比他大的是n位置 
        stk.push(n-1);
        for (int i = n - 2; i >= 0; --i) {
            while(!stk.empty() && nums[stk.top()] <= nums[i]) {
                // 此时肯定选择i位置作为第一个比左边大的位置
                stk.pop();
            }
            if (stk.empty()) {
                // 没有比他大的了
                right[i] = n;
            } else {
                right[i] = stk.top();
            }
            stk.push(i);
        }

        auto &left = stk;
        left = stack<int>();
        for (int i = 0; i < n; ++i) {
            while(!left.empty() && nums[left.top()] < nums[i]) {
                left.pop();
            }
            if (left.empty() || nums[left.top()] == nums[i]) {
                // 左边没有比 i 位置更高的了
                // 当相同时，说明以这个为最低位的已经考虑过了
                left.push(i);
            } else {
                // 找出右边第一个比他大的位置
                if (right[i] < n) {
                    ans += (min(nums[left.top()], nums[right[i]]) - nums[i]) * (right[i] - left.top() - 1);
                }
                left.push(i);
            }
        }
        return ans;
    }

    int trapdp(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        vector<int> leftMax(n);
        leftMax[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = std::max(nums[i], leftMax[i-1]);
        }
        int rightMax = nums[n-1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax = std::max(rightMax, nums[i]);
            ans += (std::min(leftMax[i], rightMax) - nums[i]);
        }
        return ans;
    }
 
    int trapstk(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        stack<int> stk;
        stk.push(0);
        for(int i = 1; i < n; ++i) {
            while(!stk.empty() && nums[stk.top()] < nums[i]) {
                int top = stk.top();
                stk.pop();
                if(stk.empty()) {
                    break;
                }
                int left = stk.top();
                ans += (std::min(nums[left], nums[i]) - nums[top]) * (i - left - 1);
            }
            stk.push(i);
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {5,2,1,2,1,5};
    Solution s;
    cout << s.trapstk(nums) << endl;
    return 0;
}