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
int dist[2][MAX_N][MAX_M];

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

    if (elm.idx > idx)
    {
        ret = true;
    }

    return ret;
}

bool cmp24(const Elem & elm, int idx)
{
    bool ret = false;

    if (elm.idx < idx)
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

    dist[0][x][y] = 1;

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

    int now = 0;
    int ans = 1;

    for (int i = 0; i < k; i++)
    {
        now = 1 - now;
        int s, t, d;
#if DEBUG
        fscanf(fp, "%d %d %d", &s, &t, &d);
#else
        scanf("%d %d %d", &s, &t, &d);
#endif

        if (1 == d)
        {
            for (int col = 1; col <= m; col++)
            {
                deque<Elem> dq;
                
                for (int row = n; row >= 1; row--)
                {
                    if (1 == flags[row][col])
                    {
                        dq.clear();
                    }
                    else
                    {
                        insertDeque(dq, NULL, row + (t - s + 1), cmp13);
                        
                        dist[now][row][col] = dist[1 - now][row][col];
                        if (false == dq.empty())
                        {
                            Elem elm = dq.front();
                            int tmp = elm.d - row;
                            if (tmp > dist[now][row][col])
                            {
                                dist[now][row][col] = tmp;
                                if (tmp > ans)
                                {
                                    ans = tmp;
                                }
                            }
                        }

                        if (dist[1 - now][row][col])
                        {
                            Elem elm;
                            elm.d = row + dist[1 - now][row][col];
                            elm.idx = row;

                            insertDeque(dq, &elm, row + (t - s + 1), cmp13);
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
                
                for (int row = 1; row <= n; row++)
                {
                    if (1 == flags[row][col])
                    {
                        dq.clear();
                    }
                    else
                    {
                        dist[now][row][col] = dist[1 - now][row][col];
                        
                        insertDeque(dq, NULL, row - (t - s + 1), cmp24);
                        
                        if (false == dq.empty())
                        {
                            Elem elm = dq.front();
                            int tmp = elm.d + row;
                            if (tmp > dist[now][row][col])
                            {
                                dist[now][row][col] = tmp;
                                if (tmp > ans)
                                {
                                    ans = tmp;
                                }
                            }
                        }

                        if (dist[1 - now][row][col])
                        {
                            Elem elm;
                            elm.d = dist[1 - now][row][col] - row;
                            elm.idx = row;

                            insertDeque(dq, &elm, row - (t - s + 1), cmp24);
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
                
                for (int col = m; col >= 1; col--)
                {
                    if (1 == flags[row][col])
                    {
                        dq.clear();
                    }
                    else
                    {
                        dist[now][row][col] = dist[1 - now][row][col];
                        
                        insertDeque(dq, NULL, col + (t - s + 1), cmp13);
                        
                        if (false == dq.empty())
                        {
                            Elem elm = dq.front();
                            int tmp = elm.d - col;
                            if (tmp > dist[now][row][col])
                            {
                                dist[now][row][col] = tmp;
                                if (tmp > ans)
                                {
                                    ans = tmp;
                                }
                            }
                        }

                        if (dist[1 - now][row][col])
                        {
                            Elem elm;
                            elm.d = col + dist[1 - now][row][col];
                            elm.idx = col;

                            insertDeque(dq, &elm, col + (t - s + 1), cmp13);
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
            
                for (int col = 1; col <= m; col++)
                {
                    if (1 == flags[row][col])
                    {
                        dq.clear();
                    }
                    else
                    {
                        dist[now][row][col] = dist[1 - now][row][col];
                        
                        insertDeque(dq, NULL, col - (t - s + 1), cmp24);
                        
                        if (false == dq.empty())
                        {
                            Elem elm = dq.front();
                            int tmp = elm.d + col;
                            if (tmp > dist[now][row][col])
                            {
                                dist[now][row][col] = tmp;
                                if (tmp > ans)
                                {
                                    ans = tmp;
                                }
                            }
                        }

                        if (dist[1 - now][row][col])
                        {
                            Elem elm;
                            elm.d = dist[1 - now][row][col] - col;
                            elm.idx = col;

                            insertDeque(dq, &elm, col - (t - s + 1), cmp24);
                        }
                    }
                }
            }
        }
    }

    printf("%u\n", ans - 1);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
