#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool visited[600][600];
string s[600];

class data {
public:
    int x;
    int y;
    data(int a, int b) {
        x = a;
        y = b;
    }
};

vector<::data> v;
int m, n;

void dfs(int i, int j) {
    if (visited[i][j] == true)
        return;
    visited[i][j] = true;
    if (i == n - 1 && j == m - 1) {
        v.push_back(::data(n - 1, m - 1));
        //cout << "yaaaaaaaaaay";
        cout << v.size() << endl;
        for (int i = 0; i<v.size(); i++) {
            cout << v[i].x + 1 << " " << v[i].y + 1 << endl;
        }
        //return;
    }
    else {
        if (i>0 && j>0 && s[i - 1][j - 1] == '0') {
            v.push_back(::data(i, j));
            dfs(i - 1, j - 1);
            v.pop_back();
        }
        if (i>0 && s[i - 1][j] == '0') {
            v.push_back(::data(i, j));
            // visited[i-1][j]=true;
            dfs(i - 1, j);
            v.pop_back();
        }
        if (i<n - 1 && j>0 && s[i + 1][j - 1] == '0') {
            v.push_back(::data(i, j));
            // visited[i+1][j-1]=true;
            dfs(i + 1, j - 1);
            v.pop_back();
        }
        if (j<m - 1 && s[i][j + 1] == '0') {
            v.push_back(::data(i, j));
            // visited[i][j+1]=true;
            dfs(i, j + 1);
            v.pop_back();
        }
        if (i<n - 1 && j<m - 1 && s[i + 1][j + 1] == '0') {
            v.push_back(::data(i, j));
            //visited[i+1][j+1]=true;
            dfs(i + 1, j + 1);
            v.pop_back();
        }
        if (i<n - 1 && s[i + 1][j] == '0') {
            v.push_back(::data(i, j));
            //visited[i+1][j]=true;
            dfs(i + 1, j);
            v.pop_back();
        }
        if (i>0 && j<m - 1 && s[i - 1][j + 1] == '0') {
            v.push_back(::data(i, j));
            //visited[i-1][j+1]=true;
            dfs(i - 1, j + 1);
            v.pop_back();
        }
        if (j>0 && s[i][j - 1] == '0') {
            v.push_back(::data(i, j));
            //visited[i][j-1]=true;
            dfs(i, j - 1);
            v.pop_back();
        }
    }
    //return;

}


int main()
{
    cin >> n >> m;
    for (int i = 0; i<n; i++) {
        cin >> s[i];
    }
    //v.push_back(data(0,0));
    dfs(0, 0);
    if (visited[n - 1][m - 1] != true) {
        cout << "That's a dead end!" << endl;
    }
    return 0;
}