#include <vector>

using namespace std;

/**
 * @brief Return the index of the pair whose first element is equal to the
 * target x, or if x not found, return the index of the element e that is the
 * smallest element satisfying x < e.
 *
 * @param nums vector of pairs
 * @param low starting index
 * @param high ending index
 * @param x target
 */
int binary_search_pairs_lte(vector<pair<int, int>> &nums, int low, int high, int x)
{
	int last_suitable = -1;
	while (low <= high) {
		int mid = low + (high - low) / 2;

		// Check if x is present at mid
		if (nums[mid].first == x)
			return mid;

		// If x greater, ignore left half
		if (nums[mid].first < x) {
			low = mid + 1;
		}

		// If x is smaller, ignore right half
		else {
			last_suitable = mid;
			high = mid - 1;
		}
	}

	// If we reach here, then element was not present
	return last_suitable;
}


/**
 * @brief Basic binary search, return -1 if element not found
 */
int binary_search(vector<int> &nums, int low, int high, int x)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;

		// Check if x is present at mid
		if (nums[mid] == x)
			return mid;

		// If x greater, ignore left half
		if (nums[mid] < x) {
			low = mid + 1;
		}

		// If x is smaller, ignore right half
		else {
			high = mid - 1;
		}
	}

	// If we reach here, then element was not present
	return -1;
}

/**
 * @brief Return the index of the element which is equal to the
 * target x, or if x not found, return the index of the element e that is the
 * smallest element satisfying x < e.
 */
int binary_search_lte(vector<int> &nums, int low, int high, int x)
{
	int last_suitable = -1;
	while (low <= high) {
		int mid = low + (high - low) / 2;

		// Check if x is present at mid
		if (nums[mid] == x)
			return mid;

		// If x greater, ignore left half
		if (nums[mid] < x) {
			low = mid + 1;
		}

		// If x is smaller, ignore right half
		else {
			last_suitable = mid;
			high = mid - 1;
		}
	}

	// If we reach here, then element was not present
	return last_suitable;
}

/**
 * @brief Return the index of the element which is equal to the
 * target x, or if x not found, return the index of the element e that is the
 * smallest element satisfying x > e.
 */
int binary_search_gte(vector<int> &nums, int low, int high, int x)
{
	int last_suitable = -1;
	while (low <= high) {
		int mid = low + (high - low) / 2;

		// Check if x is present at mid
		if (nums[mid] == x)
			return mid;

		// If x greater, ignore left half
		if (nums[mid] < x) {
			last_suitable = mid;
			low = mid + 1;
		}

		// If x is smaller, ignore right half
		else {
			high = mid - 1;
		}
	}

	// If we reach here, then element was not present
	return last_suitable;
}
