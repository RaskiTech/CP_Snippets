class STree {
public:
    vector<int> data;
    int offset;
    STree(int size, vector<int>& startVals)
    {
        offset = 1;
        while (size > offset) offset <<= 1;
        data = vector<int>(2*offset, 0);

        for (int i = 0; i < startVals.size(); i++)
            data[offset+i] = startVals[i];
        
        for (int i = offset-1; i > 0; i--)
        {
            data[i] = data[2*i] + data[2*i+1];
        }
    }

    void Add(int idx, int val) {Set(idx, data[offset+idx]+val);}
    void Set(int idx, int val) {
        idx += offset;
        data[idx] = val;
        idx /= 2;
        while (idx > 0)
        {
            data[idx] = data[2*idx] + data[2*idx+1];
            idx /= 2;
        }
    }
    int Range(int LInc, int RInc) {
        LInc += offset; RInc += offset;
        int sum = 0;
        while (LInc <= RInc)
        {
            if (LInc % 2 == 1) sum += data[LInc++];
            if (RInc % 2 == 0) sum += data[RInc--];
            LInc /= 2;
            RInc /= 2;
        }
        return sum;
    }
};


int ST_GetRange(vector<int> &tree, int lowerInclusive, int upperInclusive) {
    lowerInclusive += tree.size() / 2; upperInclusive += tree.size() / 2;
    int s = INIT_VAL; // 0 for SumTree and INT_MAX for MinTree
    while (lowerInclusive <= upperInclusive) {
        // Sum tree
        //if (lowerInclusive%2 == 1) s += tree[lowerInclusive++];
        //if (upperInclusive%2 == 0) s += tree[upperInclusive--];
        // Min tree
        if (lowerInclusive%2 == 1) s = min(tree[lowerInclusive++], s);
        if (upperInclusive%2 == 0) s = min(tree[upperInclusive--], s);

        lowerInclusive /= 2; upperInclusive /= 2;
    }
    return s;
}

////////////////////////////////////////////////////
//// Another implementation with just functions ////
////////////////////////////////////////////////////

void ST_Set(vector<int> &tree, int index, int newVal) {
    index += tree.size() / 2;
    
    //tree[index] += newVal; // For adding
    tree[index] = newVal; // For setting value

    for (index /= 2; index >= 1; index /= 2) {
        //tree[index] = tree[2*index]+tree[2*index+1]; // Sum tree
        tree[index] = min(tree[2*index], tree[2*index+1]); // Min tree
    }
}

// Create segment tree
vector<int> ST_Create(vector<int> &input, int valueCount) {
    int res = 1;
    while (res < valueCount) res <<= 1;
    vector<int> tree(2 * res, INIT_VAL);

    // Add input to the end
    for (int i = 0; i < input.size(); i++) {
        tree[res + i] = input[i];
    }

    // start from the end, from the second last element -> -2
    for (int i = res * 2 - 2; i > 0; i -= 2) {
        tree[i/2] = min(tree[i], tree[i + 1]); // Min tree
        //tree[i/2] = tree[i] + tree[i + 1]); // Sum tree
    }
    return tree;
}

vector<int> segment_tree = ST_Create(vec, vec.size());
