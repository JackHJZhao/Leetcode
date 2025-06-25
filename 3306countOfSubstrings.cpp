#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    long long countOfSubstrings(string s, int k) {
        long long ans = 0;
        int n = s.size();
        int aeiou_mask = (1 << ('a' - 'a')) + (1 << ('e' - 'a')) + (1 << ('i' - 'a')) + (1 << ('o' - 'a')) + (1 << ('u' - 'a'));
        int mask = 0;
        vector<int> aeiou_last(26, -1);
        int j = 0;          // 从 j 开始，包括j位置
        int i = 0;
        int t = 0;
        int cur_k = 0;
        for (; i < n; ++i) {
            int idx = (s[i] - 'a');
            if ((aeiou_mask >> idx) & 0x01) {
                // 元音
                aeiou_last[idx] = i;
                mask |= (1 << idx);
                if (cur_k == k && mask == aeiou_mask) {
                    // k 个辅音，且包含所有的五个元音
                    t = std::max(t, j);
                    for ( ; t < i; ++t) {
                        int index = (s[t] - 'a');
                        if (aeiou_last[index] == t || ((aeiou_mask >> index) & 0x01) == 0) {
                            // 辅音，或者最后一个元音，退出
                            break;
                        }
                    }
                    ans += (t - j + 1);
                }
            } else {
                cur_k++;        // 辅音数量+1
                if (cur_k > k) {
                    // 大于k个，此时绝对只多于一个
                    for ( ; j <= i; ++j) {
                        int index = (s[j] - 'a');
                        if (((aeiou_mask >> index) & 0x01) == 0) {
                            // 遇到第一个辅音，以下一个位置开始
                            ++j;
                            --cur_k;
                            break;
                        }
                        if (aeiou_last[index] == j) {
                            // 这个位置，说明后面的位置肯定没有这个元音了
                            mask &= (~ (1 << index));
                            aeiou_last[index] = -1;
                        }
                    }
                }
                if (cur_k == k && mask == aeiou_mask) {
                    // 刚好 k 个辅音
                    t = std::max(t, j);
                    for (; t < i; ++t) {
                        int index = (s[t] - 'a');
                        if (aeiou_last[index] == t || ((aeiou_mask >> index) & 0x01) == 0) {
                            // 辅音，或者最后一个元音，退出
                            break;
                        }
                    }
                    ans += (t - j + 1);
                }
            }
        }
        return ans;
    }
};

int main() {
    string s = "ieaouqqieaouqq";
    int k = 1;
    Solution so;
    cout << so.countOfSubstrings(s, k) << endl;
    return 0;
}