#include <vector>

class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        int max_num = 0;
        std::vector<int> backet(46, 0);
        while (lowLimit <= highLimit)
        {
            int sum = 0;
            int num = lowLimit;
            while (num)
            {
                sum += num % 10;
                num /= 10;
            }
            backet[sum]++;
            if (backet[sum] > max_num)
            {
                max_num = backet[sum];
            }
            lowLimit++;
        }
        return max_num;
    }
};
