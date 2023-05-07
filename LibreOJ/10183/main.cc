// https://loj.ac/p/10183
// 单调队列 https://oi-wiki.org/dp/opt/monotonous-queue-stack/

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
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

using namespace std;

#define DEBUG   0
#define MAX_T   2001
#define MAX_P   2001

vector< vector<long long> > profit(MAX_T, vector<long long>(MAX_P, LLONG_MIN));

class Day
{
public:
    int ap, bp, as, bs;

    Day()
    {
        ap = bp = as = bs = 0;
    }
};

class Elem
{
public:
    long long p;
    int s;

    Elem()
    {
        p = s = 0;
    }
};

unsigned int t, maxp, w;
Day days[MAX_T];

void insertDeque(deque<Elem> &dq, Elem * elm, int minS)
{
    while (false == dq.empty())
    {
        Elem first = dq.front();
        if (first.s < minS)
        {
            dq.pop_front();
        }
        else
        {
            break;
        }
    }

    if (elm)
    {
        if (dq.empty())
        {
            dq.push_back(*elm);
        }
        else
        {
            Elem first = dq.front();
            if (first.p <= elm->p)
            {
                dq.clear();
                dq.push_back(*elm);
            }
            else
            {
                while (true)
                {
                    Elem last = dq.back();
                    if (last.p <= elm->p)
                    {
                        dq.pop_back();
                    }
                    else
                    {
                        break;
                    }
                }
                dq.push_back(*elm);
            }
        }
    }
}

void proc(unsigned int d, unsigned int pre, int p, deque<Elem> &buy, deque<Elem> &sell)
{
    if (0 == p)
    {
        // init sell deque
        for (size_t i = p + 1; i <= maxp && i <= p + days[d].bs; i++)
        {
            Elem elm;
            elm.p = profit[pre][i] + i * days[d].bp;
            elm.s = i;
            insertDeque(sell, &elm, p + 1);
        }
    }
    else
    {
        // 0 < p
        // buy deque
        {
            Elem elm;
            elm.p = profit[pre][p - 1] + (p - 1) * days[d].ap;
            elm.s = p - 1;
            insertDeque(buy, &elm, p - days[d].as);
        }

        // sell deque
        {
            if (p + days[d].bs <= maxp)
            {
                Elem elm;
                elm.p = profit[pre][p + days[d].bs] + (p + days[d].bs) * days[d].bp;
                elm.s = p + days[d].bs;
                insertDeque(sell, &elm, p + 1);
            }
            else
            {
                insertDeque(sell, NULL, p + 1);
            }
        }
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif
    
#if DEBUG
    fscanf(fp, "%u %u %u", &t, &maxp, &w);
#else
    scanf("%u %u %u", &t, &maxp, &w);
#endif

    for (size_t i = 1; i <= t; i++)
    {
        int ap, bp, as, bs;
#if DEBUG
    fscanf(fp, "%d %d %d %d", &ap, &bp, &as, & bs);
#else
    scanf("%d %d %d %d", &ap, &bp, &as, & bs);
#endif
        days[i].ap = ap;
        days[i].bp = bp;
        days[i].as = as;
        days[i].bs = bs;
    }

    long long ans = 0;

    for (size_t i = 1; i <= t; i++)
    {
        if (1 == i)
        {
            profit[i][0] = 0;
            for (size_t j = 1; j <= days[i].as; j++)
            {
                profit[i][j] = 0 - j * days[i].ap;
            }
        }
        else if (i < 1 + w + 1)
        {
            profit[i][0] = profit[i - 1][0];
            for (size_t j = 1; j <= days[i].as; j++)
            {
                profit[i][j] = 0 - j * days[i].ap;
                if (profit[i - 1][j] > profit[i][j])
                {
                    profit[i][j] = profit[i - 1][j];
                }
            }
            for (size_t j = days[i].as + 1; j <= maxp; j++)
            {
                profit[i][j] = profit[i - 1][j];
            }
        }
        else
        {
            unsigned int pre = i - w - 1;
            deque<Elem> buy, sell;
            for (size_t j = 0; j <= maxp; j++)
            {
                profit[i][j] = profit[i - 1][j];

                // proc buy, sell deque
                proc(i, pre, j, buy, sell);

                if (false == buy.empty())
                {
                    Elem elm = buy.front();
                    long long tmp = elm.p - j * days[i].ap;
                    if (tmp > profit[i][j])
                    {
                        profit[i][j] = tmp;

                        if (t == i && ans < profit[i][j])
                        {
                            ans = profit[i][j];
                        }
                    }
                }

                if (false == sell.empty())
                {
                    Elem elm = sell.front();
                    long long tmp = elm.p - j * days[i].bp;
                    if (tmp > profit[i][j])
                    {
                        profit[i][j] = tmp;

                        if (t == i && ans < profit[i][j])
                        {
                            ans = profit[i][j];
                        }
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);    

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
