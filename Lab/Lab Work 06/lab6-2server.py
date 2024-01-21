import socket
import random

def tcp_number_server():
    server_address = ('localhost', 27679)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind(server_address)
        server_socket.listen()

        print(f"TCP Number Server is listening on {server_address}")

        while True:
            connection, client_address = server_socket.accept()
            print(f"Connection from {client_address}")

            try:
                for _ in range(5):  # Sending 5 random numbers
                    random_number = random.randint(1, 100)
                    connection.sendall(str(random_number).encode())
                    data = connection.recv(1024)
                    print(f"Received from {client_address}: {data.decode()}")

            finally:
                connection.close()

if __name__ == "__main__":
    tcp_number_server()
