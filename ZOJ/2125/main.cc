// https://vjudge.net/problem/ZOJ-2125

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
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

#define ST_BITS 4
#define ST_MASK 15
#define QS_SIZE 600000

class Record
{
public:
    unsigned long long state;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int h = 6, w = 9;
unordered_map<unsigned long long, unsigned int> cnts[2];
char cells[7][10];

int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long gMask = 0;

inline void init(int start)
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].state = ((unsigned long long)1) << ((start - 1) * ST_BITS);

    qTail[act]++;
}

int main()
{
    gMask = ((unsigned long long)1) << (9 * ST_BITS);
    gMask -= 1;

    int start;
    while (scanf("%d", &start))
    {
        for (size_t col = 1; col <= 9; col++)
        {
            for (size_t row = 1; row <= 6; row++)
            {
                cin >> cells[row][col];
            }
        }

        // init
        init(start);


    }


    return 0;
}
