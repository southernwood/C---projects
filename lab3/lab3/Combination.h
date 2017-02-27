#include <vector>
#include <iostream>
#include <iterator>                                                                                

using namespace std;

void combinationuntil(vector<int> v, int n, int r, int index, vector<int> data, int i, vector<int> &s){
	if (index == r){
		
		for (int j = 0; j<r; ++j)
			s.push_back(data[j]);
		
		return;
	}

	if (i >= n){
		return;
	}
	data[index] = v[i];
	combinationuntil(v, n, r, index + 1, data, i + 1, s);
	combinationuntil(v, n, r, index, data, i + 1, s);
}

void printcomb(vector<int> v, int r, vector<int> &s){
	vector<int> data(r, 0);
	int n = v.size();
	combinationuntil(v, n, r, 0, data, 0, s);
};
