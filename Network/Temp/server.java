package Network.Temp;

import java.net.ServerSocket;
import java.net.Socket;

public class server {
  public static void main(String[] args) {
    ServerSocket socket;
    Socket clientSocket = null;
    try {
      socket = new ServerSocket(5000);
      clientSocket = socket.accept();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
  
}
