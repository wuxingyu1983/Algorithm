#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define DEBUG   0

const int k = 2;

bool compare_double(double x, double y, double epsilon = 0.0001f)
{
    if (fabs(x - y) < epsilon)
        return true; // they are same
    return false;    // they are not same
}

class Point
{
public:
    double x, y;

    Point(){}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

vector<Point> points;

bool cmp(Point &a, Point &b)
{
    bool ret = false;

    if (a.x < b.x)
    {
        ret = true;
    }
    else if (compare_double(a.x, b.x))
    {
        if (a.y < b.y)
        {
            ret = true;
        }
    }
    
    return ret;
}

double distance(Point &a, Point &b)
{
    double ret;

    ret = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));

    return ret;
}

// kd-tree node
class Node
{
public:
    double point[k];
    double min[k];
    double max[k];
    Node *left, *right;

    Node(double arr[]);
};

Node::Node(double arr[])
{
    for (size_t i = 0; i < k; i++)
    {
        point[i] = min[i] = max[i] = arr[i];
    }

    left = right = NULL;
}

bool cmp0(Point &a, Point &b)
{
    return (a.x < b.x);
}

bool cmp1(Point &a, Point &b)
{
    return (a.y < b.y);
}
Node *buildKDTree(vector<Point>::iterator ps, int ps_size, int curr_level)
{
    Node *ret = NULL;

    int mid_idx = ps_size / 2;
    if (0 >= curr_level)
    {
        nth_element(ps, ps + mid_idx, ps + ps_size, cmp0);
    }
    else
    {
        nth_element(ps, ps + mid_idx, ps + ps_size, cmp1);
    }

    Point mid = *(ps + mid_idx);
    double arr[] = {mid.x, mid.y};
    ret = new Node(arr);

    if (0 < mid_idx)
    {
        // left
        ret->left = buildKDTree(ps, mid_idx, curr_level + 1);

        for (size_t i = 0; i < k; i++)
        {
            if (ret->min[i] > ret->left->min[i])
            {
                ret->min[i] = ret->left->min[i];
            }

            if (ret->max[i] < ret->left->max[i])
            {
                ret->max[i] = ret->left->max[i];
            }
        }
    }

    if (mid_idx + 1 < ps_size)
    {
        // right
        ret->right = buildKDTree(ps + mid_idx + 1, ps_size - mid_idx - 1, curr_level + 1);

        for (size_t i = 0; i < k; i++)
        {
            if (ret->min[i] > ret->right->min[i])
            {
                ret->min[i] = ret->right->min[i];
            }

            if (ret->max[i] < ret->right->max[i])
            {
                ret->max[i] = ret->right->max[i];
            }
        }
    }

    return ret;
}

void findMin(Node &node, Point &point, double &min)
{
    if (false == compare_double(node.point[0], point.x) || false == compare_double(node.point[1], point.y))
    {
        Point np = Point(node.point[0], node.point[1]);
        double tmp = distance(np, point);
        if (tmp < min)
        {
            min = tmp;
        }
    }

    Node *children[] = {node.left, node.right};

    for (size_t i = 0; i < 2; i++)
    {
        Node *child = children[i];

        if (child)
        {
            if (point.x >= child->min[0] && point.x <= child->max[0] && point.y >= child->min[1] && point.y <= child->max[1])
            {
                // in rect
                // find min from child
                findMin(*child, point, min);
            }
            else if (point.x >= child->min[0] && point.x <= child->max[0])
            {
                double tmp_min = fabs(point.y - child->min[1]);
                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                    continue;
                }

                tmp_min = fabs(point.y - child->max[1]);
                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                }
            }
            else if (point.y >= child->min[1] && point.y <= child->max[1])
            {
                double tmp_min = fabs(point.x - child->min[0]);
                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                    continue;
                }

                tmp_min = fabs(point.x - child->max[0]);
                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                }
            }
            else
            {
                Point tmp_p = Point(child->min[0], child->min[1]);
                double tmp_min = distance(tmp_p, point);

                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                    continue;
                }

                tmp_p = Point(child->min[0], child->max[1]);
                tmp_min = distance(tmp_p, point);

                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                    continue;
                }

                tmp_p = Point(child->max[0], child->min[1]);
                tmp_min = distance(tmp_p, point);

                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                    continue;
                }

                tmp_p = Point(child->max[0], child->max[1]);
                tmp_min = distance(tmp_p, point);

                if (tmp_min < min)
                {
                    findMin(*child, point, min);
                }
            }
        }
    }
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
        double x, y;

#if DEBUG
        inFile >> x >> y;
#else
        cin >> x >> y;
#endif

        points.push_back(Point(x, y));
    }

    // sort
    sort(points.begin(), points.end(), cmp);

    double min = -1;

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
            double tmp = distance(*pre, *it);
            if (compare_double(tmp, 0))
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
    
    if (false == compare_double(min, 0))
    {
        // build kd-tree
        Node *root = NULL;

        root = buildKDTree(points.begin(), points.size(), -1);

        // find min
        for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
        {
            findMin(*root, *it, min);
        }
    }

    cout << fixed << setprecision(4) << min << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
