import socket


def udp_broadcast_client(broadcast_port):
    # Create a UDP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Enable broadcasting on the socket
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    try:
        # Bind the socket to a specific port for receiving broadcasts
        client_socket.bind(('0.0.0.0', broadcast_port))
        print(f"Listening for broadcasts on port {broadcast_port}")

        while True:
            # Receive data from any sender
            data, sender_address = client_socket.recvfrom(1024)
            print(f"Received broadcast from {sender_address}: {data.decode('utf-8')}")

    finally:
        # Close the socket when done
        client_socket.close()


# Example usage:
if __name__ == "__main__":

    broadcast_port = 8888
    udp_broadcast_client(broadcast_port)