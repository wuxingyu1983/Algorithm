// http://poj.org/problem;jsessionid=49743215C3FBD3C529FBB64C68579633?id=3133

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
// #include <unordered_map>
#include <map>
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
#define MAX_W 10
#define MAX_H 10
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned int len;

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
// unordered_map<unsigned int, unsigned int> cnts[2];
map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)     \
    NEW = OLD;                            \
    NEW &= ~(ST_MASK << ((POS)*ST_BITS)); \
    NEW |= (VAL) << ((POS)*ST_BITS);

inline void init()
{
    // 每一个 test 前，初始化
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    cnts[0].clear();
    cnts[1].clear();

    now_x = 0;
    now_y = w;

    qs[act][0].state = 0;
    qs[act][0].len = 0;

    qTail[act]++;
}

inline void addSts(unsigned int st, unsigned int len, int idx)
{
    //    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    map<unsigned int, unsigned int>::iterator it = cnts[idx].find(st);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = st;
        qs[idx][pInQ].len = len;

        cnts[idx][st] = pInQ;
        qTail[idx]++;
    }
    else
    {
        if (len < qs[idx][it->second].len)
        {
            qs[idx][it->second].len = len;
        }
    }
}

inline void forwardFunc(unsigned int &newSt, int plusVal, int minusVal, int newVal)
{
    int pos = now_y + 1;
    int s = 1;
    while (pos <= w)
    {
        int v = getVal4St(newSt, pos);
        if (plusVal == v)
        {
            s++;
        }
        else if (minusVal == v)
        {
            s--;
            if (0 == s)
            {
                setVal4St(newSt, newSt, pos, newVal);
                break;
            }
        }

        pos++;
    }
}

inline void backwardFunc(unsigned int &newSt, int plusVal, int minusVal, int newVal)
{
    int pos = now_y - 2;
    int s = 1;
    while (0 <= pos)
    {
        int v = getVal4St(newSt, pos);
        if (plusVal == v)
        {
            s++;
        }
        else if (minusVal == v)
        {
            s--;
            if (0 == s)
            {
                setVal4St(newSt, newSt, pos, newVal);
                break;
            }
        }

        pos--;
    }
}

int main()
{
    while (true)
    {
        cin >> h >> w;

        if (0 == h && 0 == w)
        {
            break;
        }

        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }

        init();

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
                        if (0 == qs[act][iQ].state)
                        {
                            if (0 == ans || ans > (qs[act][iQ].len - 2))
                            {
                                ans = qs[act][iQ].len - 2;
                            }
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
                unsigned int st = qs[act][iQ].state;
                unsigned int len = qs[act][iQ].len;

                if (1 == now_y)
                {
                    st <<= ST_BITS;
                }

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                if ('1' == cells[now_x][now_y])
                {
                    // 障碍物
                    addSts(st, len, nAct);
                }
                else if ('0' == cells[now_x][now_y])
                {
                    if (0 == left && 0 == up)
                    {
                        // do nothing
                        addSts(st, len, nAct);

                        if (h > now_x && w > now_y && '1' != cells[now_x + 1][now_y] && '1' != cells[now_x][now_y + 1])
                        {
                            int rightUp = getVal4St(st, now_y + 1);
                            if (rightUp && ('2' != cells[now_x][now_y + 1] || '3' != cells[now_x][now_y + 1]))
                            {
                                continue;
                            }

                            unsigned int newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 1);
                            setVal4St(newSt, newSt, now_y, 2);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                    else if (0 == left || 0 == up)
                    {
                        // 有1个 plug
                        int val = left + up;
                        unsigned int newSt;

                        if (h > now_x && '1' != cells[now_x + 1][now_y])
                        {
                            if ((3 == val && '3' == cells[now_x + 1][now_y]) || (6 == val && '2' == cells[now_x + 1][now_y]))
                            {
                                continue;
                            }

                            newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, val);
                            setVal4St(newSt, newSt, now_y, 0);

                            addSts(newSt, len + 1, nAct);
                        }

                        if (w > now_y && '1' != cells[now_x][now_y + 1])
                        {
                            if ((3 == val && '3' == cells[now_x][now_y + 1]) || (6 == val && '2' == cells[now_x][now_y + 1]))
                            {
                                continue;
                            }

                            int rightUp = getVal4St(st, now_y + 1);
                            if (rightUp && ('2' != cells[now_x][now_y + 1] || '3' != cells[now_x][now_y + 1]))
                            {
                                continue;
                            }

                            newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 0);
                            setVal4St(newSt, newSt, now_y, val);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                    else
                    {
                        // 有2个 plug
                        unsigned int newSt = st;

                        if ((3 == left && 3 == up) || (6 == left && 6 == up))
                        {
                            // do nothing
                        }
                        else if (3 == left || 3 == up)
                        {
                            if (1 == left || 1 == up)
                            {
                                forwardFunc(newSt, 1, 2, 3);
                            }
                            else if (2 == left || 2 == up)
                            {
                                backwardFunc(newSt, 2, 1, 3);
                            }
                            else
                            {
                                // 非法
                                continue;
                            }
                        }
                        else if (6 == left || 6 == up)
                        {
                            if (1 == left || 1 == up)
                            {
                                forwardFunc(newSt, 1, 2, 6);
                            }
                            else if (2 == left || 2 == up)
                            {
                                backwardFunc(newSt, 2, 1, 6);
                            }
                            else
                            {
                                // 非法
                                continue;
                            }
                        }
                        else if (1 == left && 1 == up)
                        {
                            forwardFunc(newSt, 1, 2, 1);
                        }
                        else if (2 == left && 2 == up)
                        {
                            backwardFunc(newSt, 2, 1, 2);
                        }
                        else if (2 == left && 1 == up)
                        {
                            // do nothing
                        }
                        else
                        {
                            // 非法
                            continue;
                        }

                        setVal4St(newSt, newSt, now_y - 1, 0);
                        setVal4St(newSt, newSt, now_y, 0);

                        addSts(newSt, len + 1, nAct);
                    }
                }
                else if ('2' == cells[now_x][now_y])
                {
                    unsigned int newSt = st;
                    if (0 == left && 0 == up)
                    {
                        if (h > now_x && '1' != cells[now_x + 1][now_y])
                        {
                            if ('3' == cells[now_x + 1][now_y])
                            {
                                continue;
                            }

                            newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 3);
                            setVal4St(newSt, newSt, now_y, 0);

                            addSts(newSt, len + 1, nAct);
                        }

                        if (w > now_y && '1' != cells[now_x][now_y + 1])
                        {
                            if ('3' == cells[now_x][now_y + 1])
                            {
                                continue;
                            }

                            int rightUp = getVal4St(st, now_y + 1);
                            if (rightUp && ('2' != cells[now_x][now_y + 1] || '3' != cells[now_x][now_y + 1]))
                            {
                                continue;
                            }

                            newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 0);
                            setVal4St(newSt, newSt, now_y, 3);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                    else if (0 == left || 0 == up)
                    {
                        int val = left + up;
                        if (3 == val)
                        {
                            // do nothing
                        }
                        else if (1 == val)
                        {
                            forwardFunc(newSt, 1, 2, 3);
                        }
                        else if (2 == val)
                        {
                            backwardFunc(newSt, 2, 1, 3);
                        }
                        else
                        {
                            // 非法
                            continue;
                        }

                        setVal4St(newSt, newSt, now_y - 1, 0);
                        setVal4St(newSt, newSt, now_y, 0);

                        addSts(newSt, len + 1, nAct);
                    }
                }
                else
                {
                    // '3' == cells[now_x][now_y]
                    unsigned int newSt = st;
                    if (0 == left && 0 == up)
                    {
                        if (h > now_x && '1' != cells[now_x + 1][now_y])
                        {
                            if ('2' == cells[now_x + 1][now_y])
                            {
                                continue;
                            }

                            newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 6);
                            setVal4St(newSt, newSt, now_y, 0);

                            addSts(newSt, len + 1, nAct);
                        }

                        if (w > now_y && '1' != cells[now_x][now_y + 1])
                        {
                            if ('2' == cells[now_x][now_y + 1])
                            {
                                continue;
                            }

                            int rightUp = getVal4St(st, now_y + 1);
                            if (rightUp && ('2' != cells[now_x][now_y + 1] || '3' != cells[now_x][now_y + 1]))
                            {
                                continue;
                            }

                            newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 0);
                            setVal4St(newSt, newSt, now_y, 6);

                            addSts(newSt, len + 1, nAct);
                        }
                    }
                    else if (0 == left || 0 == up)
                    {
                        int val = left + up;
                        if (6 == val)
                        {
                            // do nothing
                        }
                        else if (1 == val)
                        {
                            forwardFunc(newSt, 1, 2, 6);
                        }
                        else if (2 == val)
                        {
                            backwardFunc(newSt, 2, 1, 6);
                        }
                        else
                        {
                            // 非法
                            continue;
                        }

                        setVal4St(newSt, newSt, now_y - 1, 0);
                        setVal4St(newSt, newSt, now_y, 0);

                        addSts(newSt, len + 1, nAct);
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
