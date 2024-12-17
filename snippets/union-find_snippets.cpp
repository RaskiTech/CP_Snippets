class UnionFind {
public:
    vector<int> data;
    vector<int> length;
    int count;
    UnionFind(int n) : data(vector<int>(n)), length(vector<int>(n, 1)), count(n) {
        for (int i = 0; i < data.size(); i++)
            data[i] = i;
    }
    int Find(int a) {
        while (a != data[a])
            a = data[a];
        return a;
    }
    bool Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b)
            return false;
        if (length[a] < length[b])
            swap(a, b);
        length[a] += length[b];
        data[b] = a;
        count--;
        return true;
    }
};
