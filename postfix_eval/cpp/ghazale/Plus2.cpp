#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include<math.h>

using namespace std;
int con(string str) {
    int ans = 0;
    for (int i = 0; i<str.length(); i++)
    {
        ans = (str[i] - '0') + ans * 10;

    }
    return ans;
}

int operatorWeight(char c)
{
    int w = -1;
    switch (c)
    {
        case '+': w = 1;
            break;
        case '-': w = 2;
            break;
        case '*': w = 3;
            break;
        case '/': w = 4;
            break;
        case '^': w = 5;
            break;
        default : w = 0;
    }
    return w;
}

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c=='^')
        return true;
    else
        return false;
}

bool isParenthesses(char c) {
    if (c == '(' || c == ')')
        return true;
    else
        return false;
}

bool isSpace(char c) {
    if (c == ' ') {
        return true;
    }
    else return false;
}

bool isOperand(char c)
{
    if (!isOperator(c) && c!='(' && c!=')' && c!=' ' && c!='=')
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
        Array<T> b(max(2 * (top + 1), 1));
        for (int i = 0; i<top + 1; i++) {
            b[i] = c[i];
        }
        c = b;
    }
public:
    Stack() :c(10) {
        top = -1;
    }
    void push(T a) {
        if (top + 2 >= c.size()) resize();
        c[++top] = a;
    }
    T topp() {
        return c[top];
    }
    int sizest() {
        return top + 1;
    }
    T pop() {
        T y = c[top];
        if (top != -1)
            top--;
        if (3 * (top+1) <= c.size()) resize();
        return y;
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
    int answer = 0;
    string s, postfix, tmp = "";
    getline(cin, s);
    //s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
    //cout << s << endl;
    Stack<char> st;
    Stack<int> st2;
    int j = 0;
    string s2="";
    for (int i = 0; i < s.length(); i++) {
        s2 += s[i];
        if (isOperand(s[i])) {
            if (i<s.length() - 1 && s[i + 1] == '(')
                s2 += " * ";
        }
        if (s[i] == ')') {
            if (i<s.length() - 1 && isOperand(s[i + 1]))
                s2 += " * ";
            if (i<s.length()-1 && s[i + 1] == '(')
                s2 += " * ";
        }
    }
    s = s2;
    for (int i = 0; i < s.length(); i++)
    {
        //while (isOperand(s[i])) {
        //	tmp += s[i];
        //	i++;
        //}
        if (isOperator(s[i])) {
            while (!st.isEmpty() && st.topp() != '(' && isPriority(st.topp(), s[i])) {
                postfix += st.topp();
                st.pop();
            }
            st.push(s[i]);
        }
        else if (isOperand(s[i])) {
            //if (s[i + 1] == '(') {
            //	st.push('*');
            //}
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
            //if (s[i + 1] == '(' || isOperand(s[i+1]) ) {
            //	st.push('*');
            //}
        }
        if (isSpace(s[i])) {
            postfix += s[i];
        }
        //cout << postfix << endl;
    }
    while (!st.isEmpty()) {
        postfix += st.topp();
        st.pop();
    }
    postfix += "=";

    for (int i = 0; i < postfix.length(); i++) {
        if (isOperand(postfix[i])) {
            tmp = postfix[i];
            while (isOperand(postfix[++i])) {
                tmp += postfix[i];
            }
            i--;
            j = con(tmp);
            tmp = "";
            st2.push(j);
        }else if (isSpace(postfix[i])) {
            continue;
        }else if (isOperator(postfix[i])) {
            if (postfix[i] == '+') {
                int x = st2.pop();
                int y = st2.pop();
                st2.push(y + x);
            }
            if (postfix[i] == '-') {
                int x = st2.pop();
                int y = st2.pop();
                st2.push(y - x);
            }
            if (postfix[i] == '/') {
                int x = st2.pop();
                int y = st2.pop();
                st2.push(y / x);
            }
            if (postfix[i] == '*') {
                int x = st2.pop();
                int y = st2.pop();
                st2.push(y * x);
            }
            if (postfix[i] == '^') {
                int x = st2.pop();
                int y = st2.pop();
                st2.push(pow(y,x));
            }
        }
        if (postfix[i] == '=') {
            cout << st2.pop();
        }
    }
    //cout << postfix << endl;
    return 0;
}