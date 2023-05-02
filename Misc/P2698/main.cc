// https://www.luogu.com.cn/problem/P2698
// 单调队列 https://oi-wiki.org/ds/monotonous-queue/

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

using namespace std;

#define DEBUG   0
#define MAX_N   100005

class Raindrop
{
public:
    int x, y;

    Raindrop()
    {
        x = y = 9;
    }
};

inline bool comp(Raindrop &a, Raindrop &b)
{
    return (a.x < b.x);
}

Raindrop rds[MAX_N];

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    unsigned int n, d;
#if DEBUG
    fscanf(fp, "%u %u", &n, &d);
#else
    scanf("%u %u", &n, &d);
#endif

    for (size_t i = 0; i < n; i++)
    {
        int x, y;

#if DEBUG
        fscanf(fp, "%d %d", &x, &y);
#else
        scanf("%d %d", &x, &y);
#endif

        rds[i].x = x;
        rds[i].y = y;
    }

    // sort by x
    sort(rds, rds + n, comp);

    int w = -1;

    deque<Raindrop *> dque;

    for (size_t run = 0; run < 2; run++)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (dque.empty())
            {
                dque.push_back(&(rds[i]));
            }
            else
            {
                Raindrop *first = dque.front();
                if (first->y >= rds[i].y)
                {
                    dque.clear();
                    dque.push_back(&(rds[i]));
                    continue;
                }

                while (false == dque.empty())
                {
                    first = dque.front();

                    if (rds[i].y - first->y < d)
                    {
                        break;
                    }
                    else
                    {
                        int tmp = abs(rds[i].x - first->x);
                        if (0 > w || tmp < w)
                        {
                            w = tmp;
                        }

                        dque.pop_front();
                    }
                }

                while (false == dque.empty())
                {
                    Raindrop *back = dque.back();
                    if (back->y < rds[i].y)
                    {
                        break;
                    }
                    else
                    {
                        dque.pop_back();
                    }
                }

                dque.push_back(&(rds[i]));
            }
        }

        if (0 == run)
        {
            dque.clear();
            reverse(rds, rds + n);
        }
    }

    printf("%d\n", w);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
