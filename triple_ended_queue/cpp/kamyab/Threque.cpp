#include <iostream>
#include <assert.h>


using namespace std;



template <typename T>
class Array{
public:
	Array(int len = 10){
		lenght=len;
		a = new T[lenght];
	}
	T& operator[](int i){
		assert(i >=0 && i<lenght);
		return a[i];
	}
	Array<T>& operator=(Array<T> &b){
		if(a != NULL) delete[] a;
		a = b.a;
		b.a = NULL;
		lenght = b.lenght;
		return *this;
	}
	int size(){
		return lenght;
	}
	
	
private:
	int lenght;
	T *a;
};


template<class T>
class DualArrayDeque;

template <typename T>
class Stack{
	friend class DualArrayDeque<T>;
	
public:
	Stack(){
		n=0;
	}
	
	int size(){
		return n;
	}
	
	T get(int i){
		return a[i];
	}
	
	T set(int i, int x){
		T y = a[i];
		a[i] = x;
		return y;
	}
	void add(T x){
		
		if(n+1 > a.size()) resize();
		
		a[n]=x;
		n++;
	}
	T remove(){
		T x = a[n-1];
		n--;
		if(n <= 3*a.size()) resize();
		return x;
	}
	bool isEmpyt(){
		return n>0?0:1;
	}
	
	
private:
	Array<T> a;
	int n;
	void resize(){
		Array<T> b(max(2*n,1));
		for (int i=0;i<n;i++) {
			b[i]=a[i];
		}
		a=b;
	}
	
};

template <typename T>
class DualArrayDeque{
	
public:
	int size(){
		return front.size() + back.size();
	}
	T get(int i) {
		if (i < front.size()) {
			return front.get(front.size()-i-1);
		} else {
			return back.get(i-front.size());
		}
	}
	T set(int i, T x) {
		if (i < front.size()) {
			return front.set(front.size()-i-1, x);
			
		} else {
			return back.set(i-front.size(), x);
		}
	}
	void addFirst(T x){
		front.add(x);
		if(front.size() > 3*back.size())
			balance();
		
	}
	void addLast(T x){
		back.add(x);
		if(3*front.size() < back.size())
			balance();
		
	}
	T removeFirst(){
		
		T x;

		if(!front.isEmpyt()){
			x = front.remove();
		} else if(back.size()>1){
			balance();
			x = front.remove();
		}else {
			if(!back.isEmpyt())
				x= back.remove();
		}
		if(3*front.size() < back.size())
			balance();
		return x;
	}
	T removeLast(){
		T x ;

		if(!back.isEmpyt()){
			x = back.remove();
		} else if(front.size()>1){
			balance();
			x = back.remove();
		} else{
			x = front.remove();
		}
		if(front.size() > 3*back.size())
			balance();
		return x;
	}
	bool isEmpty(){
		return size()==0;
	}
	
	
private:
	Stack<T> front;
	Stack<T> back;
	
	void balance(){
		int n = size();
		int nf= n/2;
		Array<T> af(max(2*nf,1));
		for(int i=0;i< nf; i++){
			af[nf-i-1] = get(i);
		}
		int nb = n - nf;
		Array<T> ab(max(2*nb, 1));
		for (int i=0;i<nb;i++) {
			ab[i]= get(nf+i);
		}
		front.a = af;
		front.n = nf;
		back.n = nb;
		back.a= ab;
	}
	
};

template <typename T>
class DualArrayDequePlus{
	
public:
	DualArrayDequePlus(T* q, int ss){
		for (int i=0;i<ss/2;i++) {
			front.addLast(q[i]);
		}
		for (int i=ss/2;i<ss;i++) {
			back.addLast(q[i]);
		}
		balance();
	}
	void addFirst(T x){
		front.addFirst(x);
		balance();
	}
	
	
	void addLast(T x){
		back.addLast(x);
		balance();
	}
	
	void addMiddle(T x){
		back.addFirst(x);
		balance();
	}
	
	T removeFirst(){
		T x;
		if(!front.isEmpty()){
		   x = front.removeFirst();
		} else{
			x=back.removeFirst();
		}
		balance();
		return x;
	}
	
	
	T removeLast(){
		T x;
		if(!back.isEmpty()){
			x = back.removeLast();
		} else{
			x=front.removeLast();
		}
		balance();
		return x;
		
	}
	
	T removeMiddle(){
		T x ;
		if(back.size()==front.size()){
			
			if(!front.isEmpty()){
				x = front.removeLast();
			} else{
				x= back.removeLast();

			}
			
		} else{
			if(!back.isEmpty()){
				x = back.removeFirst();
			} else{
				x=front.removeFirst();
			}
		}
		
		balance();
		
		return x;
	}
	
	
private:
	DualArrayDeque<T> front;
	DualArrayDeque<T> back;
	int size(){
		return front.size() + back.size();
	}
	void balance(){
		while( !(front.size()== back.size() || front.size()+1== back.size() )){
			if(front.size()+1<back.size()){
				T x;
				x = back.removeFirst();
					front.addLast(x);
				
			} else if(front.size()>back.size() ){
				T x;
				x = front.removeLast();
				back.addFirst(x);
			}
		}
		
	}
	
};



int main() {
	int* a =new int[100 * 1000 +7];
	int n=0;
	while(true){
		cin >> a[n];
		n++;
		if(getchar()=='\n')
			break;
	}
	DualArrayDequePlus<int> aa(a,n);
	delete[] a;
	string ss;
	while(ss!="end"){
		cin >> ss;
		if(ss=="add"){
			char tmp;
			int y;
			cin >> tmp >> y;
			if(tmp=='h')
				aa.addFirst(y);
			if(tmp=='t')
				aa.addLast(y);
			if(tmp=='m')
				aa.addMiddle(y);
		}
		if(ss=="remove"){
			char tmp;
			cin >> tmp;
			if(tmp=='h')
				cout << aa.removeFirst() << endl;
			if(tmp=='t')
				cout << aa.removeLast() << endl;
			if(tmp=='m')
				cout << aa.removeMiddle() << endl;
		}
		
	}
	
	
}