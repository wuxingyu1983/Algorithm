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
int ch[MAX_NODES][2], w[MAX_NODES], xorv[MAX_NODES], root;
int tot = 0;


int mknode()
{
    ++tot;
    ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
    return tot;
}

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

void insert(int &o, int x, int dp)
{
    if (!o)
        o = mknode();
    if (dp >= MAXH - 1)
        return (void)(w[o]++);
    insert(ch[o][(x >> (MAXH - 1 - dp)) & 1], x, dp + 1);
    maintain(o);
}

void erase(int o, int x, int dp)
{
    if (dp >= MAXH - 1)
        return (void)(w[o]--);
    erase(ch[o][(x >> (MAXH - 1 - dp)) & 1], x, dp + 1);
    maintain(o);
}

int main()
{
    int q;
    scanf("%d", &q);

    for (size_t i = 0; i < q; i++)
    {
        char op;
        int x;

        scanf("%c %d", &op, &x);

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
        }
        break;
        }
    }

    return 0;
}
