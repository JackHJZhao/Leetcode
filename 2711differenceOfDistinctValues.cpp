#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));

        // 首先按照第一列的元素作为起点计算其左上角不同元素个数，再返回计算右下角，得到结果
        for (int t = m - 1; t >= 0; --t) {
            unordered_set<int> cnt;
            // 第一列，此时j都从0开始
            int i = t, j = 0;
            for ( ; i < m && j < n; ++i, ++j) {
                ans[i][j] = cnt.size();
                cnt.emplace(grid[i][j]);
            }

            --i;
            --j;            // 将i j 放在合法位置
            cnt = unordered_set<int>();         // 置空
            // 到达底部了，需要返回了，此时只需要 j >= 0 即可保证 i 的取值合法
            for ( ; j >= 0; --i, --j) {
                ans[i][j] = ans[i][j] > cnt.size() ? ans[i][j] - cnt.size() : cnt.size() - ans[i][j];
                cnt.emplace(grid[i][j]);    // 将当前值放入
            }
        }

        // 按照第一行，进行相同的操作

        for (int t = 1; t < n; ++t) {
            unordered_set<int> cnt;

            int i = 0, j = t;
            for (; i < m && j < n; ++i, ++j) {
                ans[i][j] = cnt.size();
                cnt.emplace(grid[i][j]);
            }
            --i;
            --j;            // 将i j 放在合法位置
            cnt = unordered_set<int>();         // 置空
            // 到达底部了，需要返回了，此时只需要 i >= 0 即可保证 i 的取值合法
            for ( ; i >= 0; --i, --j) {
                ans[i][j] = ans[i][j] > cnt.size() ? ans[i][j] - cnt.size() : cnt.size() - ans[i][j];
                cnt.emplace(grid[i][j]);    // 将当前值放入
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> grid = {{1,2,3},{3,1,5},{3,2,1}};
    Solution s;
    auto ans = s.differenceOfDistinctValues(grid);
    for (auto &r : ans) {
        for (auto c : r) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
}