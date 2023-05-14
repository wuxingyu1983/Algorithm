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
int dist[MAX_N][MAX_M];

class Elem
{
public:
    int d;
    int idx;

    Elem()
    {
        d = idx = 0;
    }
};

typedef bool (*Cmp)(const Elem & elm, int idx);

bool cmp13(const Elem & elm, int idx)
{
    bool ret = false;

    if (elm.idx < idx)
    {
        ret = true;
    }

    return ret;
}

bool cmp24(const Elem & elm, int idx)
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
    fscanf(fp, "%u %u %u %u %u\n", &n, &m, &x, &y, &k);
#else
    scanf("%u %u %u %u %u\n", &n, &m, &x, &y, &k);
#endif

    dist[x][y] = 1;

    char c;
    for (int row = 1; row <= n; row++)
    {
        for (int col = 1; col <= m; col++)
        {
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
#if DEBUG
        fscanf(fp, "%c", &c);
#else
        scanf("%c", &c);
#endif
    }

    unsigned ans = 1;

    for (int i = 0; i < k; i++)
    {
        int s, t, d;
#if DEBUG
        fscanf(fp, "%d %d %d\n", &s, &t, &d);
#else
        scanf("%d %d %d\n", &s, &t, &d);
#endif

        if (1 == d)
        {
            for (int col = 1; col <= m; col++)
            {
                deque<Elem> dq;

                // init dq
                for (int row = 1; row <= n && row <= 1 + (t + 1 - s); row++)
                {
                    
                    if (0 == flags[row][col] && dist[row][col])
                    {
                        Elem elm;
                        elm.d = row + dist[row][col];
                        elm.idx = row;

                        insertDeque(dq, &elm, 1, cmp13);
                    }
                }

                for (int row = 1; row <= n; row++)
                {
                    insertDeque(dq, NULL, row, cmp13);
                    
                    if (0 == flags[row][col] && false == dq.empty())
                    {
                        Elem elm = dq.front();
                        int tmp = elm.d - row;
                        if (tmp > dist[row][col])
                        {
                            dist[row][col] = tmp;
                            if (tmp > ans)
                            {
                                ans = tmp;
                            }
                        }
                    }

                    if (row + 1 + (t + 1 - s) <= n)
                    {
                        int bnd = row + 1 + (t + 1 - s);
                        if (0 == flags[bnd][col] && dist[bnd][col])
                        {
                            Elem elm;
                            elm.d = bnd + dist[bnd][col];
                            elm.idx = bnd;

                            insertDeque(dq, &elm, row + 1, cmp13);
                        }
                    }
                }
            }
        }
        else if (2 == d)
        {
            for (int col = 1; col <= m; col++)
            {
                deque<Elem> dq;

                // init dq
                for (int row = n; row >= 1 && row >= n - (t + 1 - s); row--)
                {
                    if (0 == flags[row][col] && dist[row][col])
                    {
                        Elem elm;
                        elm.d = dist[row][col] - row;
                        elm.idx = row;

                        insertDeque(dq, &elm, n, cmp24);
                    }
                }

                for (int row = n; row >= 1; row--)
                {
                    insertDeque(dq, NULL, row - 1, cmp24);
                    
                    if (0 == flags[row][col] && false == dq.empty())
                    {
                        Elem elm = dq.front();
                        int tmp = elm.d + row;
                        if (tmp > dist[row][col])
                        {
                            dist[row][col] = tmp;
                            if (tmp > ans)
                            {
                                ans = tmp;
                            }
                        }
                    }

                    if (row - 1 - (t + 1 - s) >= 1)
                    {
                        int bnd = row - 1 - (t + 1 - s);
                        if (0 == flags[bnd][col] && dist[bnd][col])
                        {
                            Elem elm;
                            elm.d = dist[bnd][col] - bnd;
                            elm.idx = bnd;

                            insertDeque(dq, &elm, row - 1, cmp24);
                        }
                    }
                }
            }
        }
        else if (3 == d)
        {
            for (int row = 1; row <= n; row++)
            {
                deque<Elem> dq;

                // init dq
                for (int col = 1; col <= m && col <= 1 + (t + 1 - s); col++)
                {
                    if (0 == flags[row][col] && dist[row][col])
                    {
                        Elem elm;
                        elm.d = col + dist[row][col];
                        elm.idx = col;

                        insertDeque(dq, &elm, 1, cmp13);
                    }
                }

                for (int col = 1; col <= m; col++)
                {
                    insertDeque(dq, NULL, col + 1, cmp13);
                    
                    if (0 == flags[row][col] && false == dq.empty())
                    {
                        Elem elm = dq.front();
                        int tmp = elm.d - col;
                        if (tmp > dist[row][col])
                        {
                            dist[row][col] = tmp;
                            if (tmp > ans)
                            {
                                ans = tmp;
                            }
                        }
                    }

                    if (col + 1 + (t + 1 - s) <= m)
                    {
                        int bnd = col + 1 + (t + 1 - s);
                        if (0 == flags[row][bnd] && dist[row][bnd])
                        {
                            Elem elm;
                            elm.d = bnd + dist[row][bnd];
                            elm.idx = bnd;

                            insertDeque(dq, &elm, col + 1, cmp13);
                        }
                    }
                }
                
            }
        }
        else
        {
            // 4 == d
            for (int row = 1; row <= n; row++)
            {
                deque<Elem> dq;
            
                // init dq
                for (int col = m; col >= 1 && col >= m - (t + 1 - s); col--)
                {
                    if (0 == flags[row][col] && dist[row][col])
                    {
                        Elem elm;
                        elm.d = dist[row][col] - col;
                        elm.idx = col;

                        insertDeque(dq, &elm, m, cmp24);
                    }
                }

                for (int col = m; col >= 1; col--)
                {
                    insertDeque(dq, NULL, col - 1, cmp24);
                    
                    if (0 == flags[row][col] && false == dq.empty())
                    {
                        Elem elm = dq.front();
                        int tmp = elm.d + col;
                        if (tmp > dist[row][col])
                        {
                            dist[row][col] = tmp;
                            if (tmp > ans)
                            {
                                ans = tmp;
                            }
                        }
                    }

                    if (col - 1 - (t + 1 - s) >= 1)
                    {
                        int bnd = col - 1 - (t + 1 - s);
                        if (0 == flags[row][bnd] && dist[row][bnd])
                        {
                            Elem elm;
                            elm.d = dist[row][bnd] - bnd;
                            elm.idx = bnd;

                            insertDeque(dq, &elm, col - 1, cmp24);
                        }
                    }
                }
            }
        }
/*
#if DEBUG
        fscanf(fp, "%c", &c);
#else
        scanf("%c", &c);
#endif
*/
    }

    printf("%u\n", ans - 1);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
