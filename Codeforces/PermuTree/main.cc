// https://codeforces.com/contest/1856/problem/E2

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

bitset<3> dp1;
bitset<5> dp2;
bitset<9> dp3;
bitset<17> dp4;
bitset<33> dp5;
bitset<65> dp6;
bitset<129> dp7;
bitset<257> dp8;
bitset<513> dp9;
bitset<1025> dp10;
bitset<2049> dp11;
bitset<4097> dp12;
bitset<8193> dp13;
bitset<16385> dp14;
bitset<32769> dp15;
bitset<65537> dp16;
bitset<131073> dp17;
bitset<262145> dp18;
bitset<524289> dp19;
bitset<1000001> dp20;

inline void init(int x)
{
    switch (x)
    {
    case 1:
        dp1.reset();
        dp1[0] = 1;
        break;
    case 2:
        dp2.reset();
        dp2[0] = 1;
        break;
    case 3:
        dp3.reset();
        dp3[0] = 1;
        break;
    case 4:
        dp4.reset();
        dp4[0] = 1;
        break;
    case 5:
        dp5.reset();
        dp5[0] = 1;
        break;
    case 6:
        dp6.reset();
        dp6[0] = 1;
        break;
    case 7:
        dp7.reset();
        dp7[0] = 1;
        break;
    case 8:
        dp8.reset();
        dp8[0] = 1;
        break;
    case 9:
        dp9.reset();
        dp9[0] = 1;
        break;
    case 10:
        dp10.reset();
        dp10[0] = 1;
        break;
    case 11:
        dp11.reset();
        dp11[0] = 1;
        break;
    case 12:
        dp12.reset();
        dp12[0] = 1;
        break;
    case 13:
        dp13.reset();
        dp13[0] = 1;
        break;
    case 14:
        dp14.reset();
        dp14[0] = 1;
        break;
    case 15:
        dp15.reset();
        dp15[0] = 1;
        break;
    case 16:
        dp16.reset();
        dp16[0] = 1;
        break;
    case 17:
        dp17.reset();
        dp17[0] = 1;
        break;
    case 18:
        dp18.reset();
        dp18[0] = 1;
        break;
    case 19:
        dp19.reset();
        dp19[0] = 1;
        break;
    case 20:
    default:
        dp20.reset();
        dp20[0] = 1;
        break;
    }
}

inline void func(int x, int offset)
{
    switch (x)
    {
    case 1:
        dp1 |= dp1 << offset;
        break;
    case 2:
        dp2 |= dp2 << offset;
        break;
    case 3:
        dp3 |= dp3 << offset;
        break;
    case 4:
        dp4 |= dp4 << offset;
        break;
    case 5:
        dp5 |= dp5 << offset;
        break;
    case 6:
        dp6 |= dp6 << offset;
        break;
    case 7:
        dp7 |= dp7 << offset;
        break;
    case 8:
        dp8 |= dp8 << offset;
        break;
    case 9:
        dp9 |= dp9 << offset;
        break;
    case 10:
        dp10 |= dp10 << offset;
        break;
    case 11:
        dp11 |= dp11 << offset;
        break;
    case 12:
        dp12 |= dp12 << offset;
        break;
    case 13:
        dp13 |= dp13 << offset;
        break;
    case 14:
        dp14 |= dp14 << offset;
        break;
    case 15:
        dp15 |= dp15 << offset;
        break;
    case 16:
        dp16 |= dp16 << offset;
        break;
    case 17:
        dp17 |= dp17 << offset;
        break;
    case 18:
        dp18 |= dp18 << offset;
        break;
    case 19:
        dp19 |= dp19 << offset;
        break;
    case 20:
    default:
        dp20 |= dp20 << offset;
        break;
    }
}

void dfs(int node, const vector<vector<int>>& children, vector<long long>& sums)
{
    sums[node] = 1; // Count the current node

    for (int child : children[node])
    {
        dfs(child, children, sums);
        sums[node] += sums[child]; // Add the size of the subtree rooted at the child
    }
}

void solve(const int n, const vector<vector<int>>& children, vector<long long>& sums, long long &ans)
{
    long long max = 0;

    for (int node = 1; node <= n; node++)
    {
        if (1 < children[node].size())
        {
            vector<long long> vec;
            for (int child : children[node])
            {
                vec.push_back(sums[child]);
            }
            sort(vec.begin(), vec.end());
            vec.push_back(0);
            
            // get dpX
            int x = 20;
            while ((1 << (x - 1)) >= (sums[node] - 1))
            {
                x --;
            }
            
            init(x);

            int pre = 0;
            int cnt = 0;
            for (int i = 0; i < vec.size(); i++)
            {
                if (pre != vec[i])
                {
                    int step = 1;
                    while (step <= cnt)
                    {
                        func(x, step * pre);
                        cnt -= step;
                        step <<= 1;
                    }

                    if (0 < cnt)
                    {
                        func(x, cnt * pre);
                    }

                    pre = vec[i];
                    cnt = 1;
                }
                else
                {
                    cnt ++;
                }
            }

            switch (x)
            {
            case 1:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp1[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 2:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp2[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 3:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp3[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 4:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp4[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 5:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp5[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 6:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp6[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 7:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp7[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 8:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp8[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 9:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp9[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 10:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp10[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 11:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp11[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 12:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp12[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 13:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp13[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 14:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp14[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 15:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp15[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 16:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp16[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 17:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp17[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 18:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp18[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 19:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp19[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            case 20:
            default:
                for (int i = (sums[node] - 1) / 2; i >= 1; i--)
                {
                    if (dp20[i])
                    {
                        max = i;
                        break;
                    }
                }
                break;
            }

            ans += max * (sums[node] - 1 - max);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;

        children[p].push_back(i);
    }

    vector<long long> sums(n + 1, 0);

    dfs(1, children, sums);

    long long ans = 0;

    solve(n, children, sums, ans);

    cout << ans << "\n";

    return 0;
}
