// CS161: Design and Analysis of Algorithms, Programming Assignment 1.1

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

tuple<long long int, vector<int>> merge_and_count(vector<int> a, vector<int> b) {
	vector<int> c;
	int sentinel = max(* max_element(a.begin(), a.end()) + 1, * max_element(b.begin(), b.end()) + 1);
	a.push_back(sentinel);
	b.push_back(sentinel);

	long long int inversions = 0;

	int j = 0;
	int k = 0;

	while (j < a.size() - 1 || k < b.size() - 1) {
		if (a[j] < b[k]) {
			c.push_back(a[j]);
			j++;
		} else if (a[j] > b[k] && a[j] != sentinel) {
			inversions += (a.size() - j - 1);
			c.push_back(b[k]);
			k++;
		} else if (a[j] == b[k]) {
			c.push_back(a[j]);
			j++;
		} else {
			c.push_back(b[k]);
			k++;
		}
	}

	tuple<long long int, vector<int>> output (inversions, c);

	return output;
}

tuple<long long int, vector<int>> sort_and_count_inversions(vector<int> v) {
	if (v.size() == 1) {
		tuple<long long int, vector<int>> base_case (0, v);
		return base_case;
	}

	tuple<long long int, vector<int>> x = sort_and_count_inversions(vector<int> (v.begin(), v.end() - floor((double) v.size()/2)));
	tuple<long long int, vector<int>> y = sort_and_count_inversions(vector<int> (v.begin() + ceil((double) v.size()/2), v.end()));
	tuple<long long int, vector<int>> z = merge_and_count(get<1>(x), get<1>(y));

	tuple<long long int, vector<int>> output (get<0>(x) + get<0>(y) + get<0>(z), get<1>(z));

	return output;
}

// tests (from https://lagunita.stanford.edu/courses/course-v1:Engineering+Algorithms1+SelfPaced/discussion/forum/course/threads/5c06974bb670a66bdc000000)

void testRandomPositiveVector() {
	vector<int> randomPositiveVector;
	randomPositiveVector.push_back(3);
	randomPositiveVector.push_back(5);
	randomPositiveVector.push_back(100);
	randomPositiveVector.push_back(9);
	randomPositiveVector.push_back(6);
	randomPositiveVector.push_back(0);
    int inversions = get<0>(sort_and_count_inversions(randomPositiveVector));
    if (inversions == 8)
        cout << "SUCCESS for testRandomPositiveVector";
    else
        cout << "FAILURE for testRandomPositiveVector";
    cout << ": correct answer is " << 8 << ", your answer is " << inversions << endl;
}

void testRandomMixedVector() {
	vector<int> randomMixedVector;
	randomMixedVector.push_back(5);
	randomMixedVector.push_back(1);
	randomMixedVector.push_back(-3);
	randomMixedVector.push_back(2);
	randomMixedVector.push_back(6);
	randomMixedVector.push_back(-4);
	randomMixedVector.push_back(0);
    int inversions = get<0>(sort_and_count_inversions(randomMixedVector));
    if (inversions == 13)
        cout << "SUCCESS for testRandomMixedVector";
    else
        cout << "FAILURE for testRandomMixedVector";
    cout << ": correct answer is " << 13 << ", your answer is " << inversions << endl;
}

void testRandomNegativeVector() {
	vector<int> randomNegativeVector;
	randomNegativeVector.push_back(-3);
	randomNegativeVector.push_back(-1);
	randomNegativeVector.push_back(-6);
	randomNegativeVector.push_back(-4);
	randomNegativeVector.push_back(0);
	randomNegativeVector.push_back(-2);
    int inversions = get<0>(sort_and_count_inversions(randomNegativeVector));
    if (inversions == 6)
        cout << "SUCCESS for testrandomNegativeVector";
    else
        cout << "FAILURE for testrandomNegativeVector";
    cout << ": correct answer is " << 6 << ", your answer is " << inversions << endl;
}

void testOneNumVector() {
	vector<int> oneNumVector;
	oneNumVector.push_back(3);
    int inversions = get<0>(sort_and_count_inversions(oneNumVector));
    if (inversions == 0)
        cout << "SUCCESS for testOneNumVector";
    else
        cout << "FAILURE for testOneNumVector";
    cout << ": correct answer is " << 0 << ", your answer is " << inversions << endl;
}

void testTwoNumVector() {
	vector<int> twoNumVector;
	twoNumVector.push_back(2);
	twoNumVector.push_back(1);
    int inversions = get<0>(sort_and_count_inversions(twoNumVector));
    if (inversions == 1)
        cout << "SUCCESS for testTwoNumVector";
    else
        cout << "FAILURE for testTwoNumVector";
    cout << ": correct answer is " << 1 << ", your answer is " << inversions << endl;
}

void testSortedVector() {
	vector<int> sortedVector;
	sortedVector.push_back(1);
	sortedVector.push_back(2);
	sortedVector.push_back(3);
	sortedVector.push_back(4);
	sortedVector.push_back(5);
	sortedVector.push_back(6);
    int inversions = get<0>(sort_and_count_inversions(sortedVector));
    if (inversions == 0)
        cout << "SUCCESS for testSortedVector";
    else
        cout << "FAILURE for testSortedVector";
    cout << ": correct answer is " << 0 << ", your answer is " << inversions << endl;
}

void testOppositeSortedVector() {
	vector<int> oppositeSortedVector;
	oppositeSortedVector.push_back(6);
	oppositeSortedVector.push_back(5);
	oppositeSortedVector.push_back(4);
	oppositeSortedVector.push_back(3);
	oppositeSortedVector.push_back(2);
	oppositeSortedVector.push_back(1);
    int inversions = get<0>(sort_and_count_inversions(oppositeSortedVector));
    if (inversions == 15)
        cout << "SUCCESS for testOppositeSortedVector";
    else
        cout << "FAILURE for testOppositeSortedVector";
    cout << ": correct answer is " << 15 << ", your answer is " << inversions << endl;
}

void testSortedNegativeVector() {
	vector<int> sortedNegativeVector;
	sortedNegativeVector.push_back(-5);
	sortedNegativeVector.push_back(-4);
	sortedNegativeVector.push_back(-3);
	sortedNegativeVector.push_back(-2);
	sortedNegativeVector.push_back(-1);
	sortedNegativeVector.push_back(0);
    int inversions = get<0>(sort_and_count_inversions(sortedNegativeVector));
    if (inversions == 0)
        cout << "SUCCESS for testSortedNegativeVector";
    else
        cout << "FAILURE for testSortedNegativeVector";
    cout << ": correct answer is " << 0 << ", your answer is " << inversions << endl;
}

void testSortedOppositeNegativeVector() {
	vector<int> sortedOppositeNegativeVector;
	sortedOppositeNegativeVector.push_back(0);
	sortedOppositeNegativeVector.push_back(-1);
	sortedOppositeNegativeVector.push_back(-2);
	sortedOppositeNegativeVector.push_back(-3);
	sortedOppositeNegativeVector.push_back(-4);
	sortedOppositeNegativeVector.push_back(-5);
    int inversions = get<0>(sort_and_count_inversions(sortedOppositeNegativeVector));
    if (inversions == 15)
        cout << "SUCCESS for testSortedOppositeNegativeVector";
    else
        cout << "FAILURE for testSortedOppositeNegativeVector";
    cout << ": correct answer is " << 15 << ", your answer is " << inversions << endl;
}

void testVectorWithDoubles() {
	vector<int> vectorWithDoubles;
	vectorWithDoubles.push_back(3);
	vectorWithDoubles.push_back(4);
	vectorWithDoubles.push_back(1);
	vectorWithDoubles.push_back(2);
	vectorWithDoubles.push_back(1);
	vectorWithDoubles.push_back(5);
	vectorWithDoubles.push_back(2);
    int inversions = get<0>(sort_and_count_inversions(vectorWithDoubles));
    if (inversions == 10)
        cout << "SUCCESS for testVectorWithDoubles";
    else
        cout << "FAILURE for testVectorWithDoubles";
    cout << ": correct answer is " << 10 << ", your answer is " << inversions << endl;
}

void testVectorAllSame() {
	vector<int> vectorAllSame;
	vectorAllSame.push_back(2);
	vectorAllSame.push_back(2);
	vectorAllSame.push_back(2);
	vectorAllSame.push_back(2);
	vectorAllSame.push_back(2);
    int inversions = get<0>(sort_and_count_inversions(vectorAllSame));
    if (inversions == 0)
        cout << "SUCCESS for testVectorAllSame";
    else
        cout << "FAILURE for testVectorAllSame";
    cout << ": correct answer is " << 0 << ", your answer is " << inversions << endl;
}

void testVectorLargeNumbers() {
	vector<int> vectorLargeNumbers;
	vectorLargeNumbers.push_back(400);
	vectorLargeNumbers.push_back(350);
	vectorLargeNumbers.push_back(550);
	vectorLargeNumbers.push_back(1000);
	vectorLargeNumbers.push_back(1);
    int inversions = get<0>(sort_and_count_inversions(vectorLargeNumbers));
    if (inversions == 5)
        cout << "SUCCESS for testVectorLargeNumbers";
    else
        cout << "FAILURE for testVectorLargeNumbers";
    cout << ": correct answer is " << 5 << ", your answer is " << inversions << endl;
}

int main() {
	testRandomPositiveVector();
	testRandomMixedVector();
	testRandomNegativeVector();
	testOneNumVector();
	testTwoNumVector();
	testSortedVector();
	testOppositeSortedVector();
	testSortedNegativeVector();
	testSortedOppositeNegativeVector();
	testVectorWithDoubles();
	testVectorAllSame();
	testVectorLargeNumbers();

	vector<int> problem;
	string line;
	ifstream inputVector ("IntegerArray.txt");
	if (inputVector.is_open()) {
		while (getline(inputVector, line))
			problem.push_back(stoi(line));
		inputVector.close();
	}

	cout << "This vector has " << get<0>(sort_and_count_inversions(problem)) << " inversions." << endl;

}