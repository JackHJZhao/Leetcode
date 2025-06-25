#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> presum_cnt; 
        presum_cnt[0] = 1;          // 前面等于0的一定有一个
        int ans = 0;
        int presum = 0;
        for (auto num : nums) {
            presum += num;
            int t = presum - k;     // 找到前缀和等于 t 的位置数，然后一直当当前为止，肯定等于k
            if (presum_cnt.find(t) != presum_cnt.end()) {
                ans += presum_cnt[t];
            }
            presum_cnt[presum]++;
        }
        return ans;
    }
};