import java.io.*;
import java.net.*;
import java.util.*;
 
public class tcpclient
{
    public static Scanner sc = new Scanner(System.in);
    public static void main(String []args)
    {
        try
        {
            String ip;
            int port;
            System.out.println("Enter the Ip and Port Number = ");
            ip = sc.next();
            sc.nextLine();
            port=sc.nextInt();
            Socket client = new Socket(ip,port);
            BufferedReader k = new BufferedReader(new InputStreamReader(System.in));
            
            System.out.println("Enter File Name = ");
            String filename = k.readLine();
            OutputStream ostream = client.getOutputStream();
            PrintWriter print = new PrintWriter(ostream,true);
            print.println(filename);
            
            InputStream istream = client.getInputStream();
            BufferedReader fread = new BufferedReader(new InputStreamReader(istream));
            while((filename = fread.readLine()) != null)
            {
                System.out.println(filename);
            }
            
            k.close();
            client.close();
            fread.close();
        }
        catch(Exception ex) {}
    }
}
