#include <iostream>
#include <cmath>
#include <map>

using namespace std;


bool visited[33554433];
map<long long, int> mp;
map<long long, long long> p;
map<long long, long long> inv_mp;
vector<vector<int> > solutions;

int idx = 1;

void show(int mat[5][5]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; i+j < 5; j++){
				if(mat[i][j]==1) cout<<"* ";
				else cout<<"o ";
		}
		cout<<endl;
		for(int k = 2; k < i+3; k++) cout<<" ";
	}
	cout<<endl;
}

long long hash_fct(int (&mat)[5][5]){
	long long val = 0;
	
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			val += mat[i][j] * (1<<(5*i+j));
		}
	}
	return val;
}



int get_total(int (&mat)[5][5]){
	int tot = 0;
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			tot += mat[i][j];
		}
	}
	return tot;
}

void show_str(int hval){
	int mat[5][5];
	for(int i = 0; i < 5;i++){
		for(int j = 0; j < 5; j++){
			mat[i][j] = (hval%2);
			hval /= 2;
		}
	}
	show(mat);
}

void dfs(int (&mat)[5][5], int parent){
	long long hval = hash_fct(mat);
	visited[hval] = true;
	mp[hval] = idx;
	inv_mp[idx] = hval;
	p[idx] = parent;
	idx++;
	auto mat_orig = mat;
	if(get_total(mat)==1){
		// show(mat);
		idx = mp[hash_fct(mat)];
		int itr = idx;
		vector<int> solution;
		solution.push_back(inv_mp[itr]);
		while(p[itr] != -1){
			itr = p[itr];
			// show_str(inv_mp[itr]);
			solution.push_back(inv_mp[itr]);
		}
		reverse(solution.begin(), solution.end());
		solutions.push_back(solution);
		return;
	}
	for(int i = 0; i < 5; i++){
		for(int j = 0; i+j < 5; j++){
			if(mat[i][j]!=0) continue;
			//**o
			if(j>=2 && mat[i][j-2]==1 && mat[i][j-1]==1){
				mat[i][j-2] = 0;
				mat[i][j-1] = 0;
				mat[i][j] = 1;
				if(!visited[hash_fct(mat)]){
					dfs(mat, mp[hval]);
				}
				mat[i][j-2] = 1;
				mat[i][j-1] = 1;
				mat[i][j] = 0;
			}
			// //o**
			if(j+2<5 && mat[i][j+2]==1 && mat[i][j+1]==1){
				mat[i][j+2] = 0;
				mat[i][j+1] = 0;
				mat[i][j] = 1;
				if(!visited[hash_fct(mat)]){
					dfs(mat, mp[hval]);
				}
				mat[i][j+2] = 1;
				mat[i][j+1] = 1;
				mat[i][j] = 0;
			}
			// //  *
			// // *
			// //o
			if(j+2<5 && i-1>=0 && mat[i-1][j+1]==1 && mat[i-2][j+2]==1){
				mat[i-1][j+1] = 0;
				mat[i-2][j+2] = 0;
				mat[i][j] = 1;
				if(!visited[hash_fct(mat)]){
					dfs(mat, mp[hval]);
				}
				mat[i-1][j+1] = 1;
				mat[i-2][j+2] = 1;
				mat[i][j] = 0;
			}
			// //*
			// // *
			// //  o
			if(i-2>=0 && mat[i-2][j]==1 && mat[i-1][j]==1){
				mat[i-2][j] = 0;
				mat[i-1][j] = 0;
				mat[i][j] = 1;
				if(!visited[hash_fct(mat)]){
					dfs(mat, mp[hval]);
				}
				mat[i-2][j] = 1;
				mat[i-1][j] = 1;
				mat[i][j] = 0;
			}
			// //  o
			// // *
			// //*
			if(j-2>=0 && i+2 < 5 && mat[i+2][j-2]==1 && mat[i+1][j-1]==1){
				
				mat[i+2][j-2] = 0;
				mat[i+1][j-1] = 0;
				mat[i][j] = 1;
				if(!visited[hash_fct(mat)]){
					dfs(mat, mp[hval]);
				}				
				mat[i+2][j-2] = 1;
				mat[i+1][j-1] = 1;
				mat[i][j] = 0;
			}
			//o
			// *
			//  *
			if(i+2 <5 && mat[i+1][j]==1 && mat[i+2][j]==1){
				mat[i+1][j] = 0;
				mat[i+2][j] = 0;
				mat[i][j] = 1;
				if(!visited[hash_fct(mat)]){
					dfs(mat, mp[hval]);
				}
				mat[i+1][j] = 1;
				mat[i+2][j] = 1;
				mat[i][j] = 0;
			}
		}
	}
	return;
}



int main(){
	int mat[5][5];
	for(int i = 0; i < 5;i++){
		for(int j = 0; j < 5; j++){
			mat[i][j] = 0;
		}
	}
	for(int i = 0; i < 5; i++){
		for(int j = 0; i+j < 5; j++){
			mat[i][j] = 1;
		}
	}
	mat[0][4] = 0;
	mp[hash_fct(mat)] = idx;
	inv_mp[idx] = hash_fct(mat);
	p[idx] = -1;
	idx++;
	dfs(mat, -1);
	for(int s = 0; s<solutions.size();s++){
		auto sol = solutions[s];
		cout<<"Solution no "<<s+1<<" :"<<endl<<endl;
		for(auto itr : sol){
			show_str(itr);
		}
		cout<<"---------------------------"<<endl;
		cin.ignore();
	}
	return 0;
}


