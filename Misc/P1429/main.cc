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

bool compare_float(float x, float y, float epsilon = 0.0001f)
{
    if (fabs(x - y) < epsilon)
        return true; // they are same
    return false;    // they are not same
}

class Point
{
public:
    float x, y;

    Point(){}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

vector<Point> points;

bool cmp(Point &a, Point &b)
{
    bool ret = false;

    if (a.x < b.x)
    {
        ret = true;
    }
    else if (compare_float(a.x, b.x))
    {
        if (a.y < b.y)
        {
            ret = true;
        }
    }
    

    return ret;
}

float distance(Point &a, Point &b)
{
    float ret;

    ret = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));

    return ret;
}

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

        points.push_back(Point(x, y));
    }

    // sort
    sort(points.begin(), points.end(), cmp);

    float min = -1;

    // pre-find min
    vector<Point>::iterator it = points.begin();
    vector<Point>::iterator pre = points.end();
    while (it != points.end())
    {
        if (pre == points.end())
        {
            pre = it;
        }
        else
        {
            float tmp = distance(pre, it);
            if (compare_float(tmp, 0))
            {
                min = tmp;
                break;
            }
            else
            {
                if (0 > min || tmp < min)
                {
                    min = tmp;
                }
            }
        }

        it ++; 
    }
    
    if (false == compare_float(min, 0))
    {
        // build kd-tree

    }

    cout << fixed << setprecision(4) << min << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
