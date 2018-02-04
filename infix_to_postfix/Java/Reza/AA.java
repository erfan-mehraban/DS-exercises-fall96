
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


public class AA {
    public static void main(String[] args){
        Scanner var=new Scanner(System .in);
        String s=var.next();
        char [] a=s.toCharArray();
        char[] b=new char [s.length()];
        char x='@';
        Stack o=new Stack(2);
        int c=0;
        for(int i=0;i<a.length;i++)
        {
            x='@';
            if(a[i]=='(')
            {
                o.push(a[i]);
            }
            else if(65<=(int)a[i] && (int)a[i]<=90)
            {
                b[c]=a[i];
                c++;
            }
            else if(a[i]==')')
            {
                x=o.pop();
                while(x!='(')
                { 
                    b[c]=x;
                    c++;
                    x=o.pop();
                }
            }
            else if (a[i]=='+'||a[i]=='-')
            {
                    x=o.pop();
                    while(x!='0' && x!='(')
                    {
                        b[c]=x;
                        c++;
                        x=o.pop();
                    }
                    if(x=='(')
                        o.push(x);
                    o.push(a[i]);
            }
            else if (a[i]=='*'||a[i]=='/')
            {
                    x=o.pop();
                        while((x!='0')&&(x!='(')&&(x!='+') && (x!='-'))
                        {
                            b[c]=x;
                            c++;
                            x=o.pop();
                        }
                    if(x=='+' || x=='-' || x=='(')
                        o.push(x);
                    o.push(a[i]);
            }
        }
        x=o.pop();
        while(x!='0')
        {
            b[c]=x;
            c++;
            x=o.pop();
        }
        for(int i=0;i<c;i++)
            System.out.print(b[i]);
        
    }
    
}
