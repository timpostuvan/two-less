#include <iostream>
#include <vector>
#include <algorithm>

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


vector<vector<int>> larger[maxn][maxn][maxn];
vector<vector<int>> path;

vector<vector<vector<int>>> solutions;

int max_length = 0;

vector<vector<int>> intersection(vector<vector<int>> &a, vector<vector<int>> &b){ 
    vector<vector<int>> ret;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ret));
    return ret;
}

void f(vector<vector<int>> &possible){
	if(path.size() + possible.size() < max_length){
		return;
	}

	if(possible.size() == 0 && path.size() >= max_length){
		cout << path.size() << endl;
		max_length = path.size();
		solutions.push_back(path);
		return;
	}

	for(auto i : possible){
		path.push_back(i);

		vector<vector<int>> new_possible = intersection(possible, larger[i[0]][i[1]][i[2]]);
		f(new_possible);

		path.pop_back();
	}
}


int main(){
	int n = 5;

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
	path.push_back({0, 0, 0});

	f(possible);

	for(int i = 0; i < solutions.size(); i++){
		for(int j = 0; j < solutions[i].size(); j++){
			cout << "(" << solutions[i][j][0] << ", " << solutions[i][j][1] << ", " << solutions[i][j][2] << ") "; 
		}
		cout << endl;
	}
	return 0;
}