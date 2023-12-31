// https://www.luogu.com.cn/problem/P5347

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
#define MAX_HW 10
#define QS_SIZE 1000000

const unsigned int ST_BITS = 4;
const unsigned long long ST_MASK = 15;
const unsigned long long MOD = 998244353;

#define getVal4St(ST, POS) (((ST) >> ((POS) * ST_BITS)) & ST_MASK)

#define setVal4St(ST, POS, VAL)                                  \
    ST &= ~(((unsigned long long)ST_MASK) << ((POS) * ST_BITS)); \
    if (VAL)                                                     \
        ST |= ((unsigned long long)(VAL)) << ((POS) * ST_BITS);

unsigned long long quick_pow(unsigned long long a, unsigned long long b)
{
    unsigned long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return ans;
}

unsigned long long inv(unsigned long long a, unsigned long long b)
{
    return (a * quick_pow(b, MOD - 2)) % MOD;
}

class Record
{
public:
    unsigned long long state; // 轮廓线cell状态
    unsigned long long sum;

    unsigned char minUnused;

    Record() {}
};

char cells[MAX_HW][MAX_HW];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w, op;
unsigned long long c;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

// 最小表示法重编码
#define recode(ST, UNUSED)             \
    int bb[10];                        \
    memset(bb, -1, sizeof(bb));        \
    int bn = 1;                        \
    bb[0] = 0;                         \
    for (int i = 0; i <= w; i++)       \
    {                                  \
        int tmp = getVal4St(ST, i);    \
        if (tmp)                       \
        {                              \
            if (0 > bb[tmp])           \
            {                          \
                bb[tmp] = bn++;        \
            }                          \
            setVal4St(ST, i, bb[tmp]); \
        }                              \
    }                                  \
    UNUSED = bn;

#define addSts(ST, SUM, IDX)                                                                  \
    unsigned char unused;                                                                     \
    unsigned long long recodedSt = ST;                                                        \
    recode(recodedSt, unused);                                                                \
    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[IDX].find(recodedSt); \
    if (it == cnts[IDX].end())                                                                \
    {                                                                                         \
        int pInQ = qTail[IDX];                                                                \
        qs[IDX][pInQ].state = recodedSt;                                                      \
        qs[IDX][pInQ].sum = SUM;                                                              \
        qs[IDX][pInQ].minUnused = unused;                                                     \
        cnts[IDX][recodedSt] = pInQ;                                                          \
        qTail[IDX]++;                                                                         \
    }                                                                                         \
    else                                                                                      \
    {                                                                                         \
        qs[IDX][it->second].sum += SUM;                                                       \
        qs[IDX][it->second].sum %= MOD;                                                       \
    }

bool check0(int x, int y)
{
    bool bRet = false;

    if ('#' != cells[x][y])
    {
        bRet = true;
    }

    return bRet;
}

bool check1(int x, int y)
{
    bool bRet = false;

    if ('#' != cells[x][y] && '#' != cells[h + 1 - x][w + 1 - y])
    {
        bRet = true;
    }

    return bRet;
}

inline void funcSymOddCell(unsigned long long st, unsigned long long sum, unsigned char minUnused, bool (*check)(int x, int y), int nAct)
{
    if (now_y <= (w / 2))
    {
        if (1 == now_y)
        {
            st <<= ST_BITS;
        }

        unsigned int left = getVal4St(st, now_y - 1);
        unsigned int up = getVal4St(st, now_y);
        unsigned int bottom = getVal4St(st, w + 1 - now_y);
        unsigned long long newSt = st;

        if (left)
            setVal4St(newSt, now_y - 1, 0);

        if (up)
            setVal4St(newSt, now_y, 0);

        if (bottom)
            setVal4St(newSt, w + 1 - now_y, 0);

        if (up && bottom)
        {
            unsigned long long newSum = sum;

            if (up != bottom)
            {
                // bottom ==> up
                for (int i = 0; i <= w; i++)
                {
                    if (bottom == getVal4St(newSt, i))
                    {
                        setVal4St(newSt, i, up);
                    }
                }
            }

            int i;
            for (i = 0; i <= w; i++)
            {
                if (up == getVal4St(newSt, i))
                {
                    break;
                }
            }

            if (i > w)
            {
                newSum = (sum * c) % MOD;
            }

            if (left)
            {
                if (check(now_x + 1, now_y))
                {
                    // 贯穿
                    setVal4St(newSt, now_y, left);
                    addSts(newSt, newSum, nAct);
                }
            }
            else
            {
                addSts(newSt, newSum, nAct);
            }
        }
        else if (up || bottom)
        {
            int val = up + bottom;

            // 只能打住
            if (left)
            {
                // left ==> val
                for (int i = 0; i <= w; i++)
                {
                    if (left == getVal4St(newSt, i))
                    {
                        setVal4St(newSt, i, val);
                    }
                }
            }

            unsigned long long newSum = sum;

            int i;
            for (i = 0; i <= w; i++)
            {
                if (val == getVal4St(newSt, i))
                {
                    break;
                }
            }

            if (i > w)
            {
                newSum = (sum * c) % MOD;
            }

            addSts(newSt, newSum, nAct);
        }
        else
        {
            // 0 == up && 0 == bottom
            if (0 == left)
            {
                // 跳过
                addSts(newSt, sum, nAct);

                // 新启
                if (check(now_x + 1, now_y))
                {
                    setVal4St(newSt, now_y, minUnused);
                    addSts(newSt, sum, nAct);
                }
            }
            else
            {
                // 打住
                unsigned long long newSum = sum;

                int i;
                for (i = 0; i <= w; i++)
                {
                    if (left == getVal4St(newSt, i))
                    {
                        break;
                    }
                }

                if (i > w)
                {
                    newSum = (sum * c) % MOD;
                }

                addSts(newSt, newSum, nAct);

                // 贯穿
                if (check(now_x + 1, now_y))
                {
                    setVal4St(newSt, now_y, left);
                    addSts(newSt, sum, nAct);
                }
            }
        }
    }
    else
    {
        // finished
        unsigned int left = getVal4St(st, now_y - 1);
        unsigned long long newSum = sum;

        if (w & 1)
        {
            unsigned int up = getVal4St(st, now_y);

            if (up && left)
            {
                newSum = (sum * c) % MOD;

                if (up != left)
                {
                    newSum = (newSum * c) % MOD;
                }
            }
            else if (up || left)
            {
                newSum = (sum * c) % MOD;
            }
        }
        else
        {
            if (left)
            {
                newSum = (sum * c) % MOD;
            }
        }

        addSts(0, newSum, nAct);
    }
}

inline void funcCell(unsigned long long st, unsigned long long sum, unsigned char minUnused, bool (*check)(int x, int y), int nAct)
{
    if (1 == now_y)
    {
        st <<= ST_BITS;
    }

    unsigned int left = getVal4St(st, now_y - 1);
    unsigned int up = getVal4St(st, now_y);
    unsigned long long newSt = st;

    if (left && up)
    {
        if (left == up)
        {
            // 再 穿透
            if (h > now_x && check(now_x + 1, now_y) && w > now_y && check(now_x, now_y + 1))
            {
                addSts(newSt, sum, nAct);
            }

            // 打住
            {
                unsigned long long newSum = sum;

                setVal4St(newSt, now_y - 1, 0);
                setVal4St(newSt, now_y, 0);

                int i = 0;
                for (i = 0; i <= w; i++)
                {
                    if (left == getVal4St(newSt, i))
                    {
                        break;
                    }
                }

                if (i > w)
                {
                    newSum = (sum * c) % MOD;
                }

                addSts(newSt, newSum, nAct);
            }
        }
        else
        {
            if (h > now_x && check(now_x + 1, now_y) && w > now_y && check(now_x, now_y + 1))
            {
                setVal4St(newSt, now_y - 1, up);
                setVal4St(newSt, now_y, left);

                addSts(newSt, sum, nAct);
            }

            // 打住
            {
                // up ==> left
                unsigned long long newSum = sum;

                setVal4St(newSt, now_y - 1, 0);
                setVal4St(newSt, now_y, 0);

                int i = 0;
                for (i = 0; i <= w; i++)
                {
                    if (up == getVal4St(newSt, i))
                    {
                        setVal4St(newSt, i, left);
                    }
                }

                for (i = 0; i <= w; i++)
                {
                    if (left == getVal4St(newSt, i))
                    {
                        break;
                    }
                }

                if (i > w)
                {
                    newSum = (sum * c) % MOD;
                }

                addSts(newSt, newSum, nAct);
            }
        }
    }
    else if (left || up)
    {
        unsigned int val = left + up;

        // 打住
        {
            unsigned long long newSum = sum;

            setVal4St(newSt, now_y - 1, 0);
            setVal4St(newSt, now_y, 0);

            int i = 0;
            for (i = 0; i <= w; i++)
            {
                if (val == getVal4St(newSt, i))
                {
                    break;
                }
            }

            if (i > w)
            {
                newSum = (sum * c) % MOD;
            }

            addSts(newSt, newSum, nAct);
        }

        if (h > now_x && check(now_x + 1, now_y))
        {
            setVal4St(newSt, now_y - 1, val);

            addSts(newSt, sum, nAct);
        }

        if (w > now_y && check(now_x, now_y + 1))
        {
            newSt = st;

            setVal4St(newSt, now_y - 1, 0);
            setVal4St(newSt, now_y, val);

            addSts(newSt, sum, nAct);
        }
    }
    else
    {
        // 跳过
        {
            addSts(newSt, sum, nAct);
        }

        if (h > now_x && check(now_x + 1, now_y))
        {
            setVal4St(newSt, now_y - 1, minUnused);

            addSts(newSt, sum, nAct);
        }

        if (w > now_y && check(now_x, now_y + 1))
        {
            newSt = st;

            setVal4St(newSt, now_y, minUnused);

            addSts(newSt, sum, nAct);
        }

        if (h > now_x && check(now_x + 1, now_y) && w > now_y && check(now_x, now_y + 1))
        {
            newSt = st;

            setVal4St(newSt, now_y, minUnused);
            setVal4St(newSt, now_y - 1, minUnused);

            addSts(newSt, sum, nAct);
        }
    }
}

unsigned long long funcSymOdd(bool (*check)(int x, int y))
{
    unsigned long long ret = 0;
    bool finish = false;

    while (0 < qTail[act])
    {
        if (finish)
        {
            if (1 == qTail[act])
            {
                ret = qs[act][0].sum;
            }

            break;
        }

        int nAct = 1 - act;

        if (w == now_y)
        {
            now_x++;
            now_y = 1;
        }
        else
        {
            now_y++;
        }

        if (false == check(now_x, now_y))
        {
            if (1 == now_y)
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    qs[act][iQ].state <<= ST_BITS;
                }
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                unsigned long long sum = qs[act][iQ].sum;
                unsigned char minUnused = qs[act][iQ].minUnused;

                if ((h + 1) / 2 == now_x)
                {
                    funcSymOddCell(st, sum, minUnused, check, nAct);
                }
                else
                {
                    funcCell(st, sum, minUnused, check, nAct);
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        if ((h + 1) / 2 == now_x && now_y > (w / 2))
        {
            finish = true;
        }
    }

    return ret;
}

unsigned long long funcSymEven(bool (*check)(int x, int y))
{
    unsigned long long ret = 0;
    bool finish = false;

    int iEnd = w / 2;
    if (w & 1)
    {
        iEnd++;
    }

    while (0 < qTail[act])
    {
        if (finish)
        {
            if (1 == qTail[act])
            {
                ret = qs[act][0].sum;
            }

            break;
        }

        int nAct = 1 - act;

        if (w == now_y)
        {
            now_x++;
            now_y = 1;
        }
        else
        {
            now_y++;
        }

        if (false == check(now_x, now_y) && h / 2 >= now_x)
        {
            if (1 == now_y)
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    qs[act][iQ].state <<= ST_BITS;
                }
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                unsigned long long sum = qs[act][iQ].sum;
                unsigned char minUnused = qs[act][iQ].minUnused;

                if (h / 2 >= now_x)
                {
                    funcCell(st, sum, minUnused, check, nAct);
                }
                else
                {
                    // h / 2 < now_x
                    if (1 == now_y)
                    {
                        st <<= ST_BITS;
                    }

                    int i = 0;
                    for (i = 1; i <= iEnd; i++)
                    {
                        unsigned int up = getVal4St(st, i);
                        unsigned int bottom = getVal4St(st, w + 1 - i);

                        if (!up && bottom)
                        {
                            break;
                        }
                        else if (up && !bottom)
                        {
                            break;
                        }
                    }

                    if (i > iEnd)
                    {
                        // 合法
                        unsigned long long newSt = st;
                        unsigned long long newSum = sum;

                        for (i = 1; i <= iEnd; i++)
                        {
                            unsigned int up = getVal4St(newSt, i);
                            unsigned int bottom = getVal4St(newSt, w + 1 - i);

                            if (up)
                            {
                                setVal4St(newSt, i, 0);
                                setVal4St(newSt, w + 1 - i, 0);

                                bool flag = true;
                                // bottom ==> up
                                for (size_t j = 0; j <= w; j++)
                                {
                                    unsigned int tmp = getVal4St(newSt, j);
                                    if (bottom == tmp)
                                    {
                                        flag = false;
                                        setVal4St(newSt, j, up);
                                    }
                                    else if (up == tmp)
                                    {
                                        flag = false;
                                    }
                                }

                                if (flag)
                                {
                                    newSum = (newSum * c) % MOD;
                                }
                            }
                        }

                        addSts(0, newSum, nAct);
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        if (h / 2 < now_x)
        {
            finish = true;
        }
    }

    return ret;
}

unsigned long long func(bool (*check)(int x, int y))
{
    unsigned long long ret = 0;
    bool finish = false;

    while (0 < qTail[act])
    {
        if (finish)
        {
            if (1 == qTail[act])
            {
                ret = qs[act][0].sum;
            }

            break;
        }

        int nAct = 1 - act;

        if (w == now_y)
        {
            now_x++;
            now_y = 1;
        }
        else
        {
            now_y++;
        }

        if (false == check(now_x, now_y))
        {
            if (1 == now_y)
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    qs[act][iQ].state <<= ST_BITS;
                }
            }
        }
        else
        {
            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned long long st = qs[act][iQ].state;
                unsigned long long sum = qs[act][iQ].sum;
                unsigned char minUnused = qs[act][iQ].minUnused;

                funcCell(st, sum, minUnused, check, nAct);
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        if (h == now_x && w == now_y)
        {
            finish = true;
        }
    }

    return ret;
}

inline void init()
{
    act = 0;

    now_x = 0;
    now_y = w;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].sum = 1;
    qs[act][0].minUnused = 1;

    qTail[0] = 1;
    qTail[1] = 0;
}

int main()
{
    cin >> h >> w >> c >> op;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> cells[row][col];
        }
    }

    init();

    unsigned long long ans = func(check0);

    if (op)
    {
        init();

        unsigned long long sum23 = func(check1);

        init();

        unsigned long long sym = 0;
        if (h & 1)
        {
            sym = funcSymOdd(check1);
        }
        else
        {
            sym = funcSymEven(check1);
        }

        //        printf("ans = %llu, sum23 = %llu, sym = %llu\n", ans, sum23, sym);

        ans += MOD;
        ans -= inv((sum23 + MOD - sym), 2);
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}
