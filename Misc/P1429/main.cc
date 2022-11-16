#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define DEBUG   0

class Point
{
public:
    float x, y;

    Point();
};

int main()
{
    int n;

#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    for (size_t i = 0; i < n; i++)
    {
        float x, y;

#if DEBUG
        inFile >> x >> y;
#else
        cin >> x >> y;
#endif


    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
