// https://codeforces.com/problemset/problem/53/E#

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
#define ST1_BITS 3
#define ST1_MASK 7
#define ST2_BITS 1
#define ST2_MASK 1
#define QS_SIZE 3000000

class Record
{
public:
    unsigned int state1;
    unsigned short state2;
    unsigned int cnt;
    unsigned char minUnused;
    unsigned char roads;

    Record() {}
};

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);


Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map

int n, m, k;
unsigned int finalSt;
unsigned int ans;

unsigned char digits[1024];

inline void addSts(unsigned int st1, unsigned short st2, unsigned int cnt, int roads, int idx)
{
    if (roads == (n - 1))
    {
        if (finalSt == st1)
        {
            if (digits[st2])
            {
                if (k == digits[st2])
                {
                    ans += cnt;
                }
            }
            else
            {
                int tmp = 0;

                for (size_t pos = 0; pos < n; pos++)
                {
                    if (getVal4St(st2, pos, ST2_BITS, ST2_MASK))
                    {
                        tmp++;
                    }
                }

                digits[st2] = tmp;
                
                if (k == tmp)
                {
                    ans += cnt;
                }
            }
        }
        else
        {
            cout << st1 << endl;
        }
    }
    else
    {
        int bb[16];
        memset(bb, -1, sizeof(bb));

        int bn = 1;
        bb[0] = 0;
        for (int i = 0; i < n; i++)
        {
            int tmp = getVal4St(st1, i, ST1_BITS, ST1_MASK);
            if (0 < tmp)
            {
                if (0 > bb[tmp])
                {
                    bb[tmp] = bn++;
                }
                setVal4St(st1, i, bb[tmp], ST1_BITS, ST1_MASK);
            }
        }

        // 目前有 bn - 1 个 block, 至少需要 bn - 1 - 1 个 road 才能形成一个整体
        // 目前 还有 n - 1 - roads 条可选
        if ((n - 1) < (bn - 2 + roads))
        {
            return;
        }

        unsigned long long key = (((unsigned long long)st1) << 12) + st2;

        unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx].find(key);
        if (it == cnts[idx].end())
        {
            int pInQ = qTail[idx];
            // 加入队尾
            qs[idx][pInQ].state1 = st1;
            qs[idx][pInQ].state2 = st2;
            qs[idx][pInQ].cnt = cnt;
            qs[idx][pInQ].roads = roads;

            qs[idx][pInQ].minUnused = bn;

            cnts[idx][key] = pInQ;
            qTail[idx]++;
        }
        else
        {
            qs[idx][it->second].cnt += cnt;
        }
    }
}

int main()
{
    cin >> n >> m >> k;
    
    // init
    ans = 0;

    finalSt = 1;
    for (size_t i = 1; i < n; i++)
    {
        finalSt <<= ST1_BITS;
        finalSt += 1;
    }

    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].cnt = 1;
    qs[act][0].minUnused = 1;
    qs[act][0].roads = 0;

    qTail[act]++;

    int maxLen = 0;

    for (size_t i = 0; i < m; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        v1--;
        v2--;

        int nAct = 1 - act;

        if (maxLen < qTail[act])
        {
            maxLen = qTail[act];
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st1 = qs[act][iQ].state1;
            unsigned short st2 = qs[act][iQ].state2;
            unsigned int cnt = qs[act][iQ].cnt;
            unsigned char minUnused = qs[act][iQ].minUnused;
            unsigned char roads = qs[act][iQ].roads;

            // 忽略该 road
            addSts(st1, st2, cnt, roads, nAct);

            unsigned int gp1 = getVal4St(st1, v1, ST1_BITS, ST1_MASK);  // group 1
            unsigned int gp2 = getVal4St(st1, v2, ST1_BITS, ST1_MASK);  // group 2

            if (gp1 && gp2)
            {
                if (gp1 != gp2)
                {
                    // 2 个不同的 group 合并
                    // gp2 ==> gp1，gp1 < gp2
                    if (gp2 < gp1)
                    {
                        swap(gp1, gp2);
                    }

                    for (int i = 0; i < n; i++)
                    {
                        int tmp = getVal4St(st1, i, ST1_BITS, ST1_MASK);
                        if (gp2 == tmp)
                        {
                            setVal4St(st1, i, gp1, ST1_BITS, ST1_MASK);
                        }
                    }

                    setVal4St(st2, v1, 0, ST2_BITS, ST2_MASK);
                    setVal4St(st2, v2, 0, ST2_BITS, ST2_MASK);

                    addSts(st1, st2, cnt, roads + 1, nAct);
                }
            }
            else if (gp1)
            {
                setVal4St(st1, v2, gp1, ST1_BITS, ST1_MASK);

                setVal4St(st2, v1, 0, ST2_BITS, ST2_MASK);
                setVal4St(st2, v2, 1, ST2_BITS, ST2_MASK);

                addSts(st1, st2, cnt, roads + 1, nAct);
            }
            else if (gp2)
            {
                setVal4St(st1, v1, gp2, ST1_BITS, ST1_MASK);

                setVal4St(st2, v1, 1, ST2_BITS, ST2_MASK);
                setVal4St(st2, v2, 0, ST2_BITS, ST2_MASK);

                addSts(st1, st2, cnt, roads + 1, nAct);
            }
            else
            {
                setVal4St(st1, v1, minUnused, ST1_BITS, ST1_MASK);
                setVal4St(st1, v2, minUnused, ST1_BITS, ST1_MASK);

                setVal4St(st2, v1, 1, ST2_BITS, ST2_MASK);
                setVal4St(st2, v2, 1, ST2_BITS, ST2_MASK);

                addSts(st1, st2, cnt, roads + 1, nAct);
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    cout << maxLen << endl;
    cout << ans << endl;

    return 0;
}
