
import java.util.Scanner;

class Stack{
	char[] a;
	int n;

	public void resize() {
		char[] b = new char[Math.max(n*2,1)];
		for (int i = 0; i < n; i++) {
			b[i] = a[i];
		}
		a = b;
                b=null;
	}
        
	public Stack(int x) {
                a=new char[x];
		n = 0;
	}
	
	
	public void push(char x) {
		if (n + 1 > a.length) resize();
		a[n] = x;
		n++;
	}
	
	public char pop() {
                if(n>=1)
                {
                    char x = a[n-1];
                    n--;
                    if (a.length >= 3*n) resize();
                    return x;
                }
                return '0';
	}
	
	public void clear() {
		n = 0;
		resize();
	}
}
class Stacki{
	int[] a;
	int n;

	public void resize() {
		int[] b = new int[Math.max(n*2,1)];
		for (int i = 0; i < n; i++) {
			b[i] = a[i];
		}
		a = b;
                b=null;
	}
        
	public Stacki(int x) {
                a=new int[x];
		n = 0;
	}
	
	
	public void push(String x) {
		if (n + 1 > a.length) resize();
                int b=0;
                int c=1;
                if(x.charAt(0)!='-'){
                    for(int i=x.length()-1;i>=0;i--)
                    {
                        b+=c*((int)(x.charAt(i))-48);
                        c*=10;
                    }
                }
                else{
                    for(int i=x.length()-1;i>=1;i--)
                    {
                        b+=c*((int)(x.charAt(i))-48);
                        c*=10;
                    }
                    b=-b;
                }
		a[n] = b;
		n++;
	}
        public void pushi(int x) {
		if (n + 1 > a.length) resize();
		a[n] = x;
		n++;
	}
	
	public int pop() {
                if(n>=1)
                {
                    int x = a[n-1];
                    n--;
                    if (a.length >= 3*n) resize();
                    return x;
                }
                return 0;
	}
	
	public void clear() {
		n = 0;
		resize();
	}
}


public class A {
    public static boolean isNumber(String s){
        if(s.equals("+")||s.equals("-")||s.equals("/")||s.equals("*")||s.equals("^")||s.equals("(")||s.equals(")"))
            return false;
        return true;
    }
    public static void main(String[] args){
        Scanner var=new Scanner(System .in);
        String s=var.nextLine();
        String[] p=s.split(" ");
        s=null;
        String[] d=new String [p.length*4];
        int n=0;
        for(int i=0;i<p.length;i++){
            int f=0;int g=0;
            for(int j=0 ;j<p[i].length();j++){
                f=0;
                if(p[i].charAt(j)=='('){
                    d[n]=""+'(';
                    n++;
                    f=1; g=1;
                }
                else if(p[i].charAt(j)==')'){
                    d[n]=""+')';
                    n++;
                    f=1; g=1;
                }
                else if(f==0){
                    int k=j;
                    while(k<p[i].length()-1 && p[i].charAt(k)!='(' && p[i].charAt(k)!=')'  )
                        k++;
                    if(k==p[i].length()-1 && p[i].charAt(k)!='(' && p[i].charAt(k)!=')')
                    {
                        d[n]=p[i].substring(j);
                        n++;
                        j=k;
                    }
                    else{
                        d[n]=p[i].substring(j,k);
                        n++;
                        j=k-1;
                    }
                    
                }
            }
            
        }
        p=null;
        String[] a=new String[n];
        for(int i=0;i<n;i++)
            a[i]=d[i];
        d=null;

        String[] b=new String [a.length];
   
        char x='@';
        Stack o=new Stack(10);
        int c=0;
        boolean f;
        
        for(int i=0;i<a.length;i++)
        {
            f=false;
            x='@';
            if(a[i].equals("("))
            {
                o.push('(');
            }
            
            else if(a[i].equals(")"))
            {
                x=o.pop();
                while(x!='(')
                { 
                    b[c]=""+x;
                    c++;
                    x=o.pop();
                }
                if(i+1<a.length && (isNumber(a[i+1])||a[i+1].equals("(")))
                {
                    
                    f=true;
                }

            }
            else if(isNumber(a[i]))
            {
                b[c]=a[i];
                c++;
                if(i+1<a.length && a[i+1].equals("("))
                    f=true;
            }
            else if (a[i].equals("+"))
            {
                    x=o.pop();
                    while(x!='0' && x!='(')
                    {
                        b[c]=""+x;
                        c++;
                        x=o.pop();
                    }
                    if(x=='(')
                        o.push(x);
                    o.push('+');
            }
            else if (a[i].equals("-"))
            {
                    x=o.pop();
                    while(x!='0' && x!='(' && x!='+')
                    {
                        b[c]=""+x;
                        c++;
                        x=o.pop();
                    }
                    if( x=='(' || x=='+')
                        o.push(x);
                    o.push('-');
            }
            else if (a[i].equals("/"))
            {
                    x=o.pop();
                    while(x!='0' && x!='(' && x!='+' && x!='-' && x!='*')
                    {
                        b[c]=""+x;
                        c++;
                        x=o.pop();
                    }
                    if(x=='(' || x=='+' || x=='-' || x=='*')
                        o.push(x);
                    o.push('/');
            }
            else if (a[i].equals("^"))
            {
                    x=o.pop();
                    while(x!='0' && x!='(' && x!='+' && x!='-' && x!='*' && x!='/')
                    {
                        b[c]=""+x;
                        c++;
                        x=o.pop();
                    }
                    if(x=='(' || x=='+' || x=='-' || x=='*' || x=='/')
                        o.push(x);
                    o.push('^');
            }
            if (a[i].equals("*")||f==true)
            {
                    x=o.pop();
                        while((x!='0')&&(x!='(')&&(x!='+') && (x!='-'))
                        {
                            b[c]=""+x;
                            c++;
                            x=o.pop();
                        }
                    if(x=='(' || x=='+' || x=='-')
                        o.push(x);
                    
                    o.push('*');
            }
        }
        x=o.pop();
        while(x!='0')
        {
            b[c]=""+x;
            c++;
            x=o.pop();
        }
       /*for(int i=0;i<c;i++)
            System.out.print(b[i]);*/
        
        Stacki g=new Stacki(10);
        for(int i=0;i<c;i++)
        {
            if(isNumber(b[i])){
                g.push(b[i]);
            }
            else{
                if(b[i].equals("+"))
                {
                    int op2=g.pop();
                    int op1=g.pop();
                    int r=op1+op2;
                    g.pushi(r);
                }
                else if(b[i].equals("-"))
                {
                    int op2=g.pop();
                    int op1=g.pop();
                    int r=op1-op2;
                    g.pushi(r);
                }
                else if(b[i].equals("*"))
                {
                    int op2=g.pop();
                    int op1=g.pop();
                    int r=op1*op2;
                    g.pushi(r);
                }
                else if(b[i].equals("/"))
                {
                    int op2=g.pop();
                    int op1=g.pop();
                    int r=op1/op2;
                    g.pushi(r);
                }
                else if(b[i].equals("^"))
                {
                    int op2=g.pop();
                    int op1=g.pop();
                    int r=1;
                    for(int j=1;j<=op2;j++)
                        r*=op1;
                    g.pushi(r);
                }
            }
        }
        System.out.println(g.pop());
    }
    
}

