// https://www.luogu.com.cn/problem/P1933

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define DEBUG   0
#define MAX_H   51
#define MAX_W   4
#define BITS    8
#define MASK    255 
#define MOD     11192869

#define getState(ST, POS) ((ST) >> ((POS) * BITS)) & MASK

#define setState(ST, POS, VAL)         \
    ST &= ~(((MASK)) << ((POS)*BITS)); \
    ST |= ((VAL)) << ((POS)*BITS);

char hall[MAX_H][MAX_W];
char path[155];

int h, w;

unordered_map<unsigned int, unsigned int> cnts[2]; // key - state, value - count
int act = 0;                                       // 当前生效的 map

vector<int> idxes[8];

int main()
{
    cin >> w >> h;

    for (size_t i = 1; i <= h; i++)
    {
        for (size_t j = 1; j <= w; j++)
        {
            int t;
            cin >> t;

            hall[j][i] = t;
        }
    }

    int flag = 0;
    for (size_t i = 1; i <= w * h; i++)
    {
        int l;
        cin >> l;

        path[i] = l;

        flag <<= 1;
        flag &= 7;
        flag |= l;

        if (3 <= i)
        {
            idxes[flag].push_back(i - 1);
        }
    }



    return 0;
}