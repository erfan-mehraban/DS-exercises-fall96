#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;
template <class T>
class array {
public:
    T size;
    T *a;

    array() {
        size = 0;
        a = new T[0];
    }

    array(int s) {
        size = s;
        a = new T[size];
    }

    T &operator[](int i) {
        return a[i];
    }
    array<T>& operator=(array<T> &b) {
        if (a != NULL) delete[] a;
        size=b.size;
        a = b.a;
        return *this;
    }
};

template <class T>
class deque{
public:
    array <T> a;
    int size;
    int head;
    deque(){
        size=0;
        head=0;
    }

    T get(int i){
        return a[(head+i)% a.size];
    }

    T set(int i,T x){
        T temp=a[(head+i)% a.size];
        a[(head+i)% a.size]=x;
        return temp;
    }
    
    T print(){
        for (int i = 0; i < size ; ++i)
            cout << get(i) << " ";
        cout << endl;
    }
    void resize(){
        array<T> temp(max(1,2*size));

        for(int c =0 ; c < size ; c++)
            temp[c] = a[ (head+c) % a.size ];
        
        head=0;
        a=temp;
    }

    void append(int i,T x){
        if( size+1 > a.size )
            resize();

        if( size/2 > i ) {
            head = (head==0)? a.size-1 : head-1;
            for (int t=0; t<=i-1; t++)
                a[ (head+t) % a.size ] = a[ (head+t+1) % a.size ];
        }
        else
            for (int t = size; t > i; t--)
                a[ (head + t) % a.size ] = a[ (head + t - 1) % a.size ];

        a[ (head+i) % a.size] = x;
        size++;
    }

    T remove(int i) {
        T x = a[ (head+i) % a.size ];

        if ( size/2 > i ) {
            for (int k = i; k > 0; k--)
                a[ (head+k) % a.size ] = a[ (head + k - 1) % a.size ];
            head = ( head + 1 ) % a.size;
        } else
            for (int k = i; k < size-1; k++)
                a[ (head+k) % a.size ] = a[ (head + k + 1) % a.size ];

        size--;
        if (a.size > 3*size)
            resize();
        return x;
    }


    void push(T x){
        append(size,x);
    }

    T pop(){
        T temp = a[(head+size-1)%a.size];
        size--;
        if (3*size < a.size) resize();
        return temp;
    }

    void pushLeft(T x){
        if( (size+1) > a.size )
            resize();

        head = (head==0)? a.size-1 : head-1;
        size++;
        a[head] = x;
    }

    T popLeft(){
        T temp = a[head];
        head = (head + 1) % a.size;
        size--;

        if (3*size < a.size)
                resize();
        return temp;
    }
};

template <class T>
void shift(deque<T> & f, deque<T> & s){
    if(f.size > s.size) // shift right
        s.pushLeft(f.pop());

    else if (f.size +1 < s.size) // shift left
        f.push(s.popLeft());
}

int  main() {
    deque <int> second,first;

    ////////
    int  x, counter = 0;
    string line;
    getline(cin, line);
    istringstream c (line);
    istringstream in (line);
    for (int i=0 ; c >> x ; i++)
        counter++;

    for (int i=0 ; i<(counter/2) ; i++) {
        in>>x;
        first.append(i, x);
    }

    for (int i=0 ; i<( counter - (counter/2) ) ; i++) {
        in>>x;
        second.append(i, x);
    }
    ///////

    // cout << "***" << endl;
    // first.print(); second.print();
    // cout << "***" << endl;

    string cmnd="" , place;

    while( cmnd != "end" ) {
        ///
        getline(cin, line);
        istringstream command(line);
        command >> cmnd;
        ///

        if ( cmnd == "add" ){
                command >> place;
                command >> x;

                if( place == "h" )
                    first.pushLeft(x);

                else if ( place == "t" )
                    second.push(x);

                else if ( place == "m" )
                    if( second.size == first.size )
                        second.pushLeft(x);
                    else
                        first.push(x);
        }

        else if ( cmnd == "remove" ){
            command >> place;

            if( place == "h" )
                if (first.size != 0)
                    cout << first.popLeft() << endl;
                else
                    cout << second.pop() << endl;
            
            else if( place == "t" )
                cout << second.pop() << endl;

            else if( place == "m" )
                if( first.size == second.size )
                    cout << first.pop() << endl;
                else 
                    cout << second.popLeft() <<endl;
        }

        shift(first, second);
        // cout << "***" << endl;
        // first.print(); second.print();
        // cout << "***" << endl;
    }
}