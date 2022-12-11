import java.net.*;
import java.io.*;
import java.util.*;
 
public class tcpserver 
{
    public static Scanner sc = new Scanner(System.in);
    public static void main(String []args)
    {
        try
        {
            int port;
            System.out.println("Enter the Port Number");
            port=sc.nextInt();
            ServerSocket se = new ServerSocket(port);
            System.out.println("Server waiting ... ");
            Socket server = se.accept();
            System.out.println("Connection Established!");
            
            InputStream istream = server.getInputStream();
            BufferedReader f_name = new BufferedReader(new InputStreamReader(istream));
            String fname = f_name.readLine();
            BufferedReader fread = new BufferedReader(new FileReader(fname));
            OutputStream ostream = server.getOutputStream();
            PrintWriter print = new PrintWriter(ostream,true);
            
            while((fname= fread.readLine()) != null)
            {
                print.println(fname);
            }
            
            server.close();
            se.close();
            f_name.close();
            fread.close();
        }
        catch(Exception ex) {}
    }
}
