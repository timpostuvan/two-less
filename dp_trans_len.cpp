#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#define INF 10000000
#define OFF_N 10
#define OFFSET 1000

using namespace std;

#define maxn 20

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

vector<int> convert_to_dp_state(vector<vector<int>> &possible){
	vector<int> ret;
	for(int i = 0; i < possible.size(); i += 3){
		int first = 0;
		int second = 0;
		int third = 0;

		if(i < possible.size()){
			first = (possible[i][0] * OFF_N * OFF_N + possible[i][1] * OFF_N + possible[i][2]);
		}

		if(i + 1 < possible.size()){
			second = (possible[i + 1][0] * OFF_N * OFF_N + possible[i + 1][1] * OFF_N + possible[i + 1][2]);
		}

		if(i + 2 < possible.size()){
			third = (possible[i + 2][0] * OFF_N * OFF_N + possible[i + 2][1] * OFF_N + possible[i + 2][2]);
		}

		int combined = OFFSET * OFFSET * first + OFFSET * second + third;
		ret.push_back(combined);
	}

	return ret;
}


vector<vector<int>> larger[maxn][maxn][maxn];
map<vector<int>, int> dp;

//map<vector<vector<int>>, int> dp;
// map<vector<vector<int>>, vector<vector<int>>> path;

vector<vector<int>> intersection(vector<vector<int>> &a, vector<vector<int>> &b){ 
    vector<vector<int>> ret;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ret));
    return ret;
}

int f(vector<vector<int>> &possible){
	if(possible.size() == 0){
		return 0;
	}

	vector<int> possible_hash = convert_to_dp_state(possible);
	if(dp.count(possible_hash)){
		return dp[possible_hash];
	}

	int max_len = 0;
//	vector<vector<int>> max_path;
	vector<int> smallest(possible.size(), 0);
	for(int i = 0; i < possible.size(); i++){
		if(smallest[i] == 1){
			continue;
		}	

		vector<int> v = possible[i];
		for(int j = i + 1; j < possible.size(); j++){
			if(less_equal_3(possible[i], possible[j])){
				smallest[j] = 1;
			}
		}

		vector<vector<int>> new_possible = intersection(possible, larger[v[0]][v[1]][v[2]]);

		int len = f(new_possible);

		if(1 + len > max_len){
			max_len = 1 + len;
	/*		max_path = path[new_possible];
			max_path.insert(max_path.begin(), v); */
		}
	}

	dp[possible_hash] = max_len;

//	dp[possible] = max_len;
//	path[possible] = max_path;

	return max_len;
}


int main(int argc, char* argv[]){
	int n = stoi(argv[1]);
	char* output_file = argv[2];


	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){

				for(int i1 = 0; i1 < n; i1++){
					for(int j1 = 0; j1 < n; j1++){
						for(int k1 = 0; k1 < n; k1++){
							vector<int> a = {i, j, k};
							vector<int> b = {i1, j1, k1};

							if(less_2(a, b)){
								larger[i][j][k].push_back(b);
							}
						}
					}
				}

			}
		}
	}


	ofstream out(output_file);

	vector<vector<int>> possible = larger[0][0][0];
	out << "Max length: " << f(possible) + 1 << endl;

/*	vector<vector<int>> solution = path[larger[0][0][0]];
	solution.insert(solution.begin(), {0, 0, 0});
	for(int i = 0; i < solution.size(); i++){
		out << "(" << solution[i][0] << ", " << solution[i][1] << ", " << solution[i][2] << ") "; 
	} */

	out.close();	
	return 0;
}