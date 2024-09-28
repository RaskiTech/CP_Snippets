int segment_tree_sum(int a, int b, vector<int> &tree, int n) {
    a += n; b += n;
    int s = 0;
    while (a <= b) {
        if (a%2 == 1) s += tree[a++];
        if (b%2 == 0) s += tree[b--];
        // the following are used for minimum
        // if (a%2 == 1) s = min(tree[a++], s);
        // if (b%2 == 0) s = min(tree[b--], s);
        a /= 2; b /= 2;
    }
    return s;
}

void segment_tree_add(int k, int x, vector<int> &tree, int n) {
    k += n;
    tree[k] += x;
    // tree[k] = x; // if one wants to completely replace a value
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2*k]+tree[2*k+1];
    }
}

int bit_ceil(int n) {
    int res = 1;
    while (res < n) res <<= 1;
    return res;
}

vector<int> create_segment_tree(int n, vector<int> &input, int size) {
    vector<int> tree(2 * size, 0);
    // Add input to the end
    for (int i = 0; i < n; i++) {
        tree[size + i] = input[i];
    }

    // start from the end, from the second last element -> -2
    for (int i = size * 2 - 2; i > 0; i -= 2) {
        tree[i/2] = tree[i] + tree[i + 1];
    }

    return tree;
}

int size = bit_ceil(n);
vector<int> segment_tree = create_segment_tree(n, input_line, size);