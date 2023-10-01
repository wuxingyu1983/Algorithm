// https://vjudge.net/problem/Aizu-2452

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

#define MAX_W 3
#define ST1_BITS 2
#define ST1_MASK 3
#define ST2_BITS 4
#define ST2_MASK 15
#define QS_SIZE 60000

class Record
{
public:
    unsigned char state1;           // 轮廓线段状态
    unsigned long long state2;      // 各种类瓷砖的数量
    unsigned long long cnt;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2][256];
int pos[13] = {0, 1, 3, 2, 6, 5, 4, 7, 9, 8, 11, 10, 12};

int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long ans = 0;

#define getVal4St1(ST, POS) ((ST) >> ((POS)*ST1_BITS)) & ST1_MASK

#define setVal4St1(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST1_MASK << ((POS)*ST1_BITS)); \
    NEW |= (VAL) << ((POS)*ST1_BITS);

#define getVal4St2(ST, POS) ((ST) >> ((POS)*ST2_BITS)) & ST2_MASK

#define setVal4St2(NEW, OLD, POS, VAL)                            \
    NEW = OLD;                                                    \
    NEW &= ~(((unsigned long long)ST2_MASK) << ((POS)*ST2_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST2_BITS);

int main()
{
    cin >> h >> w;

    int t[13];
    if (h < w)
    {
        // swap
        for (int i = 1; i <= 12; i++)
        {
            cin >> t[pos[i]];
        }

        swap(h, w);
    }
    else
    {
        for (int i = 1; i <= 12; i++)
        {
            cin >> t[i];
        }
    }

    // init
    unsigned long long st = 0;

    for (int i = 1; i <= 12; i++)
    {
        if (t[i])
        {
            setVal4St1(st, st, i, t[i]);
        }
    }

    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state1 = 0;
    qs[act][0].state2 = st;
    qs[act][0].cnt = 1;

    qTail[act]++;

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

        

        qTail[act] = 0;
        for (int i = 0; i < 256; i++)
        {
            cnts[act][i].clear();
        }
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
