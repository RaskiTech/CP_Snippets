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


// Ability to set ranges
class DynamicSTree {
public:
    const int NOT_SET = -1
    vector<pair<int, int>> data;
    vector<int> sizes;
    int offset;
    DynamicSTree(int size) {
        offset = 1;
        while (offset < size) offset <<= 1;
        data = vector<pair<int, int>>(2*offset, {0, NOT_SET});

        sizes = vector<int>(2*offset);
        for (int i = offset; i < sizes.size(); i++)
            sizes[i] = 1;
        for (int i = offset-1; i > 0; i--)
            sizes[i] = sizes[2*i] + sizes[2*i+1];
    }

    void Set(int lInc, int rInc, int value, int offsetIdx = 1)
    {
        if (lInc >= sizes[offsetIdx] || rInc < 0)
            return;
        if (lInc <= 0 && rInc >= sizes[offsetIdx]-1)
        {
            data[offsetIdx] = {sizes[offsetIdx] * value, value};
            return;
        }

        PropagateNode(offsetIdx);
        Set(lInc, min(rInc, sizes[2*offsetIdx]), value, 2*offsetIdx);
        Set(max<int>(lInc - sizes[2*offsetIdx], 0), rInc - sizes[2*offsetIdx], value, 2*offsetIdx+1);
        data[offsetIdx] = {data[2*offsetIdx].first + data[2*offsetIdx+1].first, NOT_SET};
    }
    void PropagateNode(int offsetIdx)
    {
        int value = data[offsetIdx].second;
        if (value == NOT_SET || offsetIdx >= offset)
            return;
        data[2*offsetIdx] = {sizes[2*offsetIdx] * value, value};
        data[2*offsetIdx+1] = {sizes[2*offsetIdx+1] * value, value};
        data[offsetIdx].second = NOT_SET;
    }
    int Range(int lInc, int rInc, int offsetIdx = 1)
    {
        PropagateNode(offsetIdx);
        if (lInc <= 0 && rInc >= sizes[offsetIdx]-1)
        {
            return data[offsetIdx].first;
        }

        int sum = 0;
        if (lInc < sizes[2*offsetIdx])
            sum += Range(lInc, min(rInc, sizes[2*offsetIdx]), 2*offsetIdx);
        if (rInc >= sizes[2*offsetIdx])
            sum += Range(max<int>(0, lInc - sizes[2*offsetIdx]), rInc - sizes[2*offsetIdx], 2*offsetIdx+1);
        return sum;
    }
};
// Ability to add ranges
class DynamicSTree {
public:
    vector<pair<int, int>> data;
    vector<int> sizes;
    int offset;
    DynamicSTree(int size) {
        offset = 1;
        while (offset < size) offset <<= 1;
        data = vector<pair<int, int>>(2*offset, {0, 0});

        sizes = vector<int>(2*offset);
        for (int i = offset; i < sizes.size(); i++)
            sizes[i] = 1;
        for (int i = offset-1; i > 0; i--)
            sizes[i] = sizes[2*i] + sizes[2*i+1];
    }

    void Add(int lInc, int rInc, int value, int offsetIdx = 1)
    {
        if (lInc >= sizes[offsetIdx] || rInc < 0)
            return;
        if (lInc <= 0 && rInc >= sizes[offsetIdx]-1)
        {
            data[offsetIdx] = {data[offsetIdx].first + sizes[offsetIdx] * value, data[offsetIdx].second + value};
            return;
        }

        PropagateNode(offsetIdx);
        Add(lInc, min(rInc, sizes[2*offsetIdx]), value, 2*offsetIdx);
        Add(max<int>(lInc - sizes[2*offsetIdx], 0), rInc - sizes[2*offsetIdx], value, 2*offsetIdx+1);
        data[offsetIdx] = {data[2*offsetIdx].first + data[2*offsetIdx+1].first, 0};
    }
    void PropagateNode(int offsetIdx)
    {
        int value = data[offsetIdx].second;
        if (value == 0 || offsetIdx >= offset)
            return;
        data[2*offsetIdx] = {data[2*offsetIdx].first + sizes[2*offsetIdx] * value, data[2*offsetIdx].second + value};
        data[2*offsetIdx+1] = {data[2*offsetIdx+1].first + sizes[2*offsetIdx+1] * value, data[2*offsetIdx+1].second + value};
        data[offsetIdx].second = 0;
    }
    int Range(int lInc, int rInc, int offsetIdx = 1)
    {
        PropagateNode(offsetIdx);
        if (lInc <= 0 && rInc >= sizes[offsetIdx]-1)
            return data[offsetIdx].first;

        int sum = 0;
        if (lInc < sizes[2*offsetIdx]) sum += Range(lInc, min(rInc, sizes[2*offsetIdx]), 2*offsetIdx);
        if (rInc >= sizes[2*offsetIdx]) sum += Range(max<int>(0, lInc - sizes[2*offsetIdx]), rInc - sizes[2*offsetIdx], 2*offsetIdx+1);
        return sum;
    }
};

////////////////////////////////////////////////////
//// Another implementation with just functions ////
////////////////////////////////////////////////////

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
