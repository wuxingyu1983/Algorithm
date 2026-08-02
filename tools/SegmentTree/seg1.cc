#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class SegmentTree
{
private:
    int n;
    std::vector<T> tree;
    std::vector<T> lazy;

    void push(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            // Apply the lazy value to the current node's maximum
            tree[node] += lazy[node];

            // If it is not a leaf node, propagate the lazy value to children
            if (start != end)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            // Clear the lazy value for the current node
            lazy[node] = 0;
        }
    }

    void update_range(int node, int start, int end, int l, int r, T val)
    {
        // Process pending lazy updates first
        push(node, start, end);

        // Out of bounds: No overlap
        if (start > end || start > r || end < l)
        {
            return;
        }

        // Complete overlap: Current segment is completely within [l, r]
        if (start >= l && end <= r)
        {
            tree[node] += val;
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // Partial overlap: Recurse on children
        int mid = start + (end - start) / 2;
        update_range(2 * node, start, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, end, l, r, val);

        // Merge step: Update current node's maximum using children's actual values
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }

    T query_range(int node, int start, int end, int l, int r)
    {
        // Out of bounds: No overlap
        if (start > end || start > r || end < l)
        {
            return std::numeric_limits<T>::min();
        }

        // Process pending lazy updates
        push(node, start, end);

        // Complete overlap
        if (start >= l && end <= r)
        {
            return tree[node];
        }

        // Partial overlap: Recurse and return the maximum of both halves
        int mid = start + (end - start) / 2;
        T leftMax = query_range(2 * node, start, mid, l, r);
        T rightMax = query_range(2 * node + 1, mid + 1, end, l, r);

        return std::max(leftMax, rightMax);
    }

public:
    SegmentTree(int size)
    {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void update(int l, int r, T val)
    {
        update_range(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r)
    {
        return query_range(1, 0, n - 1, l, r);
    }
};

int main()
{
    // Example usage: Array of size 6 initialized to 0
    SegmentTree<int> st(6);

    st.update(1, 3, 10);

    st.update(2, 5, 5);

    // Query max value in range [0, 2] -> Returns 10 (from index 1)
    std::cout << "Max in [0, 2]: " << st.query(0, 2) << std::endl;

    // Query max value in range [3, 5] -> Returns 5
    std::cout << "Max in [4, 5]: " << st.query(4, 5) << std::endl;

    return 0;
}
