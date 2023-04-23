package Network.Temp;

import java.net.Socket;

public class client {
  public static void main(String[] args) {
    Socket socket;
    try {
      socket = new Socket("localhost", 5000);
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
