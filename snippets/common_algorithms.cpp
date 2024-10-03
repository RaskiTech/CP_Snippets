///////////// Boyer-Moore Majority vote ////////////
// Returns n if n is appears more than n/2 times in array, random otherwise
int findMajorityElement(int nums[], int n)
{
    int m;
    int i = 0;
    for (int j = 0; j < n; j++)
    {
        if (i == 0)
            m = nums[j], i = 1;
        else
            (m == nums[j]) ? i++ : i--;
    }
 
    return m;
}


///////////// GCD & LCM ////////////
long long gcd(long long a, long long b)
{
    long long q, r;
    while (b > 0)
    {
        q = a / b;      // quotient
        r = a - q * b;  // remainder
        a = b;
        b = r;
    }
    return a;
}
long long lcm(int a, int b) { return (a / gcd(a, b)) * b; }

/////////// Is Prime O(n) //////////
bool isPrime(int n) {
    if (n <= 1)
        return false;

    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

/////////// Topological sort //////////
// takes adjacencylist and the number of nodes. Can be modified to take
// edge pairs instead.
vector<int> topologicalSort(vector<vector<int> >& adj,
                            int V)
{
    // Vector to store indegree of each vertex
    vector<int> indegree(V);
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    // Queue to store vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        // Decrease indegree of adjacent vertices as the
        // current node is in topological order
        for (auto it : adj[node]) {
            indegree[it]--;

            // If indegree becomes 0, push it to the queue
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // Check for cycle
    if (result.size() != V) {
        cout << "Graph contains cycle!" << endl;
        return {};
    }

    return result;
}

//////////// Linked list cycle detection algorithm /////////////
// Node not defined here
void detectCycle(Node* head)
{
    if (!head || !head->next)
        return nullptr;
    
    Node* a = head->next;
    Node* b = head->next->next;

    while (b && b->next && a != b)
    {
        a = a->next;
        b = b->next->next;
    }
    if (!b || !b->next)
        return nullptr;
    
    // We are in a cycle

    a = head;
    while (a != b)
    {
        a = a->next;
        b = b->next;
    }
    // a is in the position of the first node in the cycle

    int length = 1;
    b = a->next;
    while (a != b)
    {
        length++;
        b = b->next;
    }

    return a;
}

/////////// Find max subarray sum ////////////
int maxSubarraySum(vector<int> const &arr)
{
    int max_so_far = 0;
    int max_ending_here = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        max_ending_here = max_ending_here + arr[i];
        max_ending_here = max(max_ending_here, 0);
        max_so_far = max(max_so_far, max_ending_here);
    }
 
    return max_so_far;
}



/////////////// Monotonic queue (with sliding window) //////////////
deque<int> minStorage;
for (int right = 0, left = 0; right < nums.size(); right++)
{
    while (!maxElementStorage.empty() && nums[right] < minStorage.back())
        maxElementStorage.pop_back();
    minStorage.push_back(nums[right]);

    while (/* Move left side */)
    {
        if (nums[left] == minElementStorage.front())
            minElementStorage.pop_front();
        left++;
    }
}

///////////// KMP String matching algorithm ////////////////
// Usage: vector<int> allPositions = KMPSeach("str", "str is twice in this string");
// Output: {1, 22}

#include <bits/stdc++.h>
using namespace std;

// Fills lps[] for given pattern pat
void computeLPSArray(string& pat, int M, vector<int>& lps)
{
    // Length of the previous longest prefix suffix
    int len = 0;
    lps[0] = 0;

    // loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
// Prints occurrences of pat in txt
vector<int> KMPSearch(string& pat, string& txt)
{
    int M = pat.length();
    int N = txt.length();

    // Create lps[] that will hold the longest prefix suffix
    // values for pattern
    vector<int> lps(M);

    vector<int> result;

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt
    int j = 0; // index for pat
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            result.push_back(i - j + 1);
            j = lps[j - 1];
        }

        // Mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {

            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return result;
}
