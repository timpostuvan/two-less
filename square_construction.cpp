#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

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

int main(int argc, char* argv[]){
	int n = stoi(argv[1]);
	int n_small = stoi(argv[2]);

	int m = sqrt(n);
	vector<vector<int>> path;
	for(int i = 0; i < n * m; i++){
		path.push_back({0, 0, 0});
	}

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			path[i * n + j][0] = j;
		}
	}


	for(int i = 0; i < m; i++){

		for(int j = 0; j < m; j++){
			for(int k = 0; k < m; k++){
				path[i * m * m + j * m + k][1] = (i * m) + k;
			}
		}
	} 

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			path[i * m + j][2] = i;
		}
	}

	int len_small = 0;
	for(int i = 0; i < n * m; i++){
		if(path[i][0] < n_small && path[i][1] < n_small && path[i][2] < n_small){
			len_small++;
		}
	}

	cout << path.size() << endl;

	cout << len_small << "  " << (int)(sqrt(n_small) * n_small) << endl;



	/*

	for(int j = 0; j < solutions[i].size(); j++){
		cout << "(" << solutions[i][j][0] << ", " << solutions[i][j][1] << ", " << solutions[i][j][2] << ") "; 
	}  
	cout << endl;
	*/

	return 0;
}