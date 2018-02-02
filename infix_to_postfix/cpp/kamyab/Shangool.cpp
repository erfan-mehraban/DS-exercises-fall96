#include <iostream>
#include <assert.h>
#include <string>


using namespace std;



template <typename T>
class Array{
public:
	Array(int len = 1){
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

template <typename T>
class Stack{
	
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
	T top(){
		return a[n-1];
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
	bool isEmpty(){
		return size()==0;
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
bool prio(char x, char y) {
	if( (x=='+' || x=='-') && (y=='*' || y=='/'))
		return true;
	if( (x=='+' || x=='-') && (y=='+' || y=='-'))
		return true;
	if( (x=='*' || x=='/') && (y=='*' || y=='/'))
		return true;
	return false;
}
int main() {
	Stack<char> p;
	string s;
	string ans="";
	cin >> s;

	for (int i=0;i<s.size();i++) {
	   if(s[i]>='A' && s[i]<='Z'){
			ans+=s[i];
		} else if(s[i]==')'){
			char tmp= '\0';
			
			while(!p.isEmpty() && p.top() != '('){
				tmp = p.remove();
				ans+=tmp;
			}
			p.remove();
		} else if(s[i]=='('){
			p.add(s[i]);
		}
		else{
			while(!p.isEmpty() && prio(s[i], p.top()) ){
				ans+=p.remove();
			}
			p.add(s[i]);
		}

	}
	char tmp='\0';

	while(!p.isEmpty()){
		tmp = p.remove();
		ans+=tmp;
	}
	cout << ans;
	return 0;
}

