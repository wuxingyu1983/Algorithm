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
#include <cassert>

#define N 10
#define M 100010
#define S 3000010
#define LL long long
#define DB double
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define mod 25619849
#define INF 0x3f3f3f3f
#define pir pair<int, int>
#define mp(i, j) make_pair(i, j)
#define fi first
#define se second
#define w(i, j) (1ll * ((1ll * i) << (j)))
#define e(i, j) (1ll * (((1ll * i) >> (j)) & 15))
using namespace std;
template <typename T>
inline void read(T &a)
{
    a = 0;
    T w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        a = (a << 3) + (a << 1) + (ch ^ 48);
        ch = getchar();
    }
    a *= w;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...args)
{
    read(x);
    read(args...);
}
int n, m, q, maap[N][N], num[N + 1], ncc;
bool suc;
const LL lim = (1ll << 40) - 1;
bool cur, hav[N][N][11];
vector<int> node[N][N];
struct HASH_TABLE
{
#define Mod 500009
    struct NODE
    {
        int pre, id;
    } a[S];
    int head[500010], cc, pcc; // 插头4*9=36位？
    LL state[S], f[S];
    int g[S];
    inline void init()
    {
        pcc = 0;
        memset(head, 0, sizeof(head));
    }
    inline void insert(LL sta, LL val, int len)
    {
        sta &= lim;
        int key = 1ll * sta % Mod;
        for (int cur = head[key]; cur; cur = a[cur].pre)
            if (state[a[cur].id] == sta)
            {
                int id = a[cur].id;
                if (g[id] > len)
                {
                    g[id] = len;
                    f[id] = val;
                    return;
                }
                else if (g[id] == len)
                {
                    (f[id] += val) %= mod;
                    return;
                }
                else
                    return;
            }
        a[++pcc] = {head[key], ++cc};
        head[key] = pcc;
        state[cc] = sta;
        f[cc] = val;
        g[cc] = len;
    }
#undef Mod
} hs[2];
inline void Main()
{
    memset(hav, 0, sizeof(hav));
    swap(n, m);
    cur = 0;
    suc = 1;
    rep(i, 1, n) rep(j, 1, m) read(maap[i][j]), node[i][j].clear();
    rep(i, 1, q)
    {
        int x, y, _x, _y;
        read(x, y, _x, _y);
        x++;
        y++;
        _x++;
        _y++;
        if (x == _x && y == _y)
        {
            suc = 0;
        }
        node[x][y].push_back(i);
        node[_x][_y].push_back(i);
        hav[x][y][i] = hav[_x][_y][i] = 1;
        if (node[x][y].size() > 4)
        {
            suc = 0;
        }
        if (node[_x][_y].size() > 4)
        {
            suc = 0;
        }
    }
    rep(i, 1, n) rep(j, 1, m) if (!node[i][j].size()) rep(k, 1, q) hav[i][j][k] = 1;
    if (!suc)
    {
        printf("-1 0\n");
        return;
    }
    hs[0].init();
    hs[0].cc = 0;
    hs[1].init();
    hs[1].cc = 0;
    hs[cur].init();
    hs[cur].cc = 0;
    hs[cur].insert(0, 1, 0);
    rep(i, 1, n)
    {
        rep(j, 1, hs[cur].cc)(hs[cur].state[j] <<= 4) &= lim;
        rep(j, 1, m)
        {
            hs[cur].init();
            cur ^= 1;
            hs[cur].cc = 0;
            rep(k, 1, hs[cur ^ 1].cc)
            {
                LL sta = hs[cur ^ 1].state[k] & lim, val = hs[cur ^ 1].f[k];
                int len = hs[cur ^ 1].g[k];
                int fr = e(sta, (j - 1) * 4), fd = e(sta, j * 4);
                LL base = sta ^ w(fr, (j - 1) * 4) ^ w(fd, j * 4);
                if (maap[i][j] == 1)
                {
                    if (node[i][j].size())
                        continue;
                    if (!fd && !fr)
                        hs[cur].insert(base, val, len);
                }
                else if (!node[i][j].size())
                {
                    if (!fr && !fd)
                    {
                        hs[cur].insert(base, val, len);
                        if (j < m && !maap[i][j + 1] && i < n && !maap[i + 1][j])
                            rep(typ, 1, q) if (hav[i][j + 1][typ] && hav[i + 1][j][typ]) hs[cur].insert(base | w(typ, (j - 1) * 4) | w(typ, j * 4), val, len + 2);
                    }
                    else if ((fr && !fd) || (!fr && fd))
                    {
                        if (i < n && !maap[i + 1][j] && hav[i + 1][j][fr | fd])
                            hs[cur].insert(base | w(fr | fd, (j - 1) * 4), val, len + 1);
                        if (j < m && !maap[i][j + 1] && hav[i][j + 1][fr | fd])
                            hs[cur].insert(base | w(fr | fd, j * 4), val, len + 1);
                    }
                    else if (fr && fd)
                    {
                        if (fd == fr)
                        {
                            hs[cur].insert(base, val, len);
                            if (j < m && !maap[i][j + 1] && i < n && !maap[i + 1][j])
                                rep(typ, 1, q) if (typ ^ fr && hav[i][j + 1][typ] && hav[i + 1][j][typ]) hs[cur].insert(base | w(typ, (j - 1) * 4) | w(typ, j * 4), val, len + 2);
                        }
                        else if (j < m && !maap[i][j + 1] && i < n && !maap[i + 1][j] && hav[i][j + 1][fd] && hav[i + 1][j][fr])
                            hs[cur].insert(base | w(fr, (j - 1) * 4) | w(fd, j * 4), val, len + 2);
                    }
                    else
                        assert(0);
                }
                else
                {
                    if (fr == fd && fr)
                        continue;
                    bool afr = 0, afd = 0;
                    ncc = 0;
                    for (int x : node[i][j])
                    {
                        if (x == fr)
                            afr = 1;
                        if (x == fd)
                            afd = 1;
                    }
                    if (fr && !afr)
                        continue;
                    if (fd && !afd)
                        continue;
                    for (int x : node[i][j])
                        if (x ^ fr && x ^ fd)
                            num[++ncc] = x;
                    if (ncc == 0)
                    {
                        hs[cur].insert(base, val, len);
                    }
                    else if (ncc == 1)
                    {
                        int x = num[1];
                        if (j < m && !maap[i][j + 1] && hav[i][j + 1][x])
                            hs[cur].insert(base | w(x, j * 4), val, len + 1);
                        if (i < n && !maap[i + 1][j] && hav[i + 1][j][x])
                            hs[cur].insert(base | w(x, (j - 1) * 4), val, len + 1);
                    }
                    else if (ncc == 2)
                    {
                        if (j >= m || i >= n || maap[i][j + 1] || maap[i + 1][j])
                            continue;
                        if (hav[i + 1][j][num[1]] && hav[i][j + 1][num[2]])
                            hs[cur].insert(base | w(num[1], (j - 1) * 4) | w(num[2], j * 4), val, len + 2);
                        if (hav[i + 1][j][num[2]] && hav[i][j + 1][num[1]])
                            hs[cur].insert(base | w(num[2], (j - 1) * 4) | w(num[1], j * 4), val, len + 2);
                    }
                }
            }
        }
    }
    rep(i, 1, hs[cur].cc) if (!hs[cur].state[i]) return printf("%d %lld\n", hs[cur].g[i], hs[cur].f[i]), void();
    printf("-1 0\n");
}
signed main()
{
    while (1)
    {
        read(n, m, q);
        if (!(n + m + q))
            break;
        Main();
    }
    return 0;
}
