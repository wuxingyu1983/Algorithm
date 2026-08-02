#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> tree;
    std::vector<T> lazy;

    // Helper function to push pending updates down to children
    void push(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            int mid = start + (end - start) / 2;

            // Update left child
            tree[2 * node] += (mid - start + 1) * lazy[node];
            lazy[2 * node] += lazy[node];

            // Update right child
            tree[2 * node + 1] += (end - mid) * lazy[node];
            lazy[2 * node + 1] += lazy[node];

            // Clear current node's lazy value
            lazy[node] = 0;
        }
    }

    void update_range(int node, int start, int end, int ql, int qr, T val)
    {
        // No overlap
        if (qr < start || ql > end)
            return;

        // Total overlap
        if (ql <= start && end <= qr)
        {
            tree[node] += (end - start + 1) * val;
            if (start != end)
            { // Not a leaf
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // Partial overlap: push down, update children, and recalculate parent
        push(node, start, end);
        int mid = start + (end - start) / 2;
        update_range(2 * node, start, mid, ql, qr, val);
        update_range(2 * node + 1, mid + 1, end, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    T query_range(int node, int start, int end, int ql, int qr)
    {
        // No overlap
        if (qr < start || ql > end)
            return 0;

        // Total overlap
        if (ql <= start && end <= qr)
            return tree[node];

        // Partial overlap: push down updates before reading children
        push(node, start, end);
        int mid = start + (end - start) / 2;
        T leftSum = query_range(2 * node, start, mid, ql, qr);
        T rightSum = query_range(2 * node + 1, mid + 1, end, ql, qr);
        return leftSum + rightSum;
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void update(int l, int r, T val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        return query_range(1, 0, n - 1, l, r);
    }
};

int main() {
    // Example usage: Array of size 6 initialized to 0
    SegmentTree<int> st(6);

    // Set values in range [1, 3] to 10
    st.update(1, 3, 10);

    // Set values in range [2, 5] to 5
    st.update(2, 5, 5);

    // Query sum value in range [0, 2] -> Returns 10 (from index 1)
    std::cout << "Sum in [0, 2]: " << st.query(0, 2) << std::endl;

    // Query sum value in range [3, 5] -> Returns 5
    std::cout << "Sum in [2, 5]: " << st.query(2, 5) << std::endl;

    return 0;
}
