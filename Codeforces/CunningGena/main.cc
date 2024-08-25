// https://codeforces.com/contest/417/problem/D

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
#define MAX_N   100
#define MAX_M   20
#define MAX_2M  1048576
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 2000000

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

unsigned short n, m;
unsigned long long b;

class Friend
{
public:
    unsigned long long x;   // the desired amount of money
    unsigned long long k;   // monitors
    unsigned int canSolve;  // the numbers of problems that the friend can solve 

    Friend() { canSolve = 0; }
};

Friend friends[MAX_N];

bool comp(Friend &a, Friend &b)
{
    return (a.k > b.k);
}

class Record
{
public:
    unsigned int state;
    unsigned long long k;
    unsigned long long money;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int cnts[2][MAX_2M];
int act = 0; // 当前生效的 map

inline void addSts(unsigned int st, unsigned long long k, unsigned long long money, int idx)
{
    int it = cnts[idx][st];
    if (0 > it)
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = st;
        qs[idx][pInQ].k = k;
        qs[idx][pInQ].money = money;

        cnts[idx][st] = pInQ;
        qTail[idx]++;
    }
    else
    {
        if (money < qs[idx][it].money)
        {
            qs[idx][it].money = money;
        }
    }
}

int main()
{
    cin >> n >> m >> b;

    for (size_t i = 0; i < n; i++)
    {
        int slv;

        cin >> friends[i].x >> friends[i].k >> slv;

        for (size_t j = 0; j < slv; j++)
        {
            int problem;

            cin >> problem;
            problem --;

            setVal4St(friends[i].canSolve, problem, 1, ST_BITS, ST_MASK); 
        }
    }
    
    // sort friends
    sort(friends, friends + n, comp);

    // init
    act = 0;
    qTail[0] = 0;
    qTail[1] = 0;
    memset(cnts, -1, sizeof(cnts));

    addSts(0, 0, 0, act);

    unsigned int finalSt = (1 << m) - 1;
    long long ans = -1;

    // 遍历每个 friend
    for (size_t i = 0; i < n; i++)
    {
        if (0 == qTail[act])
        {
            break;
        }

        int nAct = 1 - act;

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned int st = qs[act][iQ].state;
            unsigned long long k = qs[act][iQ].k;
            unsigned long long money = qs[act][iQ].money;

            // 忽略该 friend
            addSts(st, k, money, nAct);

            if (friends[i].canSolve != (st & friends[i].canSolve))
            {
                unsigned int newSt = st | friends[i].canSolve;
                unsigned long long newK = k;
                unsigned long long sum;

                if (0 == st)
                {
                    // 该 friend 是第一个参与的
                    sum = friends[i].x + friends[i].k * b;
                    newK = friends[i].k;
                }
                else
                {
                    sum = money + friends[i].x;
                }

                if (finalSt == newSt)
                {
                    if (0 > ans || ans > sum)
                    {
                        ans = sum;
                    }
                }
                else
                {
                    addSts(newSt, newK, sum, nAct);
                }
            }
        }

        qTail[act] = 0;
        memset(cnts[act], -1, sizeof(cnts[act]));
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
