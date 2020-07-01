#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    set<int> ss;

    int smallestRepunitDivByK(int K) {
        if (0 == K % 2)
        {
            return -1;
        }

        int m = 1;
        int len = 1;
        while (true)
        {
            if (0 == m % K)
            {
                return len;
            }

            if (ss.end() != ss.find(m % K))
            {
                return -1;
            }

            ss.insert(m % K);
            m = (10 * m + 1) % K;
            len ++;
        }
    }
};

int main()
{
    int n;
    cin >> n;

    Solution s;
    cout << s.smallestRepunitDivByK(n) << endl;

    return 0;
}
