#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
bool sortY(const pair<double,double> &a,const pair<double,double> &b) {
	return a.second<b.second;
}

class Node{
public:
	Node* parent,* leftChild, *rightChild, *left, *right, *yTree;
	double value;
	double x,y;
	Node(){
		parent = leftChild = rightChild = left= right= nullptr;
		x = y = value = INT32_MAX;
	}
};


class RangeTree{

public:


	RangeTree(pair<double,double>* sortedArray, int n){
		vector<pair<Node*,double> > v;
		for (int i = 0; i < n; ++i) {
			Node* newLeave = new Node();
			newLeave->x = sortedArray[i].first;
			newLeave->y = sortedArray[i].second;
			v.push_back(make_pair(newLeave,newLeave->x));
		}
		for (int i = 0; i < v.size(); ++i) {
			if(i>0)
				v[i].first->left = v[i-1].first;
			if(i<v.size()-1)
				v[i].first->right = v[i+1].first;
		}
		while(v.size()!=1){
			vector<pair<Node*,double> > tmp;

			for (int i=0;i<v.size()-1; i+=2){
				Node* innnerNode = new Node();
				innnerNode->leftChild = v[i].first;
				innnerNode->rightChild = v[i+1].first;

				v[i].first->parent = v[i+1].first->parent = innnerNode;
				innnerNode->value = v[i].second;
				tmp.push_back(make_pair(innnerNode,v[i+1].second));


				Node* ll=innnerNode->leftChild, *rr=innnerNode->rightChild;

				while(ll->leftChild!= nullptr)
					ll = ll->leftChild;
				while(rr->rightChild!= nullptr)
					rr = rr->rightChild;

				vector <pair<double,double> > sortedByY;
				while(ll!=rr){
					sortedByY.push_back(make_pair(ll->x,ll->y));
					ll = ll->right;
				}
				sortedByY.push_back(make_pair(ll->x,ll->y));
				sort(sortedByY.begin(),sortedByY.end(),sortY);
				innnerNode->yTree = BuildTree(sortedByY);



			}
			if(v.size()%2!=0){
				tmp.push_back(v[v.size()-1]);
			}
			v = tmp;
		}

		root = v[0].first;


	}

	vector<pair<double,double> > find(double ax, double bx, double ay, double by){

		vector<Node*> nodes;
		vector< pair<double,double> > ans;

		if(root== nullptr)
			return ans;
		Node* u = root;
		while(u->rightChild!= nullptr or u->leftChild!= nullptr) {
 			if (u->value < ax) {
				u = u->rightChild;
			} else if (u->value >= bx) {
				u = u->leftChild;

			} else
				break;
		}
		Node* l = u->leftChild, *r = u->rightChild;
		if(u->value == INT32_MAX and u->x<=bx and u->x>=ax){
			nodes.push_back(u);
		}

		while(l!= nullptr){
			if(l->value != INT32_MAX and ax <= l->value){
				nodes.push_back(l->rightChild);
				l = l->leftChild;
			} else if(l->x != INT32_MAX and ax <= l->x){
				nodes.push_back(l);
				break;
			}
			else if(l->value != INT32_MAX and ax > l->value){
				l = l->rightChild;
			} else
				break;
		}
		while(r!= nullptr){
			if(r->value != INT32_MAX and bx > r->value){
				nodes.push_back(r->leftChild);
				r = r->rightChild;
			} else if(r->x != INT32_MAX and bx >= r->x){
				nodes.push_back(r);
				break;
			} else if(r->value != INT32_MAX and bx <= r->value){
				r = r->leftChild;
			} else
				break;
		}
		for(int i=0;i <nodes.size();i++){
			findY(ay, by, nodes[i], ans);
		}

		return ans;

	}

private:
	Node* root;

	Node* BuildTree(vector<pair<double, double> > sortedArray) {
		root = new Node();
		vector<pair<Node*,double> > v;
		for (int i = 0; i < sortedArray.size(); ++i) {
			Node* newLeave = new Node();
			newLeave->x = sortedArray[i].first;
			newLeave->y = sortedArray[i].second;
			v.push_back(make_pair(newLeave,newLeave->y));
		}
		for (int i = 0; i < v.size(); ++i) {
			if(i>0)
				v[i].first->left = v[i-1].first;
			if(i<v.size()-1)
				v[i].first->right = v[i+1].first;
		}
		while(v.size()!=1) {
			vector<pair<Node *, double> > tmp;

			for (int i = 0; i < v.size()-1; i += 2) {
				Node *innerNode = new Node();
				innerNode->leftChild = v[i].first;
				innerNode->rightChild = v[i + 1].first;

				v[i].first->parent = v[i + 1].first->parent = innerNode;
				innerNode->value = v[i].second;
				tmp.push_back(make_pair(innerNode, v[i + 1].second));

			}
			if(v.size()%2!=0){
				tmp.push_back(v[v.size()-1]);
			}
			v = tmp;
		}
		return v[0].first;
	}

	void findY(double ay, double by, Node *node, vector<pair<double, double> >& v) {
		if(node== nullptr)
			return;
		if(node->x!=INT32_MAX){
			if(node->y<=by and node->y >=ay )
				v.push_back(make_pair(node->x,node->y));
			return;
		}
		Node* u = node->yTree;
		while(u->leftChild != nullptr and u->rightChild!= nullptr) {
			if (ay <= u->value)
				u = u->leftChild;
			else if(ay > u->value)
				u = u->rightChild;
		}
		if(u!=nullptr and u->y<ay){
			u = u->right;
		}
		while(u!=nullptr and u->y<=by) {
			v.push_back(make_pair(u->x, u->y));
			u = u->right;
		}
	}

};
int main() {
	int n;
	cin >> n;
	double * x = new double[n];
	double* y = new double[n];
	pair<double,double>* dots = new pair<double,double>[n];
	for (int i = 0; i <n ; ++i) {
		cin >> x[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> y[i];
	}
	for (int i = 0; i < n; ++i) {
		dots[i].first=x[i];
		dots[i].second=y[i];
	}
	sort(dots,dots+n);
	RangeTree r(dots,n);
	int m;
	cin >> m;
	for(int i=0; i<m ; i++){
		double ax,ay,bx,by;
		cin >> ax >> ay >> bx >> by;
		vector<pair<double,double> > v = r.find(ax,bx,ay,by);
		sort(v.begin(),v.end(), sortY );

		if(v.size()==0)
			cout << "None" << endl;
		else {
			for (int j = 0; j < v.size(); ++j) {
				cout << v[j].first << " ";
			}
			cout << endl;
			for (int j = 0; j < v.size(); ++j) {
				cout << v[j].second << " ";
			}
			cout << endl;
		}
	}


	return 0;
}
