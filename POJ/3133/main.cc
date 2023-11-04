// http://poj.org/problem;jsessionid=49743215C3FBD3C529FBB64C68579633?id=3133

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
#define MAX_H 10
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state;   // 轮廓线段状态
    unsigned int len;

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)     \
    NEW = OLD;                            \
    NEW &= ~(ST_MASK << ((POS)*ST_BITS)); \
    NEW |= (VAL) << ((POS)*ST_BITS);

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

    qs[act][0].state = 0;
    qs[act][0].len = 0;

    qTail[act]++;
}

inline void addSts(unsigned int st, unsigned int len, int idx)
{
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = st;
        qs[idx][pInQ].len = len;

        cnts[idx][st] = pInQ;
        qTail[idx]++;
    }
    else
    {
        if (len < qs[idx][it->second].len)
        {
            qs[idx][it->second].len = len;
        }
    }
}

int main()
{
    while (true)
    {
        cin >> h >> w;

        if (0 == h && 0 == w)
        {
            break;
        }

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }

        init();

        int ans = 0;

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
                    // TBD

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
                unsigned int len = qs[act][iQ].len;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        cout << ans << endl;
    }

    return 0;
}
