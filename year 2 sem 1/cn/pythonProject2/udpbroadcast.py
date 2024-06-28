import socket
import struct


def udp_broadcast(message, port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    try:
        packed_data = struct.pack('!I', message)
        client_socket.sendto(packed_data, ('<broadcast>', port))
    finally:
        client_socket.close()

if __name__ == "__main__":
    message = 42
    port = 8888
    udp_broadcast(message, port)