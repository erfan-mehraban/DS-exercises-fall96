
import java.util.Scanner;
class Element{
    int i;
    int j;
    int p;
}
class Stack{
    Element[] a;
    int n=0;
    Stack(){
        a=new Element[10];
    }
    void push(Element b)
    {
        if(n==a.length)
            resize();
        a[n]=b;
        n++;
    }
    Element pop()
    {
        if(3*n<a.length)
            resize();
        if(n!=0){            
            n--;
            return a[n];
        }
        else return null;
    }
    void resize(){
        Element[] b=new Element[2*n];
        for(int i=0;i<n;i++)
            b[i]=a[i];
        a=b;
        b=null;
    }
}

public class A {
    static char [][]a;
    static int n;static int m;
    public static Element next(Element e){
        Element g=new Element();
        int i=e.i; int j=e.j;
        if(i-1>=0 && j-1>=0 && a[i-1][j-1]=='0' && b[i-1][j-1]=='0')
        {
            g.i=i-1; g.j=j-1;
            return g;
        }
        if(i-1>=0 && j>=0 && a[i-1][j]=='0' && b[i-1][j]=='0')
        {
            g.i=i-1; g.j=j;
            return g;
        }
        if(i-1>=0 && j+1<=m-1 && a[i-1][j+1]=='0' && b[i-1][j+1]=='0')
        {
            g.i=i-1; g.j=j+1;
            return g;
        }
        
        if(i>=0 && j-1>=0 && a[i][j-1]=='0' && b[i][j-1]=='0')
        {
            g.i=i; g.j=j-1;
            return g;
        }
        if(i>=0 && j+1<=m-1 && a[i][j+1]=='0' && b[i][j+1]=='0')
        {
            g.i=i; g.j=j+1;
            return g;
        }
        
        if(i+1<=n-1 && j-1>=0 && a[i+1][j-1]=='0' && b[i+1][j-1]=='0')
        {
            g.i=i+1; g.j=j-1;
            return g;
        }
        if(i+1<=n-1 && j>=0 && a[i+1][j]=='0' && b[i+1][j]=='0')
        {
            g.i=i+1; g.j=j;
            return g;
        }
        if(i+1<=n-1 && j+1<=m-1 && a[i+1][j+1]=='0' && b[i+1][j+1]=='0')
        {
            g.i=i+1; g.j=j+1;
            return g;
        }
        
        return null;
    }
    public static void main (String []args){       
        
        Element e;
        Element ne;
        Scanner var=new Scanner(System.in);
        n=var.nextInt();
        m=var.nextInt();
        a=new char[n][m];
        Stack d=new Stack();
        for(int i=0;i<n;i++){
            String s=var.next();
            for(int j=0;j<m;j++)
            {
                a[i][j]=s.charAt(j);        
            }
        }
            
        int i=0; int j=0; boolean f=true;
        while(!(i==n-1 && j==m-1)&&(f)){
            e=new Element(); e.i=i; e.j=j;         
            
            ne =new Element(); ne=next(e);
            
            if(ne==null){
                if(i==0 && j==0){
                    f=false;
                    break;
                }
                else{
                    e=d.pop();
                    i=e.i;j=e.j;
                }
            }
            
            else{
                i=ne.i; j=ne.j;
                d.push(e);
            }
        }
        if(f==false)
            System.out.println("That's a dead end!");
        else{
            e=new Element(); e.i=n-1; e.j=m-1;
            d.push(e);
            System.out.println(d.n);
            for(int k=0;k<d.n;k++){
                System.out.println((d.a[k].i+1)+" "+(d.a[k].j+1));
            }
        }
    }
}


