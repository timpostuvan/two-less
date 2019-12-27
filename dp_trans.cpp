#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define INF 10000000

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

vector<vector<int>> larger[maxn][maxn][maxn];
map<vector<vector<int>>, int> dp;
map<vector<vector<int>>, vector<vector<int>>> path;

vector<vector<int>> intersection(vector<vector<int>> &a, vector<vector<int>> &b){ 
    vector<vector<int>> ret;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ret));
    return ret;
}

int f(vector<vector<int>> &possible){
	if(possible.size() == 0){
		return 0;
	}

	if(dp.count(possible)){
		return dp[possible];
	}

	int max_len = 0;
	vector<vector<int>> max_path;
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
			max_path = path[new_possible];
			max_path.insert(max_path.begin(), v);
		}
	}

	dp[possible] = max_len;
	path[possible] = max_path;

	return max_len;
}


int main(){
	int n = 7;

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


	vector<vector<int>> possible = larger[0][0][0];
	cout << "Max length: " << f(possible) + 1 << endl;


	vector<vector<int>> solution = path[larger[0][0][0]];
	solution.insert(solution.begin(), {0, 0, 0});
	for(int i = 0; i < solution.size(); i++){
		cout << "(" << solution[i][0] << ", " << solution[i][1] << ", " << solution[i][2] << ") "; 
	} 
	
	return 0;
}