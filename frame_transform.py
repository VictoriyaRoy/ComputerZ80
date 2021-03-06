import socket
import sys
import serial

def sock_create(interface, sock=None):
    sock = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
    sock.bind((interface, 0))
    return sock

if __name__ == "__main__":
    print(sys.version)
    ser = serial.Serial("/dev/ttyUSB1", 9600)
    sock = sock_create("lo", 0xEEFA)
    i = 0
    while True:
        i += 1
        pack = ser.read(98)
        print(f"processed packet number {i}\n")
        res = sock.send(pack)

#packet: (98 bytes)
#     packet = bytes([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
# 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x45, 0x00, 
# 0x00, 0x54, 0xe5, 0xe6, 0x40, 0x00, 0x40, 0x01, 
# 0x56, 0xc0, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, 
# 0x00, 0x01, 0x08, 0x00, 0x4f, 0x99, 0x83, 0x46, 
# 0x00, 0x00, 0xa3, 0x66, 0xe1, 0x61, 0x00, 0x00, 
# 0x00, 0x00, 0x1f, 0xc6, 0x03, 0x00, 0x00, 0x00, 
# 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
# 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 
# 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 
# 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 
# 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 
# 0x26, 0x27])
