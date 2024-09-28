int bitree_sum(int k, vector<int> &tree) {
    int s = 0;
    while (k >= 1) {
        s += tree[k];
        k -= k&-k;
    }
    return s;
}

void bitree_add(int k, int x, int n, vector<int> &tree) {
    while (k <= n) {
        tree[k] += x;
        k += k&-k;
    }
}

// NOTE the output vector must be initialized to 0
void create_bitree(vector<int> &input, vector<int> &output, int length)
{
    for (int k = 1; k < length + 1; k++) {
        output[k-1] += input[k-1];
        int p_k = k& (-k);
        if ((k-1) + p_k < length)
            output[(k-1) + p_k] += output[k-1];
    }
}