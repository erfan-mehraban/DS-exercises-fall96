#include <iostream>
#include <assert.h>

const int BL_SIZE = 10;

using namespace std;

class Data{
public:
	Data(string k ="", string v =""){
		key=k;
		value=v;
	}
	bool operator ==(Data x){
		return key==x.key;
	}
	bool operator<(Data x){
		return key < x.key;
	}
	bool operator>(Data x){
		return key > x.key;
	}
	string key;
	string value;
	static Data null;
};
Data Data::null = Data();


template <typename T>
class Array{
public:
	Array(int len=1){
		length=len;
		a = new T[length];
	}
	T&operator[](int i){
		assert(i>=0 and i<length);
		return a[i];
	}
	int size(){
		return length;
	}
	Array<T>& operator=(Array<T> &b) {
		if(a != nullptr) delete[] a;
		a = b.a;
		length = b.length;
		b.a= nullptr;
		return *this;
	}

protected:
	T* a;
	int length;
};

template <typename T>
class ArrayDeque{
public:
	ArrayDeque(): a(1){
		n=0;
		j=0;
	}
	T get(int i){
		return a[ (j+i)% a.size()];
	}
	T set(int i, T x){
		T tmp = a[ (j+i)% a.size()];
		a[ (j+i)% a.size()] = x;
		return tmp;
	}
	int size(){
		return n;
	}

	void add(int i, T x){
		if(n+1> a.size()) resize();
		if(i<n/2){
			j = (j==0) ? a.size()-1: j-1;
			for (int k = 0; k <= i-1; ++k) {
				a[(j+k)%a.size()] = a[(j+k+1)%a.size()];
			}

		} else{
			for (int k = n; k > i ; k--) {
				a[(j+k)% a.size()] = a[ (j+k-1)%a.size()];
			}
		}
		a[(i+j) % a.size()] = x;
		n++;
	}
	T remove(int i){
		T tmp = a[(i+j)%a.size()];
		if(i<n/2){
			for (int k = i; k > 0; k--) {
				a[(j+k)% a.size()] = a[(j+k-1)% a.size()];
			}
			j = (j+1) % a.size();

		} else{
			for (int k = i; k < n-1 ; ++k) {
				a[(j+k)%a.size()] = a[(j+k+1)%a.size()];
			}
		}
		n--;
		if(a.size()>3*n) resize();
		return tmp;
	}

private:

	void resize() {
		Array<T> b(max(1,2*n));
		for (int i = 0; i < n; ++i) {
			b[i] = a[ (i+j)% a.size()];
		}
		a=b;
		j=0;
	}

protected:
	Array<T> a;
	int j;
	int n;
};

template <typename T>
class SkipList{
public:
	SkipList(){
		null = T::null;
		n = 0;
		h = 0;
		Node *u = new Node(0);
		sentinel = u;

	}
	int size(){
		return n;
	};
	T find(T x){
		Node* u = findPrevNode(x);
		if(u->next[0] == nullptr)
			return null;
		int i=0;
		while(i < u->next[0]->d.size() and x > u->next[0]->d.get(i) ){
			i++;
		}
		return u->next[0]->d.get(i);
	}

	bool add(T x){
		Node *u = sentinel;
		int r = h;
		int comp = 0;
		Node* stack[h+1];
		while(r>=0){
			while ( (u->next[r] != nullptr)  and  (u->next[r]->d.last() < x) ){
				u = u->next[r];
			}
			if( u->next[r]!= nullptr and u->next[r]->d.last() == x)
				return false;

			stack[r]=u;
			r--;
		}
		if(u->next[0]!= nullptr){
			for (int i = 0; i < u->next[0]->d.size(); ++i) {
				if(x==u->next[0]->d.get(i))
					return false;
			}
		}
		if(u!= sentinel and u->next[0]== nullptr and u->d.size() < BL_SIZE){
			u->d.add(x);
			n++;
			return true;
		}
		if(u!= sentinel and u->next[0]!= nullptr and u->d.size() < BL_SIZE ){
			u->d.add(x);
			n++;
			u->d.add(u->next[0]->d.removeFirst());
			u->next[0]->d.add(u->d.removeLast());

			return true;
		}
		int rr=0;
		Node* ww = u;
		Node* stack2[BL_SIZE+1];
		while(rr<BL_SIZE-1 and ww->next[0] != nullptr and ww->next[0]->d.size()==BL_SIZE){
			stack2[rr] = ww->next[0];
			rr++;
			ww = ww->next[0];
		}
		if(rr==BL_SIZE-1){
			spread(stack2,stack);

			u->next[0]->d.add(x);
			n++;
			return true;
		}
		if(ww->next[0]== nullptr){
			Node* newNode = new Node(pickHeight());
			for (int i = 0; i <=min(h,newNode->height) ; ++i) {
				newNode->next[i] = stack[i]->next[i];
				stack[i]->next[i] = newNode;
			}
			if(newNode->height > h){
				Node* newSentinel = new Node(newNode->height);
				for(int i=0;i<=h;i++){
					newSentinel->next[i] = sentinel->next[i];
				}
				for (int j=h+1;j<=newNode->height;j++) {
					newSentinel->next[j] = newNode;
					newNode->next[j] = nullptr;
				}
				sentinel = newSentinel;
				h = newSentinel->height;
			}

			newNode->d.add(x);
			n++;
			if(u==sentinel){
				u->next[0]->d.add(u->next[0]->next[0]->d.removeFirst());
				u->next[0]->next[0]->d.add(u->next[0]->d.removeLast());
			}
			if(u->next[0]->next[0]!= nullptr){
				u->next[0]->d.add(u->next[0]->next[0]->d.removeFirst());
				u->next[0]->next[0]->d.add(u->next[0]->d.removeLast());
			}
			return true;
		}
		while(rr>0){
			stack2[rr-1]->next[0]->d.add(stack2[rr-1]->d.removeLast());
			rr--;
		}
		u->next[0]->d.add(x);
		n++;

		return true;
	}
	void print(){
		Node* u = sentinel;
		while(u->next[0]!= nullptr){
			int i=0;
			cout << " << " << u->next[0]->d.size() << " >> ";
			while(u->next[0]->d.size()>i) {
				cout << u->next[0]->d.get(i).key << " ";
				i++;
			}
			u = u->next[0];
		}
		cout << endl;
	}
	bool remove(T x){
		bool removed = false;
		Node *u = sentinel;
		int r = h;
		int comp = 0;
		Node* stack[h+1];
		while(r>=0){
			while ( (u->next[r] != nullptr)  and  (u->next[r]->d.last() < x) ){
				u = u->next[r];
			}
			stack[r]=u;
			r--;
		}
		if(u->next[0] == nullptr)
			return false;
		if(u->next[0]!= nullptr){
			int i=0;
			while(x > u->next[0]->d.get(i)){
				i++;
			}
			if(!(u->next[0]->d.get(i) == x))
				return false;
		}
		int rr=0;
		Node* ww = u;
		Node* stack2[BL_SIZE+1];
		while(rr<BL_SIZE-1 and ww->next[0] != nullptr and ww->next[0]->d.size()==BL_SIZE-2){
			stack2[rr] = ww->next[0];
			rr++;
			ww = ww->next[0];
		}
		if(rr==BL_SIZE-1){
			gather(stack2);
			rr=0;
			int hh = u->next[0]->height;
			Node* del = u->next[0];
			for (int i = 0; i <= hh ; ++i) {
				stack[i]->next[i] = stack[i]->next[i]->next[i];
			}
			delete del;
		}

		while(rr>0){
			stack2[rr-1]->d.add(stack2[rr-1]->next[0]->d.removeFirst());
			rr--;
		}
		n--;
		u->next[0]->d.remove(x);
		if(u->next[0]->d.size()==0 and u->next[0]->next[0]== nullptr){
			int hh = u->next[0]->height;
			Node* del = u->next[0];
			for (int i = 0; i <= hh ; ++i) {
				stack[i]->next[i] = stack[i]->next[i]->next[i];
			}
			delete del;
		}
		if(u->next[0]->next[0]!= nullptr){
			u->next[0]->d.add(u->next[0]->next[0]->d.removeFirst());
			u->next[0]->next[0]->d.add(u->next[0]->d.removeLast());
		}
		return true;
	}
private:
	class BDeque : public ArrayDeque<T>{
		using ArrayDeque<T>::a;
		using ArrayDeque<T>::j;
		using ArrayDeque<T>::n;
	public:
		BDeque(int b){
			null = T::null;
			n=0;
			j=0;
			Array<T> z(BL_SIZE);
			a=z;
		}
		virtual ~BDeque(){}
		virtual int size(){
			return n;
		}
		virtual void add(T x){
			int i=0;
			while (x > ArrayDeque<T>::get(i) and i<size())
				i++;
			ArrayDeque<T>::add(i,x);
		}
		virtual bool remove(T x){
			int i=0;
			while (x>ArrayDeque<T>::get(i))
				i++;
			if(ArrayDeque<T>::get(i)==x){
				ArrayDeque<T>::remove(i);
				return true;
			} else
				return false;
		}
		void addLast(T x){
			ArrayDeque<T>::add(size(),x);
		}
		T last(){
			if(size()>0)
				return ArrayDeque<T>::get(size()-1);
			return null;
		}
		T removeLast(){
			return ArrayDeque<T>::remove(size()-1);
		}
		virtual void resize(){}

		T removeFirst() {
			return ArrayDeque<T>::remove(0);
		}

	private:
		T null;
	};
	class Node{
	public:
		Node(int h): d(BL_SIZE){
			height=h;
			next = new Node*[height+1];
			for (int i=0;i<=height;i++) {
				next[i]= nullptr;
			}
		}
		BDeque d;
		T x;
		int height;
		Node** next;
	};
	Node *sentinel;
	int h;
	int n;
	T null;

	int pickHeight(){
		int z;
		z = rand();
		int k = 0;
		int m = 1;
		while( (m & z) !=0){
			k++;
			m <<= 1;
		}
		return k;
	}


	Node* findPrevNode(T x){
		Node *u = sentinel;
		int r = h;
		while(r>=0){
			while(u->next[r] != nullptr and (u->next[r]->d.last()<x) )
				u= u->next[r];
			r--;
		}
		return u;
	}

	void spread(Node** stack2, Node** stack){
		Node* newNode = new Node(pickHeight());
		for (int i = 0; i <=min(h,newNode->height) ; ++i) {
			newNode->next[i] = stack[i]->next[i];
			stack[i]->next[i] = newNode;
		}
		if(newNode->height > h){
			Node* newSentinel = new Node(newNode->height);
			for(int i=0;i<=h;i++){
				newSentinel->next[i] = sentinel->next[i];
			}
			for (int j=h+1;j<=newNode->height;j++) {
				newSentinel->next[j] = newNode;
				newNode->next[j] = nullptr;
			}
			sentinel = newSentinel;
			h = newSentinel->height;
		}
		int rr=0;
		Node* u = newNode;
		while(rr<BL_SIZE-1){
			while(u->d.size()<BL_SIZE-1){
				u->d.addLast(u->next[0]->d.removeFirst());
			}
			u= u->next[0];
			rr++;
		}
	}
	void gather(Node** stack2){

		int rr=BL_SIZE-2;
		while(rr>0){
			stack2[rr]->d.add(stack2[rr]->d.removeLast());
			rr--;
		}
	}

};

int main() {
	SkipList<Data> a;

	int n;
	cin >> n;
	for (int i = 0; i <n ; ++i) {
		string s;
		cin >> s;
		if(s=="add"){
			string key;
			string value;
			cin >> key >> value;
			bool done = a.add(Data(key,value));
			if(done)
				cout << "added" << endl;
			else
				cout << "already in there" << endl;
		} else if(s=="find"){
			string key;
			cin >> key;
			if(a.find(Data(key))==Data::null)
				cout << "not found" << endl;
			else{
				cout << a.find(Data(key)).value << endl;

			}

		} else if(s=="remove"){
			string key;
			cin >> key;
			bool done = a.remove(Data(key));
			if(done)
				cout << "removed" << endl;
			else
				cout << "does not exist" << endl;

		}
		else if(s=="print"){
			a.print();
		}
	}

	return 0;
}