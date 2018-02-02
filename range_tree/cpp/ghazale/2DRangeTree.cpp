#include <iostream>
#include <vector>
#include <algorithm>
#include<set>

using namespace std;

template<typename T>
class Node {
public:
	T x;
	T y;
	Node *parent;
	Node *left, *right;
	Node(T value, T value2) {
		left = right = parent = NULL;
		x = value;
		y = value2;
	}
	Node() {
		left = right = parent = NULL;
		x = 0;
		y = 0;
	}

};
template<typename T>
bool func(Node<T>* i1, Node<T>* i2)
{
	return (i1->x < i2->x);
}
template<typename T>
bool func2(Node<T>* i1, Node<T>* i2)
{
	return (i1->y < i2->y);
}
template<typename T>
class RangeTree {
protected:
	vector<Node<T>*> data;
	vector<Node<T>*> data2;
	set<T> savedNodes1;
	set<T> savedNodes1y;
	Node<T> *split;
	vector<Node<T>*> savedNodes;
	vector<Node<T>*> savedNodesy;
	Node<T> *root;
	Node<T> *rootMain;
	T null;
	Node<T> *nil;

public:

	RangeTree(vector<T> a, vector<T> b) {
		this->null = (T)NULL;
		nil = NULL;
		root = nil;
		pushingData(a, b);
	}
	void pushingData(vector<T> vecx, vector<T> vecy) {
		for (int i = 0; i < vecx.size(); i++) {
			Node<T> *u = new Node<T>(vecx[i], vecy[i]);
			data.push_back(u);
		}
		sort(data.begin(), data.end(), func<T>);
		buildTree();
		rootMain = root;
	}
	void buildTree() {
		for (int i = 0; i < data.size() / 2; i++) {
			Node<T> *q = data[i];
			data[i] = data[data.size() - i - 1];
			data[data.size() - 1 - i] = q;
		}
		while (data.size() != 1 && data2.size() != 1) {
			if (data.size() == 0) {
				while (data2.size() > 1) {
					while (data2.size() > 1) {
						Node<T> *x = data2[data2.size() - 1];
						data2.pop_back();
						Node<T> *y = data2[data2.size() - 1];
						data2.pop_back();
						data.push_back(makeParent(x, y));
						if (data2.size() == 1) {
							Node<T> *w = data2[data2.size() - 1];
							data2.pop_back();
							data.push_back(w);
						}
					}
					for (int i = 0; i < data.size() / 2; i++) {
						Node<T> *q = data[i];
						data[i] = data[data.size() - i - 1];
						data[data.size() - 1 - i] = q;
					}
				}
			}
			if (data2.size() == 0) {
				while (data.size() > 1) {
					while (data.size() > 1) {
						Node<T> *x = data[data.size() - 1];
						data.pop_back();
						Node<T> *y = data[data.size() - 1];
						data.pop_back();
						data2.push_back(makeParent(x, y));
						if (data.size() == 1) {
							Node<T> *w = data[data.size() - 1];
							data.pop_back();
							data2.push_back(w);
						}
					}
					for (int i = 0; i < data2.size() / 2; i++) {
						Node<T> *q = data2[i];
						data2[i] = data2[data2.size() - i - 1];
						data2[data2.size() - 1 - i] = q;
					}
				}
			}
		}
		if (data.size() == 1) {
			root = data[data.size() - 1];
			data.pop_back();
		}
		if (data2.size() == 1) {
			root = data2[data2.size() - 1];
			data2.pop_back();
		}
	}
	Node<T>* makeParent(Node<T>* first, Node<T>* second) {
		Node<T> *par = new Node<T>();
		par->left = first;
		first->parent = par;
		par->right = second;
		second->parent = par;
		par->x = getMax(par->left)->x;
		par->y = getMax(par->left)->y;
		return par;
	}

	Node<T>* getMax(Node<T> *u) {
		while (u->right != nil) {
			u = u->right;
		}
		return u;
	}

	Node<T>* findSplitNodex(T x1, T x2) {
		Node<T> *w = rootMain;
		int comp = compare(x1, w->x);
		int comp2 = compare(x2, w->x);
		while (w->left != nil && w->right != nil && (x1>w->x || w->x >= x2)) {
			if (w->x >= x2)
				w = w->left;
			else
				w = w->right;
		}
		split = w;
		return w;
	}
	Node<T>* findSplitNodey(T y1, T y2) {
		Node<T> *w = root;
		int comp = compare(y1, w->y);
		int comp2 = compare(y2, w->y);
		while (w->left != nil && w->right != nil && (y1>w->y || w->y >= y2)) {
			if (w->y >= y2)
				w = w->left;
			else
				w = w->right;
		}
		split = w;
		return w;
	}

	int compare(T a, T b) {
		if (a > b)
			return 1;
		else if (a == b)
			return 0;
		else
			return -1;
	}
	void savingDatay(Node<T> *w) {
		if (savedNodes1.find(w->y) == savedNodes1.end()) {
			savedNodes.push_back(w);
			savedNodes1.insert(w->y);
		}
		if (w->left != nil) {
			savingDatay(w->left);
		}
		if (w->right != nil)
			savingDatay(w->right);
	}
	void savingData(Node<T> *w) {
		if (savedNodes1.find(w->x) == savedNodes1.end()) {
			savedNodes.push_back(w);
			savedNodes1.insert(w->x);
		}
		if (w->left != nil) {
			savingData(w->left);
		}
		if (w->right != nil)
			savingData(w->right);
	}
	void leftQueryx(T x1, T x2) {
		Node<T> *u = findSplitNodex(x1, x2);
		if (u->left == nil && u->right == nil) {
			if (u->x >= x1 && u->x <= x2) {
				savingData(u);
			}
		}
		else {
			u = u->left;
			while (u->left != nil || u->right != nil) {
				if (x1 <= u->x) {
					savingData(u->right);
					u = u->left;
				}
				else {
					u = u->right;
				}
			}
			if (u->x >= x1 && u->x <= x2) {
				if (savedNodes1.find(u->x) == savedNodes1.end()) {
					savedNodes.push_back(u);
					savedNodes1.insert(u->x);
				}

			}
		}
	}
	void rightQueryx(T x1, T x2) {
		Node<T> *u = findSplitNodex(x1, x2);
		if (u->left == nil && u->right == nil) {
			if (u->x >= x1 && u->x <= x2) {
				savingData(u);
			}
		}
		else {
			u = u->right;
			while (u->left != nil || u->right != nil) {
				if (x2 >= u->x) {
					savingData(u->left);
					u = u->right;
				}
				else {
					u = u->left;
				}
			}
			if (u->x >= x1 && u->x <= x2) {
				if (savedNodes1.find(u->x) == savedNodes1.end()) {
					savedNodes.push_back(u);
					savedNodes1.insert(u->x);
				}
			}
		}
	}
	void leftQueryy(T y1, T y2) {
		Node<T> *u = findSplitNodey(y1, y2);
		if (u->left == nil && u->right == nil) {
			if (u->y >= y1 && u->y <= y2) {
				savingDatay(u);
			}
		}
		else {
			u = u->left;
			while (u->left != nil || u->right != nil) {
				if (y1 <= u->y) {
					savingDatay(u->right);
					u = u->left;
				}
				else {
					u = u->right;
				}
			}
			if (u->y >= y1 && u->y <= y2) {
				if (savedNodes1.find(u->y) == savedNodes1.end()) {
					savedNodes.push_back(u);
					savedNodes1.insert(u->y);
				}

			}
		}
	}
	void rightQueryy(T y1, T y2) {
		Node<T> *u = findSplitNodey(y1, y2);
		if (u->left == nil && u->right == nil) {
			if (u->y >= y1 && u->y <= y2) {
				savingDatay(u);
			}
		}
		else {
			u = u->right;
			while (u->left != nil || u->right != nil) {
				if (y2 >= u->y) {
					savingDatay(u->left);
					u = u->right;
				}
				else {
					u = u->left;
				}
			}
			if (u->y >= y1 && u->y <= y2) {
				if (savedNodes1.find(u->y) == savedNodes1.end()) {
					savedNodes.push_back(u);
					savedNodes1.insert(u->y);
				}
			}
		}
	}
	void make2DTree(T x1, T y1, T x2, T y2) {
		leftQueryx(x1, x2);
		rightQueryx(x1, x2);
		if (savedNodes.size() == 0)
			cout << "None" << endl;
		else {
			data = savedNodes;
			savedNodes.erase(savedNodes.begin(), savedNodes.end());
			savedNodes1.erase(savedNodes1.begin(), savedNodes1.end());
			sort(data.begin(), data.end(), func2<T>);
			buildTree();
			leftQueryy(y1, y2);
			rightQueryy(y1, y2);
			if (savedNodes.size() == 0)
				cout << "None" << endl;
			else {
				sort(savedNodes.begin(), savedNodes.end(), func2<T>);
				for (int i = 0; i < savedNodes.size(); i++) {
					cout << savedNodes[i]->x << " ";
				}
				cout << endl;
				for (int i = 0; i < savedNodes.size(); i++) {
					cout << savedNodes[i]->y << " ";
				}
				cout << endl;
				savedNodes.erase(savedNodes.begin(), savedNodes.end());
				savedNodes1.erase(savedNodes1.begin(), savedNodes1.end());
				data.erase(data.begin(), data.end());
				data2.erase(data2.begin(), data2.end());
			}
		}

	}
};

int main() {
	int n;
	vector<double> dataX;
	vector<double> dataY;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double x;
		cin >> x;
		dataX.push_back(x);
	}
	for (int i = 0; i < n; i++) {
		double y;
		cin >> y;
		dataY.push_back(y);
	}
	RangeTree<double>rt2(dataX, dataY);
	cin >> n;
	for (int i = 0; i < n; i++) {
		double x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		rt2.make2DTree(x1, y1, x2, y2);
	}

}