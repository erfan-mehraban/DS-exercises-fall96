
import static java.lang.Integer.max;
import java.util.NoSuchElementException;
import java.util.Random;
import java.util.Scanner;
class Element{
    String k;
    double v;
}

 class BDeque {
    Element [] a;
    int b=50;
    int j=0;
    int n=0;
    int location;
    
    
    public BDeque(){
        a=new Element[b+1];
    }
    
    int findIndex(String s,int m1,int m2){ //m2 tedad aazaye arraye ast
        if (m2==1){
            if(s.compareTo(a[m1].k)==0)
            {
                //System.out.println("are1");
                location=m1;
                return -1;
            }
            else if(s.compareTo(a[m1].k)>0)
            {
                //System.out.println("are2");
                return (m1+1)%a.length;
            }
            else {
                //System.out.println("are3");
                return m1;
            }
        }
        if(m2==0){
            //System.out.println("are4");
            return m1;
        }
        if(s.compareTo(a[(m1+m2/2-1)%a.length].k)<0)
            return findIndex(s,m1,m2/2);
        else if(s.compareTo(a[(m1+m2/2-1)%a.length].k)>0)
            return findIndex(s,(m1+m2/2)%a.length,m2-m2/2);
        else
            {
                //System.out.println("are5");
                location=(m1+m2/2-1)%a.length;
                return -1;
            }
   
    }
    
    void find(String s)
    {
         int i=findIndex(s,j,n);
         if(i==-1){
             SESSet.p[SESSet.k]=Double.toString(a[location].v);
             SESSet.k++;
         }
         else if(i==(j+n)%a.length){
             SESSet.p[SESSet.k]="not found";
             SESSet.k++;
         }
         else {
             SESSet.p[SESSet.k]=Double.toString(a[i].v);
             SESSet.k++;
         }
    }
    
    void add(Element x) {      
        int i=findIndex(x.k,j,n);
        if(i==-1 && SESSet.flag==0){
            SESSet.p[SESSet.k]="already in there";
            SESSet.k++;
        }
        else{
            if(j<=i)
                i=i-j;
            else
                i=a.length-j+i;
            if (i < n/2) { // shift a[0],..,a[i-1] left one position
                j = ((j-1)+a.length)% a.length;
                for (int k = 0; k <= i-1; k++)
                    a[(j+k)%a.length] = a[(j+k+1)%a.length];
            } 
            else { // shift a[i],..,a[n-1] right one position
                for (int k = n; k > i; k--)
                    a[(j+k)%a.length] = a[(j+k-1)%a.length];
            }
            a[(j+i)%a.length] = x;
            n++;
            if(SESSet.flag==0){
                SESSet.p[SESSet.k]="added";
                SESSet.k++;
            }
        }
    }
    
    Element remove(String s) {
        int i=findIndex(s,j,n);
        if((i!=-1||n==0)&&(SESSet.flag==0)){
            SESSet.p[SESSet.k]="does not exist";
            SESSet.k++;
            return null;
        }
        else{
            i=location;
            if(j<=i)
                i=i-j;
            else
                i=a.length-j+i;
            Element x = a[(j+i)%a.length];
            
            if (i < n/2) { // shift a[0],..,[i-1] right one position
                for (int k = i; k > 0; k--)
                    a[(j+k)%a.length] = a[(j+k-1)%a.length];
                j = (j + 1) % a.length;
            } else { // shift a[i+1],..,a[n-1] left one position
                for (int k = i; k < n-1; k++)
                     a[(j+k)%a.length] = a[(j+k+1)%a.length];
            }
            n--;
            if(SESSet.flag==0){
                SESSet.p[SESSet.k]="removed";
                SESSet.k++;
            }
            return x;
        }
    }
    
    public void print(){
        System.out.println(j);
        if(j+n-1>=a.length){
            for(int i=j;i<a.length;i++)
                    System.out.println(a[i].k);
                for(int i=0;i<=(j+n-1)%a.length;i++)
                    System.out.println(a[i].k);
        }
        else
            for(int i=j;i<=j+n-1;i++)
                System.out.println(a[i].k);
    }
 }

class Node {
    BDeque d;
    Node[] next;
    Node prev;
    Node(int h) {
        d = new BDeque();
        next = new Node[h+1];
    }
    Node(Node x)
    {
        
    }
    int height() {
        return next.length - 1;
    }
}

class SESSet{
    static Node sentinel=new Node(15);
    static String [] p;  static int k=0;  static int flag=0; 
    SESSet(){
       sentinel.d=null; 
    }
    
    int pickHeight() {
        Random rand=new Random();
        int z = rand.nextInt();
        int k = 0;
        int m = 1;
        while ((z & m) != 0) {
        k++;
        m <<= 1;
        }
        return k;
    }
    
    Node findPredNode(String s) {
        Node u = sentinel;
        int r = sentinel.height();
        while (r >= 0) { 
            //System.out.println("r"+r);
            while(u.next[r] != null && u.next[r].d.n==0)
               u=u.next[r];
            while (u.next[r] != null && u.next[r].d.a[(u.next[r].d.j+u.next[r].d.n-1)%u.next[r].d.a.length].k.compareTo(s) < 0)
                u = u.next[r]; 
            r--;
        }
        return u;
    }
    
    void find(String s) {
        Node u = findPredNode(s);
        if (u.next[0]==null){
            p[k]="not found";
            k++;
        }
        else
            u.next[0].d.find(s);
    }
    
    boolean add(Element e) {
        Node u = sentinel;
        int r =sentinel.height() ;
        Node[] stack=new Node[16]; //r+1
        
        while (r >= 0) {
            while (u.next[r] != null && u.next[r].d.a[(u.next[r].d.j+u.next[r].d.n-1)%u.next[r].d.a.length].k.compareTo(e.k)< 0)
                u = u.next[r];     
            stack[r--] = u; // going down, store u
        }
    
        if(u.next[0] != null && u.next[0].d.findIndex(e.k, u.next[0].d.j, u.next[0].d.n)==-1){
            p[k]="already in there";
            k++;
            return false;
        }
        
        Node g=u;
        int c=0;
        while(g.next[0]!=null && g.next[0].d.n==g.next[0].d.b+1 && c<u.next[0].d.b){ //b ta ro dide dar b omin block hast
            g=g.next[0];
            c++;
        }
        
        if(c>0 && c<u.next[0].d.b)
        {   
            if (g.next[0]==null)
            {
                Node u2 = sentinel;
                int r2 =sentinel.height() ;
                Node w2= new Node(pickHeight()); 
                while (r2 >= 0) {
                    while (u2.next[r2] != null )
                        u2 = u2.next[r2];
                    if(r2<=w2.height())
                        u2.next[r2]=w2;
                    r2--;
                }
                w2.prev=u2; 
            }
            flag=1;
            while(g!=u)
            {
                
                g.next[0].d.add(g.d.remove(g.d.a[(g.d.j+g.d.n-1)%g.d.a.length].k));
                g=g.prev;
            }   
            flag=0;
        }
        else if(u.next[0]!= null && c==u.next[0].d.b)        //spread
        {
            Node u3 = sentinel;
            int r3 =sentinel.height() ;
            Node w3= new Node(pickHeight()); 
            while (r3 >= 0) {
                while(u3.next[r3] != null && u3.next[r3].d.n==0)
               u3=u3.next[r3];
                while (u3.next[r3] != null && u3!=g)
                    u3 = u3.next[r3];
                if(r3<=w3.height()){
                    w3.next[r3]=u3.next[r3];
                    u3.next[r3]=w3;
                }
                r3--;
            }
            w3.prev=u3;
            flag=1;
            while(g!=u)
            {
                while(g.next[0].d.n<g.next[0].d.b){
                    g.next[0].d.add(g.d.remove(g.d.a[(g.d.j+g.d.n-1)%g.d.a.length].k));
                }
                g=g.prev;
            }
            flag=0;
        }

        
        if(u.next[0]==null && ( u==sentinel || u.d.n>=u.d.b+1) )  // akharin blocke  
        {
            Node w = new Node(pickHeight());
            int h=sentinel.height();
            while (h < w.height())
                stack[++h] = sentinel;           // height increased
            //System.out.println("w length"+w.next.length);
            for (int i = 0; i < w.next.length; i++) {
                //System.out.println("i"+i);
                w.next[i] = stack[i].next[i];
                stack[i].next[i] = w;
            }
            w.prev=u;
        }
        else if(u.next[0]==null && u.d.n<u.d.b+1){
            u.d.add(e);
            return true;
        }
        
        u.next[0].d.add(e);
        return true; 
    }
    
    boolean remove(String s) {
        Node u = sentinel;
        int r = sentinel.height();
        while (r >= 0) {
            while (u.next[r] != null && u.next[r].d.a[(u.next[r].d.j+u.next[r].d.n-1)%u.next[r].d.a.length].k.compareTo(s)< 0)
                u = u.next[r];
            r--;
        }       
        if (u.next[0]==null){
            p[k]="does not exist";
            k++;
            return false;
        } 
        
        Node g=u;
        int c=0;
        while(g.next[0]!=null && g.next[0].d.n==g.next[0].d.b-1 && c<u.next[0].d.b){ //b ta ro dide dar b omin block hast
            g=g.next[0];
            c++;
        }
        if(c>0 && c<u.next[0].d.b)
        {   
            flag=1;
            if (g.next[0]==null)
                g=g.prev;
            while(g!=u)
            {
                g.d.add(g.next[0].d.remove(g.next[0].d.a[g.next[0].d.j].k));
                g=g.prev;
            }              
            flag=0;
        }
        else if(u.next[0]!= null && c==u.next[0].d.b)      //gather
        {
 
            flag=1;
            Node x=u.next[0];
            while(x!=g)
            {
                while(x.d.n<u.next[0].d.b){
                    x.d.add(x.next[0].d.remove(x.next[0].d.a[x.next[0].d.j].k));
                }
                x=x.next[0];
            }
            flag=0;
            Node u4=sentinel;
            int r4=sentinel.height();
            int h=g.height();
            while (r4 >= 0) {
                while(u4.next[r4] != null && u4.next[r4]!=g)
                    u4=u4.next[r4];
                if(r4<=h){
                    u4.next[r4]=g.next[r4];
                }
                r4--;
            }
            g=null;
        }

        u.next[0].d.remove(s);
        return true;
    }
    
    public static void print(){
        for(int i=0;i<SESSet.p.length;i++)
            System.out.println(SESSet.p[i]);
    }
}
public class A {
    public static void main (String [] args){
        SESSet a=new SESSet();
        Scanner var=new Scanner(System.in);
        int c=var.nextInt();
        SESSet.p=new String[c];
        Element e=new Element();
       /* e.k="salam";
        e.v=1.0;
        
       /* f=d;
        f.next[0]=g;
        if(d.next[0]==g)
            System.out.println("yes");
       // f=f.next[0];
        
        /*d.next[3]=f;
        f.d.add(e);
        System.out.println(d.next[2].d.a[0].k);*/
       
        for(int i=1;i<=c;i++){
            String s=var.next();
            if(s.equals("add"))
            {
                e.k=var.next();
                e.v=var.nextDouble();
                a.add(e);
                e=new Element();
            }
            else if(s.equals("find"))
            {
                a.find(var.next());   
            }
            else if(s.equals("remove"))
            {
                a.remove(var.next());
            }
        }
        SESSet.print();
        /*SESSet.sentinel.next[0].d.print();
        SESSet.sentinel.next[0].next[0].d.print();
        SESSet.sentinel.next[0].next[0].next[0].d.print();
        SESSet.sentinel.next[0].next[0].next[0].next[0].d.print();*/
    }
}


