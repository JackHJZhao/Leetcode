#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class RangeFreqQuery {
    unordered_map<int, vector<int>> index;
public:
    RangeFreqQuery(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n; ++i) {
            index[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int value) {
        auto &pos = index[value];
        // 找到第一个大于等于left的元素的位置
        auto it1 = lower_bound(pos.begin(), pos.end(), left);
        if (it1 == pos.end()) {
            // 在这个区间内没有任何元素等于value
            return 0;
        }
        // 找到第一个大于right的元素位置
        auto it2 = upper_bound(pos.begin(), pos.end(), right);
        return it2 - it1;
    }
};
