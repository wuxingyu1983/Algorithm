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
#include <unordered_map>
#include <bitset>

using namespace std;

class Solution
{
public:
    int numberOfBeautifulIntegers(int low, int high, int k)
    {
        int ret = 0;

        ret = getNumOfBeautyInt(high, k) - getNumOfBeautyInt(low - 1, k);

        return ret;
    }

private:
    int edp[9][20][11];     // even 偶数
    int odp[9][20][11];     // odd 奇数

    int getNumOfBeautyInt(const int num, const int k)
    {
        int ret = 0;

        if (10 <= num)
        {
            string strNum = to_string(num);
            int digit = strNum.length();        // 位数

            memset(edp, 0, sizeof(edp));
            memset(odp, 0, sizeof(odp));

            for (size_t n = 0; n < 10; n++)
            {
                if (n % 2)
                {
                    // odd
                    odp[0][n % k][1] ++;
                }
                else
                {
                    // even
                    edp[0][n % k][1] ++;
                }
            }

            for (size_t d = 1; d < digit - 1; d++)
            {
                int tmp = pow(10, d);
                for (int n = 9; n >= 0; n--)
                {
                    if (0 == n)
                    {
                        ret += edp[d][0][0] + odp[d][0][0];
                    }

                    int newM = n * tmp % k;

                    for (size_t iK = 0; iK < k; iK++)
                    {
                        for (size_t offset = 0; offset < 10; offset++)
                        {
                            if (edp[d - 1][iK][offset])
                            {
                                if (n % 2)
                                {
                                    // odd
                                    if (0 == offset)
                                    {
                                        odp[d][(iK + newM) % k][1] += edp[d - 1][iK][offset];
                                    }
                                    else
                                    {
                                        edp[d][(iK + newM) % k][offset - 1] += edp[d - 1][iK][offset];
                                    }
                                }
                                else
                                {
                                    // even
                                    edp[d][(iK + newM) % k][offset + 1] += edp[d - 1][iK][offset];
                                }
                            }

                            if (odp[d - 1][iK][offset])
                            {
                                if (n % 2)
                                {
                                    // odd
                                    odp[d][(iK + newM) % k][offset + 1] += odp[d - 1][iK][offset];
                                }
                                else
                                {
                                    // even
                                    if (0 == offset)
                                    {
                                        edp[d][(iK + newM) % k][1] += odp[d - 1][iK][offset];
                                    }
                                    else
                                    {
                                        odp[d][(iK + newM) % k][offset - 1] += odp[d - 1][iK][offset];
                                    }
                                }
                            }
                        }
                    }
                }

                
                
            }
             

        }

        return ret;
    }
};

int main()
{
    int low, high, k;
    cin >> low >> high >> k;

    Solution s;
    cout << s.numberOfBeautifulIntegers(low, high, k);

    return 0;
}