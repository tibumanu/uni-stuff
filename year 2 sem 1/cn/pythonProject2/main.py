import socket
import struct
import sys
import time

import select

# print(sys.argv)
# port = 8888
# IP_address = "192.168.1.23"
#
# client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#
# client_socket.connect((IP_address, port))
# huh = input()
# print(huh)
#
# master = [socket.socket(), client_socket]
#
# while True:
#     read_fds = master
#
#     ready_to_read, _, _ = select.select(read_fds, [], [])
#     if socket.socket() in ready_to_read:
#         data = "sugema"
#         client_socket.send(bytes(data, "ascii"))
#         print("sent data brah")
#         if data == "QUIT":
#             client_socket.close()
#             break
#
#     elif client_socket in ready_to_read:
#         data = client_socket.recv(1024).decode("ascii")
#         print(data)


port = 8888
IP_address = "172.30.112.97"
master = []
hello_message = "Hellooooo, welcome to the concurrent server."


def sendToAll(message, ignore_list):
    for fd in master:
        if fd not in ignore_list:
            fd.send(bytes(message, "ascii"))


def getIpAddress(socket_descriptor):
    peer = socket_descriptor.getpeername()
    return peer


def udp_broadcast(message, port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    try:
        packed_data = struct.pack('!I', message)
        client_socket.sendto(packed_data, ('<broadcast>', port))
    finally:
        client_socket.close()

def udp_broadcast_server(broadcast_port):
    # Create a UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Enable broadcasting on the socket
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    print(f"Broadcasting on port {broadcast_port}")

    while True:
        # Send a broadcast message
        message = "Hello, wwwww!"
        packed_data = struct.pack('!I', len(message)) + message.encode("utf-8")
        server_socket.sendto(packed_data, ('<broadcast>', broadcast_port))

        # Sleep for a short duration before broadcasting again
        time.sleep(2)


if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    master.append(server_socket)

    server_socket.bind((IP_address, port))

    server_socket.listen(10)

    while True:
        ready_to_read, _, _ = select.select(master, [], [], 1)

        for fd in ready_to_read:
            if fd == server_socket:
                client_socket, address = server_socket.accept()
                master.append(client_socket)
                client_socket.send(bytes(hello_message, "ascii"))
            else:
                received_message = fd.recv(1024).decode("ascii")
                if received_message == "QUIT":
                    master.remove(fd)
                    fd.close()
                else:
                    print("got this: ", received_message)
                    message = str(getIpAddress(fd)[0]) + "," + str(getIpAddress(fd)[1]) + " : " + received_message
                    sendToAll(message, [server_socket])
                    message = "Hello, wwwww!"
                    #packed_data = struct.pack('!I', len(message)) + message.encode("utf-8")
                    #server_socket.sendto(packed_data, ('<broadcast>', 8888))


