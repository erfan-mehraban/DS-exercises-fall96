/*import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;
*/
import java.util.*;
class Node {
    Node p;
    Node r;
    Node l;
    Node m;
    float x;
    float y;
    Node (float x , float y){
        this.x=x;
        this.y=y;
    }
    Node(Node n){
        this.x=n.x;
        this.y=n.y;
    }
    Node(){
        
    }
}

public class A {
    
    static List<Node> a;     //sorted list by x
    static Node r;   //root
    static List<Node> c;     //find answer
    public static Node makeXTree(){

        List<Node> b=new ArrayList<Node>();
        
        for(int i=0;i<a.size()-1;i=i+2){
            Node x1=new Node((Node)a.get(i));
            Node x2=new Node((Node)a.get(i+1));  
            Node x=new Node(x1);
            x.l=x1;
            x.r=x2;
            x1.p=x;
            x2.p=x;
            b.add(x);
            x.m=makeYTree(i,i+1);
        }
        if(a.size()%2!=0)
            b.add((Node)a.get(a.size()-1));
        
        int c=4;
        while(b.size()!=1){
            int n=b.size();
            for(int i=0;i<n-1;i=i+2){  
                Node x1=b.get(0);
                Node x2=b.get(1);
                Node x=x1;
                if(x2.l==null && x2.r==null)
                    x2=new Node(b.get(1)); 
                while(x.r!=null)
                    x=x.r;
                x=new Node(x);
                x.l=x1;
                x.r=x2;
                x1.p=x;
                x2.p=x;
                b.remove(0);
                b.remove(0);
                b.add(x);
                x.m=makeYTree(c*(i/2),c*(i/2)+c-1);
            }
            if(n%2!=0){
                b.add(b.get(0));
                b.remove(0);
            }
            c*=2;
        }
        return b.get(0);
        
}
    
    public static Node makeYTree(int a1 , int a2){

        List<Node> b=new ArrayList<Node>();
        if (a2>=a.size())
            a2=a.size()-1;
        
        for(int i=a1;i<=a2;i++){
           b.add(a.get(i));
        }  
        Collections.sort(b,new Comparator<Node>(){      //koochik be bozorg
            //@Override
            public int compare(Node n1,Node n2){
                return n1.y<n2.y ? 1 : (n1.y>n2.y) ? -1 : 0;
            }
        });
        
        int n=b.size();
        for(int i=0;i<n-1;i=i+2){           
            Node x1=new Node(b.get(0));
            Node x2=new Node(b.get(1));  
            Node x=new Node(x1);
            x.l=x1;
            x.r=x2;
            x1.p=x;
            x2.p=x;
            b.remove(0);
            b.remove(0);
            b.add(x);
        }
        if(n%2!=0){
                b.add(b.get(0));
                b.remove(0);
        }

        while(b.size()!=1){
            n=b.size();
            for(int i=0;i<n-1;i=i+2){  
                Node x1=b.get(0);
                Node x2=b.get(1);
                Node x=x1;
                if(x2.l==null && x2.r==null)
                    x2=new Node(b.get(1)); 
                while(x.r!=null)
                    x=x.r;
                x=new Node(x);
                x.l=x1;
                x.r=x2;
                x1.p=x;
                x2.p=x;
                b.remove(0);
                b.remove(0);
                b.add(x);
            }

            if(n%2!=0){
                b.add(b.get(0));
                b.remove(0);
            }
        }
        return b.get(0);
        
}
    public static void find(float x1,float y1,float x2,float y2){
        Node u1=r; 
        Node u2;
        while(true && u1.r!=null){
            if(x1<=u1.x && u1.x<=x2)
                break;
            if(x1>u1.x)
                u1=u1.r;
            else if(x2<u1.x)
                u1=u1.l;
        }
        u2=u1;   int f=0;             //split node       u1 for finding x1     u2 for finding x2
        if(u1.r!=null){
                u1=u1.l;
                u2=u2.r;
                f=1;
        }
        while(u1.r!=null){           //age barg nabashe hatman 2 ta bache dare
            if(x1<=u1.x){
                if(u1.r.r!=null)
                    findy(u1.r.m,y1,y2);
                else {
                    if(u1.r.y<=y2 && y1<=u1.r.y)
                         c.add(u1.r);
                }
                if(x1==u1.x)                  
                    break;
                u1=u1.l;
            }
            else
                u1=u1.r;
        }
        if(u1.y<=y2 && y1<=u1.y &&u1.x<=x2 && x1<=u1.x)
            c.add(u1);
        
        while(u2.l!=null){           //age barg nabashe hatman 2 ta bache dare
            if(x2>=u2.x){
                if(u2.l.l!=null)
                    findy(u2.l.m,y1,y2);
                else {
                    if(u2.l.y<=y2 && y1<=u2.l.y)
                         c.add(u2.l);
                }
                /*if(x2==u2.x)                  
                    break;*/
                u2=u2.r;
            }
            else
                u2=u2.l;
        }
        if(u2.y<=y2 && y1<=u2.y &&u2.x<=x2 && x1<=u2.x && f==1)
            c.add(u2);
       
    }
    public static void findy(Node u1,float y1,float y2){
        Node u2;
        while(true && u1.r!=null){
            if(y1<=u1.y && u1.y<=y2)
                break;
            if(y1>u1.y)
                u1=u1.l;
            else if(y2<u1.y)
                u1=u1.r;
        }

        u2=u1;   int f=0;             //split node       u1 for finding y1     u2 for finding y2
        if(u1.r!=null){
                u1=u1.r;
                u2=u2.l;
                f=1;
        }
        
        while(u1.l!=null){           //age barg nabashe hatman 2 ta bache dare
            if(y1<=u1.y){
                if(u1.l.l!=null){
                    Node t=u1.l;
                    Node s=t;
                    while(t.l!=null)
                        t=t.l;
                    while(s.r!=null)
                        s=s.r;
                    for(int i=0;i<a.size();i++)
                    {
                        if(a.get(i).y==s.y){
                            while(s.y!=t.y){
                                i++;
                                c.add(s);
                                s=a.get(i);
                            }
                            c.add(t);
                            break;
                        }
                                
                    }
                }
                    
                else {
                    if(u1.l.y<=y2 && y1<=u1.l.y)
                         c.add(u1.l);
                }
                if(y1==u1.y){                 
                    break;
                }
                u1=u1.r;
            }
            else
                u1=u1.l;
        }
        if(u1.y<=y2 && y1<=u1.y)
            c.add(u1);
        
        
        while(u2.r!=null){           //age barg nabashe hatman 2 ta bache dare
            if(y2>=u2.y){
                if(u2.r.r!=null){
                    Node t=u2.r;
                    Node s=t;
                    while(t.l!=null)
                        t=t.l;
                    while(s.r!=null)
                        s=s.r;
                    for(int i=0;i<a.size();i++)
                    {
                        if(a.get(i).y==s.y){
                            while(s.y!=t.y){
                                i++;
                                c.add(s);
                                s=a.get(i);
                            }
                            c.add(t);
                            break;
                        }
                                
                    }
                }
                    
                else {
                    if(u2.r.y<=y2 && y1<=u2.r.y)
                         c.add(u2.r);
                }
                if(y2==u2.y){                 
                    break;
                }
                u2=u2.l;
            }
            else
                u2=u2.r;
        }
        if(u2.y<=y2 && y1<=u2.y && f==1)
            c.add(u2);
               
    }
    
    public static void printx(Node u){
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
       printx(u.l);
       printx(u.r);
    }
    public static void printy(Node u){
       if (u == null) {
           //System.out.println(".");
           return;
       }
       if(u.p!=null){
           if(u.p.r==u)
                System.out.println("           "+u.p.y+"        "+"*"+u.y);
           else
                System.out.println("*"+u.y+"        "+u.p.y+"        ");
       }
       else  System.out.println("           *"+u.y);
       printy(u.l);
       printy(u.r);
    }
    public static void main(String[] args){
        List<Float> a1=new ArrayList<Float>();
        List<Float> a2=new ArrayList<Float>();        
        a=new ArrayList<Node>();
        c=new ArrayList<Node>();
        Scanner var=new Scanner(System.in);
        
        int n1=var.nextInt();
        for(int i=1;i<=n1;i++){
           a1.add(var.nextFloat());
        }
        for(int i=1;i<=n1;i++){
           a2.add(var.nextFloat());
        }
        for(int i=0;i<n1;i++){
           a.add(new Node(a1.get(i),a2.get(i)));
        }  
        a1=null;a2=null;
        Collections.sort(a,new Comparator<Node>(){      //koochik be bozorg
           // @Override
            public int compare(Node n1,Node n2){
                return n1.x>n2.x ? 1 : (n1.x<n2.x) ? -1 : 0;
            }
        });
        
        /*Node g=new Node(57,6);
        Node f=new Node(4,5);
        g.p=f;
        a.add(g);
        a.add(f);
        System.out.println(a.get(1).x);
        Node m=a.get(1);
        a.remove(1);
        
        System.out.println(a.get(1).x);*/
        r=makeXTree();
        /*printx(r);
        /*System.out.println(""+"*****************");
        printy(r.m);
        /*for(Node i:a)
            System.out.println(i.x+"    "+i.y);*/
        
        int n2=var.nextInt();
        for(int i=1;i<=n2;i++){
            find(var.nextFloat(),var.nextFloat(),var.nextFloat(),var.nextFloat());
            if(c.size()==0)
                System.out.println("None");
            Collections.sort(c,new Comparator<Node>(){      //koochik be bozorg
          //  @Override
            public int compare(Node n1,Node n2){
                return n1.y>n2.y ? 1 : (n1.y<n2.y) ? -1 : 0;
            }
        });
            for(int j=0;j<c.size();j++){
                //System.out.println("size"+c.size());
                float h=c.get(j).x;
                if (h%1!=0)
                    System.out.print(h);
                else
                    System.out.print((int)h);
                if(j==c.size()-1)
                    System.out.println("");
                else
                    System.out.print(" ");
            }
            for(int j=0;j<c.size();j++){
                float h=c.get(j).y;
                if (h%1!=0)
                    System.out.print(h);
                else
                    System.out.print((int)h);
                if(j==c.size()-1)
                    System.out.println("");
                else
                    System.out.print(" ");
            }
            c=null;
            c=new ArrayList<Node>();
        }
    }
}
