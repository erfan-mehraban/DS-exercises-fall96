#include <iostream>
#include <climits>
#include <queue>

using namespace std;

queue<double> balancing;


class AVL{
public:
	AVL(){
		root = nullptr;
		external = new Node();
		external->height = -1;
		external->value = INT32_MIN;
	}

	bool add(double x){
		Node *u = root;
		if(u == nullptr){
			Node* newNode = new Node();
			newNode->value = x;
			newNode->left = external;
			newNode->right = external;
			root = newNode;
			return true;
		}
		while(true){
			if(u->value == x)
				return false;
			else if(u->value > x and u->left != external) {
				u = u->left;
			}
			else if(u->value > x and u->left == external){
				Node* newNode = new Node;
				newNode->parent = u;
				u->left = newNode;
				newNode->value = x;
				newNode->left = external;
				newNode->right = external;

				Node *w = newNode;
				while(w!= nullptr){
					w->height = max(w->left->height, w->right->height) + 1;
					w= w->parent;
				}
				insertionBalance(newNode);
				return true;
			}
			else if(u->value < x and u->right != external)
				u = u->right;
			else if(u->value < x and u->right == external){

				Node* newNode = new Node;
				newNode->parent = u;
				u->right = newNode;

				newNode->value = x;
				newNode->left = external;
				newNode->right = external;

				Node *w = newNode;
				while(w != nullptr){
					w->height = max(w->left->height, w->right->height) + 1;
					w= w->parent;
				}

				insertionBalance(newNode);
				return true;
			}
		}
	}


	bool remove(double x){
		Node *u = root;
		if(u== nullptr)
			return false;
		while(true){
			if(u->value == x){

				if(u->left == external and u->right == external){
					Node* tmp = u->parent;
					if(root==u) {
						root = nullptr;
						delete u;
						return true;
					}
					if(u->parent->right ==u)
						u->parent->right = external;
					else if(u->parent->left ==u)
						u->parent->left = external;
					Node* w = tmp;
					while(w!= nullptr){
						w->height = max(w->left->height, w->right->height)+1;
						w= w->parent;
					}
					deletionBalance(tmp);
					delete u;
					return true;
				}
				else if(u->left != external and u->right == external){
					Node *tmp = u->parent;
					if(u!=root){
						if(u->parent->left == u) {
							u->parent->left = u->left;
							u->left->parent =  u->parent;
						}else {
							u->parent->right = u->left;
							u->left->parent = u->parent;
						}
					}
					else if(u==root){
						u->left->parent = nullptr;
						root = u->left;
					}
					Node* w = tmp;
					while(w!= nullptr){
						w->height = max(w->left->height, w->right->height)+1;
						w= w->parent;
					}
					deletionBalance(tmp);
					delete u;
					return true;
				}
				else if(u->left == external and u->right != external){
					Node* tmp = u->parent;
					if(u!=root) {
						if(u->parent->left == u) {
							u->parent->left = u->right;
							u->right->parent =  u->parent;
						}else {
							u->parent->right = u->right;
							u->right->parent = u->parent;
						}
					}
					else if(u==root){
						u->right->parent = nullptr;
						root = u->right;
					}
					Node* w = tmp;
					while(w!= nullptr){
						w->height = max(w->left->height, w->right->height)+1;
						w= w->parent;
					}
					deletionBalance(tmp);
					delete u;
					return true;
				}else if(u->left != external and u->right != external){
					Node *newR = u->left;
					Node* tmp;
					while (newR->right != external) {
						newR = newR->right;
					}
					tmp=newR->parent;
					u->value = newR->value;

					if(newR == newR->parent->left) {
						newR->parent->left = external;

					}else {
						newR->parent->right = external;
					}
					Node* w = tmp;
						while(w!= nullptr){
							w->height = max(w->left->height, w->right->height)+1;
							w= w->parent;
						}
					deletionBalance(tmp);
					delete newR;
					return true;
				}

			}
			else if(u->value > x and u->left != external)
				u = u->left;
			else if(u->value > x and u->left == external){
				return false;
			}
			else if(u->value < x and u->right != external)
				u = u->right;
			else if(u->value < x and u->right == external){
				return false;
			}
		}
	}
	double find(double x){
		Node *u = root;
		Node* successor = external;
		while(true){
			if(u->value == x) {
				return u->value;
			}
			else if(u->value > x and u->left != nullptr) {
				successor = u;
				u = u->left;
			}
			else if(u->value > x and u->left == nullptr){
				return successor->value;
			}
			else if(u->value < x and u->right != nullptr) {
				u = u->right;
			}
			else if(u->value < x and u->right == nullptr){
				return successor->value;
			}
		}

	}



private:
	class Node{
	public:
		Node* parent;
		Node* left;
		Node*right;
		int height;
		double value;
		Node(){
			parent= nullptr;
			left= nullptr;
			right= nullptr;
			height=0;
			value = 0;
		}
	};
	Node* root;
	Node* external;
	void insertionBalance(Node * u) {
		Node* node = u;
		Node* child = external;
		Node* grandChild = external;
		while(node != nullptr and abs(node->right->height - node->left->height) < 2){
			grandChild = child;
			child = node;
			node = node->parent;
		}
		if(node == nullptr)
			return;

		if(node->left == child and child->left == grandChild){
			balancing.push(node->value);
			rotateRight(node);
		} else if(node->left == child and child->right == grandChild){
			balancing.push(node->value);
			rotateLeft(child);
			rotateRight(node);
		} else if(node->right == child and child->left == grandChild){
			balancing.push(node->value);
			rotateRight(child);
			rotateLeft(node);
		} else if(node->right == child and child->right == grandChild){
			balancing.push(node->value);
			rotateLeft(node);
		}
		insertionBalance(node);

	}
	void deletionBalance(Node *u){
		Node* node = u;
		Node* child ;
		Node* grandChild ;
		while(node != nullptr and abs(node->right->height - node->left->height) < 2){
			node = node->parent;
		}
		if(node == nullptr)
			return;

		if(node->left->height > node->right->height)
			child = node->left ;
		else
			child = node->right;

		if(child->left->height > child->right->height)
			grandChild = child->left ;
		else
			grandChild = child->right;
		
		if(node->left == child and child->left == grandChild){
			balancing.push(node->value);
			rotateRight(node);
		} else if(node->left == child and child->right == grandChild){
			balancing.push(node->value);
			rotateLeft(child);
			rotateRight(node);
		} else if(node->right == child and child->left == grandChild){
			balancing.push(node->value);
			rotateRight(child);
			rotateLeft(node);
		} else if(node->right == child and child->right == grandChild){
			balancing.push(node->value);
			rotateLeft(node);
		}
		deletionBalance(node);
	}
	Node* rotateLeft(Node* u){
		Node* w = u->right;
		w->parent = u->parent;
		if(w->parent != nullptr){
			if( w->parent->left == u)
				w->parent->left=w;
			else
				w->parent->right =w;
		}
		u->right = w->left;
		if( u-> right != external){
			u->right->parent =u;
		}
		u->parent = w;
		w->left = u;
		if(u==root){
			root = w;
		}
		Node *ww = u;
		while(ww != nullptr){
			ww->height = max(ww->left->height, ww->right->height) + 1;
			ww= ww->parent;
		}

		return w;
	}
	Node* rotateRight(Node* u){
		Node* w = u->left;
		w->parent = u->parent;
		if(w->parent != nullptr){
			if( w->parent->left == u)
				w->parent->left=w;
			else
				w->parent->right =w;
		}
		u->left = w->right;
		if( u-> left != external){
			u->left->parent =u;
		}
		u->parent = w;
		w->right = u;
		if(u==root){
			root = w;
			root->parent = nullptr;
		}
		Node *ww = u;
		while(ww != nullptr){
			ww->height = max(ww->left->height, ww->right->height) + 1;
			ww= ww->parent;
		}

		return w;
	}

};

int main() {
	AVL tree;

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		if(s=="add"){
			double x;
			cin >> x;
			if(tree.add(x))
				cout << "added" << endl;
			else
				cout << "already in there" << endl;
			while(!balancing.empty()) {
				cout << "balancing " << balancing.front();
				if(balancing.front() == (int)balancing.front())
					cout << ".0";
				cout << endl;
				balancing.pop();
			}

		}
		if(s=="remove"){
			double x;
			cin >> x;
			if(tree.remove(x))
				cout << "removed" << endl;
			else
				cout << "does not exist" << endl;
			while(!balancing.empty()) {
				cout << "balancing " << balancing.front();
				if(balancing.front() == (int)balancing.front())
					cout << ".0";
				cout << endl;
				balancing.pop();
			}
		}
		if(s=="find"){
			double x;
			cin >> x;
			double tmp;
			tmp = tree.find(x);
			if(tmp==INT32_MIN){
				cout << "not found" << endl;
			} else {
				cout << tmp;
				if(tmp == (int)tmp)
					cout << ".0";
				cout << endl;
			}

		}

	}

	return 0;
}