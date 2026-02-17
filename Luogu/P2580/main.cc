// https://www.luogu.com.cn/problem/P2580

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
#include <map>

using namespace std;

const int MAX_N = 600000;

class trie
{
public:
    trie()
    {
        cnt = 0;
        nex.resize(MAX_N);
        for (size_t i = 0; i < MAX_N; i++)
        {
            nex[i].resize(26, 0);
        }
        
        exist.resize(MAX_N, 0);
        found.resize(MAX_N, 0);
    }

    void insert(const char *s, int l)
    { // 插入字符串
        int p = 0;
        for (int i = 0; i < l; i++)
        {
            int c = s[i] - 'a';
            if (!nex[p][c])
                nex[p][c] = ++cnt; // 如果没有，就添加结点
            p = nex[p][c];
        }
        exist[p] = true;
    }

    int find(const char *s, int l)
    { // 查找字符串
        int p = 0;
        for (int i = 0; i < l; i++)
        {
            int c = s[i] - 'a';
            if (!nex[p][c])
                return 0;
            p = nex[p][c];
        }

        if (exist[p])
        {
            found[p] ++;
        }
        return found[p];
    }

private:
    int cnt;
    vector< vector<int> > nex;
    vector<int> exist, found;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    trie tr;

    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;

        tr.insert(str.c_str(), str.length());
    }
    
    int m;
    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        string str;
        cin >> str;

        int found = tr.find(str.c_str(), str.length());
        if (0 == found)
            cout << "WRONG" << "\n";
        else if (1 == found)
            cout << "OK" << "\n";
        else
            cout << "REPEAT" << "\n";
    }

    return 0;
}
