// https://vjudge.net/problem/HDU-3958
// https://acm.hdu.edu.cn/showproblem.php?pid=3958

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

#define DEBUG 0
#define MAX_W 10
#define MAX_H 21
#define ST1_BITS 2
#define ST1_MASK 3
#define ST2_BITS 1
#define ST2_MASK 1
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state1;   // 轮廓线段状态
    unsigned short state2; // 轮廓cells状态
    unsigned int len;
    char grid[MAX_H][MAX_W]; // 满足当前 state 状态下的 一组 可能的 grid

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St1(ST, POS) ((ST) >> ((POS)*ST1_BITS)) & ST1_MASK

#define setVal4St1(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST1_MASK << ((POS)*ST1_BITS)); \
    NEW |= (VAL) << ((POS)*ST1_BITS);

#define getVal4St2(ST, POS) ((ST) >> ((POS)*ST2_BITS)) & ST2_MASK

#define setVal4St2(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST2_MASK << ((POS)*ST2_BITS)); \
    NEW |= (VAL) << ((POS)*ST2_BITS);

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    now_x = 0;
    now_y = w;

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].len = 1;

    qTail[act]++;
}

int main()
{
    int t;
    cin >> t;

    int sx, sy, tx, ty;

    while (t --)
    {
        cin >> h >> w;

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];

                if ('S' == cells[row][col])
                {
                    sx = row;
                    sy = col;
                }

                if ('T' == cells[row][col])
                {
                    tx = row;
                    ty = col;
                }
            }
        }

        if (1 == (abs(sx - tx) + abs(sy - ty)))
        {
            
        }
        else
        {
            init();

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
                    unsigned int st1 = qs[act][iQ].state1;
                    unsigned short st2 = qs[act][iQ].state2;
                    unsigned int len = qs[act][iQ].len;

                    if (1 == now_y)
                    {
                        st1 <<= ST1_BITS;
                        st2 <<= ST2_BITS;
                    }
                }

                qTail[act] = 0;
                cnts[act].clear();
                act = nAct;
            }
        }

        // 空格
        string str;
        getline(cin, str);
    }

    return 0;
}
