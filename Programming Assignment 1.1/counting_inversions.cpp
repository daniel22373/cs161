// CS161: Design and Analysis of Algorithms, Programming Assignment 1.1

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> merge(vector<int> v) {
	vector<int> c (v.size());
	vector<int> a = vector<int> (v.begin(), v.end() - v.size()/2);
	vector<int> b = vector<int> (v.begin() + v.size()/2, v.end());

	int j = 0;
	int k = 0;

	while (j < a.size() && k < b.size()) {
		if (a[j] < b[k]) {
			c.push_back(a[j]);
			j++;
		} else {
			c.push_back(b[k]);
			k++;
		}
	}

	return c;
}

int mergeSort(vector<int> v) {
	if (v.size() == 1) return 0;

	int x = mergeSort(vector<int> (v.begin(), v.end() - v.size()/2));
	int y = mergeSort(vector<int> (v.begin() + v.size()/2, v.end()));
	int z = merge(v).size();

	return x + y + z;
}

int main() {
	vector<int> test1;
	test1.push_back(1);
	test1.push_back(3);
	test1.push_back(5);
	test1.push_back(2);
	test1.push_back(4);
	test1.push_back(6);

	cout << "The vector contains:" << endl;

	for (int i = 0; i < test1.size(); i++) {
		cout << test1[i] << endl;
	}

	test1 = merge(test1);

	cout << "The vector contains:" << endl;

	for (int i = 0; i < test1.size(); i++) {
		cout << test1[i] << endl;
	}

	// cout << "This vector has " << mergeSort(test1, test.size()) << " inversions." << endl;

}