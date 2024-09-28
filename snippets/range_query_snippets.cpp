#include <cassert>
#include <vector>

using namespace std;

// ***** SUBARRAY SUMS *****
// Create sum array, REMEMBER TO TAKE BY REFERENCE
void create_sub_sum_array(vector<int> &input, int length, vector<int> &aux)
{
    assert(length > 0);
    aux[0] = input[0];
    for (int i = 1; i < length; i++) {
        aux[i] = aux[i - 1] + input[i];
    }
}

// Get subarray sum
int sub_array_sum(vector<int> &sums, int a, int b)
{
    assert(a <= b);
    int reduction = a - 1 < 0 ? 0 : sums[a - 1];
    return sums[b] - reduction;
}

// Creates matrix of array sums from top left to bottom right
// first coordinate is considered as column index and second one as row index
// (as in x,y coordinate system)
void create_matrix_subsum_array(int n, vector<int> input[], int sum[n][n])
{
    assert(n > 0);
    sum[0][0] = input[0][0];
    for (int j = 0; j < n; j++) {
        int row_sum = 0;
        for (int i = 0; i < n; i++) {
            row_sum += input[j][i];
            sum[j][i] = row_sum;
            if (j >= 1) {
                sum[j][i] += sum[j-1][i];
            }
        }
    }
}

// Matrix version of subarray sums
// upper left corner: (x1, y1), bottom right corner (x2, y2)
int matrix_subarray_sum(int n, int sum[n][n], int x1, int y1, int x2, int y2)
{
    assert(n > 0);
    assert(x1 >= 0);
    assert(y1 >= 0);
    assert(x2 >= x1);
    assert(y2 >= y1);

    if (x1 >= 1 && y1 >= 1) {
        return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1-1];
    }
    if (x1 == 0 && y1 == 0){
        return sum[x2][y2];
    }
    if (y1 == 0) {
        return sum[x2][y2] - sum[x1-1][y2];
    }
    if (x1 == 0) {
        return sum[x2][y2] - sum[x2][y1-1];
    }
    return -1; // We should not reach this
}

// ***** BINARY INDEXED TREE *****
// Get subarray sum from BIT
int bitree_sum(int k, vector<int> &tree) {
    int s = 0;
    while (k >= 1) {
        s += tree[k];
        k -= k&-k;
    }
    return s;
}

// Update element k by amount x in vector tree with n elements
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
