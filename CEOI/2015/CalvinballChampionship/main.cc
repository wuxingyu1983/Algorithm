// https://www.luogu.com.cn/problem/P4798

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
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

const int maxN = 10001;
const int mod = 1000007;

int maxT[maxN];

int main()
{
    int n;
    cin >> n;

    vector<int> tms;
    for (size_t i = 0; i < n; i++)
    {
        int t;
        cin >> t;

        tms.push_back(t);

        if (0 == i)
        {
            maxT[i] = t;
        }
        else
        {
            if (maxT[i - 1] < t)
            {
                maxT[i] = t;
            }
            else
            {
                maxT[i] = maxT[i - 1];
            }
        }
    }
   
    int ans = 0;

    cout << ans << endl;

    return 0;
}
