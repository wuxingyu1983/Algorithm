// https://codeforces.com/problemset/problem/11/D

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
#define MAX_N 19
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 3000000

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

class Record
{
public:
    unsigned int state1;
    unsigned int state2;    // 1 - 叶子节点
    unsigned int cnt;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map

int ans = 0;
int n, m;

inline void addSts(unsigned int st1, unsigned int st2, unsigned int cnt, int idx)
{
    if (0 != st1 && 0 == st2)
    {
//        cout << st1 << " " << st2 << endl;
        ans += cnt;
        return;
    }

    unsigned long long key = (((unsigned long long)st1) << MAX_N) + st2;

    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state1 = st1;
        qs[idx][pInQ].state2 = st2;
        qs[idx][pInQ].cnt = cnt;

        cnts[idx][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        qs[idx][it->second].cnt += cnt;
    }
}

int main()
{
    cin >> n >> m;

    // init
    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].cnt = 1;

    qTail[act]++;

    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a --;
        b --;

        int nAct = 1 - act;

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st1 = qs[act][iQ].state1;
            unsigned int st2 = qs[act][iQ].state2;
            unsigned int cnt = qs[act][iQ].cnt;

            // 忽略该条边
            addSts(st1, st2, cnt, nAct);

            if (getVal4St(st1, a, ST_BITS, ST_MASK) && getVal4St(st1, b, ST_BITS, ST_MASK))
            {
                // a, b 都已连接了
                if (getVal4St(st2, a, ST_BITS, ST_MASK) && getVal4St(st2, b, ST_BITS, ST_MASK))
                {
                    // a, b 都是叶子节点，才有效
                    unsigned int newSt1 = st1;
                    unsigned int newSt2 = st2;

                    setVal4St(newSt2, a, 0, ST_BITS, ST_MASK);
                    setVal4St(newSt2, b, 0, ST_BITS, ST_MASK);

                    addSts(newSt1, newSt2, cnt, nAct);

//                    printf("(%u, %u) => (%u, %u)\n", st1, st2, newSt1, newSt2);
                }
            }
            else if (getVal4St(st1, a, ST_BITS, ST_MASK))
            {
                if (getVal4St(st2, a, ST_BITS, ST_MASK))
                {
                    // a 已经连接
                    unsigned int newSt1 = st1;
                    unsigned int newSt2 = st2;

                    setVal4St(newSt1, b, 1, ST_BITS, ST_MASK);

                    setVal4St(newSt2, a, 0, ST_BITS, ST_MASK);
                    setVal4St(newSt2, b, 1, ST_BITS, ST_MASK);

                    addSts(newSt1, newSt2, cnt, nAct);

//                    printf("(%u, %u) => (%u, %u)\n", st1, st2, newSt1, newSt2);
                }
            }
            else if (getVal4St(st1, b, ST_BITS, ST_MASK))
            {
                // b 已经连接
                swap(a, b);

                if (getVal4St(st2, a, ST_BITS, ST_MASK))
                {
                    unsigned int newSt1 = st1;
                    unsigned int newSt2 = st2;

                    setVal4St(newSt1, b, 1, ST_BITS, ST_MASK);

                    setVal4St(newSt2, a, 0, ST_BITS, ST_MASK);
                    setVal4St(newSt2, b, 1, ST_BITS, ST_MASK);

                    addSts(newSt1, newSt2, cnt, nAct);

//                    printf("(%u, %u) => (%u, %u)\n", st1, st2, newSt1, newSt2);
                }
            }
            else
            {
                unsigned int newSt1 = st1;
                unsigned int newSt2 = st2;

                setVal4St(newSt1, a, 1, ST_BITS, ST_MASK);
                setVal4St(newSt1, b, 1, ST_BITS, ST_MASK);

                setVal4St(newSt2, a, 1, ST_BITS, ST_MASK);
                setVal4St(newSt2, b, 1, ST_BITS, ST_MASK);

                addSts(newSt1, newSt2, cnt, nAct);

//                printf("(%u, %u) => (%u, %u)\n", st1, st2, newSt1, newSt2);
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
