#include<bits/stdc++.h>
using namespace std;


class Partition {
	int nodes;
public:
	Partition(int nodes) {
		this->nodes = nodes;
	}

	void partition(vector<int> &partition1, vector<int> &partition2, int s1, int s2, map<int, int> &permanent_lock) {
		for (int i = 1; i <= nodes; i++){
			if (permanent_lock[i] == false){
				if ((rand() + i) % 2 == 1){
					if ((int)partition1.size() == s1)partition2.push_back(i);
					else if ((int)partition2.size() == s2)partition1.push_back(i);
					else partition1.push_back(i);
				}
				else{
					if ((int)partition1.size() == s1)partition2.push_back(i);
					else if ((int)partition2.size() == s2)partition1.push_back(i);
					else partition2.push_back(i);
				}
			}
		}
	}
};