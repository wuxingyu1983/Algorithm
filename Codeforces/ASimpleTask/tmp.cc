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
#define MAX_2N 524288
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 30000000

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
int sums[MAX_N + 1];
int n, m;

char edges[MAX_N][MAX_N];
char digits[MAX_2N];

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

    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a --;
        b --;

        edges[a][b] = 1;
        edges[b][a] = 1;
    }
    
    // init
    for (size_t st = 1; st < (1 << n); st++)
    {
        for (size_t pos = 0; pos < n; pos++)
        {
            if (st & (1 << pos))
            {
                digits[st] ++;
            }
        }
    }

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();
    
    qTail[act]++;

    for (size_t pos = 0; pos < n; pos++)
    {
        addSts(1 << pos, 1 << pos, 1, act);
    }

    while (qTail[act])
    {
        int nAct = 1 - act;

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st1 = qs[act][iQ].state1;
            unsigned int st2 = qs[act][iQ].state2;
            unsigned int cnt = qs[act][iQ].cnt;
        
            if (1 == digits[st2])
            {
                int v;
                for (v = 0; v < n; v++)
                {
                    if (st2 & (1 << v))
                    {
                        break;
                    }
                }
                
                for (size_t a = 0; a < n; a++)
                {
                    if (edges[v][a])
                    {
                        for (size_t b = a + 1; b < n; b++)
                        {
                            if (edges[v][b])
                            {
                                unsigned int newSt1 = st1;
                                unsigned int newSt2 = 0;

                                setVal4St(newSt1, a, 1, ST_BITS, ST_MASK);
                                setVal4St(newSt1, b, 1, ST_BITS, ST_MASK);

                                setVal4St(newSt2, a, 1, ST_BITS, ST_MASK);
                                setVal4St(newSt2, b, 1, ST_BITS, ST_MASK);

                                addSts(newSt1, newSt2, cnt, nAct);
                            }
                        }
                    }
                }
                
            }
            else
            {
                // 2 == digits[st2]
                int v1 = -1, v2 = -1;

                for (int p = 0; p < n; p++)
                {
                    if (st2 & (1 << p))
                    {
                        if (0 > v1)
                        {
                            v1 = p;
                        }
                        else
                        {
                            v2 = p;
                            break;
                        }
                    }
                }

                // v1 和 v2 中间是否有 edge
                if (edges[v1][v2])
                {
                    addSts(st1, 0, cnt, nAct);
                }

                // 有个 v 和 v1, v2 都有 edge
                for (size_t v = 0; v < n; v++)
                {
                    if (0 == getVal4St(st1, v, ST_BITS, ST_MASK) && edges[v][v1] && edges[v][v2])
                    {
                        unsigned int newSt1 = st1;

                        setVal4St(newSt1, v, 1, ST_BITS, ST_MASK);

                        addSts(newSt1, 0, cnt, nAct);
                    }
                }
                
                // a - v1 和 b - v2
                for (size_t a = 0; a < n; a++)
                {
                    if (edges[v1][a] && 0 == getVal4St(st1, a, ST_BITS, ST_MASK))
                    {
                        for (size_t b = 0; b < n; b++)
                        {
                            if (edges[v1][b] && a != b && 0 == getVal4St(st1, b, ST_BITS, ST_MASK))
                            {
                                unsigned int newSt1 = st1;
                                unsigned int newSt2 = 0;

                                setVal4St(newSt1, a, 1, ST_BITS, ST_MASK);
                                setVal4St(newSt1, b, 1, ST_BITS, ST_MASK);

                                setVal4St(newSt2, a, 1, ST_BITS, ST_MASK);
                                setVal4St(newSt2, b, 1, ST_BITS, ST_MASK);

                                addSts(newSt1, newSt2, cnt, nAct);
                            }
                        }
                    }
                }
                
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
