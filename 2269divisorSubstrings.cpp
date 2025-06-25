#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = std::to_string(num);
        int ans = 0;
        long long n = 0;
        long long m = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (i < k) {
                m *= 10;
                n *= 10;
                n += (s[i] - '0');
            } else {
                if (n != 0 && num % n == 0) {
                    ans++;
                }
                n *= 10;
                n += (s[i] - '0');
                n %= m;
            }
        }    
        if (n != 0 && num % n == 0) {
            ++ans;
        }
        return ans;
    }
};


int main() {
    vector<pair<int, int>> test;
    test.push_back(pair<int, int>(240, 2));
    test.push_back(pair<int, int>(430043, 2));
    Solution s;
    for (int i = 0; i < test.size(); ++i) {
        std::cout << test[i].first << ' ' << test[i].second << '\t';
        std::cout << s.divisorSubstrings(test[i].first, test[i].second) << std::endl;
    }
}