import socket
import struct

host = "112.137.129.129"
port = 27001

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((host, port))

def to_endian(number):
    return number.to_bytes(4, 'little')

def string_to_endian(string):
    return bytes(string, 'utf-8')

MSV = '21020765'

PKT_HELLO =  to_endian(0) + to_endian(len(MSV)) + string_to_endian(MSV)

try:
    client.send(PKT_HELLO)
    while True:
        type = int.from_bytes(struct.unpack('<i', client.recv(4)))
        if type == 1:
            struct.unpack('<i', client.recv(4))
            data = struct.unpack('<ii', client.recv(8))
            print("type =", type)
            print("data =", data)
            PKT_RESULT = to_endian(2) + to_endian(4) + to_endian(data[0] + data[1])
            client.send(PKT_RESULT)
        elif type == 3:
            print("Error")
            break
        elif type == 4:
            length = int.from_bytes(struct.unpack('<i', client.recv(4)))
            fla = client.recv(length)
            print(fla)
            break
        else:
            break

finally:
    client.close()
