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
    int minNumberOfSemesters(int n, vector<vector<int>> &relations, int k)
    {
        // init
        pN = n;
        pK = k;
        memset(term, 0, sizeof(term));
        for (size_t i = 0; i < relations.size(); i++)
        {
            int parent = relations[i][0] - 1;
            int child = relations[i][1] - 1;

            parents[child].push_back(parent);
        }
        finalSt = (1 << n) - 1;

        int iRet = 0; // term - 1
        act = 0;
        term[act][0] = 1;

        while (true)
        {
            iRet++;
            for (size_t st = 0; st <= finalSt; st++)
            {
                if (term[act][st])
                {
                    if (proc(st, st, 0, 0))
                    {
                        goto END;
                    }
                }
            }
            memset(term[act], 0, sizeof(term[act]));
            act = 1 - act;
        }

    END:
        return iRet;
    }

private:
    int pN, pK;
    int act;
    int finalSt;
    vector<int> parents[15];
    char term[2][32768];

    bool proc(int st, int newSt, int start, int tmpK)
    {
        bool bRet = false;

        if (newSt == finalSt)
        {
            bRet = true;
        }
        else
        {
            if (start < pN && tmpK < pK)
            {
                // 不选该 start 课程
                bRet = proc(st, newSt, start + 1, tmpK);

                // 选该 start 课程
                if (false == bRet && 0 == ((1 << start) & newSt))
                {
                    bool flag = true;
                    for (vector<int>::iterator it = parents[start].begin(); it != parents[start].end(); it++)
                    {
                        if (0 == (st & (1 << *it)))
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        term[1 - act][newSt | (1 << start)] = 1;
                        bRet = proc(st, newSt | (1 << start), start + 1, tmpK + 1);
                    }
                }
            }
        }

        return bRet;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> vec;

    int parent, child;
    while (cin >> parent >> child)
    {
        vec.push_back(vector<int>{parent, child});
        if (cin.get() == '\n')
            break;
    }

    Solution s;
    cout << s.minNumberOfSemesters(n, vec, k) << endl;

    return 0;
}
