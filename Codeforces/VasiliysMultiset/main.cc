// https://codeforces.com/problemset/problem/706/D

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <map>

using namespace std;

const int MAX_N = 200000;
const int MAXH = 32;
const int MAX_NODES = MAXH * MAX_N;
int ch[MAX_NODES][2], /*w[MAX_NODES], xorv[MAX_NODES],*/ root, cnt[MAX_NODES];
int tot = 0;


int mknode()
{
    ++tot;
    ch[tot][1] = ch[tot][0] /* = w[tot] = xorv[tot]*/ = 0;
    return tot;
}

/*
void maintain(int o)
{
    w[o] = xorv[o] = 0;
    if (ch[o][0])
    {
        w[o] += w[ch[o][0]];
        xorv[o] ^= xorv[ch[o][0]] << 1;
    }
    if (ch[o][1])
    {
        w[o] += w[ch[o][1]];
        xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
    }
    w[o] = w[o] & 1;
}
*/

void insert(int &o, int x, int dp)
{
    if (!o)
        o = mknode();
    cnt[o] ++;
    if (dp >= MAXH)
//        return (void)(w[o]++);
        return;
    insert(ch[o][(x >> (MAXH - 1 - dp)) & 1], x, dp + 1);
//    maintain(o);
}

void erase(int o, int x, int dp)
{
    cnt[o] --;
    if (dp >= MAXH)
//        return (void)(w[o]--);
        return;
    erase(ch[o][(x >> (MAXH - 1 - dp)) & 1], x, dp + 1);
//    maintain(o);
}

int main()
{
    int q;
    scanf("%d\n", &q);

    insert(root, 0, 0);

    for (size_t i = 0; i < q; i++)
    {
        char op;
        int x;

        scanf("%c %d\n", &op, &x);

        switch (op)
        {
        case '+':
        {
            insert(root, x, 0);
        }
        break;
        case '-':
        {
            erase(root, x, 0);
        }
        break;
        case '?':
        default:
        {
            int ret = 0;
            int p = root;
            for (int i = 31; i >= 0; i--)
            {
                int c = (x >> i) & 1;
                if (0 < ch[p][1 - c] && 0 < cnt[ch[p][1 - c]])
                {
                    ret |= 1 << i;
                    p = ch[p][1 - c];
                }
                else
                {
                    p = ch[p][c];
                }
            }
            
            printf("%d\n", ret);
        }
        break;
        }
    }

    return 0;
}
