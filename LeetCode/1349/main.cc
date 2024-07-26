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

class Solution
{
public:
    int maxStudents(vector<vector<char>> &seats)
    {
        int iRet = 0;

        m = seats.size();
        n = seats[0].size();

        int finalSt = (1 << n) - 1;

        init();

        dp[0][0] = 0;

        for (size_t row = 1; row <= m; row++)
        {
            for (size_t pre = 0; pre <= finalSt; pre++)
            {
                if (0 <= dp[row - 1][pre])
                {
                    for (size_t curr = 0; curr <= finalSt; curr++)
                    {
                        if (flags[pre][curr])
                        {
                            bool valid = true;

                            for (size_t col = 0; col < n; col++)
                            {
                                if ('#' == seats[row - 1][col] && (curr && (1 << col)))
                                {
                                    valid = false;
                                    break;
                                }
                            }

                            if (valid)
                            {
                                if (0 > dp[row][curr] || dp[row][curr] < (ones[curr] + dp[row - 1][pre]))
                                {
                                    dp[row][curr] = ones[curr] + dp[row - 1][pre];
                                    if (row == m && iRet < dp[row][curr])
                                    {
                                        iRet = dp[row][curr];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return iRet;
    }

private:
    unsigned char ones[256];
    unsigned char flags[256][256];
    int dp[9][256];
    int m, n;   // row, col

    void init()
    {
        memset(ones, 0, sizeof(ones));
        memset(flags, 1, sizeof(flags));
        memset(dp, -1, sizeof(dp));

        for (size_t st = 0; st < 256; st++)
        {
            for (size_t i = 0; i < 8; i++)
            {
                if (st & (1 << i))
                {
                    ones[st] ++;
                }
            }
        }

        for (size_t pre = 0; pre < 256; pre++)
        {
            for (size_t curr = 0; curr < 256; curr++)
            {
                for (size_t i = 0; i < 8; i++)
                {
                    if (curr & (1 << i))
                    {
                        if (0 < i && ((curr & (1 << (i - 1))) || (pre & (1 << (i - 1)))))
                        {
                            flags[pre][curr] = 0;
                            break;
                        }

                        if (7 > i && ((curr & (1 << (i + 1))) || (pre & (1 << (i + 1)))))
                        {
                            flags[pre][curr] = 0;
                            break;
                        }
                    }
                }
            }
        }
        
    }
};

int main()
{
    int m, n;       // row, col
    cin >> m >> n;

    char seat;
    vector<vector<char>> seats;

    for (size_t row = 0; row < m; row++)
    {
        seats.push_back(vector<char>());

        for (size_t col = 0; col < n; col++)
        {
            cin >> seat;
            seats[row].push_back(seat);
        }
    }

    Solution s;
    cout << s.maxStudents(seats) << endl;

    return 0;
}
