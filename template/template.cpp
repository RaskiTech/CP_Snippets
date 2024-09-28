#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	// Read the input parameters
	int n, m;
	cin >> n >> m;

	// Read pairs from multiple lines
	vector<pair<int, int> > input_pairs(m);
	for (int i = 0; i < m; i++) {
		cin >> input_pairs[i].first >> input_pairs[i].second;
	}

	// Read values from one line
	vector<int> input_line(n);
	for (int i = 0; i < n; i++) {
		cin >> input_line[i];
	}

    // Read input matrix
    vector<int> input_matrix[n];
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            char tmp;
            cin >> tmp;
            if (tmp == '*') input_matrix[j].push_back(1);
            else input_matrix[j].push_back(0);
        }
    }

	cout << "TODO: result" << "\n";
	return 0;
}
