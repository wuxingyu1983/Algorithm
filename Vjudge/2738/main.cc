// https://vjudge.net/problem/UVALive-2738
// https://www.papamelon.com/problem/119

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

#define DEBUG 0
#define MAX_N 1001

class Line
{
public:
    /*
        已经处理过（x, y）格子后，状态为state的个数cnt
    */
    int x, y;
    int state;

    Line()
    {
        x = y = 0;
        state = 0;
    }
};

queue<Line> lines;

inline int setState(int state, int pos, int val)
{
    int ret = state;

    // clear
    ret &= ~(3 << pos);

    ret |= val << pos;

    return ret;
}

map<int, vector<short> > cnts[2];
int act = 0; // 当前生效的 map
unsigned char flags[MAX_N][5];

void vecPlus(vector<short> &x, vector<short> &y, vector<short> &sum)
{
    int carry = 0;
    vector<short>::iterator itx = x.begin();
    vector<short>::iterator ity = y.begin();

    while (itx != x.end() && ity != y.end())
    {
        short tmp = *itx + *ity + carry;
        sum.push_back(tmp % 1000);
        carry = tmp / 1000;

        itx ++;
        ity ++;
    }

    while (itx != x.end())
    {
        short tmp = *itx + carry;
        sum.push_back(tmp % 1000);
        carry = tmp / 1000;

        itx ++;
    }
    
    while (ity != y.end())
    {
        short tmp = *ity + carry;
        sum.push_back(tmp % 1000);
        carry = tmp / 1000;

        ity ++;
    }

    if (0 < carry)
    {
        sum.push_back(carry);
    }
}

void vecPrint(int n, vector<short> &vec)
{
    cout << n << ": ";

    reverse(vec.begin(), vec.end());

    for (size_t i = 0; i < vec.size(); i++)
    {
        if (0 == i)
        {
            cout << vec[i];
        }
        else
        {
            cout << "," << setfill('0') << setw(3) << vec[i];
        }
    }

    cout << endl;
}

void insertLine(Line &line, vector<short> &cnt)
{
    // 判断是否已经存在了
    map<int, vector<short> >::iterator it = cnts[1 - act].find(line.state);
    if (it == cnts[1 - act].end())
    {
        cnts[1 - act][line.state] = cnt;
        lines.push(line);
    }
    else
    {
        // TBD
        vector<short> sum;
        vecPlus(cnt, it->second, sum);
        cnts[1 - act][line.state] = sum;
    }
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

    while (true)
    {
        bool f = false;

        string str_n;

        cin >> str_n;

        if ("#" == str_n)
        {
            break;
        }

        int n = stoi(str_n);

        // init
        cnts[0].clear();
        cnts[1].clear();
        act = 0;
        memset(flags, 0, MAX_N * 5);

        int m = 4;
        int end_x = n, end_y = 4;

        // start
        Line start;
        start.x = 0;
        start.y = m;
        start.state = 0;

        lines.push(start);

        flags[0][m] = 1;

        vector<short> tmp;
        tmp.push_back(1);
        cnts[act][0] = tmp;

        vector<short> ans;

        while (false == lines.empty())
        {
            Line pre = lines.front();
            lines.pop();

            int now_x = pre.x,
                now_y = pre.y;
            int state = pre.state;

            if (0 == flags[now_x][now_y])
            {
                // 第一次访问 (now_x, now_y)
                flags[now_x][now_y] = 1;
                cnts[act].clear();
                act = 1 - act;
            }

            vector<short> pre_cnt = cnts[act][state];

            if (m == pre.y)
            {
                now_x++;
                now_y = 1;
                state <<= 2;
            }
            else
            {
                now_y++;
            }

            int i = (state >> ((now_y - 1) * 2)) & 3;
            int j = (state >> (now_y * 2)) & 3;

            Line now;
            now.x = now_x;
            now.y = now_y;

            if (0 == i && 0 == j)
            {
                if (m > now_y && end_x > now_x)
                {
                    state = setState(state, (now_y - 1) * 2, 1);
                    state = setState(state, now_y * 2, 2);

                    now.state = state;

                    insertLine(now, pre_cnt);
                }
            }
            else if (0 == i && 0 < j)
            {
                if (m > now_y)
                {
                    now.state = state;
                    insertLine(now, pre_cnt);
                }

                if (end_x > now_x)
                {
                    state = setState(state, (now_y - 1) * 2, j);
                    state = setState(state, now_y * 2, 0);

                    now.state = state;
                    insertLine(now, pre_cnt);
                }
            }
            else if (0 < i && 0 == j)
            {
                if (end_x > now_x)
                {
                    now.state = state;
                    insertLine(now, pre_cnt);
                }

                if (m > now_y)
                {
                    state = setState(state, (now_y - 1) * 2, 0);
                    state = setState(state, now_y * 2, i);

                    now.state = state;
                    insertLine(now, pre_cnt);
                }
            }
            else if (1 == i && 1 == j)
            {
                state = setState(state, (now_y - 1) * 2, 0);
                state = setState(state, now_y * 2, 0);

                int pos = (now_y + 1) * 2;
                int s = 1;
                while (pos <= m * 2)
                {
                    if (1 == ((state >> pos) & 3))
                    {
                        s++;
                    }
                    else if (2 == ((state >> pos) & 3))
                    {
                        s--;
                        if (0 == s)
                        {
                            state = setState(state, pos, 1);
                            now.state = state;
                            insertLine(now, pre_cnt);
                            break;
                        }
                    }

                    pos += 2;
                }
            }
            else if (2 == i && 2 == j)
            {
                state = setState(state, (now_y - 1) * 2, 0);
                state = setState(state, now_y * 2, 0);

                int pos = (now_y - 2) * 2;
                int s = 1;
                while (0 <= pos)
                {
                    if (2 == ((state >> pos) & 3))
                    {
                        s++;
                    }
                    else if (1 == ((state >> pos) & 3))
                    {
                        s--;
                        if (0 == s)
                        {
                            state = setState(state, pos, 2);
                            now.state = state;
                            insertLine(now, pre_cnt);
                            break;
                        }
                    }

                    pos -= 2;
                }
            }
            else if (2 == i && 1 == j)
            {
                state = setState(state, (now_y - 1) * 2, 0);
                state = setState(state, now_y * 2, 0);
                now.state = state;
                insertLine(now, pre_cnt);
            }
            else if (1 == i && 2 == j)
            {
                if (end_x == now_x && end_y == now_y)
                {
                    state = setState(state, (now_y - 1) * 2, 0);
                    state = setState(state, now_y * 2, 0);

                    if (0 == state)
                    {
                        vecPlus(pre_cnt, pre_cnt, ans);
                        vecPrint(n, ans);
                        f = true;
                    }
                }
            }
        }

        if (false == f)
        {
            cout << n << ": " << 0 << endl;
        }
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
