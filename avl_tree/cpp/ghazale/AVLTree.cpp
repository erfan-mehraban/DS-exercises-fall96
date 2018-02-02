#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <stack>

using namespace std;
template<typename T>
class Node {
public:
	T x;
	Node *parent;
	Node *left, *right;
	int height;
	Node() {
		left = right = parent = NULL;
		height = 0;
	}
};

template <typename T>
class BinarySearchTree {
protected:
	Node<T> *root;
	Node<T> *nil;
	T null;
	Node<T> *savedNode;
	int n;
	Node<T>* findLast(T x) {
		Node<T> *w = root, *pre = nil;
		while (w != nil) {
			pre = w;
			int comp = compare(x, w->x);
			if (comp < 0) {
				w = w->left;
			}
			else if (comp > 0) {
				w = w->right;
			}
			else
				return w;
		}
		return pre;
	}
	int compare(T a, T b) {
		if (a > b)
			return 1;
		else if (a == b)
			return 0;
		else
			return -1;
	}
	bool addChild(Node<T> *p, Node<T> *u) {
		savedNode = u;
		if (p == nil) {
			root = u;
		}
		else {
			int comp = compare(u->x, p->x);
			if (comp < 0) {
				p->left = u;
				(p->height)--;
			}
			else if (comp > 0) {
				p->right = u;
				(p->height)++;
			}
			else {
				return false;
			}
			u->parent = p;
		}
		n++;
		return true;
	}
	void splice(Node<T> *u) {
		Node<T> *s, *p;
		if (u->left != nil) {
			s = u->left;
		}
		else {
			s = u->right;
		}
		if (u == root) {
			root = s;
			p = nil;
		}
		else {
			p = u->parent;
			if (p->left == u) {
				p->left = s;
			}
			else {
				p->right = s;
			}
		}
		if (s != nil) {
			s->parent = p;
		}
		n--;
	}

	void remove(Node<T> *u) {
		savedNode = u->parent;
		if (u->left == nil || u->right == nil) {
			splice(u);
			delete u;
		}
		else {
			Node<T> *w = u->right;
			while (w->left != nil)
				w = w->left;
			u->x = w->x;
			splice(w);
			delete w;
		}
	}


public:
	BinarySearchTree() {
		nil = NULL;
		root = nil;
		this->null = (T)NULL;
		n = 0;
	}
	int balanceNo(Node<T> *u) {
		return (heightOfTree(u->right) - heightOfTree(u->left));
	}
	void balancing() {
		if (n < 3)
			return;
		Node<T> *o = savedNode;
		stack<Node<T>*> stack1;
		stack<Node<T>*> stack2;
		stack<Node<T>*> stack3;
		stack<Node<T>*> stack4;
		//while (u->parent != nil) {
		//	u->height = balanceNo(u);
		//	u = u->parent;
		//}
		while (o != nil) {
			int b = balanceNo(o);
			if ((b > 1 || b<-1) && (stack1.top() == o->left)) {
				stack1.pop();
				if (stack1.top() == o->left->left) {
					if (b == 2) {
						if ((int)o->x == o->x)
							cout << "balancing " << o->x << ".0" << endl;
						else
							cout << "balancing " << o->x << endl;
					}
					else
						cout << "balancing " << endl;
					rotateRight(o);
					return;
				}
			}
			if ((b > 1 || b<-1) && (stack2.top() == o->left)) {
				stack2.pop();
				if (stack2.top() == o->left->right) {
					if (b == 2) {
						if ((int)o->x == o->x)
							cout << "balancing " << o->x << ".0" << endl;
						else
							cout << "balancing " << o->x << endl;
					}
					else
						cout << "balancing " << endl;
					rotateLeft(o->left);
					rotateRight(o);
					return;
				}
			}
			if ((b > 1 || b<-1) && (stack3.top() == o->right)) {
				stack3.pop();
				if (stack3.top() == o->right->left) {
					if (b == 2) {
						if ((int)o->x == o->x)
							cout << "balancing " << o->x << ".0" << endl;
						else
							cout << "balancing " << o->x << endl;
					}
					else
						cout << "balancing " << endl;
					rotateRight(o->right);
					rotateLeft(o);
					return;
				}
			}
			if ((b > 1 || b<-1) && (stack4.top() == o->right)) {
				stack4.pop();
				if (stack4.top() == o->right->right) {
					if (b == 2) {
						if ((int)o->x == o->x)
							cout << "balancing " << o->x << ".0" << endl;
						else
							cout << "balancing " << o->x << endl;
					}
					else
						cout << "balancing " << endl;
					rotateLeft(o);
					return;
				}
			}
			stack1.push(o);
			stack2.push(o);
			stack3.push(o);
			stack4.push(o);
			o = o->parent;
		}
	}
	void setBalanceNo(Node<T> *u) {
		if (u == nil) return;
		while (u->parent != nil) {
			u->height = balanceNo(u);
			u = u->parent;
		}
	}
	bool add(T x) {
		Node<T> *p = findLast(x);
		Node<T> *u = new Node<T>;
		u->x = x;
		return addChild(p, u);
	}

	int size() {
		return n;
	}
	int heightOfTree(Node<T> *u) {
		if (u == nil) {
			return 0;
		}
		else
			return 1 + max(heightOfTree(u->left), heightOfTree(u->right));
	}
	void rotateRight(Node<T> *u) {
		Node<T> *w = u->left;
		w->parent = u->parent;
		if (w->parent != nil) {
			if (w->parent->left == u) {
				w->parent->left = w;
			}
			else {
				w->parent->right = w;
			}
		}
		u->left = w->right;
		if (u->left != nil) {
			u->left->parent = u;
		}
		u->parent = w;
		w->right = u;
		if (u == root) { root = w; root->parent = nil; }
	}
	void rotateLeft(Node<T> *u) {
		Node<T> *w = u->right;
		w->parent = u->parent;
		if (w->parent != nil) {
			if (w->parent->left == u) {
				w->parent->left = w;
			}
			else {
				w->parent->right = w;
			}
		}
		u->right = w->left;
		if (u->right != nil) {
			u->right->parent = u;
		}
		u->parent = w;
		w->left = u;
		if (u == root) { root = w; root->parent = nil; }
	}
	T find(T x) {
		Node<T> *w = root, *z = nil;
		while (w != nil) {
			int comp = compare(x, w->x);
			if (comp < 0) {
				z = w;
				w = w->left;
			}
			else if (comp > 0) {
				w = w->right;
			}
			else {
				return w->x;
			}
		}
		return z == nil ? null : z->x;
	}
	void balancing2() {
		Node<T> *w = savedNode;
		//Node<T> *p = w;

		while (w != nil) {
			int b = balanceNo(w);
			if ((b>1 || b<-1) && balanceNo(w)<0 && balanceNo(w->left)<0) {
				if (b == 2) {
					if ((int)w->x == w->x)
						cout << "balancing " << w->x << ".0" << endl;
					else
						cout << "balancing " << w->x << endl;
				}
				else
					cout << "balancing" << endl;
				rotateRight(w);
				w = w->parent;
				continue;
			}
			if ((b>1 || b<-1) && balanceNo(w)<0 && balanceNo(w->left)>0) {
				if (b == 2) {
					if ((int)w->x == w->x)
						cout << "balancing " << w->x << ".0" << endl;
					else
						cout << "balancing " << w->x << endl;
				}
				else
					cout << "balancing" << endl;
				rotateLeft(w->left);
				rotateRight(w);
				w = w->parent;
				continue;
			}
			if ((b>1 || b<-1) && balanceNo(w)>0 && balanceNo(w->right) >= 0) {
				if (b == 2) {
					if ((int)w->x == w->x)
						cout << "balancing " << w->x << ".0" << endl;
					else
						cout << "balancing " << w->x << endl;
				}
				else
					cout << "balancing" << endl;
				rotateLeft(w);
				w = w->parent;
				continue;
			}
			if ((b>1 || b<-1) && balanceNo(w)>0 && balanceNo(w->right) <= 0) {
				if (b == 2) {
					if ((int)w->x == w->x)
						cout << "balancing " << w->x << ".0" << endl;
					else
						cout << "balancing " << w->x << endl;
				}
				else
					cout << "balancing" << endl;
				rotateRight(w->right);
				rotateLeft(w);
				w = w->parent;
				continue;
			}
			w = w->parent;
		}
	}

	bool remove(T x) {
		Node<T> *u = findLast(x);
		if (u != nil && compare(x, u->x) == 0) {
			remove(u);
			return true;
		}
		return false;
	}
};


int main()
{
	int n;
	BinarySearchTree<double> bst;
	cin >> n;
	string s;
	double value;
	for (int i = 0; i < n; i++) {
		cin >> s;
		if (s == "add") {
			cin >> value;
			bool b = bst.add(value);
			if (b) {
				cout << "added" << endl;
				bst.balancing();
			}
			else
				cout << "already in there" << endl;

		}
		else if (s == "remove") {
			cin >> value;
			bool b = bst.remove(value);
			if (b) {
				cout << "removed" << endl;
				bst.balancing2();
			}
			else
				cout << "does not exist" << endl;
		}
		else if (s == "find") {
			cin >> value;
			if (bst.find(value) == (double)NULL) {
				cout << "not found" << endl;
			}
			else {
				int a = bst.find(value);
				if (a == bst.find(value)) {
					cout << bst.find(value) << ".0" << endl;
				}
				else
					cout << bst.find(value) << endl;
			}

		}
	}
	return 0;
}