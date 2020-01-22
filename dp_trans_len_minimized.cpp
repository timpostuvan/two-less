#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define maxn 13

bool less_2_table[maxn * maxn * maxn][maxn * maxn * maxn];
bool less_3_table[maxn * maxn * maxn][maxn * maxn * maxn];

// (x, y, z) in n-ary representation
int convert(int n, int x, int y, int z){
	int ret = n * n * x + n * y + z; 
	return ret;
}


bool less_2(vector<int> &a, vector<int> &b){
	int positions = 0;
	for(int i = 0; i < a.size(); i++){
		if(a[i] < b[i]){
			positions++;
		}
	}

	if(positions >= 2){
		return true;
	}
	else{
		return false;
	}
}

bool less_equal_3(vector<int> &a, vector<int> &b){
	int positions = 0;
	for(int i = 0; i < a.size(); i++){
		if(a[i] <= b[i]){
			positions++;
		}
	}

	if(positions >= 3){
		return true;
	}
	else{
		return false;
	}
}


int n;
vector<unsigned int> convert_to_dp_state(vector<int> &possible){
	vector<unsigned int> ret;

	unsigned int OFFSET = n * n * n;
	for(int i = 0; i < possible.size(); i += 3){
		unsigned int first = 0;
		unsigned int second = 0;
		unsigned int third = 0;

		if(i < possible.size()){
			first = possible[i];
		}

		if(i + 1 < possible.size()){
			second = possible[i + 1];
		}

		if(i + 2 < possible.size()){
			third = possible[i + 2];
		}

		unsigned int combined = OFFSET * OFFSET * first + OFFSET * second + third;
		ret.push_back(combined);
	}

	return ret;
}

map<vector<unsigned int>, int> dp;

vector<int> intersection(vector<int> &a, int value){ 
    vector<int> ret = a;
    int ind = 0;
    for(int i = 0; i < ret.size(); i++){
    	if(less_2_table[value][ret[i]]){
    		ret[ind++] = ret[i];
    	}
    }

    ret.resize(ind);
    return ret;
}



int f(vector<int> &possible){
	if(possible.size() == 0){
		return 0;
	}

	vector<int> smallest(possible.size(), 0);
	vector<int> minimized_possible;
	for(int i = 0; i < possible.size(); i++){
		if(smallest[i] == 1){
			continue;
		}	

		minimized_possible.push_back(possible[i]);

		for(int j = i + 1; j < possible.size(); j++){
			if(less_3_table[possible[i]][possible[j]]){
				smallest[j] = 1;
			}
		}
	}

	vector<unsigned int> possible_hash = convert_to_dp_state(minimized_possible);
	if(dp.count(possible_hash)){
		return dp[possible_hash];
	}

	int max_len = 0;
	for(int i = 0; i < possible.size(); i++){
		if(smallest[i] == 1){
			continue;
		}

		vector<int> new_possible = intersection(possible, possible[i]);
		int len = f(new_possible);

		if(1 + len > max_len){
			max_len = 1 + len;
		}
	}

	dp[possible_hash] = max_len;
	return max_len;
}


int main(int argc, char* argv[]){
	n = stoi(argv[1]);
	char* output_file = argv[2];

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){

				for(int i1 = 0; i1 < n; i1++){
					for(int j1 = 0; j1 < n; j1++){
						for(int k1 = 0; k1 < n; k1++){
							vector<int> a = {i, j, k};
							vector<int> b = {i1, j1, k1};

							int ind_a = convert(n, i, j, k);
							int ind_b = convert(n, i1, j1, k1);

							less_2_table[ind_a][ind_b] = less_2(a, b);
							less_3_table[ind_a][ind_b] = less_equal_3(a, b);
						}
					}
				}
			}
		}
	}

	vector<int> start;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				if(less_2_table[convert(n, 0, 0, 0)][convert(n, i, j, k)]){
					start.push_back(convert(n, i, j, k));
				}
			}
		}
	}

	ofstream out(output_file);

	out << "Max length: " << f(start) + 1 << endl;
	cout << "Max length: " << f(start) + 1 << endl;

	out.close();
	return 0;
}