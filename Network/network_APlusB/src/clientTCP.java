import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public class clientTCP {
    public static void main(String[] argv) throws IOException {
        Socket socket = new Socket("112.137.129.129", 27001);
        DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
        DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
        pktHello(dataOutputStream);

        try {
            while (true) {
                int type = byteToInt(dataInputStream.readNBytes(4));
                // read type 

                if (type == 1) // PKT_CALC
                {
                    byteToInt(dataInputStream.readNBytes(4));
                    // read length

                    int a = byteToInt(dataInputStream.readNBytes(4));
                    System.out.println(a);
                    int b = byteToInt(dataInputStream.readNBytes(4));
                    System.out.println(b);

                    byte[] types = intToLittleEndian(2); // PKT_RESULT
                    byte[] lens = intToLittleEndian(4);
                    byte[] data = intToLittleEndian(a + b);

                    byte[] pktResult = concatArray(types, lens, data);
                    dataOutputStream.write(pktResult);
                } else if (type == 3) { // PKT_BYE
                    System.out.println("error");
                    break;
                } else if (type == 4) { // PKT_FLAG
                    int len = byteToInt(dataInputStream.readNBytes(4));
                    System.out.println(new String(dataInputStream.readNBytes(len)));
                    break;
                }
            }
        } finally {
            dataOutputStream.close();
            dataInputStream.close();
            socket.close();
        }
    }

    public static void pktHello(OutputStream outputStream) throws IOException {
        int data = "21020098".getBytes().length;
        byte[] type = intToLittleEndian(0);
        byte[] len = intToLittleEndian(data);

        byte[] pktHello = concatArray(type, len, "21020098".getBytes());
        outputStream.write(pktHello);
    }

    public static byte[] intToLittleEndian(int number) {
        ByteBuffer bb = ByteBuffer.allocate(4);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        bb.putInt(number);
        return bb.array();
    }

    public static int byteToInt(byte[] bytes) {
        return ByteBuffer.allocate(4).wrap(bytes).order(ByteOrder.LITTLE_ENDIAN).getInt();
    }

    public static byte[] concatArray(byte[] bytes1, byte[] bytes2, byte[] bytes3) {
        byte[] result = new byte[bytes1.length + bytes2.length + bytes3.length];
        System.arraycopy(bytes1, 0, result, 0, bytes1.length);
        System.arraycopy(bytes2, 0, result, bytes1.length, bytes2.length);
        System.arraycopy(bytes3, 0, result, bytes1.length + bytes2.length, bytes3.length);
        return result;
    }
}