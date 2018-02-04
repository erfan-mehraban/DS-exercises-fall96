	#include <iostream>
#include <string.h>
#include <cstdio>
#include <sstream>
using namespace std;
int max(int a, int b) {
    return ((a)>(b) ? (a) : (b));
}
class position{
public:
    int i,j;
    position(int x , int y): i(x), j(y){}
      position(){
        i=-1000;
        j=-1000;
    }
};
template<class T>
class array {
public:
    T *a;
    int length;
    array(int len);
    array(int len, T init);
    virtual ~array();

    array<T>& operator=(array<T> &b) {
//        if (a != NULL) delete[] a;
        a = b.a;
        b.a = NULL;
        length = b.length;
        return *this;
    }

    T& operator[](int i) {
//        assert(i >= 0 && i < length);
        return a[i];
    }
};

template<class T>
array<T>::array(int len) {
    length = len;
    a = new T[length];
}

template<class T>
array<T>::array(int len, T init) {
    length = len;
    a = new T[length];
    for (int i = 0; i < length; i++)
        a[i] = init;
}

template<class T>
array<T>::~array() {
    if (a != NULL) delete[] a;
}


template<class T>
class ArrayQueue {
protected:
    array<T> a;
    int j;
    int n;
    void resize();
public:
    ArrayQueue();
    virtual ~ArrayQueue();
    virtual bool add(T x);
    virtual void add(int i, T x);
    virtual T remove();
    int size();
    T get(int i);
};
template<class T> inline
T ArrayQueue<T>::get(int i) {
    return a[(j + i) % a.length];
}
template<class T>
ArrayQueue<T>::ArrayQueue() : a(1) {
    n = 0;
    j = 0;
}

template<class T>
ArrayQueue<T>::~ArrayQueue() {
    //delete a;
}

template<class T>
void ArrayQueue<T>::resize() {
    array<T> b(max(1, 2*n));
    for (int k = 0; k < n; k++)
        b[k] = a[(j+k)%a.length];
    a = b;
    j = 0;
}

template<class T>
bool ArrayQueue<T>::add(T x) {
    if (n + 1 > a.length) resize();
    a[(j+n) % a.length] = x;
    n++;
    return true;
}
template<class T>
void ArrayQueue<T>::add(int i, T x) {
    if (n + 1 > a.length)	resize();
    if (i < n/2) { // shift a[0],..,a[i-1] left one position
        j = (j == 0) ? a.length - 1 : j - 1;
        for (int k = 0; k <= i-1; k++)
            a[(j+k)%a.length] = a[(j+k+1)%a.length];
    } else { // shift a[i],..,a[n-1] right one position
        for (int k = n; k > i; k--)
            a[(j+k)%a.length] = a[(j+k-1)%a.length];
    }
    a[(j+i)%a.length] = x;
    n++;
}

template<class T>
T ArrayQueue<T>::remove() {
    T x = a[j];
    j = (j + 1) % a.length;
    n--;
    if (a.length >= 3*n) resize();
    return x;
}

template<class T>
int ArrayQueue<T>::size() {
    return n;
}

template<class T>
class ArrayStack {
public:
    array<T> a;
    int n;
    virtual void resize();
    ArrayStack();
    virtual ~ArrayStack();
    int size();
    T get(int i);
    T set(int i, T x);
    virtual void add(int i, T x);
    virtual void add(T x) { add(size(), x); }
    virtual T remove(int i);
};

template<class T> inline
int ArrayStack<T>::size() {
    return n;
}

template<class T> inline
T ArrayStack<T>::get(int i) {
    return a[i];
}

template<class T> inline
T ArrayStack<T>::set(int i, T x) {
    T y = a[i];
    a[i] = x;
    return y;
}

template <class T>
ArrayStack<T>::ArrayStack() : a(1) {
    n = 0;
}

template<class T>
ArrayStack<T>::~ArrayStack() {
}

template<class T>
void ArrayStack<T>::resize() {
    array<T> b(max(2 * n, 1));
    for (int i = 0; i < n; i++)
        b[i] = a[i];
    a = b;
}

template<class T>
void ArrayStack<T>::add(int i, T x) {
    if (n + 1 > a.length) resize();
    for (int j = n; j > i; j--)
        a[j] = a[j - 1];
    a[i] = x;
    n++;
}

template<class T>
T ArrayStack<T>::remove(int i) {
    T x = a[i];
    for (int j = i; j < n - 1; j++)
        a[j] = a[j + 1];
    n--;
    if (a.length >= 3 * n) resize();
    return x;
}
class Maze{
    char * block[];
    char * status[];
    array<position> path;

};
ArrayQueue<position> solveMaze(bool **maze , int row , int column , position end){
    bool **stat = new bool *[row];
    position **tail = new position *[row];
    for (int i=0 ; i<row ; i++){
        tail[i] = new position[column];
        stat[i]=new bool[column];
        for(int j=0 ; j<column ; j++)
            stat[i][j]=0;
    }
    int i;
    int j;
    ArrayStack<position> searchstack;
    position start(0,0);
    searchstack.add(start);
    stat[0][0]=1;
    bool Status = false;
    while (searchstack.size()>0){
        position block = searchstack.remove(searchstack.size()-1);
        i=block.i;
        j=block.j;
        if (block.i == end.i && block.j==end.j){
            Status = true ;
            break;
        }
        if(i-1>=0 && i-1<row && j-1>=0 && j-1<column && maze[i-1][j-1]==0 && stat[i-1][j-1]==0)
            {
                stat[i-1][j-1]=1;
                searchstack.add(position(i-1,j-1));
                tail[i-1][j-1]=block;
            }
        if(i-1>=0 && i-1<row && j>=0 && j<column && maze[i-1][j]==0 && stat[i-1][j]==0)
        {
            stat[i-1][j]=1;
            searchstack.add(position(i-1,j));
            tail[i-1][j]=block;
        }
        if(i-1>=0 && i-1<row && j+1>=0 && j+1<column && maze[i-1][j+1]==0 && stat[i-1][j+1]==0)
        {
            stat[i-1][j+1]=1;
            searchstack.add(position(i-1,j+1));
            tail[i-1][j+1]=block;
        }
        if(i>=0 && i<row && j-1>=0 && j-1<column && maze[i][j-1]==0 && stat[i][j-1]==0)
        {
            stat[i][j-1]=1;
            searchstack.add(position(i,j-1));
            tail[i][j-1]=block;
        }
        if(i>=0 && i<row && j+1>=0 && j+1<column && maze[i][j+1]==0 && stat[i][j+1]==0)
        {
            stat[i][j+1]=1;
            searchstack.add(position(i,j+1));
            tail[i][j+1]=block;
        }
        if(i+1>=0 && i+1<row && j-1>=0 && j-1<column && maze[i+1][j-1]==0 && stat[i+1][j-1]==0)
        {
            stat[i+1][j-1]=1;
            searchstack.add(position(i+1,j-1));
            tail[i+1][j-1]=block;
        }
        if(i+1>=0 && i+1<row && j>=0 && j<column && maze[i+1][j]==0 && stat[i+1][j]==0)
        {
            stat[i+1][j]=1;
            searchstack.add(position(i+1,j));
            tail[i+1][j]=block;
        }
        if(i+1>=0 && i+1<row && j+1>=0 && j+1<column && maze[i+1][j+1]==0 && stat[i+1][j+1]==0)
        {
            stat[i+1][j+1]=1;
            searchstack.add(position(i+1,j+1));
            tail[i+1][j+1]=block;
        }
    }
    ArrayQueue<position> FinalTail;
    if (!Status){
        return FinalTail;
    }
    position temp(end.i,end.j);
    while (temp.i != -1000 && temp.j != -1000 ) {
        int i,j;
        FinalTail.add(0,temp);
        i=temp.i;
        j=temp.j;
        temp.i = (tail[i][j]).i;
        temp.j = (tail[i][j]).j;
    }
    return FinalTail;
}
int main() {
    int row,column;
    char x;
    cin>>row>>column;
    string line;
    getline(cin, line);
    bool **maze = new bool * [row];
    for(int i=0 ; i<row ; i++){
        getline(cin, line);
        istringstream row(line);
        maze[i]=new bool[column];
        for(int j=0 ; j<column ; j++){
            row>>x;
            maze[i][j]=(x=='0'?0:1);
        }
    }
    ArrayQueue<position> FinalTail = solveMaze(maze, row, column,position(row - 1, column - 1));
    if (FinalTail.size() == 0) {
        cout<<"That"<<"'"<<"s a dead end!"<<endl;
    }
    else {
        int i,j;
        cout<<FinalTail.size()<<endl;
        for (int count = 0; count < FinalTail.size(); count++) {
            i = FinalTail.get(count).i + 1;
            j = FinalTail.get(count).j + 1;
            cout << i << " " << j << endl;
        }
    }
//    for(int i=0 ; i<row ; i++){
//        for(int j=0 ; j<column ; j++){
//            cout<<maze[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    return 0;
}
