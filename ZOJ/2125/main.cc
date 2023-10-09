// https://vjudge.net/problem/ZOJ-2125

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

#define ST_BITS 4
#define ST_MASK 15
#define QS_SIZE 1000000

class Record
{
public:
    unsigned long long state;
    int cnt;
    unsigned int minUnused;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int h = 6, w = 9;
unordered_map<unsigned long long, unsigned int> cnts[2];
char cells[7][10];

int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long gMask = 0;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)                           \
    NEW = OLD;                                                  \
    NEW &= ~(((unsigned long long)ST_MASK) << ((POS)*ST_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST_BITS);

inline void addSts(unsigned long long st, int idx)
{
    if (w == now_y)
    {
        st &= gMask;
    }

    int bb[16];
    unsigned long long key = st;

    memset(bb, -1, sizeof(bb));
    int bn = 2;
    bb[0] = 0;
    bb[1] = 0;
    for (int i = 0; i <= w; i++)
    {
        int tmp = getVal4St(st, i);
        if (tmp)
        {
            if (1 == tmp)
            {
                bb[1]++;
            }
            else
            {
                if (0 > bb[tmp])
                {
                    bb[tmp] = bn++;
                }
                setVal4St(key, key, i, bb[tmp]);
            }
        }
    }

    if (0 < bb[1])
    {
        unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx].find(key);
        if (it == cnts[idx].end())
        {
            int pInQ = qTail[idx];
            // 加入队尾
            qs[idx][pInQ].state = key;
            qs[idx][pInQ].cnt = bb[1];
            qs[idx][pInQ].minUnused = bn;

            cnts[idx][key] = pInQ;
            qTail[idx]++;
        }
    }
}

inline void init(int start)
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].state = ((unsigned long long)1) << ((start - 1) * ST_BITS);
    qs[act][0].cnt = 1;

    qTail[act]++;
}

int main()
{
    gMask = ((unsigned long long)1) << (9 * ST_BITS);
    gMask -= 1;

    int start;
    while (scanf("%d", &start))
    {
        for (size_t col = 1; col <= 9; col++)
        {
            for (size_t row = 1; row <= 6; row++)
            {
                cin >> cells[row][col];
            }
        }

        // init
        init(start);

        int ans = 0;

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (w == now_y)
            {
                now_x++;
                now_y = 1;

                if (h < now_x)
                {
                    // finished
                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        if (ans < qs[act][iQ].cnt)
                        {
                            ans = qs[act][iQ].cnt;
                        }
                    }
                    break;
                }
            }
            else
            {
                now_y++;
            }

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                int cnt = qs[act][iQ].cnt;
                unsigned int minUnused = qs[act][iQ].minUnused;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if ('.' == cells[now_x][now_y])
                {
                    // empty
                    if (1 == left)
                    {
                        cnt--;
                    }
                    if (1 == up)
                    {
                        cnt--;
                    }

                    if (0 < cnt)
                    {
                        unsigned long long newst = st;

                        setVal4St(newst, newst, now_y - 1, 0);
                        setVal4St(newst, newst, now_y, 0);

                        addSts(newst, nAct);
                    }
                }
                else if ('-' == cells[now_x][now_y])
                {
                    unsigned long long newst = st;

                    // '-'
                    if (false == (1 == cnt && 1 == up))
                    {
                        setVal4St(newst, newst, now_y - 1, 0);
                        if (left)
                        {
                            setVal4St(newst, newst, now_y, left);
                        }
                        else
                        {
                            setVal4St(newst, newst, now_y, minUnused);
                        }
                        addSts(newst, nAct);
                    }

                    // '|'
                    if (false == (1 == cnt && 1 == left))
                    {
                        if (up)
                        {
                            setVal4St(newst, newst, now_y - 1, up);
                        }
                        else
                        {
                            setVal4St(newst, newst, now_y - 1, minUnused);
                        }
                        setVal4St(newst, newst, now_y, 0);

                        addSts(newst, nAct);
                    }
                }
                else if ('L' == cells[now_x][now_y])
                {
                    unsigned long long newst = st;

                    // '|_'
                    if (false == (1 == cnt && 1 == left))
                    {
                        setVal4St(newst, newst, now_y - 1, 0);

                        if (up)
                        {
                            setVal4St(newst, newst, now_y, up);
                        }
                        else
                        {
                            setVal4St(newst, newst, now_y, minUnused);
                        }

                        addSts(newst, nAct);
                    }

                    // 右转90度
                    {
                        if (1 == left)
                        {
                            cnt--;
                        }
                        if (1 == up)
                        {
                            cnt--;
                        }

                        if (0 < cnt)
                        {
                            setVal4St(newst, newst, now_y - 1, minUnused);
                            setVal4St(newst, newst, now_y, minUnused);

                            addSts(newst, nAct);
                        }
                    }

                    cnt = qs[act][iQ].cnt;

                    // 右转90度
                    if (false == (1 == cnt && 1 == up))
                    {
                        if (left)
                        {
                            setVal4St(newst, newst, now_y - 1, left);
                        }
                        else
                        {
                            setVal4St(newst, newst, now_y - 1, minUnused);
                        }

                        setVal4St(newst, newst, now_y, 0);

                        addSts(newst, nAct);
                    }

                    // 右转90度, '_|'
                    {
                        newst = st;

                        if (left && up)
                        {
                            if (left != up)
                            {
                                if (left > up)
                                {
                                    swap(left, up);
                                }

                                // left < up, up ==> left
                                for (int i = 0; i <= w; i++)
                                {
                                    int tmp = getVal4St(newst, i);
                                    if (tmp == up)
                                    {
                                        setVal4St(newst, newst, i, left);
                                    }
                                }
                            }
                        }

                        setVal4St(newst, newst, now_y - 1, 0);
                        setVal4St(newst, newst, now_y, 0);

                        addSts(newst, nAct);
                    }
                }
                else if ('T' == cells[now_x][now_y])
                {
                    unsigned long long newst = st;

                    {
                        if (left && up)
                        {
                            if (left != up)
                            {
                                if (left > up)
                                {
                                    swap(left, up);
                                }

                                // left < up, up ==> left
                                for (int i = 0; i <= w; i++)
                                {
                                    int tmp = getVal4St(newst, i);
                                    if (tmp == up)
                                    {
                                        setVal4St(newst, newst, i, left);
                                    }
                                }
                            }

                            // '_|_'
                            setVal4St(newst, newst, now_y - 1, 0);
                            setVal4St(newst, newst, now_y, left);

                            addSts(newst, nAct);

                            // 左转90度
                            setVal4St(newst, newst, now_y - 1, left);
                            setVal4St(newst, newst, now_y, 0);

                            addSts(newst, nAct);
                        }
                        else if (0 == left && 0 == up)
                        {
                            // '_|_'
                            setVal4St(newst, newst, now_y - 1, 0);
                            setVal4St(newst, newst, now_y, minUnused);

                            addSts(newst, nAct);

                            // 左转90度
                            setVal4St(newst, newst, now_y - 1, minUnused);
                            setVal4St(newst, newst, now_y, 0);

                            addSts(newst, nAct);
                        }
                        else
                        {
                            // left 和 up 有一个非0
                            // '_|_'
                            setVal4St(newst, newst, now_y - 1, 0);
                            setVal4St(newst, newst, now_y, (left + up));

                            addSts(newst, nAct);

                            // 左转90度
                            setVal4St(newst, newst, now_y - 1, (left + up));
                            setVal4St(newst, newst, now_y, 0);

                            addSts(newst, nAct);
                        }
                    }

                    newst = st;

                    // 左转90度
                    if (false == (1 == cnt && 1 == up))
                    {
                        if (left)
                        {
                            setVal4St(newst, newst, now_y - 1, left);
                            setVal4St(newst, newst, now_y, left);
                        }
                        else
                        {
                            setVal4St(newst, newst, now_y - 1, minUnused);
                            setVal4St(newst, newst, now_y, minUnused);
                        }

                        addSts(newst, nAct);
                    }

                    // 左转90度
                    if (false == (1 == cnt && 1 == left))
                    {
                        if (up)
                        {
                            setVal4St(newst, newst, now_y - 1, up);
                            setVal4St(newst, newst, now_y, up);
                        }
                        else
                        {
                            setVal4St(newst, newst, now_y - 1, minUnused);
                            setVal4St(newst, newst, now_y, minUnused);
                        }

                        addSts(newst, nAct);
                    }
                }
                else
                {
                    unsigned long long newst = st;

                    // '+'
                    if (left && up)
                    {
                        if (left != up)
                        {
                            if (left > up)
                            {
                                swap(left, up);
                            }

                            // left < up, up ==> left
                            for (int i = 0; i <= w; i++)
                            {
                                int tmp = getVal4St(newst, i);
                                if (tmp == up)
                                {
                                    setVal4St(newst, newst, i, left);
                                }
                            }
                        }

                        // '_|_'
                        setVal4St(newst, newst, now_y - 1, left);
                        setVal4St(newst, newst, now_y, left);

                        addSts(newst, nAct);
                    }
                    else if (0 == left && 0 == up)
                    {
                        setVal4St(newst, newst, now_y - 1, minUnused);
                        setVal4St(newst, newst, now_y, minUnused);

                        addSts(newst, nAct);
                    }
                    else
                    {
                        // left 和 up 有一个非0
                        setVal4St(newst, newst, now_y - 1, (left + up));
                        setVal4St(newst, newst, now_y, (left + up));

                        addSts(newst, nAct);
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        cout << ans << endl;
    }

    return 0;
}
