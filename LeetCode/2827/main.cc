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

    int fucnRec(const int num, const int idx, const int k, bool limit)
    {
        int ret = 0;
        string strNum = to_string(num);

        memset(edp[idx], 0, sizeof(int) * 20 * 11);
        memset(odp[idx], 0, sizeof(int) * 20 * 11);

        if (true == limit)
        {
            int start = 0, end = strNum.at(idx) - '0', n;

            if (0 == idx)
            {
                start = 1;    

                for (n = start; n < end; n++)
                {
                    int newM = n * pow(10, strNum.length() - 1 - idx);
                    newM %= k;

                    if (n % 2)
                    {
                        // odd
                        odp[idx][newM][1]++;
                    }
                    else
                    {
                        // even
                        edp[idx][newM][1]++;
                    }
                }

                if (idx == (strNum.length() - 1))
                    ret = edp[idx][0][0] + odp[idx][0][0];
                else
                    ret = fucnRec(num, idx + 1, k, false);

                // 处理边界
                {
                    memset(edp[idx], 0, sizeof(int) * 20 * 11);
                    memset(odp[idx], 0, sizeof(int) * 20 * 11);

                    int newM = n * pow(10, strNum.length() - 1 - idx);
                    newM %= k;

                    if (n % 2)
                    {
                        // odd
                        odp[idx][newM][1]++;
                    }
                    else
                    {
                        // even
                        edp[idx][newM][1]++;
                    }

                    if (idx == (strNum.length() - 1))
                        ret += edp[idx][0][0] + odp[idx][0][0];
                    else
                        ret += fucnRec(num, idx + 1, k, true);
                }
            }
            else
            {
                for (n = start; n < end; n++)
                {
                    int newM = n * pow(10, strNum.length() - 1 - idx);
                    newM %= k;

                    for (size_t iK = 0; iK < k; iK++)
                    {
                        for (size_t offset = 0; offset < strNum.length(); offset++)
                        {
                            if (edp[idx - 1][iK][offset])
                            {
                                if (n % 2)
                                {
                                    // odd
                                    if (0 == offset)
                                    {
                                        odp[idx][(iK + newM) % k][1] += edp[idx - 1][iK][offset];
                                    }
                                    else
                                    {
                                        edp[idx][(iK + newM) % k][offset - 1] += edp[idx - 1][iK][offset];
                                    }
                                }
                                else
                                {
                                    // even
                                    edp[idx][(iK + newM) % k][offset + 1] += edp[idx - 1][iK][offset];
                                }
                            }

                            if (odp[idx - 1][iK][offset])
                            {
                                if (n % 2)
                                {
                                    // odd
                                    odp[idx][(iK + newM) % k][offset + 1] += odp[idx - 1][iK][offset];
                                }
                                else
                                {
                                    // even
                                    if (0 == offset)
                                    {
                                        edp[idx][(iK + newM) % k][1] += odp[idx - 1][iK][offset];
                                    }
                                    else
                                    {
                                        odp[idx][(iK + newM) % k][offset - 1] += odp[idx - 1][iK][offset];
                                    }
                                }
                            }
                        }
                    }
                }

                if (idx == (strNum.length() - 1))
                    ret = edp[idx][0][0] + odp[idx][0][0];
                else
                    ret = fucnRec(num, idx + 1, k, false);

                // 处理边界
                {
                    memset(edp[idx], 0, sizeof(int) * 20 * 11);
                    memset(odp[idx], 0, sizeof(int) * 20 * 11);

                    int newM = n * pow(10, strNum.length() - 1 - idx);
                    newM %= k;

                    for (size_t iK = 0; iK < k; iK++)
                    {
                        for (size_t offset = 0; offset < strNum.length(); offset++)
                        {
                            if (edp[idx - 1][iK][offset])
                            {
                                if (n % 2)
                                {
                                    // odd
                                    if (0 == offset)
                                    {
                                        odp[idx][(iK + newM) % k][1] += edp[idx - 1][iK][offset];
                                    }
                                    else
                                    {
                                        edp[idx][(iK + newM) % k][offset - 1] += edp[idx - 1][iK][offset];
                                    }
                                }
                                else
                                {
                                    // even
                                    edp[idx][(iK + newM) % k][offset + 1] += edp[idx - 1][iK][offset];
                                }
                            }

                            if (odp[idx - 1][iK][offset])
                            {
                                if (n % 2)
                                {
                                    // odd
                                    odp[idx][(iK + newM) % k][offset + 1] += odp[idx - 1][iK][offset];
                                }
                                else
                                {
                                    // even
                                    if (0 == offset)
                                    {
                                        edp[idx][(iK + newM) % k][1] += odp[idx - 1][iK][offset];
                                    }
                                    else
                                    {
                                        odp[idx][(iK + newM) % k][offset - 1] += odp[idx - 1][iK][offset];
                                    }
                                }
                            }
                        }
                    }

                    if (idx == (strNum.length() - 1))
                        ret += edp[idx][0][0] + odp[idx][0][0];
                    else
                        ret += fucnRec(num, idx + 1, k, true);
                }
            }
        }
        else
        {
            int start = 0, end = 9;
            for (size_t n = start; n <= end; n++)
            {
                int newM = n * pow(10, strNum.length() - 1 - idx);
                newM %= k;

                for (size_t iK = 0; iK < k; iK++)
                {
                    for (size_t offset = 0; offset < strNum.length(); offset++)
                    {
                        if (edp[idx - 1][iK][offset])
                        {
                            if (n % 2)
                            {
                                // odd
                                if (0 == offset)
                                {
                                    odp[idx][(iK + newM) % k][1] += edp[idx - 1][iK][offset];
                                }
                                else
                                {
                                    edp[idx][(iK + newM) % k][offset - 1] += edp[idx - 1][iK][offset];
                                }
                            }
                            else
                            {
                                // even
                                edp[idx][(iK + newM) % k][offset + 1] += edp[idx - 1][iK][offset];
                            }
                        }

                        if (odp[idx - 1][iK][offset])
                        {
                            if (n % 2)
                            {
                                // odd
                                odp[idx][(iK + newM) % k][offset + 1] += odp[idx - 1][iK][offset];
                            }
                            else
                            {
                                // even
                                if (0 == offset)
                                {
                                    edp[idx][(iK + newM) % k][1] += odp[idx - 1][iK][offset];
                                }
                                else
                                {
                                    odp[idx][(iK + newM) % k][offset - 1] += odp[idx - 1][iK][offset];
                                }
                            }
                        }
                    }
                }
            }

            if (idx == (strNum.length() - 1))
                ret = edp[idx][0][0] + odp[idx][0][0];
            else
                ret = fucnRec(num, idx + 1, k, false);
        }

        return ret;
    }

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

            ret += fucnRec(num, 0, k, true);
        }

        return ret;
    }
};

int main()
{
    int low, high, k;
    cin >> low >> high >> k;

    Solution s;
    cout << s.numberOfBeautifulIntegers(low, high, k) << endl;

    return 0;
}