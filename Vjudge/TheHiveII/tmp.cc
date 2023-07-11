#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int STATE = 2000000 + 10; // 逐格递推每次最多能生成的状态总数,为什么100W能装下,实例测试如果装不下hasnmap就会越界报错
const int HASH = 10007;
const int MAXD = 32;
int N, M;
int cur;
int mp[MAXD][MAXD];
int code[MAXD];
long long sum; // 记录最终的最大值
struct HASHMAP
{
    int size, head[HASH], next[STATE]; // next[i]=j表示第i个状态后面链接着第j个状态
    int state[STATE];                  // state[i]=S表第i个状态是S
    long long f[STATE];                // f[i]=x表第i个状态有x种情况
    void init()
    {
        memset(head, -1, sizeof(head));
        size = 0;
    }
    void push(int st, long long num)
    {
        int h = st % HASH;
        int i;
        for (i = head[h]; i != -1; i = next[i])
        {
            if (state[i] == st)
            {
                f[i] += num;
                return;
            }
        }
        next[size] = head[h];
        head[h] = size;
        f[size] = num;
        state[size] = st;
        size++;
    }
} hm[2];
void decode(int *code, int st) // st->code
{
    for (int i = 2 * M; i >= 0; i--)
    {
        code[i] = st & 1;
        st >>= 1;
    }
}
int encode(int *code) // code->st
{
    int st = 0;
    for (int i = 0; i <= 2 * M; i++)
    {
        st <<= 1;
        st |= code[i];
    }
    return st;
}
void shift(int *code, int r)
{
    if (r % 2 == 1) // 只有奇数行到偶数行才需要右移两位，前端添0
    {
        for (int i = 2 * M; i >= 2; i--)
            code[i] = code[i - 2];
        code[0] = code[1] = 0;
    }
}
void dpblock(int i, int j) // 坏格
{
    for (int k = 0; k < hm[cur].size; k++)
    {
        int st = hm[cur].state[k];
        int code[MAXD];
        decode(code, st);
        int left = code[2 * j - 2], up = code[2 * j - 1], right = code[2 * j];
        if (left == 0 && up == 0 && right == 0) // 全无插头时,才能生成新状态
        {
            if (j == M) // j为当前行最后一列,需要右移一位
                shift(code, i);
            hm[1 - cur].push(encode(code), hm[cur].f[k]);
        }
    }
}
void dpblank(int i, int j) // 好格
{
    for (int k = 0; k < hm[cur].size; k++)
    {
        int st = hm[cur].state[k];
        int code[MAXD];
        decode(code, st);
        int left = code[j * 2 - 2], up = code[j * 2 - 1], right = code[j * 2];
        if (left && up && right) // 3端都有插头，不处理
        {
            continue;
        }
        else if ((left && up) || (left && right) || (up && right)) // 只有两个插头,直接合并即可
        {
            code[j * 2 - 2] = code[j * 2 - 1] = code[j * 2] = 0;
            if (j == M)
                shift(code, i);
            hm[1 - cur].push(encode(code), hm[cur].f[k]);
        }
        else if (left || up || right) // 只有一个插头时
        {
            if (i % 2 == 1) // 奇数行时
            {
                if (mp[i + 1][j]) // （i，j）的左下格可行
                {
                    code[j * 2 - 2] = 1;
                    code[j * 2 - 1] = 0;
                    code[j * 2] = 0;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i + 1][j + 1]) // （i，j）的右下格可行
                {
                    code[j * 2 - 2] = 0;
                    code[j * 2 - 1] = 1;
                    code[j * 2] = 0;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i][j + 1]) // （i，j）的右格可行
                {
                    code[j * 2 - 2] = 0;
                    code[j * 2 - 1] = 0;
                    code[j * 2] = 1;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
            }
            else if (i % 2 == 0) // 偶数行时
            {
                if (mp[i + 1][j - 1]) // （i，j）的左下格可行
                {
                    code[j * 2 - 2] = 1;
                    code[j * 2 - 1] = 0;
                    code[j * 2] = 0;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i + 1][j]) // （i，j）的右下格可行
                {
                    code[j * 2 - 2] = 0;
                    code[j * 2 - 1] = 1;
                    code[j * 2] = 0;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i][j + 1]) // （i，j）的右格可行
                {
                    code[j * 2 - 2] = 0;
                    code[j * 2 - 1] = 0;
                    code[j * 2] = 1;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
            }
        }
        else // 无插头,则生成新插头
        {
            if (i % 2 == 1) // 奇数行
            {
                if (mp[i + 1][j] && mp[i + 1][j + 1]) // 左下，右下可行
                {
                    code[j * 2 - 2] = 1;
                    code[j * 2 - 1] = 1;
                    code[j * 2] = 0;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i + 1][j] && mp[i][j + 1]) // 左下，右格可行
                {
                    code[j * 2 - 2] = 1;
                    code[j * 2 - 1] = 0;
                    code[j * 2] = 1;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i + 1][j + 1] && mp[i][j + 1]) // 右下，右格可行
                {
                    code[j * 2 - 2] = 0;
                    code[j * 2 - 1] = 1;
                    code[j * 2] = 1;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
            }
            else if (i % 2 == 0) // 偶数行
            {
                if (mp[i + 1][j - 1] && mp[i + 1][j])
                {
                    code[j * 2 - 2] = 1;
                    code[j * 2 - 1] = 1;
                    code[j * 2] = 0;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i + 1][j - 1] && mp[i][j + 1])
                {
                    code[j * 2 - 2] = 1;
                    code[j * 2 - 1] = 0;
                    code[j * 2] = 1;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
                if (mp[i + 1][j] && mp[i][j + 1])
                {
                    code[j * 2 - 2] = 0;
                    code[j * 2 - 1] = 1;
                    code[j * 2] = 1;
                    if (j == M)
                        shift(code, i);
                    hm[1 - cur].push(encode(code), hm[cur].f[k]);
                }
            }
        }
    }
}
void init()
{
    N = 8;
    memset(mp, 0, sizeof(mp));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            mp[i][j] = 1;
        }
    }
    char str[20];
    int t; // 有t个格子没蜂蜜
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", str);
        mp[str[1] - 'A' + 1][str[0] - 'A' + 1] = 0;
    }
}
void solve()
{
    sum = 0;
    cur = 0;
    hm[cur].init();
    hm[cur].push(0, 1);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            hm[1 - cur].init();
            if (mp[i][j])
                dpblank(i, j);
            else
                dpblock(i, j);
            cur = 1 - cur;
            // printf("****************************************\n");
            // printf("(i,j)=(%d,%d),size=%d\n",i,j,hm[cur].size);
            // for(int k=0; k<hm[cur].size; k++)
            // printf("第%d个状态是%I64d\n",k,hm[cur].state[k]);
            // printf("\n");
        }
    for (int i = 0; i < hm[cur].size; i++)
        sum += hm[cur].f[i];
    printf("%lld\n", sum);
}
int main()
{
    while (scanf("%d", &M) == 1 && M)
    {
        init();
        solve();
    }
    return 0;
}
