// https://atcoder.jp/contests/abc211/tasks/abc211_e

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
#define MAX_N 8
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 60000

int n, k;
int h, w;
char cells[MAX_N][MAX_N];

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned long long cnt[MAX_N];

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long sum = 0;

#define getSt(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setSt(ST, POS, VAL)              \
    ST &= ~(ST_MASK << ((POS)*ST_BITS)); \
    ST |= (VAL) << ((POS)*ST_BITS);

inline unsigned int recode(unsigned int st)
{
    unsigned int ret = 0;
    int bb[10];
    memset(bb, -1, sizeof(bb));
    int bn = 1;
    bb[0] = 0;
    for (int i = 0; i < w; i++)
    {
        int tmp = getSt(st, i);
        if (tmp)
        {
            if (0 > bb[tmp])
            {
                bb[tmp] = bn++;
            }
            setSt(ret, i, bb[tmp]);
        }
    }
    return ret;
}

inline int getMinUnused(unsigned int st)
{
    int ret = 1;
    int flags[10] = {0};
    for (size_t i = 0; i < w; i++)
    {
        int tmp = getSt(st, i);
        flags[tmp]++;
    }

    for (size_t i = 1; i < w; i++)
    {
        if (flags[i])
        {
            ret = i;
            break;
        }
    }

    return ret;
}

inline void addSt(unsigned int st, Record &rec, int idx, bool added)
{
    unsigned int key = recode(st);
    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = key;
        if (added)
        {
            if (2 == getMinUnused(key))
            {
                sum += rec.cnt[k - 1];
            }
            for (size_t i = 0; i < k - 1; i++)
            {
                qs[idx][pInQ].cnt[i + 1] = rec.cnt[i];
            }
            qs[idx][pInQ].cnt[0] = 0;
        }
        else
        {
            for (size_t i = 0; i < k; i++)
            {
                qs[idx][pInQ].cnt[i] = rec.cnt[i];
            }
        }

        cnts[idx][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        if (added)
        {
            if (2 == getMinUnused(key))
            {
                sum += rec.cnt[k - 1];
            }
            for (size_t i = 0; i < k - 1; i++)
            {
                qs[idx][it->second].cnt[i + 1] += rec.cnt[i];
            }
        }
        else
        {
            for (size_t i = 0; i < k; i++)
            {
                qs[idx][it->second].cnt[i] += rec.cnt[i];
            }
        }
    }
}

int main()
{
    cin >> n;
    h = w = n;
    cin >> k;

    for (size_t row = 0; row < h; row++)
    {
        for (size_t col = 0; col < w; col++)
        {
            cin >> cells[row][col];
        }
    }

    // init
    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].cnt[0] = 1;

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

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st = qs[act][iQ].state;
            int left = 0, up = 0;

            if (1 < now_y)
            {
                left = getSt(st, now_y - 2);
            }

            if (1 < now_x)
            {
                up = getSt(st, now_y - 1);
            }

            if (left && up)
            {
                
            }
            else if (left)
            {

            }
            else if (up)
            {
                if ('.' == cells[now_x - 1][now_y - 1])
                {
                    // paint it red
                    addSt(st, qs[act][iQ], nAct, true);
                }

                // no paint
                {

                }
            }
            else
            {
                // 0 == left && 0 == up
                // no paint
                {
                    addSt(st, qs[act][iQ], nAct, false);
                }

                if ('.' == cells[now_x - 1][now_y - 1])
                {
                    // paint it red
                    // find min unused
                    int minUnused = getMinUnused(st);
                    
                    setSt(st, now_y - 1, minUnused);

                    addSt(st, qs[act][iQ], nAct, true);
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    cout << sum << endl;

    return 0;
}
