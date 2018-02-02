//This Code is not completely correct! Be careful!

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include<math.h>
#include<assert.h>

using namespace std;

template<typename T>
class Array {
protected:
    T* a;
public:
    int length;
    Array(int l) {
        length = l;
        a = new T[length];
    }
    T& operator[](int i) {
        assert(i>=0 && i<length);
        return a[i];
    }
    Array<T>& operator=(Array<T> &b) {
        if (a != NULL) delete[] a;
        a = b.a;
        b.a = NULL;
        length = b.length;
        return *this;
    }
    int size(){
        return length;
    }
};
template <class T>
class DualArrayDeque;

template<typename T>
class Stack {
    friend class DualArrayDeque<T>;
private:
    Array<T> a;
    int n;
    void resize() {
        Array<T> b(max(2 * n, 1));
        for (int i = 0; i<n; i++) {
            b[i] = a[i];
        }
        a = b;
    }
public:
    Stack() :a(1){
        n=0;
    }
    T pop() {
        T x = a[n-1];
        n--;
        if(n <= 3*a.size()) resize();
        return x;

    }
    void push(int x) {
        if(n+1 > a.size()) resize();
        a[n] = x;
        n++;
    }
    T topp() {
        T x = a[n-1];
        n--;
        if(n <= 3*a.size()) resize();
        return x;
    }
    int size(){
        return n;
    }
    T get(int i) {
        return a[i];
    }
    T set(int i, T x) {
        T b = a[i];
        a[i] = x;
        return b;
    }
};

template <typename T>
class DualArrayDeque {
protected:
    Stack<T> front, back;
public:

    int size() {
        return front.size() + back.size();
    }
    T get(int i) {
        if (i < front.size())
            return front.get(front.size() - i - 1);
        else
            return back.get(i - front.size());
    }
    T set(int i, int x) {
        if (i < front.size())
            front.set(front.size() - i - 1, x);
        else
            back.set(i - front.size(), x);
    }
    T removeFirst() {
        T x;
        if(front.size()!=0)
        x=front.pop();
        else
            x=back.pop();
        balance();
        return x;
    }
    T removeLast() {
        T x;
        if(back.size()!=0)
            x=back.pop();
        else
            x=front.pop();
        balance();
        return x;
    }
    void addFirst(T x) {
        front.push(x);
        balance();
    }
    void addLast(T x) {
        back.push(x);
        balance();
    }
    void balance() {
        if (3 * front.size() < back.size() || 3 * back.size() < front.size()) {
            int n = front.size() + back.size();
            int nf = n / 2;
            Array<T> af(max(2 * nf, 1));
            for (int i = 0; i < nf; i++) {
                af[nf - i - 1] = get(i);
            }
            int nb = n - nf;
            Array<T> ab(max(2 * nb, 1));
            for (int i = 0; i < nb; i++) {
                ab[i] = get(nf + i);
            }
            front.a = af;
            front.n = nf;
            back.a = ab;
            back.n = nb;
        }
    }
};

template <typename T>
class DS {
protected:
    int n;
public:
    DualArrayDeque<T> a, b;
    DS() {
        n = a.size() + b.size();
    }
    int size() {
        return a.size() + b.size();
    }
    void addT(T x) {

        b.addLast(x);

        balancePlus();
    }
    void addH(T x) {
        a.addFirst(x);
        balancePlus();
    }
    void addM(T x) {
        if (a.size() > b.size()) {
            b.addFirst(x);
        }
        else {
            a.addLast(x);
        }
        balancePlus();
    }
    T removeH() {
        T x;
        if(a.size()!=0)
            x= a.removeFirst();
        else
            x= b.removeLast();
        balancePlus();
        return x;
    }
    T removeT() {
        T x;
        if(b.size()!=0)
            x= b.removeLast();
        else
            x= a.removeFirst();
        balancePlus();
        return x;
    }
    T removeM() {
        T x;
        if (a.size()==b.size()){
            if(a.size()!=0)
                x= a.removeLast();
            else
                x= b.removeFirst();
        }else {
            if(b.size()!=0)
                x= b.removeFirst();
            else
                x= a.removeLast();
        }
        balancePlus();
        return x;
    }
    void balancePlus() {

            if (a.size() > b.size()) {
                b.addFirst(a.removeLast());
            }
             if(b.size()>a.size()+1){
                a.addLast(b.removeFirst());
            }
    }

};



int main()
{
    string s, s2="", tmp = "",ans;
    char ch;
    int num,a[100000],n=0;
    DS<int> obj;
    while(true){
        cin >> a[n];
        n++;
        if(getchar()=='\n')
            break;
    }
    for (int i = 0; i < n; i++) {
        obj.addT(a[i]);
    }
    while (tmp != "end") {
        cin >> tmp;
        if (tmp == "remove") {
            cin >> ch;
            if (ch == 'h') {
//                ans += obj.removeH();
                cout << obj.removeH() << endl;
            }
            if (ch == 't') {
//                ans += obj.removeT();
                cout << obj.removeT() << endl;

            }
            if (ch == 'm') {
//                ans += obj.removeM();
                cout << obj.removeM() << endl;

            }

        }
        else if (tmp == "add") {
            cin >> ch;
            if (ch == 't') {
                cin >> num;
                obj.addT(num);
            }
            if (ch == 'h') {
                cin >> num;
                obj.addH(num);
            }
            if (ch == 'm') {
                cin >> num;
                obj.addM(num);
            }
        }
    }
    for (int i = 0; i < s.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

