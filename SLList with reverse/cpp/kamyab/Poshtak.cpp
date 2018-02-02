#include <iostream>

using namespace std;

template <typename T>
class SLList{
	T null;
public:
	SLList(){
		null = (T)NULL;
		n=0;
		head = NULL;
		tail = NULL;
	}
	int size(){
		return n;
	}
	void push(T x){
		Node* u = new Node(x);
		u->next = head;
		head = u;
		if(n==0){
			tail = head;
		}
		n++;
	}
	T pop(){
		if(n==0) return null;
		T tmp = head->x;
		Node* u = head;
		head= head->next;
		delete u;
		if(--n==0) tail= NULL;
		return tmp;
	}

	void add(T x){
		Node* u = new Node(x);
		if(n==0){
			head=u;
			tail =u;
		} else {
			u->next = NULL;
			tail->next = u;
			tail = u;
		}
		n++;
	}
	void reverse(int i, int j) {
		if (i == j)
			return;

		Node *stack[j];
		Node *u = head;
		Node *start;
		Node *end;
		int rr = 0;
		int k = 1;
		while (k < i - 1) {
			u = u->next;
			k++;
		}
		start = u;
		if (i == 1) {
			stack[rr] = u;
			rr++;
		}
		while (rr <= j - i) {
			u = u->next;
			stack[rr] = u;
			rr++;
		}

		end = u->next;
		if (i == 1) {
			start = stack[rr - 1];
			head = start;
			rr--;
		}
		while (rr > 0) {
			start->next = stack[rr - 1];
			start = start->next;
			rr--;
		}
		start->next = end;
		if (start->next == NULL)
			tail = start;

		return;
	}

private:
	class Node{
	public:
		Node* next;
		T x;
		Node(T x0){
			x = x0;
			next = NULL;
		}
	};
	Node *head,*tail;
	int n;
};
int main(){
	SLList<int> a;
	int n;
	cin >> n;
	for (int i = 0; i <n ; ++i) {
		string s;
		cin >> s;
		if(s=="removeLast"){
			if(a.size()==0){
				cout << "empty" << endl;
			} else
				cout << a.pop() << endl;
		} else if(s=="addLast"){
			int tmp;
			cin >> tmp;
			a.push(tmp);

		} else if(s=="addFirst"){
			int tmp;
			cin >> tmp;
			a.add(tmp);

		} else if(s=="reverse"){
			int x,y;
			cin >> x >> y;
			a.reverse(a.size()-y+1,a.size()-x+1);

		}
	}

}