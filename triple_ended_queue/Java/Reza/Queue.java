
package r;

import static java.lang.Integer.max;
import java.util.NoSuchElementException;


public class Queue {
    int [] a;
    int j=0;
    int n=0;
    public Queue(int x){
        a=new int[x];
    }
    public void addFirst(int x){
        if (n + 1 > a.length) resize();
        a[((j-1)+a.length) % a.length] = x;
        j=((j-1)+a.length)%a.length;
        n++;
    }
    public void addLast(int x){
        if (n + 1 > a.length) resize();
        a[(j+n) % a.length] = x;
        n++;
    }
    public int removeFirst(){
        if (n == 0) throw new NoSuchElementException();
        int x = a[j];
        j = (j + 1) % a.length;
        n--;
        if (a.length >= 3*n) resize();
        return x;
    }
    public int removeLast(){
        if (n == 0) throw new NoSuchElementException();
        int x = a[(j+n-1)%a.length];
        n--;
        if (a.length >= 3*n) resize();
        return x;
    }
    public void resize(){
        int[] b = new int [max(1,n*2)];
        for (int k = 0; k < n; k++)
        b[k] = a[(j+k) % a.length];
        a = b;
        j = 0;
    }
    public void print(){
        if(j+n-1>=a.length){
            for(int i=j;i<a.length;i++)
                    System.out.println(a[i]);
                for(int i=0;i<=(j+n-1)%a.length;i++)
                    System.out.println(a[i]);
        }
        else
            for(int i=j;i<=j+n-1;i++)
                System.out.println(a[i]);
    }
}
