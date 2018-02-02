#include <iostream>

using namespace std;

int a[1000*1000];

int main()
{
	int n, m, i, j;
	cin >> n >> m;
	string s;
	for (int k = 0; k < n; k++) {
		a[k]=k+1;
	}
	for (int k = 0; k < m; k++) {
		cin >> s;
		if (s == "REV") {
			cin >> i >> j;
			int tmp;
            for (int t = 0; t <= (j-i)/2; t++) {
                tmp = a[t+i-1];
                a[t+i-1] = a[j-1-t];
                a[j-1-t] = tmp;
            }
		}
		else if (s == "NAME") {
			cin >> i;
			cout << a[i-1] << endl;
		}
	}
}
