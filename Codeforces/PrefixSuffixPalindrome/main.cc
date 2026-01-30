// https://codeforces.com/contest/1326/problem/D2

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

using namespace std;

string preprocString(string &s)
{
    string ret = "^";
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        ret += '#';
        ret += s.at(i);
    }
    ret += "#$";

    return ret;
}

string func(string &str)
{
    string ret;


    return ret;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        string str;
        cin >> str;

        cout << func(str) << endl;
    }
    
    return 0;
}
