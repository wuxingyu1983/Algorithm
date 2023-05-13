// https://www.luogu.com.cn/problem/P2254

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
#include <bitset>

using namespace std;

#define DEBUG   0
#define MAX_N   202
#define MAX_M   202

unsigned int n, m, x, y, k;

vector< bitset<MAX_M> > flags(MAX_N);
unsigned int dist[MAX_N][MAX_M];

class Elem
{
public:
    unsigned int d;
    int idx;

    Elem()
    {
        d = idx = 0;
    }
};

typedef bool (*Cmp)(const Elem & elm, int idx);

bool cmp1(const Elem & elm, int idx)
{
    bool ret = false;

    if (elm.idx > idx)
    {
        ret = true;
    }

    return ret;
}

void insertDeque(deque<Elem> &dq, Elem * elm, int idx, Cmp cmp)
{
    while (false == dq.empty())
    {
        Elem first = dq.front();
        if (cmp(first, idx))
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
            if (first.d <= elm->d)
            {
                dq.clear();
                dq.push_back(*elm);
            }
            else
            {
                while (true)
                {
                    Elem last = dq.back();
                    if (last.d <= elm->d)
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

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%u %u %u %u %u", &n, &m, &x, &y, &k);
#else
    scanf("%u %u %u %u %u", &n, &m, &x, &y, &k);
#endif

    dist[x][y] = 1;

    for (size_t row = 1; row <= n; row++)
    {
        for (size_t col = 1; col <= m; col++)
        {
            char c;
#if DEBUG
            fscanf(fp, "%c", &c);
#else
            scanf("%c", &c);
#endif
            if ('x' == c)
            {
                flags[row][col] = 1;
            }
        }
    }

    unsigned ans = 1;

    for (size_t i = 0; i < k; i++)
    {
        unsigned int s, t, d;
#if DEBUG
        fscanf(fp, "%u %u %u", &s, &t, &d);
#else
        scanf("%u %u %u", &s, &t, &d);
#endif

        if (1 == d)
        {
            for (size_t col = 1; col <= m; col++)
            {
                deque<Elem> dq;

                // init dq
                for (size_t row = 1; row <= n && row <= 1 + (t + 1 - s); row++)
                {
                    if (0 == flags[row][col])
                    {
                        Elem elm;
                        elm.d = row + dist[row][col];

                        insertDeque(dq, &elm, 1 + (t + 1 - s), cmp1);
                    }
                }
                

                for (size_t row = 1; row <= n; row++)
                {
                    if (1 == flags[row][col])
                    {

                    }
                    else
                    {

                    }
                }
            }
            
        }
        else if (2 == d)
        {

        }
        else if (3 == d)
        {

        }
        else
        {
            // 4 == d
        }
    }

    printf("%u\n", ans);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
