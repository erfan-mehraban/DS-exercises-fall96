#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
using namespace std;
template <class T>
class array {
public:
    T *a;
    int length;
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
//        if (a != NULL) delete[] a;
        a = b.a;
        b.a=NULL;
        length=b.length;
        return *this;
    }
};

template<class T>
class arraystack {
public:
    array<T> a;
    int n;
    arraystack (){
        n=0;
    }
    int size() {
        return n;
    }
    T get(int i) {
        return a[i];
    }
    T set(int i, T x) {
        T y = a[i];
        a[i] = x;
        return y;
    }
    void add(int i, T x) {
        if (n + 1 > a.length) resize();
        for (int j = n; j > i; j--)
            a[j] = a[j - 1];
        a[i] = x;
        n++;
    }
    T remove(int i) {
        T x = a[i];
        for (int j = i; j < n - 1; j++)
            a[j] = a[j + 1];
        n--;
        if (a.length >= 3 * n) resize();
        return x;
    }
    void resize() {
        array <T> b(max(2 * n, 1));
        for (int i = 0; i < n; i++)
            b[i] = a[i];
        a = b;
    }
    void push(T x){
        if (n+1>a.length) resize();
        a[n]=x;
        n++;
    }
    T pop() {
        if (n > 0) {
            T x = a[n - 1];
            n--;
            if (a.length >= 3 * n) resize();
            return x;
        }
        else{
            return 0;}
    }
    T top(){
        if(n>0)
            return a[n-1];
        else
            return 0;
    }
};
int precedence(char c) {
    switch (c) {
        case '^':
            return 4;
            break;
        case '/':
            return 3;
            break;
        case '*':
            return 2;
            break;
        case '-':
            return 1;
            break;
        case '+':
            return 1;
            break;
        default:
            return 0;
    }
}
void convert(arraystack<char>& infix,arraystack<string>& postfix) {
    arraystack<char> operators;
    string temp;
    for (int i = 0; i < infix.n; i++) {
        if (infix.a[i] >= '0' && infix.a[i] <= '9') {
            int operand=0;
            while (i < infix.n && infix.a[i] >= '0' && infix.a[i] <= '9'){
                operand = (operand*10) + (infix.a[i] - '0');
                i++;
            }
            i--;
                stringstream stream ;
                stream<<operand ;
                stream>>temp;
                postfix.push(temp);
        } else if (precedence(infix.a[i])) {
            while (operators.n > 0 && precedence(operators.top()) >= precedence(infix.a[i])) {
                string temp;
                char op;
                if(operators.n>0)
                    op=operators.pop();
                stringstream stream ;
                stream<< op ;
                stream>>temp;
                postfix.push(temp);
            }
            operators.push(infix.a[i]);
        }
        else if (infix.a[i] == '(')
        {
            if(infix.a[i-1] >= '0' && infix.a[i-1] <= '9')
                operators.push('*');
            operators.push(infix.a[i]);
        }
        else if (infix.a[i]==')'){
            while(operators.n>0   && operators.top()!='(' ){
                char op;
                string temp;
                if(operators.n>0)
                    op=operators.pop();
                stringstream stream ;
                stream << op ;
                stream>>temp;
                postfix.push(temp);
            }
            if(operators.n>0)
                operators.pop();
            if(infix.a[i+1] >= '0' && infix.a[i+1] <= '9')
                operators.push('*');
            if(infix.a[i+1] == '(' )
                operators.push('*');
        }
    }
    while(operators.n>0){
        char op;
        if(operators.n>0)
            op=operators.pop();
        stringstream stream ;
        stream << op ;
        stream>>temp;
        postfix.push(temp);
    }

}

int evaluatePostfix(arraystack<string> postfix) {
    arraystack<int> R ;
    for(int i=0; i<postfix.size(); i++){
        if (postfix.a[i]=="+" || postfix.a[i]=="-" || postfix.a[i]=="*" || postfix.a[i]=="/" || postfix.a[i]=="^"){
            int operand2 = R.top(); R.pop();
            int operand1 = R.top(); R.pop();
            int result ;
            if(postfix.a[i]=="+")
                result=operand1+operand2;
            if(postfix.a[i]=="-")
                result=operand1-operand2;
            if(postfix.a[i]=="*")
                result=operand1*operand2;
            if(postfix.a[i]=="/")
                result=operand1/operand2;
            if(postfix.a[i]=="^")
                result= (int) pow((double)operand1, (double)operand2);

            R.push(result);
        }
        else{
            int operand;
            stringstream stream;
            stream<<postfix.a[i];
            stream >> operand;
            R.push(operand);
        }
    }
    return R.top();
}

int main(){
    arraystack <char> infix;
    arraystack<string> postfix;
    char temp;
    string line;
    getline(cin, line);
    istringstream mystring(line);
    for(int i=0 ; mystring >> temp ; i++){
        infix.push(temp);
    }
    convert(infix,postfix);
//    for (int j=0 ; j<postfix.n ; j++)
//        cout<<postfix.a[j]<<" ";
    int result=0;
    result=evaluatePostfix(postfix);
    cout <<result;
    return 0;
}
