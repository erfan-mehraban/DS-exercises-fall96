
import static java.lang.Double.compare;
import java.util.Scanner;

class Node{
    Node p;   Node l;   Node r;
    int h=0;
    double x;
    Node(double v){
        x=v;
    }
}
class Avl{
    Node r=null;      //root
    int n=0;

public int h(Node u){
    if(u==null)
        return -1;
    return u.h;
}
public int max(int a, int b){
    if(a>=b)
        return a;
    else
        return b;
}
public int bf(Node u){
    if(u==null)
        return 0;
    return h(u.r)-h(u.l);
}

public void rr(Node y){                //right rotate
    Node x=y.l;
    if(y.p!=null){
        if(y.p.r==y)
            y.p.r=x;
        else
            y.p.l=x;
    }
    else{
        r=x;
    }
    x.p=y.p;
    y.p=x;
    if(x.r!=null)
        x.r.p=y;
    y.l=x.r;
    x.r=y;
    y.h=1+max(h(y.l),h(y.r));
    x.h=1+max(h(x.l),h(x.r));
}
public void lr(Node y){              //left rotate
    Node x=y.r;
    if(y.p!=null){
        if(y.p.r==y)
            y.p.r=x;
        else
            y.p.l=x;
    }
    else{
        r=x;
    }
    x.p=y.p;
    y.p=x;
    if(x.l!=null)
        x.l.p=y;
    y.r=x.l;
    x.l=y;
    y.h=1+max(h(y.l),h(y.r));
    x.h=1+max(h(x.l),h(x.r));
}

public void balance(Node z,Node y,Node x){
    if(z.l==y && y.l==x){
        rr(z);
    }
    else if(z.l==y && y.r==x){
        lr(y);
        rr(z);
    }
    else if(z.r==y && y.r==x){
        lr(z);
    }
    else if(z.r==y && y.l==x){
        rr(y);
        lr(z);
    }
}
Node find(double v) {
    Node w = r, z = null;
    while (w != null) {
        int comp = compare(v, w.x);
        if (comp < 0) {
            z=w;
            w = w.l;
        } else if (comp > 0) {
            w = w.r;
        } else {
            return w;
        }
    }
    if(z!=null)
        return z;
    else
    {
        return null;
    }
}

public boolean add(double v){
        Node u=r;
        Node p=null;
        if(r==null){
            r=new Node(v);
            System.out.println("added");
            n++;
        }
        else{
            while(u!=null){
                if(v<u.x){
                    p=u;
                    u=u.l;
                }
                else if(v>u.x){
                    p=u;
                    u=u.r;
                }
                else{
                    System.out.println("already in there");
                    return false;
                }
            }
            u=new Node(v);
            if(v<p.x)
                p.l=u;
            else
                p.r=u;
            u.p=p;
            
            System.out.println("added");
            n++;
            
            Node x=null;
            while(p!=null){
                p.h=1+max(h(p.l),h(p.r));
                if(1<bf(p) || bf(p)<-1 ){
                    System.out.println("balancing"+" "+p.x);
                    balance(p,u,x);
                }
                x=u;
                u=p;    
                p=p.p;
            }
        }  
        
        return true;
}
    
void splice(Node u) {
    Node s, p;
    if (u.l != null) {
        s = u.l;
    }
    else {
        s = u.r;
    }
    
    if (u == r) {
        r = s;
        p = null;
    } 
    else {
        p = u.p;
        if (p.l == u) {
            p.l = s;    
        } 
        else {
            p.r = s;
        }
    }
    if (s != null) {
        s.p = p;
    }
    u=null;
}
    
void remove(double v) {
    Node u=find(v);
    Node p=null;
    if(u!=null && u.x==v){
        if (u.l == null || u.r == null) {
            p=u.p;
            splice(u);
        } else {
            Node w = u.l;
            while (w.r != null)
                w = w.r;
            u.x = w.x;
            p=w.p;
            splice(w);
        }
        System.out.println("removed");
        n--;
        if(n==0)
            r=null;
        else{
            Node x=null;
            Node y=null;
            while(p!=null){
                p.h=1+max(h(p.l),h(p.r));
                if(1<bf(p) || bf(p)<-1 ){
                    System.out.println("balancing"+" "+p.x);
                    if(h(p.l)>h(p.r))
                        y=p.l;
                    else
                        y=p.r;
                    if(h(y.l)>h(y.r))
                        x=y.l;
                    else
                        x=y.r;
                    balance(p,y,x);
                    } 
                    p=p.p;
            }
        }
    }
    else System.out.println("does not exist");
}
    
    public void print(Node u){
       if (u == null) {
           //System.out.println(".");
           return;
       }
       if(u.p!=null){
           if(u.p.r==u)
                System.out.println("           "+u.p.x+"        "+"*"+u.x);
           else
                System.out.println("*"+u.x+"        "+u.p.x+"        ");
       }
       else  System.out.println("           *"+u.x);
       print(u.l);
       print(u.r);
    }
   
}
public class  A{
    public static void main (String [] args){
        Scanner var=new Scanner(System.in);
        Avl a=new Avl();
        int n=var.nextInt();
        for(int i=1;i<=n;i++)
        {
            String s=var.next();
            if(s.equals("add")){
                a.add(var.nextDouble());                  
            }
            else if(s.equals("find")){
                Node p=a.find(var.nextDouble());
                if(p!=null)
                    System.out.println(p.x);
                else
                    System.out.println("not found");
            }
            else if(s.equals("remove")){
                a.remove(var.nextDouble());                  
            }
        }
        /*a.print(a.r);
        System.out.println(a.r.x);*/
    }
}
