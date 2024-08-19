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

#define DEBUG 0
#define MAX_N 10
#define MAX_2N 1024
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 3000000

class Record
{
public:
    unsigned short state1; // 已经加入树的节点
    unsigned short state2; // 最后一层的节点
    unsigned short state3; // 节点是否是 end , 1 - yes
    unsigned int cnt;

    Record() {}
};

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map

int n, m, k;
vector<int> v1s, v2s;

unsigned int finalSt;
unsigned int ans;

unsigned char digits[MAX_2N];

inline void addSts(unsigned short st1, unsigned short st2, unsigned short st3, unsigned int cnt, int idx)
{
    if (st1 == finalSt && k == digits[st3])
    {
        ans += cnt;
        return;
    }

    unsigned int key = (((unsigned int)st1) << (2 * MAX_N)) + (((unsigned int)st2) << MAX_N) + st3;

    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state1 = st1;
        qs[idx][pInQ].state2 = st2;
        qs[idx][pInQ].state3 = st3;
        qs[idx][pInQ].cnt = cnt;

        cnts[idx][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        qs[idx][it->second].cnt += cnt;
    }
}

void func(unsigned int layer, int start, unsigned short st1, unsigned short st2, unsigned short currSt2, unsigned short st3, unsigned int cnt, int idx)
{
    for (size_t i = start; i < m; i++)
    {
        int v1 = v1s[i];
        int v2 = v2s[i];

        if (getVal4St(st1, v1, ST_BITS, ST_MASK) && getVal4St(st1, v2, ST_BITS, ST_MASK))
        {
            // v1, v2 都已经在树上了
        }
        else if (getVal4St(st2, v1, ST_BITS, ST_MASK))
        {
            // v1 在树上，并且在上一个 layer，可以连接
            // 忽略该 road, 继续后面的
            func(layer, i + 1, st1, st2, currSt2, st3, cnt, idx);

            unsigned short newSt2 = currSt2;
            setVal4St(newSt2, v2, 1, ST_BITS, ST_MASK);

            unsigned short newSt1 = st1 | newSt2;

            unsigned short newSt3 = st3;
            setVal4St(newSt3, v2, 1, ST_BITS, ST_MASK);

            if (1 == layer && 1 == digits[newSt2])
            {
            }
            else
            {
                setVal4St(newSt3, v1, 0, ST_BITS, ST_MASK);
            }

            addSts(newSt1, newSt2, newSt3, cnt, idx);

            func(layer, i + 1, newSt1, st2, newSt2, newSt3, cnt, idx);

            break;
        }
        else if (getVal4St(st2, v2, ST_BITS, ST_MASK))
        {
            // v2 在树上，并且在上一个 layer，可以连接
            swap(v1, v2);

            // 忽略该 road, 继续后面的
            func(layer, i + 1, st1, st2, currSt2, st3, cnt, idx);

            unsigned short newSt2 = currSt2;
            setVal4St(newSt2, v2, 1, ST_BITS, ST_MASK);

            unsigned short newSt1 = st1 | newSt2;

            unsigned short newSt3 = st3;
            setVal4St(newSt3, v2, 1, ST_BITS, ST_MASK);

            if (1 == layer && 1 == digits[newSt2])
            {
            }
            else
            {
                setVal4St(newSt3, v1, 0, ST_BITS, ST_MASK);
            }

            addSts(newSt1, newSt2, newSt3, cnt, idx);

            func(layer, i + 1, newSt1, st2, newSt2, newSt3, cnt, idx);

            break;
        }
        else
        {
            // v1, v2 都不在树上，忽略掉
        }
    }
}

int main()
{
    cin >> n >> m >> k;

    for (size_t i = 0; i < m; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        v1s.push_back(v1 - 1);
        v2s.push_back(v2 - 1);
    }

    // init
    ans = 0;

    finalSt = (1 << n) - 1;

    for (size_t st = 1; st <= finalSt; st++)
    {
        for (size_t pos = 0; pos < n; pos++)
        {
            if (getVal4St(st, pos, ST_BITS, ST_MASK))
            {
                digits[st]++;
            }
        }
    }

    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    // 初始化，只是 1号节点
    qs[act][0].state1 = 1;
    qs[act][0].state2 = 1;
    qs[act][0].state3 = 1;
    qs[act][0].cnt = 1;

    qTail[act]++;

    int maxLen = 0;

    for (size_t layer = 1; layer < n; layer++)
    {
        if (0 == qTail[act])
        {
            break;
        }

        int nAct = 1 - act;

        if (maxLen < qTail[act])
        {
            maxLen = qTail[act];
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned short st1 = qs[act][iQ].state1;
            unsigned short st2 = qs[act][iQ].state2;
            unsigned short st3 = qs[act][iQ].state3;
            unsigned int cnt = qs[act][iQ].cnt;

            func(layer, 0, st1, st2, 0, st3, cnt, nAct);
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

//    cout << maxLen << endl;
    cout << ans << endl;

    return 0;
}
