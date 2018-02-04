#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;
template <class T>
class array {
public:
    T *a;
    T length;
    array(int len) {
        length = len;
        a = new T[length];
    }

    array() {
        length = 0;
        a = new T[0];
    }

    T &operator[](int i) {
        return a[i];
    }
    array<T>& operator=(array<T> &b) {
        if (a != NULL) delete[] a;
        a = b.a;
        b.a=NULL;
        length=b.length;
        return *this;
    }
};
class arraystack {
public:
    array<char> a;
    int n;
    arraystack (){
        n=0;
    }
    int size() {
        return n;
    }
    char get(int i) {
        return a[i];
    }
    char set(int i, char x) {
        char y = a[i];
        a[i] = x;
        return y;
    }
    void add(int i, char x) {
        if (n + 1 > a.length) resize();
        for (int j = n; j > i; j--)
            a[j] = a[j - 1];
        a[i] = x;
        n++;
    }
    char remove(int i) {
        char x = a[i];
        for (int j = i; j < n - 1; j++)
            a[j] = a[j + 1];
        n--;
        if (a.length >= 3 * n) resize();
        return x;
    }
    void resize() {
        array <char> b(max(2 * n, 1));
        for (int i = 0; i < n; i++)
            b[i] = a[i];
        a = b;
    }
    void push(char x){
        if (n+1>a.length) resize();
        a[n]=x;
        n++;
    }
    char pop() {
            char x = a[n - 1];
            n--;
            return x;
    }
    char top(){
            return a[n-1];
    }
};
int precedence(char c) {
    switch (c) {
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        default:
            return 0;
    }
}
void convert(char ch , arraystack &operators) {
    if (ch >= 'A' && ch <= 'Z')
        cout << ch;
    else if (precedence(ch)) {
        while (operators.n > 0 && precedence(operators.top()) >= precedence(ch)) {
            cout<<operators.pop();
        }
        operators.push(ch);
    }
    else if (ch == '(') {
        operators.push(ch);
    }
    else if (ch == ')') {
        while (operators.n > 0 && operators.top() != '(') {
            cout<<operators.pop();
        }
        operators.pop();
    }
}
    int main() {
        arraystack operators;
        char temp;
        string line;
        getline(cin, line);
        istringstream mystring(line);
        for (int i = 0; mystring >> temp; i++)
            convert(temp,operators);
        while (operators.n > 0)
            cout<<operators.pop();
        return 0;
    }