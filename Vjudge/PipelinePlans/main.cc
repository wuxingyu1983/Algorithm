// https://vjudge.net/problem/Aizu-2452

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

#define ST1_BITS 3
#define ST1_MASK 7
#define ST2_BITS 4
#define ST2_MASK 15
#define QS_SIZE 600000

class Record
{
public:
    unsigned short state1;     // 轮廓线段状态
    unsigned long long state2; // 各种类瓷砖的数量
    unsigned long long cnt;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2][4096];
int pos[13] = {0, 1, 3, 2, 6, 5, 4, 7, 9, 8, 11, 10, 12};

int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long ans = 0;
int gMask = 0;

#define getVal4St1(ST, POS) ((ST) >> ((POS)*ST1_BITS)) & ST1_MASK

#define setVal4St1(NEW, OLD, POS, VAL)      \
    NEW = OLD;                              \
    NEW &= ~(ST1_MASK << ((POS)*ST1_BITS)); \
    NEW |= (VAL) << ((POS)*ST1_BITS);

#define getVal4St2(ST, POS) ((ST) >> ((POS)*ST2_BITS)) & ST2_MASK

#define setVal4St2(NEW, OLD, POS, VAL)                            \
    NEW = OLD;                                                    \
    NEW &= ~(((unsigned long long)ST2_MASK) << ((POS)*ST2_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST2_BITS);

inline unsigned short recode(unsigned short st)
{
    unsigned short ret = st;

    int bb[10];
    memset(bb, -1, sizeof(bb));
    int bn = 2;
    bb[0] = 0;
    for (int i = 0; i <= w; i++)
    {
        int tmp = getVal4St1(st, i);
        if (tmp)
        {
            if (1 == tmp)
            {
                bb[1] = 1;
            }
            else
            {
                if (0 > bb[tmp])
                {
                    bb[tmp] = bn++;
                }
                setVal4St1(ret, ret, i, bb[tmp]);
            }
        }
    }

    if (0 > bb[1])
    {
        // invalid
        ret = 0;
    }

    return ret;
}

inline int findMinUnused(unsigned short st)
{
    int ret = 0;

    for (int i = 0; i <= w; i++)
    {
        int tmp = getVal4St1(st, i);
        if (tmp > ret)
        {
            ret = tmp;
        }
    }

    ret++;

    return ret;
}

inline void addSts(unsigned short st1, unsigned long long st2, unsigned long long cnt, int idx)
{
    if (w == now_y)
    {
        st1 &= gMask;
    }

    unsigned short key = recode(st1);

    if (0 < key)
    {
        unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx][key].find(st2);
        if (it == cnts[idx][key].end())
        {
            int pInQ = qTail[idx];
            // 加入队尾
            qs[idx][pInQ].state1 = key;
            qs[idx][pInQ].state2 = st2;
            qs[idx][pInQ].cnt = cnt;

            cnts[idx][key][st2] = pInQ;
            qTail[idx]++;
        }
        else
        {
            qs[idx][it->second].cnt += cnt;
        }
    }
}

int main()
{
    cin >> h >> w;

    int t[13];
    if (h < w)
    {
        // swap
        for (int i = 1; i <= 12; i++)
        {
            cin >> t[pos[i]];
        }

        swap(h, w);
    }
    else
    {
        for (int i = 1; i <= 12; i++)
        {
            cin >> t[i];
        }
    }

    // init
    unsigned long long st = 0;

    for (int i = 1; i <= 12; i++)
    {
        if (t[i])
        {
            setVal4St2(st, st, i, t[i]);
        }
    }

    gMask = (1 << (w * ST1_BITS)) - 1;

    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qs[act][0].state1 = 0;
    qs[act][0].state2 = st;
    qs[act][0].cnt = 1;

    qTail[act]++;

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
                break;
            }
        }
        else
        {
            now_y++;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned short st1 = qs[act][iQ].state1;
            unsigned long long st2 = qs[act][iQ].state2;
            unsigned long long cnt = qs[act][iQ].cnt;

            if (1 == now_y)
            {
                st1 <<= ST1_BITS;
            }

            int left = getVal4St1(st1, now_y - 1);
            int up = getVal4St1(st1, now_y);

            int minUnused = findMinUnused(st1);

            unsigned short newst1;
            unsigned long long newst2;
            for (int type = 2; type <= 12; type++)
            {
                int remain = getVal4St2(st2, type);

                if (0 < remain)
                {
                    newst1 = st1;

                    switch (type)
                    {
                    case 2:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (up)
                            {
                                setVal4St1(newst1, newst1, now_y - 1, up);
                            }
                            else
                            {
                                setVal4St1(newst1, newst1, now_y - 1, minUnused);
                            }
                            setVal4St1(newst1, newst1, now_y, 0);
                        }
                    }
                    break;
                    case 3:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            setVal4St1(newst1, newst1, now_y - 1, 0);
                            if (left)
                            {
                                setVal4St1(newst1, newst1, now_y, left);
                            }
                            else
                            {
                                setVal4St1(newst1, newst1, now_y, minUnused);
                            }
                        }
                    }
                    break;
                    case 4:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            setVal4St1(newst1, newst1, now_y - 1, 0);
                            if (up)
                            {
                                setVal4St1(newst1, newst1, now_y, up);
                            }
                            else
                            {
                                setVal4St1(newst1, newst1, now_y, minUnused);
                            }
                        }
                    }
                    break;
                    case 5:
                    {
                        if (h == now_x && w == now_y)
                        {
                            continue;
                        }
                        else
                        {
                            setVal4St1(newst1, newst1, now_y - 1, minUnused);
                            setVal4St1(newst1, newst1, now_y, minUnused);
                        }
                    }
                    break;
                    case 6:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (left)
                            {
                                setVal4St1(newst1, newst1, now_y - 1, left);
                            }
                            else
                            {
                                setVal4St1(newst1, newst1, now_y - 1, minUnused);
                            }
                            setVal4St1(newst1, newst1, now_y, 0);
                        }
                    }
                    break;
                    case 7:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left || 1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (left && up)
                            {
                                if (left != up)
                                {
                                    bool flag = false;
                                    if (left > up)
                                    {
                                        flag = true;
                                        swap(left, up);
                                    }

                                    // left < up, up ==> left
                                    for (int i = 0; i <= w; i++)
                                    {
                                        int tmp = getVal4St1(newst1, i);
                                        if (tmp == up)
                                        {
                                            setVal4St1(newst1, newst1, i, left);
                                        }
                                    }

                                    if (flag)
                                    {
                                        swap(left, up);
                                    }
                                }
                            }

                            setVal4St1(newst1, newst1, now_y - 1, 0);
                            setVal4St1(newst1, newst1, now_y, 0);
                        }
                    }
                    break;
                    case 8:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (up)
                            {
                                setVal4St1(newst1, newst1, now_y - 1, up);
                                setVal4St1(newst1, newst1, now_y, up);
                            }
                            else
                            {
                                setVal4St1(newst1, newst1, now_y - 1, minUnused);
                                setVal4St1(newst1, newst1, now_y, minUnused);
                            }
                        }
                    }
                    break;
                    case 9:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (left)
                            {
                                setVal4St1(newst1, newst1, now_y - 1, left);
                                setVal4St1(newst1, newst1, now_y, left);
                            }
                            else
                            {
                                setVal4St1(newst1, newst1, now_y - 1, minUnused);
                                setVal4St1(newst1, newst1, now_y, minUnused);
                            }
                        }
                    }
                    break;
                    case 10:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left || 1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (left && up)
                            {
                                bool flag = false;

                                if (left != up)
                                {
                                    if (left > up)
                                    {
                                        flag = true;
                                        swap(left, up);
                                    }

                                    // left < up, up ==> left
                                    for (int i = 0; i <= w; i++)
                                    {
                                        int tmp = getVal4St1(newst1, i);
                                        if (tmp == up)
                                        {
                                            setVal4St1(newst1, newst1, i, left);
                                        }
                                    }
                                }

                                setVal4St1(newst1, newst1, now_y - 1, left);

                                if (flag)
                                {
                                    swap(left, up);
                                }
                            }
                            else if (0 == left && 0 == up)
                            {
                                setVal4St1(newst1, newst1, now_y - 1, minUnused);
                            }
                            else
                            {
                                // left, up 中有一个 > 0
                                setVal4St1(newst1, newst1, now_y - 1, (left + up));
                            }
                            setVal4St1(newst1, newst1, now_y, 0);
                        }
                    }
                    break;
                    case 11:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left || 1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            setVal4St1(newst1, newst1, now_y - 1, 0);
                            if (left && up)
                            {
                                bool flag = false;

                                if (left != up)
                                {
                                    if (left > up)
                                    {
                                        flag = true;
                                        swap(left, up);
                                    }

                                    // left < up, up ==> left
                                    for (int i = 0; i <= w; i++)
                                    {
                                        int tmp = getVal4St1(newst1, i);
                                        if (tmp == up)
                                        {
                                            setVal4St1(newst1, newst1, i, left);
                                        }
                                    }
                                }

                                setVal4St1(newst1, newst1, now_y, left);

                                if (flag)
                                {
                                    swap(left, up);
                                }
                            }
                            else if (0 == left && 0 == up)
                            {
                                setVal4St1(newst1, newst1, now_y, minUnused);
                            }
                            else
                            {
                                // left, up 中有一个 > 0
                                setVal4St1(newst1, newst1, now_y, (left + up));
                            }
                        }
                    }
                    break;
                    case 12:
                    default:
                    {
                        if (h == now_x && w == now_y)
                        {
                            if (1 == left || 1 == up)
                            {
                                ans += cnt;
                            }
                            continue;
                        }
                        else
                        {
                            if (left && up)
                            {
                                bool flag = false;

                                if (left != up)
                                {
                                    if (left > up)
                                    {
                                        flag = true;
                                        swap(left, up);
                                    }

                                    // left < up, up ==> left
                                    for (int i = 0; i <= w; i++)
                                    {
                                        int tmp = getVal4St1(newst1, i);
                                        if (tmp == up)
                                        {
                                            setVal4St1(newst1, newst1, i, left);
                                        }
                                    }
                                }

                                setVal4St1(newst1, newst1, now_y - 1, left);
                                setVal4St1(newst1, newst1, now_y, left);

                                if (flag)
                                {
                                    swap(left, up);
                                }
                            }
                            else if (0 == left && 0 == up)
                            {
                                setVal4St1(newst1, newst1, now_y - 1, minUnused);
                                setVal4St1(newst1, newst1, now_y, minUnused);
                            }
                            else
                            {
                                // left, up 中有一个 > 0
                                setVal4St1(newst1, newst1, now_y - 1, (left + up));
                                setVal4St1(newst1, newst1, now_y, (left + up));
                            }
                        }
                    }
                    break;
                    }

                    setVal4St2(newst2, st2, type, remain - 1);

                    addSts(newst1, newst2, cnt, nAct);
                }
            }

            if (false == (1 == now_x && 1 == now_y) && false == (h == now_x && w == now_y))
            {
                // type 1
                int remain = getVal4St2(st2, 1);
                if (0 < remain)
                {
                    newst1 = st1;
                    setVal4St1(newst1, newst1, now_y - 1, 0);
                    setVal4St1(newst1, newst1, now_y, 0);

                    setVal4St2(newst2, st2, 1, remain - 1);

                    addSts(newst1, newst2, cnt, nAct);
                }
            }
        }

        qTail[act] = 0;
        for (int i = 0; i < 4096; i++)
        {
            cnts[act][i].clear();
        }
        act = nAct;
    }

    cout << ans << endl;

    return 0;
}
