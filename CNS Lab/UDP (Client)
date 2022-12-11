import java.net.*;

public class udpclient 
{
	public static void main(String[] args)
	{
		try
		{
			DatagramSocket client = new DatagramSocket();
			int serverSocket = 1537;
			
			InetAddress host = InetAddress.getByName("127.0.0.1");
			String message = "Text Message";
			byte[] sendMessage = message.getBytes();
			
			DatagramPacket request = new DatagramPacket(sendMessage, sendMessage.length, host, serverSocket);
			client.send(request);
			byte[] buffer = new byte[1000];
			DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
			client.receive(reply);
			System.out.println("Client received: "+new String(reply.getData()));
			client.close();
		}
		catch(Exception ex) {}
	}
}
