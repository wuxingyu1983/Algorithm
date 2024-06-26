// https://www.luogu.com.cn/problem/AT_abc211_e
// https://atcoder.jp/contests/abc211/tasks/abc211_e

#include <cmath>
#include <cstdio>
#include <vector>
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
#define MAX_NK 9
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 600000

class Record
{
public:
    unsigned int state; // 轮廓线段状态

    unsigned long long count;
    unsigned char minUnused;

    Record() {}
};

char cells[MAX_NK][MAX_NK];
Record qs[2][QS_SIZE];
int qTail[2];
int n, k;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long ans;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

// 最小表示法重编码
#define recode(ST, UNUSED)             \
    int bb[10];                        \
    memset(bb, -1, sizeof(bb));        \
    int bn = 1;                        \
    bb[0] = 0;                         \
    for (int i = 0; i <= n; i++)       \
    {                                  \
        int tmp = getVal4St(ST, i);    \
        if (tmp)                       \
        {                              \
            if (0 > bb[tmp])           \
            {                          \
                bb[tmp] = bn++;        \
            }                          \
            setVal4St(ST, i, bb[tmp]); \
        }                              \
    }                                  \
    UNUSED = bn;

#define addSts(ST, CNT, REDS, IDX)                                                          \
    unsigned char unused;                                                                   \
    unsigned int recodedSt = ST;                                                            \
    recode(recodedSt, unused);                                                              \
    if (REDS == k)                                                                          \
    {                                                                                       \
        if (3 > unused)                                                                     \
            ans += CNT;                                                                     \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        unordered_map<unsigned int, unsigned int>::iterator it = cnts[IDX].find(recodedSt); \
        if (it == cnts[IDX].end())                                                          \
        {                                                                                   \
            int pInQ = qTail[IDX];                                                          \
            qs[IDX][pInQ].state = recodedSt;                                                \
            qs[IDX][pInQ].count = CNT;                                                      \
            qs[IDX][pInQ].minUnused = unused;                                               \
            cnts[IDX][recodedSt] = pInQ;                                                    \
            qTail[IDX]++;                                                                   \
        }                                                                                   \
        else                                                                                \
        {                                                                                   \
            qs[IDX][it->second].count += CNT;                                               \
        }                                                                                   \
    }

int main()
{
    ans = 0;

    cin >> n;
    cin >> k;

    unsigned int stMask = (1 << ((n + 1) * ST_BITS)) - 1;

    for (size_t row = 1; row <= n; row++)
    {
        for (size_t col = 1; col <= n; col++)
        {
            cin >> cells[row][col];
            if (1 == k && '.' == cells[row][col])
            {
                ans++;
            }
        }
    }

    if (1 < k)
    {
        // init
        ans = 0;

        act = 0;

        now_x = 0;
        now_y = n;

        qs[act][0].state = 0;
        qs[act][0].count = 1;
        qs[act][0].minUnused = 1;

        qTail[act]++;

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (n == now_y)
            {
                now_x++;
                now_y = 1;

                if (n < now_x)
                {
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
                unsigned long long count = qs[act][iQ].count;
                unsigned char minUnused = qs[act][iQ].minUnused;

                unsigned int reds = getVal4St(st, n + 1);
                if (1 == now_y)
                {
                    st <<= ST_BITS;
                    st &= stMask;
                    setVal4St(st, (n + 1), reds)
                }

                unsigned int left = getVal4St(st, now_y - 1);
                unsigned int up = getVal4St(st, now_y);

                if (left && up)
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, now_y - 1, 0);
                    setVal4St(newSt, now_y, 0);

                    // do nothing
                    {
                        int leftCnt = 0;
                        int upCnt = 0;

                        for (int i = 0; i <= n; i++)
                        {
                            int tmp = getVal4St(newSt, i);
                            if (tmp == left)
                            {
                                leftCnt++;
                            }
                            if (tmp == up)
                            {
                                upCnt++;
                            }
                        }

                        if (0 < leftCnt && 0 < upCnt)
                        {
                            // add
                            addSts(newSt, count, reds, nAct);
                        }
                    }

                    // white ==> red
                    if ('.' == cells[now_x][now_y])
                    {
                        reds++;

                        // up ==> left
                        for (int i = 0; i <= n; i++)
                        {
                            int tmp = getVal4St(newSt, i);
                            if (tmp == up)
                            {
                                setVal4St(newSt, i, left);
                            }
                        }

                        if (n > now_x)
                        {
                            setVal4St(newSt, now_y - 1, left);
                        }

                        if (n > now_y)
                        {
                            setVal4St(newSt, now_y, left);
                        }

                        // add
                        setVal4St(newSt, (n + 1), reds);
                        addSts(newSt, count, reds, nAct);
                    }
                }
                else if (left || up)
                {
                    unsigned int val = left + up;
                    unsigned int newSt = st;
                    setVal4St(newSt, now_y - 1, 0);
                    setVal4St(newSt, now_y, 0);

                    // do nothing
                    {
                        int valCnt = 0;

                        for (int i = 0; i <= n; i++)
                        {
                            int tmp = getVal4St(newSt, i);
                            if (tmp == val)
                            {
                                valCnt++;
                            }
                        }

                        if (0 < valCnt)
                        {
                            // add
                            addSts(newSt, count, reds, nAct);
                        }
                    }

                    // white ==> red
                    if ('.' == cells[now_x][now_y])
                    {
                        reds++;

                        if (n > now_x)
                        {
                            setVal4St(newSt, now_y - 1, val);
                        }

                        if (n > now_y)
                        {
                            setVal4St(newSt, now_y, val);
                        }

                        // add
                        setVal4St(newSt, (n + 1), reds);
                        addSts(newSt, count, reds, nAct);
                    }
                }
                else
                {
                    unsigned int newSt = st;
                    setVal4St(newSt, now_y - 1, 0);
                    setVal4St(newSt, now_y, 0);

                    // 0 == left && 0 == up
                    // do nothing, add directly
                    {
                        addSts(newSt, count, reds, nAct);
                    }

                    // white ==> red
                    if ('.' == cells[now_x][now_y])
                    {
                        reds++;
                        unsigned int newSt = st;

                        if (n > now_x)
                        {
                            setVal4St(newSt, now_y - 1, minUnused);
                        }

                        if (n > now_y)
                        {
                            setVal4St(newSt, now_y, minUnused);
                        }

                        // add
                        setVal4St(newSt, (n + 1), reds);
                        addSts(newSt, count, reds, nAct);
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }
    }

    cout << ans << endl;

    return 0;
}
