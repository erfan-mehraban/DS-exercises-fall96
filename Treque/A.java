

package r;

import java.util.Scanner;


public class A {
        public static void balance(Queue q1,Queue q2){
            int n1=q1.n; int n2=q2.n;
            int c= q1.n+q2.n;
                if(n1>c/2)
                    while(n1>c/2){
                         int x=q1.removeLast();
                         q2.addFirst(x);
                         n1=q1.n;
                    }
                else
                    while(n1<c/2){
                        int x=q2.removeFirst();
                        q1.addLast(x);
                        n1=q1.n;
                    }
        }
        public static void main(String[] args) {
            Scanner scan = new Scanner(System.in);
            Queue q1=new Queue(6);
            Queue q2=new Queue(6);
            Queue removeList=new Queue(6);
            while(scan.hasNextInt()){
                q1.addLast(scan.nextInt());
            } 
            balance(q1,q2);
            
            
            
            while (scan.hasNext()){
                String s1=scan.next();
                if(s1.equals("add"))
                {
                    String s2=scan.next();
                    if(s2.equals("h"))
                    {
                         int x=scan.nextInt();
                         q1.addFirst(x);
                         balance(q1,q2);
                    }
                    if(s2.equals("m"))
                    {
                         int x=scan.nextInt();
                         q1.addLast(x);
                         balance(q1,q2);
                    }
                    if(s2.equals("t"))
                    {
                         int x=scan.nextInt();
                         q2.addLast(x);
                         balance(q1,q2);
                    }
                }
                else if(s1.equals("remove"))
                {
                    String s2=scan.next();
                    if(s2.equals("h"))
                    {
                         removeList.addLast(q1.removeFirst());
                         balance(q1,q2);
                    }
                    if(s2.equals("m"))
                    {
                        if((q1.n+q2.n)%2==0)
                            removeList.addLast(q1.removeLast());
                        else
                            removeList.addLast(q2.removeFirst());
                         balance(q1,q2);
                    }
                    if(s2.equals("t"))
                    {
                         removeList.addLast(q2.removeLast());
                         balance(q1,q2);
                    }
                }
                else if(s1.equals("end"))
                {
                    break;
                }
            }

            for(int i=removeList.j;i<=removeList.j+removeList.n-1;i++)
                System.out.println(removeList.a[i]);
        }
        
}
