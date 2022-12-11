import java.util.*;

public class leakybucket 
{
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the number of time intervals = ");
		int n = sc.nextInt();
		int t[] = new int[n];
		
		System.out.println("Enter the time intervals = ");
		for(int i=0;i<n;i++)
			t[i]=sc.nextInt();
		
		System.out.println("Enter i and l = ");
		int i=sc.nextInt();
		int l=sc.nextInt();
		
		int lct = t[0];
		int x=0,y=0;
		for(int j=0;j<n;j++)
		{
			y = x-(t[j]-lct);
			if(y>l)
			{
				System.out.println("Non-conforming packet "+t[j]);
			}
			else
				x=y+i;
			lct=t[j];
			System.out.println("Conforming packet "+t[j]);
		}
	}
}
