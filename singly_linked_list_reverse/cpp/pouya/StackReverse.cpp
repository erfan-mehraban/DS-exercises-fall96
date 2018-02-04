#include <iostream>
#include <string>
using namespace std ;
template<class T>
class SLList {
public:
    T null;
    class Node {
    public:
        T x;
        Node *next;
        Node(T x0) {
            x = x0;
            next = NULL;
        }
    };
    Node *head;
    Node *tail;
    int n;

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

    bool add(T x) {
        Node *u = new Node(x);
        if (n == 0) {
            head = u;
        } else {
            tail->next = u;
        }
        tail = u;
        n++;
        return true;
    }

    T push(T x) {
        Node *u = new Node(x);
        u->next = head;
        head = u;
        if (n == 0)
            tail = u;
        n++;
        return x;
    }

    bool removeLast() {
        if (head==NULL){
            cout<<"empty"<<endl;
            return false;
        }
        if (n==1){
            cout<<head->x<<endl;
            head=NULL;
            tail=NULL;
        }
        else {
            Node *newtail = head ;
            Node *u = head->next ;
            while (u!=tail) {
                u = u->next;
                newtail=newtail->next;
            }
            cout<<u->x<<endl;
            newtail->next=NULL;
            tail=newtail;
        }
//        delete u;  // i commented this line and all of a sudden all the runtime errors where gone !!!!   (WHY?????)
        n--;
        return true;
    }
    Node * FindNode(int i){
        Node * traverse = head ;
        for (int j=1 ; j<i ; j++){
            traverse = traverse->next;
        }
        return traverse;
    }
    Node * get(int i){
        return FindNode(i);
    }
    bool Reverse(int i , int j){
        if (n==0 || n==1) return false;
        if(i==1 && j==n) {
            Node *prev = NULL;
            Node *current = head;
            Node *next;
            while (current != NULL) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            tail = head;
            head = prev;
        }
        else if (i==1){
            Node *I=head;
            Node *prev = NULL;
            Node *current = head;
            Node *next;
            for (int k=1 ; k<j+1 ; k++) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            I->next=current;
            head=prev;
        }
        else if (j==n) {
            Node *searchnode =head;
            for (int k=1 ; k<i-1 ; k++)
                searchnode=searchnode->next;
            Node *beforeI = searchnode;
            Node *prev = NULL;
            Node *current = searchnode->next;
            Node *next;
            for (int k = i; k < j + 1; k++) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            tail=beforeI->next;
            beforeI->next=prev;
        }
        else {
            Node *searchnode =head;
            for (int k=1 ; k<i-1 ; k++)
                searchnode=searchnode->next;
            Node *beforeI = searchnode;
            Node *prev = NULL;
            Node *current = searchnode->next;
            Node *next;
            for (int k = i; k < j + 1; k++) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            beforeI->next->next=current;
            beforeI->next=prev;
        }
        return true;
    }
};
int main() {
    SLList<int> S;
    int i,j,counter ;
    string cmd;
    int value;
    cin >>counter;
    for (int c=0 ; c<counter ; c++){
        cin>>cmd;
        if (cmd == "addFirst"){
            cin>>value;
            S.push(value);
        }
        if (cmd == "addLast"){
            cin>>value;
            S.add(value);
        }
        if (cmd == "removeLast"){
            S.removeLast();
        }
        if (cmd == "reverse"){
            cin>>i>>j;
            S.Reverse(i,j);
        }
    }
    return 0;
}