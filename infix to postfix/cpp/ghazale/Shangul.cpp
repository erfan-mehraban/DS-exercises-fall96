#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

int operatorWeight(char c)
{
	int w = -1;
	switch (c)
	{
	case '+': w = 1;
		break;
	case '-': w = 1;
		break;
	case '*': w = 2;
		break;
	case '/': w = 2;
		break;
	}
	return w;
}

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	else
		return false;
}

bool isOperand(char c)
{
	if (c >= 'A' && c <= 'Z')
		return true;
	else
		return false;
}

bool isPriority(char c1, char c2)
{
	int a = operatorWeight(c1);
	int b = operatorWeight(c2);
	if (a >= b)
		return true;
	else
		return false;
}

template <typename T>
class Array {
protected:
	int n;
	T *a;
public:
	Array(int s)
	{
		n = s;
		a = new T[n];
	}
	T& operator[](int i) {
		assert(i >= 0 && i < n);
		return a[i];
	}
	Array<T>& operator=(Array &b)
	{
		if (a != NULL) delete[] a;
		a = b.a;
		b.a = NULL;
		n = b.n;
		return *this;
	}
	int size() {
		return n;
	}
};

template<typename T>
class Stack {

protected:
    Array<T> c;
	int top;
	void resize() {
		Array<T> b(max(2 * (top+1), 1));
		for (int i = 0; i<top+1; i++) {
			b[i] = c[i];
		}
		c = b;
	}
public:
	Stack() :c(10) {
		top = -1;
	}
	void push(T a) {
	    if(top+2>=c.size()) resize();
		c[++top] = a;
	}
	T topp() {
		return c[top];
	}
	int sizest(){
	    return top+1;
	}
	void pop() {
		if (top != -1)
			top--;
		if (3 * (top) <= c.size()) resize();
	}
	bool isEmpty() {
		if (top == -1)
			return true;
		else
			return false;
	}

};


int main()
{
	string s, postfix;
	cin >> s;
	Stack<char> st;
	for (int i = 0; i < s.length(); i++)
	{
		if (isOperator(s[i])) {
			while (!st.isEmpty() && st.topp() != '(' && isPriority(st.topp(), s[i])) {
				postfix += st.topp();
				st.pop();
			}
			st.push(s[i]);
		}
		else if (isOperand(s[i])) {
			postfix += s[i];
		}
		else if (s[i] == '(') {
			st.push(s[i]);
		}
		else if (s[i] == ')') {
			while (!st.isEmpty() && st.topp() != '(') {
				postfix += st.topp();
				st.pop();
			}
			st.pop();
		}
		//cout << postfix << endl;
	}
	while (!st.isEmpty()) {
		postfix += st.topp();
		st.pop();
	}
	cout << postfix << endl;
	return 0;
}