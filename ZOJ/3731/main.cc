// https://pintia.cn/problem-sets/91827364500/exam/problems/91827369576?type=7&page=27

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

#define DEBUG   0
#define MAX_H   21
#define MAX_W   11
#define QS_SIZE 60000
#define ST_BITS 2
#define ST_MASK 3

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)                           \
    NEW = OLD;                                                  \
    NEW &= ~(((unsigned long long)ST_MASK) << ((POS)*ST_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST_BITS);

int h, w;
char cells[MAX_H][MAX_W];
int first_start, first_end;
int last_start, last_end;
int ans;

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    int sum;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

inline void init()
{
    ans = -1;

    first_start = last_start = 1;
    first_end = last_end = w;

    for (size_t col = 1; col <= w; col++)
    {
        if ('W' == cells[1][col])
        {
            first_start = col + 1;
        }
        
        if ('W' == cells[h][col])
        {
            last_start = col + 1;
        }
    }

    for (size_t col = w; col >= 1; col--)
    {
        if ('L' == cells[1][col])
        {
            first_end = col - 1;
        }

        if ('L' == cells[h][col])
        {
            last_end = col - 1;
        }
    }

    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();
}

int main()
{
    while (true)
    {
        cin >> h >> w;

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }

        init();

        if (first_start <= first_end && last_start <= last_end)
        {
            for (size_t col = first_start; col <= first_end; col++)
            {
                if ('#' != cells[1][col])
                {
                    unsigned int st = 0;

                    setVal4St(st, st, (col - 1), 3);

                    qs[act][qTail[act]].state = st;
                    qs[act][qTail[act]].sum = cells[1][col] - '0';

                    qTail[act]++;
                }
            }

            now_x = 1;
            now_y = w;

            while (0 < qTail[act])
            {
                int nAct = 1 - act;

                if (w == now_y)
                {
                    now_x++;
                    now_y = 1;

                    if (h < now_x)
                    {
                        // finished
                        break;
                    }
                }
                else
                {
                    now_y++;
                }

                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    unsigned int st = qs[act][iQ].state;
                    int sum = qs[act][iQ].sum;

                    if (1 == now_y)
                    {
                        st <<= ST_BITS;
                    }

                    
                }

                qTail[act] = 0;
                cnts[act].clear();
                act = nAct;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
