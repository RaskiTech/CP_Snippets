#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Debug printing
#ifdef DEBUG
#define deb(fmt, args...) printf("DEBUG: %d: " fmt, __LINE__, ##args)
#else
#define deb(fmt, args...)
#endif

void print_array(vector<int> in, const string title = "Vector")
{
	cout << title << " [\n";
	for (const auto& el : in) {
		cout << el << " ";
	}
	cout << "\n] END\n";
}

void print_matrix(vector<vector<int>> in, const string title = "Matrix")
{
	cout << title << "[\n";
	for (unsigned int i = 0; i < in.size(); i++) {
		for (unsigned int j = 0; j < in[i].size(); j++) {
			cout << in[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "] END\n";
}

int main(int argc, char *argv[])
{
	// Read the input parameters
	int n;
	cin >> n;

	// Read pairs from multiple lines
	vector<pair<int, int> > input_pairs(n);
	for (int i = 0; i < n; i++) {
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

	return 0;
}
