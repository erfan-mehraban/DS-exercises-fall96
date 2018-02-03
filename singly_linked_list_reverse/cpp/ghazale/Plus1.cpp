#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

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


template<typename T>
class SLList {
    T null;
    Stack<T> st;
protected:
    class Node {
    public:
        T x;
        Node *next;
        Node(T x0) {
            x = x0;
            next = NULL;
        }
        //  Node& operator=(Node b) {
        //      this->x = b->x;
        //      return *this;
        //  }
    };
    Node *head;
    Node *tail;
    int n;

public:

    SLList() {
        null = (T)NULL;
        n = 0;
        head = tail = NULL;
    }

    virtual ~SLList() {
        Node *u = head;
        while (u != NULL) {
            Node *w = u;
            u = u->next;
            delete w;
        }
    }

    int size() {
        return n;
    }

    void addLast(T x) {
        Node *u = new Node(x);
        if (n == 0) {
            head = u;
        }
        else {
            tail->next = u;
        }
        tail = u;
        n++;
    }

    void addFirst(T x) {
        Node *u = new Node(x);
        u->next = head;
        head = u;
        if (n == 0)
            tail = u;
        n++;
    }

    //T remove() {
    //    if (n == 0)	return null;
    //    T x = head->x;
    //    Node *u = head;
    //    head = head->next;
    //    delete u;
    //    if (--n == 0) tail = NULL;
    //    return x;
    //}

    void savingIndex(int a, int b) {
        Node *u = head;
        if(a==b)
            return;
        for (int i = 1; i < a; i++) {
            u = u->next;
        }
        for (int i = a; i <= b; i++) {
            st.push(u->x);
            u = u->next;
        }
    }

    void reverse(int a, int b) {
        if(a==b)
            return;
        savingIndex(a, b);
        //if (n == 0) return;
        Node *w = head;
        for (int i = 1; i < a; i++) {
            w = w->next;
        }
        for (int i = a; i <= b; i++) {
            w->x = st.pop();
            w=w->next;
        }
    }

    T removeLast() {
        Node *u = head;
        if (n == 0)
            return null;
        else if(n==1){
            T y=u->x;
            head=NULL;
            tail = NULL;
            delete u;
            n--;
            return y;
        }
        else {
            while (u->next != tail)
                u = u->next;

            tail = u;
            T y = tail->next->x;
            u=tail->next;
            tail->next = NULL;
            delete u;
            n--;
            return y;
        }
        //n--;

    }
    void print() {
        Node *u = head;
        for (int i = 0; i<size(); i++) {
            cout << u->x << " ";
            u = u->next;
        }
    }
};

int main()
{
    SLList<int> sll;
    int n;
    int a, b;
    cin >> n;
    string tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        if (tmp == "addFirst") {
            cin >> a;
            sll.addFirst(a);
        }
        else if (tmp == "addLast") {
            cin >> a;
            sll.addLast(a);
        }
        else if (tmp == "removeLast") {
            int t = sll.removeLast();
            if (t == NULL) {
                cout << "empty" << endl;
            }
            else {
                cout << t << endl;
            }
        }
        else if (tmp == "reverse") {
            cin >> a >> b;
            sll.reverse(a, b);
        }

    }
    //sll.print();
    return 0;
}