#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    // position[0] 一定能放置一个球
    // 证明：假设position[0]不放置球，只在position[1]~position[n-1]放置m个球
    // 那么，将position[1]~position[n-1]中放置的第一个球，移动到position[0]，一定不会是结果变差
    // 所以在position[0] 一定能放置一个球
    bool check(vector<int>& position, int m, int mid) {
        int n = position.size();
        int pre = position[0];
        --m;
        for (int i = 1; i < n; ++i) {
            if (m == 0) {
                return true;
            }
            if (position[i] - pre >= mid) {
                --m;
                pre = position[i];
            }
        }
        return m == 0;      // 剩下的球的个数为0时，说明一定能放下
    }
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int left = 1, right = position.back() - position[0];
        int ans = 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            // 判断是否相隔mid可以成功放下m个气球
            if (check(position, m, mid)) {
                left = mid + 1;
                ans = mid;
            } else {
                // 不能放下
                right = mid - 1;
            }
        }
        return ans;
    }
};