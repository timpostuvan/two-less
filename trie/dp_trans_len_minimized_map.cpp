#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#define INF 10000000
#define OFF_N 10
#define OFFSET 1000

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


//------------------------------------------------------------------------------------------------------------

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


//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------
struct trie_node{
	short value;
	map<short, trie_node*> map_children;

	trie_node(){
		value = -1;
	}

	~trie_node(){
		for(auto it = map_children.begin(); it != map_children.end(); it++){
			delete it -> second;
		}
	} 
};


trie_node* root;


trie_node* find_node(trie_node* node, short ind){
	if(node -> map_children.count(ind)){
		return node -> map_children[ind];
	}
	else{
		return NULL;
	}
}

trie_node* add_node(trie_node* node, short ind){
	trie_node* new_node = new trie_node();
	node -> map_children[ind] = new_node;
	
	return new_node;
}


short check_state(vector<short> &minimized_possible){
	trie_node* current = root;
	for(int i = 0; i < minimized_possible.size(); i++){
		trie_node* next_node = find_node(current, minimized_possible[i]); 

		if(next_node != NULL){
			current = next_node;
		}
		else{
			return -1;
		}
	}

	return current -> value;
}

void add_state(vector<short> &minimized_possible, short dp_value){
	trie_node* current = root;
	for(int i = 0; i < minimized_possible.size(); i++){
		trie_node* next_node = find_node(current, minimized_possible[i]);

		if(next_node == NULL){
			current = add_node(current, minimized_possible[i]);
		}
		else{
			current = next_node;
		}
	}
	current -> value = dp_value;
}


//-----------------------------------------------------------------------------------------------------------------

vector<short> intersection(vector<short> &a, short value){ 
    vector<short> ret = a;
    int ind = 0;
    for(int i = 0; i < ret.size(); i++){
    	if(less_2_table[value][ret[i]]){
    		ret[ind++] = ret[i];
    	}
    }

    ret.resize(ind);
    return ret;
}

short f(vector<short> &possible){
	if(possible.size() == 0){
		return 0;
	}

	vector<short> smallest(possible.size(), 0);
	vector<short> minimized_possible;
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

	short value = check_state(minimized_possible);
	if(value != -1){
		return value;
	}

	short max_len = 0;
	for(int i = 0; i < possible.size(); i++){
		if(smallest[i] == 1){
			continue;
		}

		vector<short> new_possible = intersection(possible, possible[i]);
		short len = f(new_possible);

		if(1 + len > max_len){
			max_len = 1 + len;
		}
	}

	add_state(minimized_possible, max_len);
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

	vector<short> start;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				if(less_2_table[convert(n, 0, 0, 0)][convert(n, i, j, k)]){
					start.push_back(convert(n, i, j, k));
				}
			}
		}
	}

	root = new trie_node();

	ofstream out(output_file);

	out << "Max length: " << f(start) + 1 << endl;
	cout << "Max length: " << f(start) + 1 << endl;

	out.close();

	delete root;

	return 0;
}