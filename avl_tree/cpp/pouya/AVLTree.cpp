#include <iostream>
using namespace std;
int max(int a, int b) {
    return ( a>b ? a : b );
}
template<class T> inline
int compare(T &x, T &y) {
    if (x < y) return -1;
    if (y < x) return 1;
    return 0;
}
void printdouble(double input){
    if ((int)input == input) {
        cout << input << ".0";
    }
    else {
        cout << input;
    }
    cout<<endl;
}

template <class T>
class Node {
public:
    T x;
    int height;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    Node() {
        left = right = parent = NULL;
        height=1;
    }
};
template <class T>
class AVLTree {
public:
    int n;
    T null;
    virtual bool remove(T x);
    Node<T>* removeNode(Node<T>* root, T key);
    Node<T> *leftRotate(Node<T> *u);
    Node<T> *rightRotate(Node<T> *u);
    Node<T> *balance(Node<T> *u);
    int height(Node<T> *node);
    int balanceStat(Node<T> *node);
    virtual bool add(T x);
    Node<T>* addNode(Node<T>* node, T x);
    bool findEQ(T x);
    Node<T> *r;    // root node
    Node<T> *nil;  // null-like node
    virtual T find(T x);
    virtual ~AVLTree();
    AVLTree();
};
template <class T>
AVLTree<T>::AVLTree() {
    nil=NULL;
    r=nil;
    n=0;
}
template <class T>
AVLTree<T>::~AVLTree() {}

template <class T>
Node<T>* AVLTree<T>::addNode(Node<T>* u, T x) {
    if (u == NULL) {
//        Node<T> * temp = new Node<T>;
//        temp->x=x;
        u = new Node<T>();
        u->x=x;
        return (u);
    }
    if (x < u->x)
        u->left  = addNode(u->left, x);
    else if (x > u->x)
        u->right = addNode(u->right, x);
    else {
        return u;
    }
    u->height = 1 + max( height(u->left), height(u->right) );
    u = balance(u);
    return u;
}
template <class T>
int AVLTree<T>::height(Node<T> *node) {
    return node==NULL?0:node->height;
}
template <class T>
int AVLTree<T>::balanceStat(Node<T> *u) {
    return u==NULL?0:( height(u->left) - height(u->right) );
}
template <class T>
Node<T> *AVLTree<T>::balance(Node<T> *u) {
    int Stat = balanceStat(u);
    if (Stat<-1) {
        cout << "balancing ";
        printdouble(u->x);
        if (balanceStat(u->right) > 0) {
            u->right= leftRotate(u->right);
            u = leftRotate(u);
        }
        else {
            u = leftRotate(u);
        }
    }
    else if (Stat>1) {
        cout << "balancing ";
        printdouble(u->x);
        if (balanceStat(u->left) >= 0) {
            u = rightRotate(u);
        }
        else {
            u->left= leftRotate(u->left);
            u = rightRotate(u);
        }
    }
    return u;
}
template <class T>
bool AVLTree<T>::findEQ(T x) {
    Node<T> *w = r;
    while (w != nil) {
        int comp = compare(x, w->x);
        if (comp < 0) {
            w = w->left;
        } else if (comp > 0) {
            w = w->right;
        } else {
            return true;
        }
    }
    return false;
}
template<class T>
bool AVLTree<T>::add(T x) {
    if(findEQ(x)) {
        cout << "already in there" << endl;
        return false;
    }
    cout<<"added"<<endl;
    r=addNode(r,x);
    return true;
}

template <class T>
Node<T> * AVLTree<T>::removeNode( Node<T>* u, T x)
{
//    if (r->x==x){
//        r =NULL;
//        return r;
//    }
    if (u == NULL)
        return u;
    if ( x < u->x )
        u->left = removeNode(u->left, x);
    else if( x > u->x )
        u->right = removeNode(u->right, x);
    else
    {
        if( (u->left == NULL) || (u->right == NULL) ) {
            Node<T> *temp = u->left;
            if (temp == NULL) {
                temp = u->right;
            }
            if (temp == NULL) {
                delete u;
                u = NULL;
            } else {
                *u = *temp;
                delete temp;
            }
        }
        else
        {
            Node<T> *w = u->left;
            while (w->right != NULL)
                w = w->right;
            u->x = w->x;
            u->left = removeNode(u->left, w->x);
        }
    }
    if (u == NULL)
        return u;
    u->height = 1 + max( height(u->left), height(u->right) );
    u = balance(u);
    return u;
}

template <class T>
bool AVLTree<T>::remove(T x) {
    if ( findEQ(x) ) {
        cout << "removed" << endl;
        r= removeNode(r,x);
        return true;
    } else {
        cout << "does not exist" << endl;
        return false;
    }
}

template< class T>
T AVLTree<T>::find(T x) {
    Node<T> *w = r, *z = nil;
    while (w != nil) {
        int comp = compare(x, w->x);
        if (comp < 0) {
            z = w;
            w = w->left;
        } else if (comp > 0) {
            w = w->right;
        } else {
            printdouble(w->x);
            return w->x;
        }
    }
    if(z==nil)
        cout<<"not found"<<endl;
    else
        printdouble(z->x);
    return z == nil ? null : z->x;
}

template <class T>
Node<T> * AVLTree<T>::leftRotate(Node<T> *u) {
    Node<T> *w = u->right;
    u->right= w->left;
    w->left= u;
    u->height = max( height(u->left), height(u->right) )+1;
    w->height = max( height(w->left), height(w->right) )+1;
    return w;
}

template <class T>
Node<T> *AVLTree<T>::rightRotate(Node<T> *u) {
    Node<T> *w = u->left;
    u->left= w->right;
    w->right= u;
    u->height = max( height(u->left), height(u->right) )+1;
    w->height = max( height(w->left), height(w->right) )+1;
    return w;
}

int main() {
    AVLTree<double> A;
    int n;
    double input;
    string cmd;
    cin>>n;
    for(int i=0 ; i<n ; i++){
        cin>>cmd;
        cin>>input;
        if(cmd=="add")
            A.add(input);
        else if(cmd=="remove")
            A.remove(input);
        else if(cmd=="find")
            A.find(input);
    }
    return 0;
}