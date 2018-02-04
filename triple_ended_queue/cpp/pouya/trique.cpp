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
template <class T>
class arraydeque{
public:
    array <T> a;
    int j=0;
    int n=0;
    T get(int i){
        return a[(j+i)% a.length];
    }
    T set(int i,T x){
        T y=a[(j+i)% a.length];
        a[(j+i)% a.length]=x;
        return y;
    }
    void add(int i,T x){
        if(n+1>a.length) resize();
        if(i<n/2) {
            j=(j==0)?a.length-1:j-1;
            for (int k=0;k<=i-1;k++)
                a[(j+k)%a.length]=a[(j+k+1)%a.length];
        }
        else {
            for (int k = n; k > i; k--)
                a[(j + k) % a.length] = a[(j + k - 1) % a.length];
        }
        a[(j+i)%a.length]=x;
        n++;
    }
    T remove(int i) {
        T x = a[(j+i)%a.length];
        if (i < n/2) {
            for (int k = i; k > 0; k--)
                a[(j+k)%a.length] = a[(j+k-1)%a.length];
            j = (j + 1) % a.length;
        }
        else {
            for (int k = i; k < n-1; k++)
                a[(j+k)%a.length] = a[(j+k+1)%a.length];
        }
        n--;
        if (3*n < a.length) resize();
        return x;
    }
    void resize(){
        array<T> b(max(1,2*n));
        for(int k =0 ; k<n; k++)
            b[k]=a[(j+k)%a.length];
        a=b;
        j=0;
    }
    void pushfirst(T x){
        if(n+1>a.length) resize();
        j=(j==0)?a.length-1:j-1;
        a[j]=x;
        n++;
    }
    void pushlast(T x){
        add(n,x);
    }
    T popfirst(){
        T x = a[j];
        j = (j + 1) % a.length;
        n--;
        if (3*n < a.length) resize();
        return x;
    }
    T poplast(){
        T x = a[(j+n-1)%a.length];
        n--;
        if (3*n < a.length) resize();
        return x;
    }
};
    template <class T>
    void balance(arraydeque<T> & back, arraydeque<T> & front){
        while(back.n!=front.n && back.n+1!=front.n)
        if(back.n>front.n){
            T temp;
            temp=back.get(back.n-1);
            back.poplast();
            front.pushfirst(temp);
        }
        else if (front.n>back.n){
            T temp;
            temp=front.get(0);
            front.popfirst();
            back.pushlast(temp);
        }
    }
int  main() {
    arraydeque <int> front,back;
    int n=0,num;
    string cmd,pos;
    string line;
    getline(cin, line);
        istringstream counting(line);
        istringstream Stream (line);
        for (int i=0 ; counting >> num ; i++) {
            n++;
        }
        for (int i=0 ; i<(n/2) ; i++) {
            Stream>>num;
            back.add(i, num);
        }
        for (int i=0 ; i<(n-(n/2)) ; i++) {
            Stream>>num;
            front.add(i, num);
        }
        while(cmd!="end") {
            getline(cin, line);
            istringstream command(line);
            command >> cmd;
            if (cmd=="add"){
                    command>>pos;
                    command>>num;
                    if(pos=="h") {
                        back.pushfirst(num);
                    }
                    else if (pos=="t"){
                        front.pushlast(num);
                    }
                    else if (pos=="m"){
                        if(back.n==front.n){
                            front.pushfirst(num);
                        }
                        else{
                            back.pushlast(num);
                        }
                    }
                }
            else if (cmd=="remove"){
                command>>pos;
                if(pos=="h") {
                    if (back.n !=0) cout << back.popfirst() << endl;
                    else cout << front.popfirst() << endl;
                }
                else if(pos=="t")
                    cout<<front.poplast()<<endl;
                else if(pos=="m"){
                    if(back.n==front.n){
                        cout<<back.poplast()<<endl;
                    }
                    else {
                        cout<<front.popfirst()<<endl;
                    }
                    }
                }
            balance(back,front);
        }
   return 0;
}