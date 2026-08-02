#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> tree;
    std::vector<T> lazy;
    std::vector<bool> has_lazy; // Tracks if a lazy value is pending

    void push(int node) {
        if (has_lazy[node]) {
            // Pass the assignment value to the left child
            tree[2 * node] = lazy[node];
            lazy[2 * node] = lazy[node];
            has_lazy[2 * node] = true;

            // Pass the assignment value to the right child
            tree[2 * node + 1] = lazy[node];
            lazy[2 * node + 1] = lazy[node];
            has_lazy[2 * node + 1] = true;

            // Clear the lazy flag for the current node
            has_lazy[node] = false;
        }
    }

    void update_range(int node, int start, int end, int l, int r, T val) {
        if (r < start || end < l) {
            return; // No overlap
        }
        if (l <= start && end <= r) {
            // Complete overlap: update node value and mark it lazy
            tree[node] = val;
            lazy[node] = val;
            has_lazy[node] = true;
            return;
        }
        // Partial overlap: push pending updates down, then recurse
        push(node);
        int mid = start + (end - start) / 2;
        update_range(2 * node, start, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, end, l, r, val);
        
        // Merge step: parent maximum is the max of its children
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }

    T query_range(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return std::numeric_limits<T>::min(); // No overlap return minimum infinity
        }
        if (l <= start && end <= r) {
            return tree[node]; // Complete overlap
        }
        // Partial overlap: resolve lazy evaluations before moving down
        push(node);
        int mid = start + (end - start) / 2;
        T left_res = query_range(2 * node, start, mid, l, r);
        T right_res = query_range(2 * node + 1, mid + 1, end, l, r);
        
        return std::max(left_res, right_res);
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        has_lazy.assign(4 * n, false);
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

    // Query max value in range [0, 2] -> Returns 10 (from index 1)
    std::cout << "Max in [0, 2]: " << st.query(0, 2) << std::endl;

    // Query max value in range [3, 5] -> Returns 5
    std::cout << "Max in [3, 5]: " << st.query(3, 5) << std::endl;

    return 0;
}
