// https://atcoder.jp/contests/arc087/tasks/arc087_b

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
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

bitset<16001> hdp;
bitset<16001> vdp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int x, y;
    cin >> x >> y;

    hdp[8000] = 1;
    vdp[8000] = 1;

    int step = 0;
    int dir = -1;    // -1 - init, 0 - h, 1 - v
    for (int i = 0; i < s.length(); i++)
    {
        if ('T' == s.at(i))
        {
            if (0 < step)
            {
                if (-1 == dir)
                {
                    hdp = hdp << step;
                }
                else if (0 == dir)
                {
                    hdp = (hdp >> step) | (hdp << step);
                }
                else
                {
                    vdp = (vdp >> step) | (vdp << step);
                }
            }

            step = 0;
            if (1 == dir)
            {
                dir = 0;
            }
            else
            {
                dir = 1;
            }
        }
        else
        {
            step ++;
        }
    }

    if (0 < step)
    {
        if (-1 == dir)
        {
            hdp = hdp << step;
        }
        else if (0 == dir)
        {
            hdp = (hdp >> step) | (hdp << step);
        }
        else
        {
            vdp = (vdp >> step) | (vdp << step);
        }
    }

    if (hdp[8000 + x] && vdp[8000 + y])
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }

    return 0;
}
