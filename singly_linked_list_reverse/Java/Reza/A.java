

import java.util.Scanner;

class Node{
    int x;
    Node n;  //next
}
class SLList{
    Node h;   //head
    Node t;   //tale
    int n=0;
    SLList(){
        h=new Node();
        t=new Node();
    }
    void addFirst(Node a){
        if(n==0){
            t=a;
            h=a;
            h.n=null;
            t.n=null;
        }
        else{
            a.n=h;
            h=a;
        }
        n++;
    }
    void addLast(Node a){
        if(n==0){
            t=a;
            h=a;
            h.n=null;
            t.n=null;
        }
        else{
            a.n=t.n;
            t.n=a;
            t=a;
        }
        n++;
    }
    void removeLast(){
        if(n==0)
            System.out.println("empty");
        else{
            Node u=h;
            if(n==1){
                h=null;
                t=null;
                h=new Node();
                t=new Node();
                System.out.println(u.x);
            }
            else{               
                while(u.n!=t )
                {
                    u=u.n;
                }
                System.out.println(u.n.x);
                u.n=t.n;
                t=u; 
            }
            n--;
        }
    }
    void reverse(int i,int j){
        if(j>i){
            int c=1;
            Node u=h;
            while(c<i-1){  //i-1 omin onsore
                u=u.n;
                c++;
            }

            Node ip;Node is;Node prev;Node next;
            if(i!=1){
                  ip=u;  //i-1 omin
                  is=u.n;  //i omin
                  prev=u.n;
                  u=u.n.n;
            }
            else{ 
                ip=null;
                is=u;
                prev=u;
                u=u.n;
            }      
            c=i+1;
            while(c<j+1){
                next=u.n;
                u.n=prev;
                prev=u;
                u=next;
                c++;
            }
            if(i==1)
                h=prev;
            else
                ip.n=prev;
            if(j==n){
                t=is;
                t.n=null;
            }
            is.n=u;
        }
    }
    void print(){
        System.out.println("print");
        Node u=h;
        while(u!=t.n)
        {
            System.out.println(u.x);
            u=u.n;
        }
    }
}
public class A {
    
    public static void main(String args[]){
        Scanner var=new Scanner(System.in);
        int n=var.nextInt();
        Node e=new Node();
        SLList a=new SLList();
        for(int i=1;i<=n;i++)
        {
            String s=var.next();
            if (s.compareTo("addFirst")==0){
                e.x=var.nextInt();
                a.addFirst(e);
            }
            else if (s.compareTo("addLast")==0){
                e.x=var.nextInt();
                a.addLast(e);
            }
            else if (s.compareTo("removeLast")==0){
                a.removeLast();
            }
            else if (s.compareTo("reverse")==0){
                int k=var.nextInt();
                a.reverse(k,var.nextInt());
            }
            e=null;
            e=new Node();
        }
        //a.print();
    }
}



