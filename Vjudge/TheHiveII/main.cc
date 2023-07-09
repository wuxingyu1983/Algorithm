// https://vjudge.net/problem/ZOJ-3466

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
#define MAX_N   26      // row
#define MAX_M   10      // col
#define BITS    2
#define MASK    3

int n, m;

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    int x, y;
    unsigned char sts[MAX_M + 1];   // 每个cell 在一条轮廓线上最多有4条边参与，用一个 char 来表示，每个边用2bits表示状态，0-1 表示同层的边，2-3，4-5，6-7 表示上层中的左上，上，右上 对应的边

    Line()
    {
        x = y = 0;
        memset(sts, 0, sizeof(sts));
    }
};

queue<Line> lines;

unsigned char cells[MAX_N + 1][MAX_M + 1]; // 1 - obstacle

// 1 个 cell 6 个边（side）, 只能有2个插头（plug）

inline void setState(unsigned char sts[], int cell, int pos, int val)
{
    // clear
    sts[cell] &= ~(MASK << (pos * BITS));
    sts[cell] |= val << (pos * BITS);
}

inline unsigned char setOneState(unsigned char st, int pos, int val)
{
    // clear
    st &= ~(MASK << (pos * BITS));
    st |= val << (pos * BITS);

    return st;
}

inline int getState(unsigned char sts[], int cell, int pos)
{
    int ret = 0;

    ret = (sts[cell] >> (pos * BITS)) & MASK;

    return 0;
}

inline long long getMainKey(unsigned char sts[])
{
    long long ret = 0;

    for (size_t i = 1; i <= m / 2; i++)
    {
        ret |= sts[i];
        ret <<= 8;
    }

    return ret;
}

inline long long getSubKey(unsigned char sts[])
{
    long long ret = 0;

    int i = m / 2;
    if (m & 1)
    {
        i ++;
    }

    for (; i <= m; i++)
    {
        ret |= sts[i];
        ret <<= 8;
    }

    return ret;
}

map<long long, map<long long, long long> > cnts[2];
int act = 0; // 当前生效的 map
unsigned char flags[MAX_N + 1][MAX_M + 1];

void insertLine(Line &line, long long cnt)
{
    // 判断是否已经存在了
    long long mKey = getMainKey(line.sts);

    map<long long, map<long long, long long> >::iterator mIt = cnts[1 - act].find(mKey);

    if (mIt == cnts[1 - act].end())
    {
        cnts[1 - act].insert(pair<long long, map<long long, long long> >(mKey, map<long long, long long>()));

    }

    mIt = cnts[1 - act].find(mKey);

    long long sKey = getSubKey(line.sts);
    map<long long, long long>::iterator it = mIt->second.find(sKey);
    if (it == mIt->second.end())
    {
        mIt->second[sKey] = cnt;
        lines.push(line);
    }
    else
    {
        mIt->second[sKey] = cnt + it->second;
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif
    
#if DEBUG
    fscanf(fp, "%d %d", &n, &m);
#else
    cin >> n >> m;
#endif

    int end_x = 0, end_y = 0;

    for (size_t i = 0; i < m; i++)
    {
        string str;

        cin >> str;

        int c = str[0] - 'A' + 1;
        int r = str[1] - 'A' + 1;

        cells[r][c] = 1;

        if (r > end_x)
        {
            end_x = r;
        }

        if (c > end_y)
        {
            end_y = c;
        }
    }

    m = n; 
    n = end_x;

    // start
    Line start;
    start.x = 0;
    start.y = m;

    lines.push(start);

    flags[0][m] = 1;
    insertLine(start, 1);

    long long ans = 0;

    while (false == lines.empty())
    {
        Line pre = lines.front();
        lines.pop();

        int now_x = pre.x,
            now_y = pre.y;
        unsigned char state[MAX_M + 1] = {0};
        memcpy(state, pre.sts, sizeof(state));

        if (0 == flags[now_x][now_y])
        {
            // 第一次访问 (now_x, now_y)
            flags[now_x][now_y] = 1;
            cnts[act].clear();
            act = 1 - act;
        }

        long long pre_cnt = cnts[act][getMainKey(state)][getSubKey(state)];

        if (m == pre.y)
        {
            now_x++;
            now_y = 1;

            if (n < now_x)
            {
                continue;
            }
        }
        else
        {
            now_y++;
        }

        // (now_x, now_y) 将要处理的 cell
        if (1 == cells[now_x][now_y])
        {
            // 障碍物
            Line now;
            now.x = now_x;
            now.y = now_y;

            memcpy(now.sts, state, sizeof(now.sts));

            insertLine(now, pre_cnt);
        }
        else
        {
            if (now_y & 1)
            {
                // 2 个可以 in 的边
                // 上一个cell 同层的插头 - 0
                int st0 = getState(state, now_y - 1, 0);
                // 该列上一层cell 的向下插头 - 2
                int st2 = getState(state, now_y, 2);
                // 该列上一层cell 的右下插头 - 3, 作用在同层下一个cell
                int st3 = getState(state, now_y, 3);
                if (st3)
                {
                    // 由于处理完该 cell 会覆盖掉st3, 将st3转递给下一个 cell 的 是st1
                    setState(state, now_y + 1, 1, st3);
                }

                Line now;
                now.x = now_x;
                now.y = now_y;

                if (0 == st0 && 0 == st2)
                {
                    if (n > now_x && 1 < now_y && 0 == cells[now_x + 1][now_y - 1] && 0 == cells[now_x + 1][now_y])
                    {
                        unsigned char oneSt = 0;
                        oneSt = setOneState(oneSt, 1, 1);
                        oneSt = setOneState(oneSt, 2, 2);
                        state[now_y] = oneSt;

                        insertLine(now, pre_cnt);
                    }

                    if (n > now_x && 1 < now_y && m > now_y && 0 == cells[now_x + 1][now_y - 1])
                    {
                        if (0 == cells[now_x + 1][now_y + 1])
                        {
                            unsigned char oneSt = 0;
                            oneSt = setOneState(oneSt, 1, 1);
                            oneSt = setOneState(oneSt, 3, 2);
                            state[now_y] = oneSt;
                            insertLine(now, pre_cnt);
                        }

                        if (0 == cells[now_x][now_y + 1])
                        {
                            unsigned char oneSt = 0;
                            oneSt = setOneState(oneSt, 1, 1);
                            oneSt = setOneState(oneSt, 0, 2);
                            state[now_y] = oneSt;
                            insertLine(now, pre_cnt);
                        }
                    }

                    if (n > now_x && m > now_y)
                    {
                        if (0 == cells[now_x + 1][now_y])
                        {
                            if (0 == cells[now_x + 1][now_y + 1])
                            {
                                unsigned char oneSt = 0;
                                oneSt = setOneState(oneSt, 2, 1);
                                oneSt = setOneState(oneSt, 3, 2);
                                state[now_y] = oneSt;
                                insertLine(now, pre_cnt);

                                if (0 == cells[now_x][now_y + 1])
                                {
                                    unsigned char oneSt = 0;
                                    oneSt = setOneState(oneSt, 3, 1);
                                    oneSt = setOneState(oneSt, 0, 2);
                                    state[now_y] = oneSt;
                                    insertLine(now, pre_cnt);
                                }
                            }

                            if (0 == cells[now_x][now_y + 1])
                            {
                                unsigned char oneSt = 0;
                                oneSt = setOneState(oneSt, 1, 1);
                                oneSt = setOneState(oneSt, 0, 2);
                                state[now_y] = oneSt;
                                insertLine(now, pre_cnt);
                            }
                        }
                    }
                    
                }
                else if ((0 == st0 && 0 < st2) || (0 < st0 && 0 == st2))
                {
                    unsigned char st = st0 + st2;
                    if (n > now_x)
                    {
                        if (0 == cells[now_x + 1][now_y])
                        {
                            unsigned char oneSt = 0;
                            oneSt = setOneState(oneSt, 2, st);
                            state[now_y] = oneSt;
                            insertLine(now, pre_cnt);
                        }

                        if (1 < now_y && 0 == cells[now_x + 1][now_y - 1])
                        {
                            unsigned char oneSt = 0;
                            oneSt = setOneState(oneSt, 1, st);
                            state[now_y] = oneSt;
                            insertLine(now, pre_cnt);
                        }

                        if (m > now_y && 0 == cells[now_x + 1][now_y + 1])
                        {
                            unsigned char oneSt = 0;
                            oneSt = setOneState(oneSt, 3, st);
                            state[now_y] = oneSt;
                            insertLine(now, pre_cnt);
                        }
                    }

                    if (m > now_y) 
                    {
                        if (0 == cells[now_x][now_y + 1])
                        {
                            unsigned char oneSt = 0;
                            oneSt = setOneState(oneSt, 0, st);
                            state[now_y] = oneSt;
                            insertLine(now, pre_cnt);
                        }
                    }
                    
                }
                else if (1 == st0 && 1 == st2)
                {

                }
                else if (2 == st0 && 2 == st2)
                {

                } 
                else if (2 == st0 && 1 == st2)
                {

                } 
                else if (1 == st0 && 2 == st2)
                {

                }
            }
            else
            {
            }
        }
    }

    cout << ans << endl;

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
