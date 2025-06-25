#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        vector<int> last_index(128, -1);
        int ans = 0;
        int j = -1;
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            j = std::max(j, last_index[c]);
            ans = std::max(ans, i - j);
            last_index[c] = i;
        } 
        return ans;
    }
};

int main() {
    Solution s;
    string ss = "abcabcbb";
    cout << s.lengthOfLongestSubstring(ss) << endl;
    return 0;
}