#include <iostream>
#include <fstream>
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

		path.push_back(v);

		vector<vector<int>> new_possible = intersection(possible, larger[v[0]][v[1]][v[2]]);
		f(new_possible);

		path.pop_back();
	}
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


	vector<vector<int>> possible = larger[0][0][0];
	path.push_back({0, 0, 0});

	f(possible);

	ofstream out(output_file);
	for(int i = 0; i < solutions.size(); i++){
		if(solutions[i].size() < solutions.back().size()){
			continue;
		}

		for(int j = 0; j < solutions[i].size(); j++){
			out << "(" << solutions[i][j][0] << ", " << solutions[i][j][1] << ", " << solutions[i][j][2] << ") "; 
		}  
		out << endl;
	} 

	out.close();
	return 0;
}