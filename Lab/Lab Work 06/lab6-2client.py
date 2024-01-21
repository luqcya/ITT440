import socket

def tcp_number_client():
    server_address = ('localhost', 27679)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect(server_address)

        for _ in range(5):  # Receiving 5 random numbers
            data = client_socket.recv(1024)
            print(f"Received from server: {data.decode()}")
            client_socket.sendall("Received".encode())

if __name__ == "__main__":
    tcp_number_client()
