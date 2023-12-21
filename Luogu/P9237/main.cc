// https://www.luogu.com.cn/problem/P9237

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

#define DEBUG 0
#define MAX_HW 11
#define QS_SIZE 60000
#define ST_BITS 4
#define ST_MASK 15

#define getVal4St1(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St1(ST, POS, VAL)                                 \
    ST &= ~(((unsigned long long)ST_MASK) << ((POS) * ST_BITS)); \
    if (VAL)                                                     \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

#define getVal4St2(ST, POS) ((ST) >> (POS)) & 1

#define setVal4St2(ST, POS, VAL) \
    ST &= ~(1 << (POS));         \
    if (VAL)                     \
        ST |= (VAL) << (POS);

#define addSts(ST1, ST2, REC, VAL, IDX)                                                     \
    {                                                                                       \
        unsigned long long key = (ST1 << (w + 1)) + ST2;                                    \
        unordered_map<unsigned long long, unsigned int>::iterator it = cnts[IDX].find(key); \
        if (it == cnts[IDX].end())                                                          \
        {                                                                                   \
            int pInQ = qTail[IDX];                                                          \
            qs[IDX][pInQ].state1 = ST1;                                                     \
            qs[IDX][pInQ].state2 = ST2;                                                     \
            memcpy(qs[IDX][pInQ].cache, REC.cache, sizeof(REC.cache));                      \
            setVal4St2(qs[IDX][pInQ].cache[now_x], now_y, VAL);                             \
            cnts[IDX][key] = pInQ;                                                          \
            qTail[IDX]++;                                                                   \
        }                                                                                   \
    }

class Record
{
public:
    unsigned long long state1; // 轮廓线段上数字（周边还有几个）状态
    unsigned short state2;     // 轮廓线段上像素（0, 1）状态
    unsigned short cache[MAX_HW];

    Record() {}
};

int h, w;
char cells[MAX_HW][MAX_HW];
Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

void init()
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    qTail[act]++;
}

int main()
{
    cin >> h >> w;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> cells[row][col];
        }
    }

    init();

    unsigned long long st1Mask = (1 << (ST_BITS * w)) - 1;
    unsigned short st2Mask = (1 << w) - 1;

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
/*
                    int row = 1;
                    for (row = 1; row <= h; row++)
                    {
                        if (0 < qs[act][iQ].cache[row])
                        {
                            break;
                        }
                    }

                    if (row > h)
*/
                    {
                        for (size_t i = 1; i <= h; i++)
                        {
                            for (size_t j = 1; j < w; j++)
                            {
                                if (getVal4St2(qs[act][iQ].cache[i], j))
                                {
                                    cout << 1;
                                }
                                else
                                {
                                    cout << 0;
                                }
                            }
                            cout << endl << endl;
                        }

                        break;
                    }
                }

                break;
            }
        }
        else
        {
            now_y++;
        }

        int remain = 0;
        if (h > now_x)
        {
            remain++;

            if (1 < now_y)
            {
                remain++;
            }

            if (w > now_y)
            {
                remain++;
            }
        }

        if (w > now_y)
        {
            remain++;
        }

        for (size_t iQ = 0; iQ < qTail[act]; iQ++)
        {
            unsigned long long st1 = qs[act][iQ].state1;
            unsigned short st2 = qs[act][iQ].state2;

            if (1 == now_y)
            {
                st1 &= st1Mask;
                st1 <<= ST_BITS;

                st2 &= st2Mask;
                st2 <<= 1;
            }

            int leftCnt = 0;
            if (1 < now_y)
            {
                leftCnt = getVal4St1(st1, now_y - 2);
            }
            int leftUpCnt = getVal4St1(st1, now_y - 1);
            int upCnt = getVal4St1(st1, now_y);
            int rightUpCnt = getVal4St1(st1, now_y + 1);

            int leftPixel = 0;
            if (1 < now_y)
            {
                leftPixel = getVal4St2(st2, now_y - 2);
            }
            int leftUpPixel = getVal4St2(st2, now_y - 1);
            int upPixel = getVal4St2(st2, now_y);
            int rightUpPixel = getVal4St2(st2, now_y + 1);

            bool valid = true;

            if ('_' != cells[now_x][now_y])
            {
                int num = cells[now_x][now_y] - '0';
                int sum = leftPixel + leftUpPixel + upPixel + rightUpPixel;

                // 当前位置 now_x, now_y 没有 pixel
                if (sum > num)
                {
                    valid = false;
                }
                else if (remain + sum < num)
                {
                    valid = false;
                }

                if (0 == leftUpCnt && valid)
                {
                    // add st
                    unsigned long long newSt1 = st1;
                    unsigned short newSt2 = st2;

                    setVal4St1(newSt1, now_y - 1, (num - sum));
                    setVal4St2(newSt2, now_y - 1, 0);

                    addSts(newSt1, newSt2, qs[act][iQ], 0, nAct);
                }

                // 当前位置 now_x, now_y 有 pixel
                valid = true;

                if (sum + 1 > num)
                {
                    valid = false;
                }
                else if (remain + sum + 1 < num)
                {
                    valid = false;
                }

                if (valid)
                {
                    if (1 < now_y)
                    {
                        if ('_' != cells[now_x][now_y - 1] && 0 == leftCnt)
                        {
                            valid = false;
                        }

                        if (1 < now_x)
                        {
                            if ('_' != cells[now_x - 1][now_y - 1] && 1 != leftUpCnt)
                            {
                                valid = false;
                            }
                        }
                    }

                    if (1 < now_x)
                    {
                        if ('_' != cells[now_x - 1][now_y] && 0 == upCnt)
                        {
                            valid = false;
                        }

                        if (w > now_y)
                        {
                            if ('_' != cells[now_x - 1][now_y + 1] && 0 == rightUpCnt)
                            {
                                valid = false;
                            }
                        }
                    }

                    if (valid)
                    {
                        unsigned long long newSt1 = st1;
                        unsigned short newSt2 = st2;

                        if (0 < leftCnt)
                        {
                            setVal4St1(newSt1, now_y - 2, leftCnt - 1);
                        }

                        setVal4St1(newSt1, now_y - 1, (num - sum - 1));

                        if (0 < upCnt)
                        {
                            setVal4St1(newSt1, now_y, upCnt - 1);
                        }

                        if (0 < rightUpCnt)
                        {
                            setVal4St1(newSt1, now_y + 1, rightUpCnt - 1);
                        }

                        setVal4St2(newSt2, now_y - 1, 1);

                        addSts(newSt1, newSt2, qs[act][iQ], 1, nAct);
                    }
                }
            }
            else
            {
                // '_' = cells[now_x][now_y]
                // 当前位置 now_x, now_y 没有 pixel
                if (0 == leftUpCnt)
                {
                    // 直接 add
                    unsigned long long newSt1 = st1;
                    unsigned short newSt2 = st2;

                    setVal4St1(newSt1, now_y - 1, 0);
                    setVal4St2(newSt2, now_y - 1, 0);

                    addSts(newSt1, newSt2, qs[act][iQ], 0, nAct);
                }

                // 当前位置 now_x, now_y 有 pixel
                valid = true;

                if (1 < now_y)
                {
                    if ('_' != cells[now_x][now_y - 1] && 0 == leftCnt)
                    {
                        valid = false;
                    }

                    if (1 < now_x)
                    {
                        if ('_' != cells[now_x - 1][now_y - 1] && 1 != leftUpCnt)
                        {
                            valid = false;
                        }
                    }
                }

                if (1 < now_x)
                {
                    if ('_' != cells[now_x - 1][now_y] && 0 == upCnt)
                    {
                        valid = false;
                    }

                    if (w > now_y)
                    {
                        if ('_' != cells[now_x - 1][now_y + 1] && 0 == rightUpCnt)
                        {
                            valid = false;
                        }
                    }
                }

                if (valid)
                {
                    unsigned long long newSt1 = st1;
                    unsigned short newSt2 = st2;

                    if (0 < leftCnt)
                    {
                        setVal4St1(newSt1, now_y - 2, leftCnt - 1);
                    }

                    setVal4St1(newSt1, now_y - 1, 0);

                    if (0 < upCnt)
                    {
                        setVal4St1(newSt1, now_y, upCnt - 1);
                    }

                    if (0 < rightUpCnt)
                    {
                        setVal4St1(newSt1, now_y + 1, rightUpCnt - 1);
                    }

                    setVal4St2(newSt2, now_y - 1, 1);

                    addSts(newSt1, newSt2, qs[act][iQ], 1, nAct);
                }
            }
        }

        qTail[act] = 0;
        cnts[act].clear();
        act = nAct;
    }

    return 0;
}
