#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int m = s.size(), n = p.size();
        if (m < n) {
            return vector<int>();
        }
        vector<int> pchar(26, 0);
        for (auto c : p) {
            pchar[c - 'a']++;
        }

        vector<int> schar(26, 0);
        for (int i = 0; i < n; ++i) {
            schar[s[i] - 'a']++;
        }

        vector<int> ans;
        int i = n;
        do {
            if (schar == pchar) {
                ans.emplace_back(i - n);
            }
            if (i == m) {
                break;
            }
            schar[s[i-n] - 'a']--;
            schar[s[i] - 'a']++;
            ++i;
        } while(true);
        return ans;
    }
};