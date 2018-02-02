#include <iostream>
#include <vector>

using namespace std;
bool mark[600+7][600+7];
bool a[600+7][600+7];
int n,m;
vector<pair<int,int>> ans;

void dfs(int i, int j, vector<pair<int,int>>& v){
	if(mark[i][j])
		return;
	if(i==n-1 and j==m-1) {
		mark[i][j]=true;
		v.push_back(make_pair(i,j));
		ans = v;
		return;
	}


	mark[i][j]=true;
	if(i<n-1 and a[i+1][j]){
		v.push_back(make_pair(i,j));

		dfs(i + 1, j, v);

		v.pop_back();
	}
	if(i>0 and a[i-1][j]){
		v.push_back(make_pair(i,j));
		dfs(i - 1, j, v);
		v.pop_back();

	}
	if(j<m-1 and a[i][j+1]){
		v.push_back(make_pair(i,j));
		dfs(i, j + 1, v);
		v.pop_back();

	}
	if(j>0 and a[i][j-1]){
		v.push_back(make_pair(i,j));
		dfs(i, j - 1, v);
		v.pop_back();

	}
	if(i<n-1 and j<m-1 and a[i+1][j+1]) {
		v.push_back(make_pair(i,j));
		dfs(i + 1, j + 1, v);
		v.pop_back();
	}
	if(i<n-1 and j>0 and a[i+1][j-1]) {
		v.push_back(make_pair(i,j));
		dfs(i + 1, j - 1, v);
		v.pop_back();

	}
	if(i>0 and j<m-1 and a[i-1][j+1]) {
		v.push_back(make_pair(i,j));
		dfs(i - 1, j + 1, v);
		v.pop_back();
	}
	if(i>0 and j>0 and a[i-1][j-1]) {
		v.push_back(make_pair(i,j));
		dfs(i - 1, j - 1, v);
		v.pop_back();
	}
	return;
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char ch=getchar();
			if(ch=='\n')
				ch=getchar();
			a[i][j]= (ch=='0');
		}
	}
	vector<pair<int,int>> start;
	dfs(0,0,start);
	if(ans.size()==0){
		cout << "That's a dead end!" << endl;
	} else{
		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); ++i) {
			cout << ans[i].first+1 << " " << ans[i].second+1 << endl;
		}
	}

	return 0;
}