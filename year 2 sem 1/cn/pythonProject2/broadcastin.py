import socket
import struct
import time


def udp_broadcast_server(message, broadcast_port):
    # Create a UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Enable broadcasting on the socket
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    try:
        while True:
            # Broadcast the message to the network on the specified port
            x = 67
            server_socket.sendto(struct.pack('!I', x), ('<broadcast>', broadcast_port))
            print(f"Broadcasted message: {message}")

            time.sleep(1)  # Adjust the sleep time as needed

    finally:
        # Close the socket when done
        server_socket.close()


def udp_send_int(sock, x, dest_addr):
    print("Sending {0}".format(x))
    sock.sendto(struct.pack("!i", x), dest_addr)


# Example usage:
if __name__ == "__main__":
    broadcast_message = "hiii im broadcastin rn!"
    broadcast_port = 8888

    udp_broadcast_server(broadcast_message, broadcast_port)
