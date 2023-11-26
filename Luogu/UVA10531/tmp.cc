#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;
const int HASH = 30007;
const int STATE = 1000010;
const int MAXD = 15;
const double EPS = 1e-15;
int n, m;
double maze[MAXD][MAXD];
int code[MAXD], ch[MAXD];

int fcmp(double x)
{
    return x < -EPS ? -1 : x > EPS;
}

void decode(LL st)
{
    int i;
    for (i = m; i >= 0; --i)
    {
        code[i] = st&7;
        st >>= 3;
    }
}

LL encode()
{
    LL st = 0;
    int i, cnt = 1;
    memset(ch, -1, sizeof(ch));
    ch[0] = 0, ch[1] = 1;
    for (i = 0; i <= m; ++i)
    {
        if (ch[code[i]] == -1)
            ch[code[i]] = ++cnt;
        code[i] = ch[code[i]];
        st <<= 3;
        st |= code[i];
    }
    return st;
}

struct HASHMAP
{
    int head[HASH], next[STATE], size;
    LL state[STATE];
    double f[STATE];
    void clear()
    {
        size = 0;
        memset(head, -1, sizeof(head));
    }
    void push(LL st, double ans)
    {
        int i;
        decode(st);
        for (i = 0; i <= m; ++i)
            if (code[i] == 1)
                break ;
        if (i == m+1) //如果编号为1的连通块不存在，那就不可行
            return ;
        int x = st%HASH;
        for (i = head[x]; i != -1; i = next[i])
            if (st == state[i])
            {
                f[i] += ans;
                return ;
            }
        f[size] = ans;
        state[size] = st;
        next[size] = head[x];
        head[x] = size ++;
    }
}hm[2];

void in()
{
    int i, j;
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            scanf("%lf", &maze[i][j]);
}

void dp_blank(int i, int j, int cur)
{
    if (!fcmp(1.0-maze[i][j]))
        return ;
    int k, lef, up, t;
    for (k = 0; k < hm[cur].size; ++k)
    {
        if (!fcmp(hm[cur].f[k]))
            continue ;
        decode(hm[cur].state[k]);
        lef = code[j-1], up = code[j];
        if (lef && up)//分类讨论只对右插头做修改
        {
            if (lef != up)
            {
                if (lef < up)
                    swap(lef, up);
                for (t = 0; t <= m; ++t)
                    if (code[t] == lef)
                        code[t] = up;
            }
        }
        else
        {
            if (lef || up)
                code[j] = lef|up;
            else
                code[j] = m+1;
        }
        hm[cur^1].push(encode(), hm[cur].f[k]*(1.0-maze[i][j]));
    }
}

void dp_block(int i, int j, int cur)
{
    if (!fcmp(maze[i][j]))
        return ;
    int k;
    for (k = 0; k < hm[cur].size; ++k)
    {
        if (!fcmp(hm[cur].f[k]))
            continue ;
        decode(hm[cur].state[k]);
        code[j] = 0;//同理
        hm[cur^1].push(encode(), hm[cur].f[k]*maze[i][j]);
    }
}

double solve()
{
    int i, j, cur = 0;
    memset(code, 0, sizeof(code));
    hm[cur].clear();
    code[1] = 1;
    hm[cur].push(encode(), 1);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
        {
            hm[cur^1].clear();
            dp_blank(i, j, cur);
            dp_block(i, j, cur);
            cur ^= 1;
        }
    double ret = 0;
    for (i = 0; i < hm[cur].size; ++i)
    {
        decode(hm[cur].state[i]);
        if (code[m] == 1)
            ret += hm[cur].f[i];
    }
    return ret;
}

void work()
{
    int i, j;
    double sum = solve();
    cout << sum << endl;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
        {
            double cache = maze[i][j];
            maze[i][j] = 1.0;
            printf("%.6lf%c", solve()*cache/sum, (j == m) ? '\n' : ' ');
            maze[i][j] = cache;
        }
}

int main()
{
    int T, iCase = 0;
    scanf("%d", &T);
    while (T --)
    {
        if (iCase++)
            printf("\n");
        in();
        work();
    }
    return 0;
}
